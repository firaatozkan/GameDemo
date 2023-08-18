#pragma once

struct SDL_Rect;
struct SDL_Renderer;
struct SDL_Texture;

class Animation
{
public:
    Animation(SDL_Renderer& rendererRef,
              const char* filePath,
              size_t maxNumOfFrames);
    ~Animation();
    void renderAt(int x, int y, bool isFlipped);
    void nextFrame();
    bool isFinished() const;
    void resetFrame();
    
private:
    SDL_Renderer& m_rendererRef;
    SDL_Texture* m_texture {nullptr};
    std::vector<SDL_Rect> m_frameVector;
    size_t m_frameIndex {0};
    size_t m_maxNumOfFrames;
};