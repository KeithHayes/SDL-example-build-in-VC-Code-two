#include "picrender.h"

PicRender::PicRender() {
	mWindow = NULL;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	mWindow = SDL_CreateWindow("SDL Debug C++", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	IMG_Init(IMG_INIT_PNG || IMG_INIT_JPG);
	mRenderer = NULL;
	mTexture = NULL;
}
PicRender::~PicRender() {
	SDL_DestroyTexture( mTexture );
    mTexture = NULL;
    SDL_DestroyRenderer( mRenderer );
	mRenderer = NULL;
    SDL_DestroyWindow( mWindow );
	mWindow = NULL;
    IMG_Quit();
	SDL_Quit();
}
void PicRender::loadpic() {
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xD7, 0x00, 0xFF);
	std::string path = "data/forest1920.jpeg";
	mTexture = IMG_LoadTexture(mRenderer, path.c_str());
	SDL_Rect texture_rect;
	texture_rect.x = 0;   // the x coordinate
	texture_rect.y = 0;   // the y coordinate
	texture_rect.w = 640; // the width of the texture
	texture_rect.h = 480; // the height of the texture
	SDL_RenderCopy( mRenderer, mTexture, NULL, &texture_rect );
	SDL_RenderPresent(mRenderer);
}
void PicRender::events() {
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
						break;
						case SDLK_DOWN:
						break;
						case SDLK_LEFT:
						break;
						case SDLK_RIGHT:
						break;
						case SDLK_HOME:
						break;
						case SDLK_PAGEUP:
						break;
						case SDLK_PAGEDOWN:
						break;
						case SDLK_END:
						break;
						default:
						break;
					}
					break;
				case SDL_KEYUP:
				break;
			}
		}
	}
	SDL_RenderClear(mRenderer);
	SDL_RenderPresent(mRenderer);
}
