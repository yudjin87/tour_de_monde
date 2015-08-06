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

#include "GeodatabaseComponent.h"
#include "GDBScriptExtension.h"
#include "ShapeFileWorkspaceFactory.h"

#include <carousel/componentsystem/ComponentDefinition.h>
#include <carousel/componentsystem/ComponentExport.h>
#include <carousel/utils/IServiceLocator.h>

static const QByteArray productName("Geodatabase");

GeodatabaseComponent::GeodatabaseComponent()
    : BaseComponent("org.carousel.demos.Geodatabase")
{
    IScriptExtension *scriptExtension = new GDBScriptExtension(this);
    registerExtension<IScriptExtension>(scriptExtension);

    addParent("org.carousel.JsScripting", 1, 0);
    addParent("org.carousel.demos.Geometry", 1, 0);
    setShortName("Geodatabase");
    setProductName(productName);
    setProvider("Carousel");
    setVersion(1, 0);
}

GeodatabaseComponent::~GeodatabaseComponent()
{
}

void GeodatabaseComponent::onShutdown(IServiceLocator *serviceLocator)
{
    IShapeFileWorkspaceFactory* factory = serviceLocator->locate<IShapeFileWorkspaceFactory>();
    delete factory;
}

bool GeodatabaseComponent::onStartup(IServiceLocator *serviceLocator)
{
    IShapeFileWorkspaceFactory* factory = new ShapeFileWorkspaceFactory();
    serviceLocator->registerInstance<IShapeFileWorkspaceFactory>(factory);
    return true;
}

EXPORT_COMPONENT(GeodatabaseComponent)

