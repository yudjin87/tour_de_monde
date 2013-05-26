/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2013 Carousel team
 * Authors:
 *   Eugene Chuguy <eugene.chuguy@gmail.com>
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

#include "Map.h"
#include "AbstractLayer.h"

#include <display/IDisplay.h>

//------------------------------------------------------------------------------
Map::Map()
    : QObject()
    , m_display(nullptr)
{
}

//------------------------------------------------------------------------------
Map::~Map()
{
    foreach(AbstractLayer *layer, m_layers)
        delete layer;

    m_layers.clear();

}

//------------------------------------------------------------------------------
void Map::addLayer(AbstractLayer *layer)
{
    m_layers.push_back(layer);
    emit layerAdded(layer);
    //mp_layer->draw(mp_scene);

    m_display->setExtent(layer->extent());
}

//------------------------------------------------------------------------------
QList<AbstractLayer *> Map::layers() const
{
    return m_layers;
}

//------------------------------------------------------------------------------
void Map::refresh()
{
    foreach(AbstractLayer *layer, m_layers)
        layer->draw(m_display);
}

//------------------------------------------------------------------------------
void Map::setDisplay(IDisplay *display)
{
    m_display = display;

    connect(m_display, SIGNAL(changed()), SLOT(refresh()));
}

//------------------------------------------------------------------------------
