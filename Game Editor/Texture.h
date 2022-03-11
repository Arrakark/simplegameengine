#pragma once

#include <iostream>
#include <string>
#include <SDL.h>

//Somehow need to scale these depending on screen
#define BLOCK_SIZE 48

using namespace std;

class CTexture
{
public:
	CTexture(SDL_Renderer*);
	~CTexture();
	bool LoadTexture();
	bool SetPath(std::string);
	bool SetWidth(int);
	bool SetHeight(int);
	bool SetFrames(int);
	bool SetFrame(int);
	bool SetCategory(int);
	bool SetID(int);
	std::string GetPath();
	int GetID();
	bool RenderTexture(double, double);
	int GetAnimate_Delay();
	int GetHealth();
	int GetLight();
	int GetActivation();
	int GetPickup_ID();
	int GetOn_Activate();
	bool GetDestroyable();
	bool GetShoot_Through();
	bool GetWalk_Through();
	bool GetDestroyed();
	bool GetGlow();
private:
	int texture_id;
	std::string path;
	SDL_Texture* optimized;
	SDL_Surface* loaded;
	SDL_Rect* currentframe;
	SDL_Rect* outframe;
	SDL_Renderer* renderer;
	int frames;
	int category;
	//animate_delay; ms between animated frames.
	int animate_delay;
	bool loop;
	int width;
	int height;
	int image_width;
	int image_height;
	//frame_width is the same as image_width
	int frame_width;
	int frame_height;
	bool destroyable;
	bool destroyed;
	int health;
	bool shoot_through;
	bool walk_through;
	int pickup_id;
	//light; light emission level from 0-100
	int light;
	//activation; 0 for non-activatible, 1 for pressure_pad activation, 2 for manual activation
	int activation;
	//on_activate; unique block ID to animate when this block is activated 
	int on_activate;
	bool glow;
};

