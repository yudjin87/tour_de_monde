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

#include "CartoUIInteractiveExtension.h"
#include "LayerTreeModel.h"
#include "LayerTreeView.h"
#include "AddShapeOperation.h"

#include <carto/ITourDuMondeDocument.h>
#include <carto/ITourDuMondeDocumentController.h>

#include <components/interactivity/ICatalogs.h>
#include <components/interactivity/IDockWidgetCatalog.h>
#include <components/interactivity/IMenuCatalog.h>
#include <components/interactivity/IOperationCatalog.h>
#include <components/interactivity/IToolBarCatalog.h>
#include <components/interactivity/ToggleActionWrapper.h>
#include <carousel/utils/IServiceLocator.h>

#include <QtWidgets/QDockWidget>
#include <QtWidgets/QMenu>
#include <QtWidgets/QListView>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QToolBar>

CartoUIInteractiveExtension::CartoUIInteractiveExtension(QObject *parent)
    : QObject(parent)
    , m_layersTree(nullptr)
    , m_serviceLocator(nullptr)
{
}

void CartoUIInteractiveExtension::configureGui(ICatalogs &inCatalogs, IServiceLocator *serviceLocator)
{
    m_serviceLocator = serviceLocator;

    ITourDuMondeDocumentController* docController = serviceLocator->locate<ITourDuMondeDocumentController>();
    connect(docController, &ITourDuMondeDocumentController::activeDocumentChanged, this, &CartoUIInteractiveExtension::onActiveDocumentChanged);
    ITourDuMondeDocument *doc = docController->document();

    IMenuCatalog &menuCatalog = inCatalogs.menuCatalog();
    IDockWidgetCatalog &catalog = inCatalogs.dockWidgetCatalog();
    m_layersTree = new LayerTreeView(menuCatalog);
    m_layersTree->setLayerTreeModel(new LayerTreeModel(doc->map(), serviceLocator));

    QDockWidget *layersDock = catalog.addDockWidget(m_layersTree, "Layers tree");

    Operation *toogleTree = new ToggleActionWrapper(layersDock->toggleViewAction(), QIcon(":/cartoUI/images/layerTree.png"));
    inCatalogs.operationCatalog().add(toogleTree);

    QMenu *viewMenu = inCatalogs.menuCatalog().addMenu("View");
    viewMenu->addAction(toogleTree);

    //
    IOperationCatalog &operationCatalog = inCatalogs.operationCatalog();
    Operation *addShape = operationCatalog.add(new AddShapeOperation());

    IToolBarCatalog &toolbarCatalog = inCatalogs.toolBarCatalog();
    QToolBar *toolBar = toolbarCatalog.add("Shapes");
    toolBar->addAction(addShape);

    QMenu *toolMenu = menuCatalog.addMenu("Tools");
    toolMenu->addAction(addShape);
}

void CartoUIInteractiveExtension::onActiveDocumentChanged(ITourDuMondeDocument *document)
{
    m_layersTree->setLayerTreeModel(new LayerTreeModel(document->map(), m_serviceLocator));
}

