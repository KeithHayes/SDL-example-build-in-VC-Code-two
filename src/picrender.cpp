#include "picrender.h"

PicRender::PicRender() {
	mWindow = NULL;
	mRenderer = NULL;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	mWindow = SDL_CreateWindow("SDL Debug C++", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
	IMG_Init(IMG_INIT_PNG || IMG_INIT_JPG);
		mOutlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
	mTexture = NULL;
}
PicRender::~PicRender() {
	SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    SDL_DestroyRenderer(mRenderer);
	mRenderer = NULL;
    SDL_DestroyWindow(mWindow);
	mWindow = NULL;
    IMG_Quit();
	SDL_Quit();
}
void PicRender::loadpic() {
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xD7, 0x00, 0xFF);
	std::string path = "data/forest1920.jpeg";
	mTexture = IMG_LoadTexture(mRenderer, path.c_str());
	SDL_Rect texture_rect;
	texture_rect.x = 0;   // the x coordinate
	texture_rect.y = 0;   // the y coordinate
	texture_rect.w = 640; // the width of the texture
	texture_rect.h = 480; // the height of the texture
	SDL_RenderCopy(mRenderer, mTexture, NULL, &texture_rect);
}
void PicRender::redpatch() {
	SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0x00, 0x00, 0xFF);		
	SDL_RenderFillRect(mRenderer, &fillRect);
}
void PicRender::greenoutline() {
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0xFF, 0x00, 0xFF);		
	SDL_RenderDrawRect(mRenderer, &mOutlineRect);
}
void PicRender::blueline() {
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0xFF, 0xFF);		
	SDL_RenderDrawLine(mRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
}
void PicRender::yellowdot() {
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0x00, 0xFF);
	for(int i = 0; i < SCREEN_HEIGHT; i += 4 )
	{
		SDL_RenderDrawPoint(mRenderer, SCREEN_WIDTH / 2, i);
	}
}
void PicRender::clear() {
	SDL_SetRenderDrawColor( mRenderer, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderClear(mRenderer);
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
							redpatch();
						break;
						case SDLK_DOWN:
							greenoutline();
						break;
						case SDLK_LEFT:
							blueline();
						break;
						case SDLK_RIGHT:
							yellowdot();
						break;
						case SDLK_HOME:
							clear();
						break;
						case SDLK_PAGEUP:
						break;
						case SDLK_PAGEDOWN:
						break;
						case SDLK_END:
							loadpic();
						break;
						default:
						break;
					}
					break;
				case SDL_KEYUP:
				break;
			}
		}
		SDL_RenderPresent(mRenderer);
	}
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xD7, 0x00, 0xFF);
	SDL_RenderClear(mRenderer);
	SDL_RenderPresent(mRenderer);
}
