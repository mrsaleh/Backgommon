#include "Engine.h"
#include <iostream>
#include <SDL_image.h>

CEngine::CEngine()
{	
	deltaTime = 0;
	lastFrameTime = 0;
	window = nullptr;
	renderer = nullptr;
	memset(& event,0,sizeof(SDL_Event));

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0) {
		std::cout << "SDL_Image init Error: " << SDL_GetError() << std::endl;
		return;
	}
	window = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	if (!window)
	{
		std::cout << "Could not create window :" << SDL_GetError() << std::endl;
		return;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		std::cout << "Could not create renderer:" << SDL_GetError() << std::endl;
		return;
	}

	this->lastFrameTime = SDL_GetPerformanceCounter();
	this->deltaTime = 0;
}

void CEngine::LoadTextureFromPng(std::string assetName) {
	std::string filename = assetName + ".png";
	SDL_Surface * surface = IMG_Load(filename.c_str());
	if (!surface) {
		std::cout << "Could not load >>" << filename << ":" << SDL_GetError() << std::endl;
		return;
	}
	SDL_Texture * texture = SDL_CreateTextureFromSurface(this->renderer, surface);
	if (!texture) {
		std::cout << "Could not create texture out of " << filename << ":" << SDL_GetError() << std::endl;
		return;
	}

	SDL_FreeSurface(surface);
	this->textures[assetName] = texture;
}

void CEngine::RegisterMouseInputListener(CMouseInputListener * mouseInputListener) {
	this->mouseInputListeners.push_back(mouseInputListener);
}


bool CEngine::DoEvents() {
	Uint64 currentFrameTime = SDL_GetPerformanceCounter();
	this->deltaTime = (currentFrameTime - lastFrameTime) / (float)SDL_GetPerformanceFrequency();
	lastFrameTime = currentFrameTime;

	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_MOUSEBUTTONDOWN && event.button.state == SDL_PRESSED) {
			for (auto mouseInputListener : this->mouseInputListeners) {
				mouseInputListener->OnClick(event.button.button, event.button.x, event.button.y);
			}
		}
		if (event.type == SDL_QUIT) {
			return false;
		}
	}

	return true;
}

void CEngine::Clear() {
	SDL_RenderClear(renderer);
}

float CEngine::GetDeltaTime() {
	return this->deltaTime;
}

void CEngine::Draw(CSprite * sprite) {
	SDL_Rect source, dest;
	CTextureRegion & region = sprite->region;
	source.x = region.x;
	source.y = region.y;
	source.w = region.width;
	source.h = region.height;
	dest.x = sprite->x - sprite->pivotX * sprite->width;
	dest.y = sprite->y - sprite->pivotY * sprite->height;
	dest.w = sprite->width;
	dest.h = sprite->height;
	SDL_Point rotationPoint;
	rotationPoint.x = sprite->pivotX*region.width;
	rotationPoint.y = sprite->pivotX*region.height;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (sprite->flipX)
		flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_HORIZONTAL);
	if (sprite->flipY)
		flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_VERTICAL);

	SDL_SetTextureColorMod(this->textures[sprite->assetName], sprite->tintR,sprite->tintG, sprite->tintB);
	SDL_SetTextureAlphaMod(this->textures[sprite->assetName], sprite->alpha);
	SDL_RenderCopyEx(renderer, this->textures[sprite->assetName], &source, &dest, sprite->ratation, &rotationPoint, flip);
}

void CEngine::Render() {
	SDL_RenderPresent(renderer);
}

CEngine::~CEngine()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}
