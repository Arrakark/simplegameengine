#pragma once

#include "Texture.h"

class CBlock
{
public:
	CBlock();
	CBlock(CTexture * passed_texture);
	~CBlock();
	bool SetTexture(CTexture * passed_texture);
	bool SetX(int passed_x);
	bool SetY(int passed_y);
	bool SetID(int);
	bool SaveBlock(FILE * file);
	bool RenderBlock(int, int);
	CTexture * GetTexture();
	int GetX();
	int GetY();
private:
	int block_id;
	CTexture* texture;
	int x;
	int y;
	//animate_delay; ms between animated frames.
	int animate_delay;
	bool loop;
	bool destroyable;
	int health;
	bool shoot_through;
	bool walk_through;
	bool destroyed;
	int pickup_id;
	int light;
	//activation; 0 for non-activatible, 1 for pressure_pad activation, 2 for manual activation
	int activation;
	//on_activate; unique block ID to animate when this block is activated 
	int on_activate;
	bool glow;
};

