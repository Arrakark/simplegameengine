#include "Block.h"



CBlock::CBlock()
{
	texture = NULL;
}

CBlock::CBlock(CTexture * passed_texture)
{
	SetTexture(passed_texture);
}


CBlock::~CBlock()
{
}

bool CBlock::SetX(int passed_x)
{
	x = passed_x;
	return true;
}

bool CBlock::SetY(int passed_y)
{
	y = passed_y;
	return true;
}


bool CBlock::SetTexture(CTexture * passed_texture)
{
	texture = passed_texture;
	if (passed_texture != NULL) {
		animate_delay = texture->GetAnimate_Delay();
		destroyable = texture->GetDestroyable();
		health = texture->GetHealth();
		shoot_through = texture->GetShoot_Through();
		walk_through = texture->GetWalk_Through();
		destroyed = texture->GetDestroyed();
		pickup_id = texture->GetPickup_ID();
		light = texture->GetLight();
		activation = texture->GetActivation();
		on_activate = texture->GetOn_Activate();
		glow = texture->GetGlow();
	}
	return false;
}

bool CBlock::SetID(int passed_id)
{
	block_id = passed_id;
	return true;
}

bool CBlock::SaveBlock(FILE * file)
{
	//save block parameters here
	fprintf_s(file, "id %i\n", block_id);
	fprintf_s(file, "texture %i\n", texture->GetID());
	fprintf_s(file, "x %i\n", x);
	fprintf_s(file, "y %i\n", y);
	//add visual identifier that block data has ended
	fprintf_s(file, "\n", y);
	return true;
}

bool CBlock::RenderBlock(int cameraX, int cameraY)
{
	if (texture != NULL) {
		texture->RenderTexture(x * BLOCK_SIZE - cameraX, y * BLOCK_SIZE - cameraY);
	}
	return true;
}

CTexture * CBlock::GetTexture()
{
	return texture;
}

int CBlock::GetX()
{
	return x;
}

int CBlock::GetY()
{
	return y;
}

