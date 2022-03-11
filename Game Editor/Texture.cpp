#include "Texture.h"


CTexture::CTexture(SDL_Renderer* passedrenderer)
{
	renderer = passedrenderer;
	texture_id = NULL;
	path = "";
	optimized = NULL;
	loaded = NULL;
	category = NULL;
	currentframe = new SDL_Rect;
	outframe = new SDL_Rect;
	frames = 1;
	animate_delay = 100;
	width = 1;
	height = 1;
	image_width = 0;
	image_height = 0;
	//frame_width is the same as image_width
	frame_width = 0;
	frame_height = 0;
	destroyable = false;
	health = 100;
	shoot_through = false;
	walk_through = false;
	destroyed = false;
	pickup_id = NULL;
	//light; light emission level from 0-100
	light = 0;
	//activation; 0 for non-activatible, 1 for pressure_pad activation, 2 for manual activation
	activation = -1;
	//on_activate; unique block ID to animate when this block is activated 
	on_activate = NULL;
	glow = false;
}

CTexture::~CTexture()
{
	//add destructor here
}

//
//	Fuction: LoadTexture, loads the image into a texture and sets appropriate variables
//	Paremeters: filepath to the image file (BMP for now)
//	block_width: the width of the block in displayable units (litterally blocks) leave NULL for 1 block
//	block_height: the height of the block in displayable units (litterally blocks) leave NULL for 1 block
//	passed_frames: how many frames are contained within the texture file (vertically spanning animation frames)
//	leave NULl for 1 frame
//
bool CTexture::LoadTexture()
{
	loaded = SDL_LoadBMP(path.c_str());
	if (loaded == NULL)
	{
		printf("Unable to load image with id %i and path %s! SDL_image Error: %s\n", texture_id, path.c_str(), SDL_GetError());
		return false;
	}
	else
	{
		//Create texture from surface pixels
		optimized = SDL_CreateTextureFromSurface(renderer, loaded);
		if (optimized == NULL)
		{
			printf("Unable to create texture id %i from %s! SDL Error: %s\n", texture_id, path.c_str(), SDL_GetError());
			return false;
		}
		//Get rid of old loaded surface
		SDL_FreeSurface(loaded);
	}
	printf("Texture %s loaded successfully with id %i\n", path.c_str(), texture_id);
	SDL_QueryTexture(optimized, NULL, NULL, &image_width, &image_height);
	frame_width = image_width;
	frame_height = image_height / frames;
	currentframe->h = frame_height;
	currentframe->w = frame_width;
	currentframe->x = 0;
	currentframe->y = 0;
	outframe->w = BLOCK_SIZE * width;
	outframe->h = BLOCK_SIZE * height;
	return true;
}

bool CTexture::SetPath(std::string passed_path)
{
	path = passed_path;
	return true;
}

bool CTexture::SetWidth(int passed_width)
{
	width = passed_width;
	return true;
}

bool CTexture::SetHeight(int passed_height)
{
	height = passed_height;
	return true;
}

bool CTexture::SetFrames(int passed_frames)
{
	frames = passed_frames;
	return true;
}

bool CTexture::SetID(int passed_id)
{
	texture_id = passed_id;
	return true;
}

std::string CTexture::GetPath()
{
	return path;
}

int CTexture::GetID()
{
	return texture_id;
}

bool CTexture::SetFrame(int frame)
{
	currentframe->x = 0;
	currentframe->y = frame_height * (frame - 1);
	return true;
}

bool CTexture::SetCategory(int passed_category)
{
	category = passed_category;
	return true;
}

bool CTexture::RenderTexture(double x, double y)
{
	outframe->x = x;
	outframe->y = y;
	int success = SDL_RenderCopy(renderer, optimized, currentframe, outframe);
	if (success) {
		return true;
	}
	else {
		return false;
	}
}

int CTexture::GetAnimate_Delay()
{
	return animate_delay;
}

int CTexture::GetHealth()
{
	return health;
}

int CTexture::GetLight()
{
	return light;
}

int CTexture::GetActivation()
{
	return activation;
}

int CTexture::GetPickup_ID()
{
	return pickup_id;
}

int CTexture::GetOn_Activate()
{
	return on_activate;
}

bool CTexture::GetDestroyable()
{
	return destroyable;
}

bool CTexture::GetShoot_Through()
{
	return shoot_through;
}

bool CTexture::GetWalk_Through()
{
	return walk_through;
}

bool CTexture::GetDestroyed()
{
	return destroyed;
}

bool CTexture::GetGlow()
{
	return glow;
}
