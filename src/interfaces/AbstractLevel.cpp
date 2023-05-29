#include <queue>
#include <vector>
#include <future>
#include <iterator>
#include <SDL.h>
#include "interfaces/BaseGame.hpp"
#include "interfaces/AbstractLevel.hpp"
#include "interfaces/AbstractObject.hpp"
#include "utils/RenderPool.hpp"

AbstractLevel::AbstractLevel(BaseGame &parentGameRef)
    : mParentGameRef(parentGameRef), mRendererRef(mParentGameRef.GetRenderer())
{
}

AbstractLevel::~AbstractLevel()
{
    for (auto object: mLevelObjects)
        delete object;
}

void AbstractLevel::AddObject(AbstractObject* object)
{
    mLevelObjects.push_back(object);
}

void AbstractLevel::RenderObjects(RenderPool& renderPool)
{
    std::vector<std::promise<void>> promiseVector(mLevelObjects.size());
    std::vector<std::future<void>> futureVector;
    
    for (size_t objectCount = 0; objectCount < mLevelObjects.size(); ++objectCount)
    {
        futureVector.push_back(promiseVector[objectCount].get_future());
        renderPool.EnqueueObject(mLevelObjects[objectCount], std::move(promiseVector[objectCount]));
    }

    for (auto& future : futureVector)
        future.wait();
}