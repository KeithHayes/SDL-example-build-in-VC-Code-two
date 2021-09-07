#ifndef PICRENDER_H
#define PICRENDER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_mixer.h>

#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class PicRender
{
public:
    PicRender();
    ~PicRender();
    void loadpic();
    void redpatch();
    void greenoutline();
    void blueline();
    void yellowdot();
    void clear();
    void events();
 
private:
    SDL_Window* mWindow;
    SDL_Surface* mScreenSurface;
    SDL_Renderer* mRenderer;
    SDL_Texture* mTexture;
    SDL_Rect mOutlineRect;
};

#endif // PICRENDER_H
