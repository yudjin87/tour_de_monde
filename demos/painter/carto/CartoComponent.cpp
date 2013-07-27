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

#include "CartoComponent.h"
#include "PainterDocumentController.h"


#include <display/IDisplay.h>

#include <carousel/componentsystem/ComponentDefinition.h>
#include <carousel/componentsystem/ComponentExport.h>
#include <carousel/utils/IServiceLocator.h>

//---------

#include "AbstractLayer.h"

#include <QtScript/QScriptEngine>

#include <components/jsscripting/IScriptService.h>
#include <components/jsscripting/IScriptConsole.h>

#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValueIterator>

Q_DECLARE_METATYPE(QList<AbstractLayer *>)

int registerScriptMetaTypes(QScriptEngine *engine);

//------------------------------------------------------------------------------
int registerScriptMetaTypes(QScriptEngine *engine)
{
    return qScriptRegisterMetaType<QList<AbstractLayer *>>(engine,
        qScriptValueFromSequence<QList<AbstractLayer *>>,
        qScriptValueToSequence<QList<AbstractLayer *>>);
}

//------------------------------------------------------------------------------
static const QByteArray productName("Carto");

//------------------------------------------------------------------------------
CartoComponent::CartoComponent()
    : BaseComponent("org.carousel.demos.Carto")
{
    addParent("org.carousel.JsScripting", 1, 0);
    addParent("org.carousel.demos.Display", 1, 0);
    addParent("org.carousel.demos.Geodatabase", 1, 0);
    addParent("org.carousel.demos.Geometry", 1, 0);
    setShortName("Carto");
    setProductName(productName);
    setProvider("Carousel");
    setVersion(1, 0);
}

//------------------------------------------------------------------------------
CartoComponent::~CartoComponent()
{
}

//------------------------------------------------------------------------------
void CartoComponent::onShutdown(IServiceLocator *serviceLocator)
{
    IPainterDocumentController *controller = serviceLocator->unregisterInstance<IPainterDocumentController>();
    delete controller;
}

//------------------------------------------------------------------------------
bool CartoComponent::onStartup(IServiceLocator *serviceLocator)
{
    static const int cartoTypeIds = registerScriptMetaTypes(serviceLocator->locate<IScriptService>()
                                                            ->console()->engine());

    IDisplay *display = serviceLocator->locate<IDisplay>();
    IPainterDocumentController *controller = new PainterDocumentController(display);
    serviceLocator->registerInstance<IPainterDocumentController>(controller);

    return true;
}

//------------------------------------------------------------------------------
EXPORT_COMPONENT(CartoComponent)

//------------------------------------------------------------------------------
