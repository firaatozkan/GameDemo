/**
 * @author Firat Ozkan
*/

#pragma once

class AbstractObject;

/**
 * @class RenderPool
 * @brief This class is a thread-pool designed to render game objects concurrently.
 */
class RenderPool
{
    using RenderPair = std::pair<AbstractObject *, std::promise<void>>;
    /**
     * @brief This is Game Object queue that the RenderPool waits on and then renders.
     * Game objects are paired with promises so that you can make sure that the object
     * is rendered.
    */
    std::queue<RenderPair> mQueue;
    mutable std::mutex mMutex;
    std::condition_variable mCondvar;
    std::vector<std::thread> mThreadVec;
    bool mIsRunning{true};
    
    void RenderThreadFunc();

public:
    explicit RenderPool(unsigned int numberOfThreads = std::thread::hardware_concurrency() - 1);
    ~RenderPool();
    void EnqueueObject(AbstractObject* object, std::promise<void>&& objectRenderPromise);
};