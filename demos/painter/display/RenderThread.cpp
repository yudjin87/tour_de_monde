#include <display/RenderThread.h>

#include <carousel/logging/LoggerFacade.h>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("RenderThread");
}

RenderThread::RenderThread(IDisplay& display, DrawingTaskQueue& queue, QObject* parent)
    : QThread(parent)
    , m_display(display)
    , m_queue(queue)
{
    QThread::setObjectName("[Render]"); // Thread name
}

RenderThread::~RenderThread()
{
}

void RenderThread::run()
{
    while (true) {
        Log.d("Waiting for rendering tasks");
        IDrawingTaskPtr task = m_queue.pop();
        Log.d("New task is comming...");

        if (task == nullptr) {
            Log.d("Empty task - exit thread");
            return;
        }

        task->draw(m_display);
    }
}

