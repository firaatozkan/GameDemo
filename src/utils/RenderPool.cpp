#include <mutex>
#include <queue>
#include <vector>
#include <thread>
#include <condition_variable>
#include <future>
#include <SDL.h>
#include "interfaces/AbstractObject.hpp"
#include "utils/RenderPool.hpp"

/**
 * @param numberOfThreads - The number of threads the RenderPool is requested to have.
*/
RenderPool::RenderPool(unsigned int numberOfThreads)
{
    for (unsigned int threadCount = 0; threadCount < numberOfThreads; ++threadCount)
        mThreadVec.emplace_back(&RenderPool::RenderThreadFunc, this);
}

RenderPool::~RenderPool()
{
    mMutex.lock();
    mIsRunning = false;
    mMutex.unlock();

    mCondvar.notify_all();

    for (auto& thread : mThreadVec)
        thread.join();
}

/**
 * @brief This is the function the render threads are running.
 * Rendering threads are spawned upon creation of class and waiting
 * for a RenderPair to be
 * pushed onto the member queue.
*/
void RenderPool::RenderThreadFunc()
{
    RenderPair objectPairToRender;

    while (true)
    {
        {
            std::unique_lock<std::mutex> lock(mMutex);
            while (mQueue.empty() && mIsRunning)
                mCondvar.wait(lock);

            if (!mIsRunning)
                break;

            objectPairToRender = std::move(mQueue.front());
            mQueue.pop();
        }

        objectPairToRender.first->Render();
        objectPairToRender.second.set_value();
    }
}

/**
 * @param object - Object that is requested to be rendered.
 * @param objectRenderPromise - Rvalue of the promise to the object being rendered.
 * @brief This method is the enqueue mechanism of the RenderPool. Via this method,
 * can the RenderPool can render the requested object.
*/
void RenderPool::EnqueueObject(AbstractObject* object, std::promise<void>&& objectRenderPromise)
{
    mMutex.lock();
    mQueue.push(std::make_pair(object, std::move(objectRenderPromise)));
    mMutex.unlock();
    mCondvar.notify_one();
}