#pragma once

#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include "Texture.h"
#include "Block.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800
#define FRAME_RATE 60
#define CAMERA_SPEED 15

class CEditor
{
public:
	CEditor();
	void GameLoop();
	bool LoadTextures(char file[]);
	bool LoadBlocks(char file[]);
	bool RenderBlocks();
	bool StartSelection(SDL_Event);
	bool ExpandSelection(SDL_Event);
	bool ClearSelection();
	bool RenderSelection();
	bool SaveSelection();
	bool SaveLevel(char file[]);
	bool SetCurrentDrawingTexture(int);
	bool HandleKeyboardInput(SDL_Event);
	std::vector<CTexture*> textures;
	std::vector<CBlock*> blocks;
private:
	bool quit;
	int current_drawing_texture;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_DisplayMode* display;
	SDL_Rect * CameraView;
	SDL_Rect * BlockSelection;
	int swidth;
	int sheight;
	int num_blocks;
	int num_textures;
	int startX;
	int startY;
	int endX;
	int endY;
	int currentBlocKID;
	int cameraX;
	int cameraY;
	SDL_Event e;
	bool buttonDown;
	FILE * texturestream;
	FILE * blockstream;
};

