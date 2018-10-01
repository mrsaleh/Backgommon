#pragma once

#include <SDL.h>
#include <map>
#include <string>
#include <vector>
#include "Sprite.h"
#include "MouseInputListener.h"

class CEngine
{
private:
	SDL_Event event;
	SDL_Window * window;
	SDL_Renderer * renderer;
	std::map<std::string, SDL_Texture *> textures;
	Uint64 lastFrameTime;
	std::vector<CMouseInputListener *> mouseInputListeners;
	float deltaTime;	
public:
	CEngine();
	bool DoEvents();
	void Render();
	float GetDeltaTime();
	void Clear();
	void LoadTextureFromPng(std::string assetName);
	void RegisterMouseInputListener(CMouseInputListener * mouseInputListener);
	void Draw(CSprite * sprite);
	~CEngine();
};

