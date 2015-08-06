#include "PanTool.h"

#include <carousel/utils/IServiceLocator.h>

#include <display/IDisplay.h>
#include <display/DisplayTransformation.h>
#include <carto/IMap.h>
#include <carto/ITourDeMondeDocument.h>
#include <carto/ITourDeMondeDocumentController.h>

#include <QtGui/QMouseEvent>

PanTool::PanTool()
    : ToolBase("Pan")
    , m_serviceLocator(nullptr)
    , m_tracked(false)
{
    setIcon(QIcon(":/navigation/images/pan.png"));
    setIconVisibleInMenu(true);
}

void PanTool::execute()
{
    ToolBase::execute();
    IDisplay *display = m_serviceLocator->locate<IDisplay>();

    // TODO: move cursors to base class
    display->setCursor(Qt::OpenHandCursor);
}

void PanTool::initialize(IServiceLocator *serviceLocator)
{
    ToolBase::initialize(serviceLocator);
    m_serviceLocator = serviceLocator;
}

bool PanTool::onMouseDown(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return false;

    m_tracked = true;
    IDisplay *display = m_serviceLocator->locate<IDisplay>();
    display->panStart(event->pos());
    display->setCursor(Qt::ClosedHandCursor);

    return true;
}

bool PanTool::onMouseMove(QMouseEvent *event)
{
    ToolBase::onMouseMove(event);
    // TODO: move tracking to base class
    if (!m_tracked)
        return false;

    IDisplay *display = m_serviceLocator->locate<IDisplay>();
    display->panMoveTo(event->pos());

    // let's other objects to continue with this event
    return false;
}

bool PanTool::onMouseUp(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return false;

    m_tracked = false;
    IDisplay *display = m_serviceLocator->locate<IDisplay>();
    display->panStop();
    display->setCursor(Qt::OpenHandCursor);

    ITourDeMondeDocumentController* docController = m_serviceLocator->locate<ITourDeMondeDocumentController>();
    ITourDeMondeDocument *doc = docController->document();
    IMap *map = doc->map();
    map->refresh();

    return true;
}

void PanTool::stopExecuting()
{
    ToolBase::stopExecuting();

    IDisplay *display = m_serviceLocator->locate<IDisplay>();
    display->unsetCursor();
}

