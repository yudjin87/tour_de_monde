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

#include <displayWidgets/DisplayWidgetsComponent.h>

#include <display/IDisplay.h>
#include <display/CoordsTracker.h>

#include <carousel/componentsystem/ComponentDefinition.h>
#include <carousel/componentsystem/ComponentExport.h>
#include <components/interactivity/IInteractionService.h>
#include <components/interactivity/InputDispatcher.h>
#include <carousel/utils/IServiceLocator.h>

#include <QtWidgets/QMainWindow>

static const QByteArray productName("DisplayWidgets");

DisplayWidgetsComponent::DisplayWidgetsComponent(QObject *parent)
    : BaseComponent("org.carousel.demos.DisplayWidgets", parent)
{
    addParent("org.carousel.Interactivity", 1, 0);
    addParent("org.carousel.demos.Geometry", 1, 0);
    addParent("org.carousel.demos.Display", 1, 0);
    setShortName("DisplayWidgets");
    setProductName(productName);
    setProvider("Carousel");
    setVersion(1, 0);
}

DisplayWidgetsComponent::~DisplayWidgetsComponent()
{
}

void DisplayWidgetsComponent::onShutdown(IServiceLocator *serviceLocator)
{
    IInteractionService* interactionService = serviceLocator->locate<IInteractionService>();
    interactionService->setDispatcher(nullptr);
}

bool DisplayWidgetsComponent::onStartup(IServiceLocator *serviceLocator)
{
    QMainWindow *mainWindow = serviceLocator->locate<QMainWindow>();
    IDisplay *display = serviceLocator->locate<IDisplay>();

    IInteractionService* interactionService = serviceLocator->locate<IInteractionService>();
    interactionService->setDispatcher(new InputDispatcher());
    interactionService->dispatcher()->setSender(display->viewport());
    interactionService->dispatcher()->activate();

    CoordsTracker* tracker = new CoordsTracker(display, mainWindow->statusBar(), this);
    Q_UNUSED(tracker)

    return true;
}

EXPORT_COMPONENT(DisplayWidgetsComponent)

