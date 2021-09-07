#include "picwindow.h"

Picwindow::Picwindow() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) { printf("SDL_Error: %s\n", SDL_GetError()); }
	else {
		mWindow = SDL_CreateWindow("SDL Debug C++", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
								   SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (mWindow == NULL) { printf("SDL_Error: %s\n", SDL_GetError()); }
		else {
			int imgFlags = IMG_INIT_PNG;
			if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
                printf( "SDL_image Error: %s\n", IMG_GetError() ); } 
			else {
                mScreenSurface = SDL_GetWindowSurface( mWindow );
            }
		}
	}
}
Picwindow::~Picwindow() {
	SDL_FreeSurface(mKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT]);
	SDL_FreeSurface(mKeyPressSurfaces[KEY_PRESS_SURFACE_UP]);
	SDL_FreeSurface(mKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN]);
	SDL_FreeSurface(mKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT]);
	SDL_FreeSurface(mKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT]);
	SDL_FreeSurface(mLoadedSurface);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}
void Picwindow::loadpics() {
	mKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = this->loadSurface("data/default.png");
	mKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = this->loadSurface("data/up.png");
	mKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = this->loadSurface("data/down.png");
	mKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = this->loadSurface("data/left.png");
	mKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = this->loadSurface("data/right.png");
}
SDL_Surface *Picwindow::loadSurface(std::string path) {
	SDL_Surface* opaqueSurface = IMG_Load(path.c_str());
	mLoadedSurface = SDL_ConvertSurface(opaqueSurface, mScreenSurface->format, 0);
	SDL_FreeSurface(opaqueSurface);
	return mLoadedSurface;
}
void Picwindow::showpic() {
	SDL_BlitSurface(mKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT], NULL, mScreenSurface, NULL);
	SDL_UpdateWindowSurface(mWindow);
}
SDL_Surface* Picwindow::clippic() {
	mLoadedSurface = IMG_Load("data/default.png");
	SDL_Surface* largesurface = IMG_Load("data/forest1280.png");
	SDL_Rect stretchRect;
	stretchRect.x = 320;
	stretchRect.y = 240;
	stretchRect.w = SCREEN_WIDTH;
	stretchRect.h = SCREEN_HEIGHT;
	SDL_BlitScaled(largesurface, &stretchRect, mLoadedSurface, NULL);
	//SDL_BlitScaled( largesurface, NULL, mLoadedSurface, NULL);
	SDL_FreeSurface(largesurface);
	return mLoadedSurface;
}
SDL_Surface* Picwindow::zoompic() {
	mLoadedSurface = IMG_Load("data/default.png");
	SDL_Surface* smallSurface = IMG_Load("data/forest320.png");
	SDL_Surface* systemSurface = SDL_ConvertSurface(smallSurface, mScreenSurface->format, 0);
	SDL_Rect stretchRect;
	stretchRect.x = 0;
	stretchRect.y = 0;
	stretchRect.w = SCREEN_WIDTH;
	stretchRect.h = SCREEN_HEIGHT;
	SDL_BlitScaled(systemSurface, NULL, mLoadedSurface, &stretchRect);
	SDL_FreeSurface(smallSurface);
	SDL_FreeSurface(systemSurface);
	return mLoadedSurface;
}
void Picwindow::textureLoad() {
	//mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
	//mLoadedSurface = IMG_Load("data/forest1920.jpeg");
	//mTexture = SDL_CreateTextureFromSurface(mRenderer, mLoadedSurface);
}

void Picwindow::events() {
	bool quit = false;
	SDL_Event e;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
				case SDL_QUIT:
					quit = true;
				break;
				case SDL_KEYDOWN:
					switch (e.key.keysym.sym) // switch on key press
					{
					case SDLK_UP:
						mCurrentSurface = mKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
					break;
					case SDLK_DOWN:
						mCurrentSurface = mKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
					break;
					case SDLK_LEFT:
						mCurrentSurface = mKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
					break;
					case SDLK_RIGHT:
						mCurrentSurface = mKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
					break;
					case SDLK_HOME:
						mCurrentSurface = mKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
					break;
					case SDLK_PAGEUP:
						mCurrentSurface = zoompic();
					break;
					case SDLK_PAGEDOWN:
						mCurrentSurface = clippic();
					break;
					case SDLK_END:
						textureLoad();
					break;						
					default:
					break;
				}
				break;
				case SDL_KEYUP:
				break;
			}
		}
		SDL_BlitSurface(mCurrentSurface, NULL, mScreenSurface, NULL);
		SDL_UpdateWindowSurface(mWindow);
	}
}