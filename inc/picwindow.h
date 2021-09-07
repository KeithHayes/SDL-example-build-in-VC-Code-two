#ifndef PICWINDOW_H
#define PICWINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_mixer.h>

#include <stdio.h>
#include <string>

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Picwindow
{
public:
    Picwindow();
    ~Picwindow();
    void loadpics();
    void showpic();
    void events();
    SDL_Surface* loadSurface( std::string path);
    SDL_Surface* clippic();
    SDL_Surface* zoompic();
    void stretch();
    void textureLoad();

private:
    SDL_Window* mWindow;
    SDL_Surface* mScreenSurface;
    SDL_Surface* mKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
    SDL_Surface* mCurrentSurface;
    SDL_Surface* mLoadedSurface;
    SDL_Renderer* mRenderer;
    SDL_Texture* mTexture;
};

#endif // PICWINDOW_H
