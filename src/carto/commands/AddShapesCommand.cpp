/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2016 Carousel team
 * Authors:
 *   Yevhen Chuhui (Eugene Chuguy) <yevhen.chuhui@gmail.com>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#include <carto/commands/AddShapesCommand.h>
#include <carto/IMap.h>
#include <carto/layers/FeatureLayer.h>
#include <carto/ITourDuMondeDocument.h>
#include <carto/ITourDuMondeDocumentController.h>

#include <geodatabase/IFeatureWorkspace.h>
#include <geodatabase/IFeatureClass.h>

#include <QtCore/QFileInfo>

AddShapesCommand::AddShapesCommand(IUndoStack *stack, ITourDuMondeDocumentController *docContr, IShapeFileWorkspaceFactory *factory, QObject *parent)
    : BaseUndoableCommand(stack, parent)
    , m_docContr(docContr)
    , m_factory(factory)
    , m_addedLayers()
{
    setText("adding shape layer(s)");
}

AddShapesCommand::~AddShapesCommand()
{
}

void AddShapesCommand::addShapeFiles(const QStringList &files)
{
    m_files = files;
}

void AddShapesCommand::redo()
{
    ITourDuMondeDocument *doc = m_docContr->document();
    IMap* map = doc->map();

    if (m_addedLayers.isEmpty())
    {
        for (QString fileName : m_files)
        {
            QFileInfo shapeFile(fileName);
            const QString &workingDirectory = shapeFile.absolutePath();

            IFeatureWorkspace* workspace = static_cast<IFeatureWorkspace*>(m_factory->openFromFile(workingDirectory));
            IFeatureClass *railwaysClass = workspace->openFeatureClass(shapeFile.completeBaseName());
            FeatureLayer *railwaysLayer = new FeatureLayer();
            railwaysLayer->setFeatureClass(railwaysClass);

            m_addedLayers.push_back(railwaysLayer);
        }
    }

    for (AbstractLayer* layer : m_addedLayers)
    {
        map->addLayer(layer);
    }

    map->refresh();
}

void AddShapesCommand::undo()
{
    ITourDuMondeDocument *doc = m_docContr->document();
    IMap* map = doc->map();
    for (AbstractLayer* layer : m_addedLayers)
    {
        // TODO: memory leak, since AddShapesCommand doesn't take ownership for removed layers. shared_ptr?
        AbstractLayer* theSame = map->takeLayer(layer);
        Q_ASSERT(theSame == layer);
    }

    map->refresh();
}


