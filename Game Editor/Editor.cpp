#include "Editor.h"



//make sure that the IDs start as small as possible; we do not want the IDs to get too large when you re-draw blocks



CEditor::CEditor()
{
	quit = false;
	window = NULL;
	renderer = NULL;
	BlockSelection = new SDL_Rect;
	cameraX = 0;
	cameraY = 0;
	buttonDown = false;
	current_drawing_texture = -1;
	//Start SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("Cannot Initialize SDL Graphics: %s\n", SDL_GetError());
		quit = true;
	}
	else
		printf("Graphics Initialized Successfully\n");

	//Start Window
	window = SDL_CreateWindow("Level Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("Cannot Initialize Window: %s\n", SDL_GetError());
		quit = true;
	}
	else
		printf("Window Initialized Successfully\n");

	//Start Renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		printf("Cannot Initialize Renderer: %s\n", SDL_GetError());
		quit = true;
	}
	else
		printf("Renderer Initialized Successfully\n");

	LoadTextures("bin/textures.vad");
	LoadBlocks("bin/level1.vad");
}

void CEditor::GameLoop()
{
	int frame = 0;
	while (quit == false) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		while (SDL_PollEvent(&e) == 1) {
			switch (e.type) {
			case SDL_MOUSEMOTION:
				if (buttonDown)
					ExpandSelection(e);
				else
					ClearSelection();
				break;
			case SDL_KEYDOWN:
				HandleKeyboardInput(e);
				break;
			case SDL_MOUSEBUTTONDOWN:
				buttonDown = true;
				StartSelection(e);
				ExpandSelection(e);
				break;
			case SDL_MOUSEBUTTONUP:
				buttonDown = false;
				SaveSelection();
				ClearSelection();
				break;
			case SDL_QUIT:
				quit = true;
				break;
			default:
				break;
			}
		}
		RenderBlocks();
		RenderSelection();
		SDL_RenderPresent(renderer);
	}
}

bool CEditor::SaveLevel(char file[])
{
	FILE * blockstream;
	fopen_s(&blockstream, file, "w");
	if (blockstream != NULL) {
		for (int i = 0; i < blocks.size(); i++) {
			if (blocks[i] != NULL && blocks[i]->GetTexture() != NULL) {
				//parse each block and save in the file
				blocks[i]->SaveBlock(blockstream);
			}
		}
		printf("Level file to %s successfully saved!\n", file);
	}
	else {
		printf("Could not save the level file to %s\n", file);
		return false;
	}
	fclose(blockstream);
	return true;
}

bool CEditor::LoadTextures(char file[])
{
	char cvalue[50];
	float ivalue = 0;
	char parameter[50];
	//set counting in array
	int id;
	fopen_s(&texturestream, file, "r");
	int line_number = 1;

	if (texturestream != NULL) {
		//file opened successfully, start loading textures
		while (fscanf_s(texturestream, "%[^ ] %[^\n]\n", parameter, _countof(parameter), cvalue, _countof(cvalue)) != -1) {
			if (sscanf_s(cvalue, "%f", &ivalue)) {
				//int data
				if (!strcmp(parameter, "id")) {
					//make sure that the id in the array matches up with the id in the file; it will be easier to load blocks this way
					while (textures.size() <= ivalue) {
						textures.emplace_back();
					}
					id = ivalue;
					textures[id] = new CTexture(renderer);
					textures[id]->SetID(ivalue);
				}
				else if (!strcmp(parameter, "animate_delay")) {}
				else if (!strcmp(parameter, "loop")) {}
				else if (!strcmp(parameter, "category")) { textures[id]->SetCategory(ivalue); }
				else if (!strcmp(parameter, "width")) { textures[id]->SetWidth(ivalue); }
				else if (!strcmp(parameter, "height")) { textures[id]->SetHeight(ivalue); }
				else if (!strcmp(parameter, "frames")) { textures[id]->SetFrames(ivalue); }
				else if (!strcmp(parameter, "destroyable")) {}
				else if (!strcmp(parameter, "destroyed")) {}
				else if (!strcmp(parameter, "health")) {}
				else if (!strcmp(parameter, "shoot_through")) {}
				else if (!strcmp(parameter, "walk_through")) {}
				else if (!strcmp(parameter, "pickup_id")) {}
				else if (!strcmp(parameter, "light")) {}
				else if (!strcmp(parameter, "activation")) {}
				else if (!strcmp(parameter, "on_activate")) {}
				else if (!strcmp(parameter, "glow")) {}
				else { printf("Could not parse int data at line number %i\n", line_number); }
			}
			else  {
				//character data
				if (!strcmp(parameter, "path")) { 
					textures[id]->SetPath(cvalue); 
				}
			}
			line_number++;
			//make it so textures only load once
			//if get frames and path are not null, load the texture.
		}
	}
	else {
		return false;
	}
	fclose(texturestream);
	textures.shrink_to_fit();
	for (int i = 0; i < textures.size(); i++) {
		if (textures[i] != NULL) {
			textures[i]->LoadTexture();
		}
	}
	//Load Actual Texture Files
	return true;
}

bool CEditor::LoadBlocks(char file[])
{
	char cvalue[50];
	float ivalue = 0;
	char parameter[50];
	//set counting in array
	int id;
	fopen_s(&blockstream, file, "r");
	int line_number = 1;

	if (blockstream != NULL) {
		//file opened successfully, start loading textures
		while (fscanf_s(blockstream, "%[^ ] %[^\n]\n", parameter, _countof(parameter), cvalue, _countof(cvalue)) != -1) {
			if (sscanf_s(cvalue, "%f", &ivalue)) {
				//int data
				if (!strcmp(parameter, "id")) {
					id = ivalue;
					while (blocks.size() <= ivalue) {
						blocks.emplace_back();
					}
					blocks[id] = new CBlock();
					blocks[id]->SetID(ivalue);
				}
				else if (!strcmp(parameter, "texture")) { 
					if (ivalue < textures.size()) {
						blocks[id]->SetTexture(textures[ivalue]);
					}
				}
				else if (!strcmp(parameter, "x")) { blocks[id]->SetX(ivalue); }
				else if (!strcmp(parameter, "y")) { blocks[id]->SetY(ivalue); }
				else if (!strcmp(parameter, "animate_delay")) {}
				else if (!strcmp(parameter, "loop")) {}
				else if (!strcmp(parameter, "width")) {}
				else if (!strcmp(parameter, "height")) {}
				else if (!strcmp(parameter, "frames")) {}
				else if (!strcmp(parameter, "destroyable")) {}
				else if (!strcmp(parameter, "destroyed")) {}
				else if (!strcmp(parameter, "health")) {}
				else if (!strcmp(parameter, "shoot_through")) {}
				else if (!strcmp(parameter, "walk_through")) {}
				else if (!strcmp(parameter, "pickup_id")) {}
				else if (!strcmp(parameter, "light")) {}
				else if (!strcmp(parameter, "activation")) {}
				else if (!strcmp(parameter, "on_activate")) {}
				else if (!strcmp(parameter, "glow")) {}
				else { printf("Could not parse int data at line number %i\n", line_number); }
			}
			else {
				//character data
				//if (!strcmp(parameter, "path")) {};
			}
			line_number++;
		}
	}
	else {
		return false;
	}
	fclose(blockstream);
	blocks.shrink_to_fit();
	return true;
}

bool CEditor::RenderBlocks()
{
	for (int i = 0; i < blocks.size(); i++) {
		if (blocks[i] != NULL) {
			blocks[i]->RenderBlock(cameraX, cameraY);
		}
	}
	return true;
}

bool CEditor::StartSelection(SDL_Event mouseevent)
{
	startX = (mouseevent.motion.x + cameraX) / (float)BLOCK_SIZE;
	startY = (mouseevent.motion.y + cameraY) / (float)BLOCK_SIZE;
	BlockSelection->x = startX * BLOCK_SIZE - cameraX;
	BlockSelection->y = startY * BLOCK_SIZE - cameraY;
	return false;
}

bool CEditor::ExpandSelection(SDL_Event mouseevent){
	endX = roundf((mouseevent.motion.x + cameraX) / (float)BLOCK_SIZE);
	endY = roundf((mouseevent.motion.y + cameraY) / (float)BLOCK_SIZE);
	int width = abs(startX - endX);
	int height = abs(endY - startY);
	
	//make sure that at least one block is selected at all times
	if (width == 0)
		width = 1;
	if (height == 0)
		height = 1;

	BlockSelection->w = width * BLOCK_SIZE;
	BlockSelection->h = height * BLOCK_SIZE;
	return true;
}

bool CEditor::ClearSelection()
{
	BlockSelection->x = 0;
	BlockSelection->y = 0;
	BlockSelection->h = 0;
	BlockSelection->w = 0;
	//Are the following redundant?
	startX = 0;
	startY = 0;
	endX = 0;
	endY = 0;
	return true;
}

bool CEditor::RenderSelection()
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderDrawRect(renderer, BlockSelection);
	return false;
}

bool CEditor::SaveSelection()
{
	int start_id = 0;
	//check here if the selected area is backwards
	for (int n = startX; n < endX; n++) {
		for (int m = startY; m < endY; m++) {
			//Loop through every single selected block here
			for (int i = 0; i < blocks.size(); i++) {
				//Loop through every single existing block in the blocks vector
				if (blocks[i] != NULL && blocks[i]->GetX() == n && blocks[i]->GetY() == m) {
					//if there is a block in the place of the old block, delete old block
					delete blocks[i];
					//create new block IN THE SAME ID as the old block
					blocks[i] = new CBlock(textures[1]);
					blocks[i]->SetID(i);
					break;
				}
			}
			if (current_drawing_texture != -1 && textures[current_drawing_texture] != NULL) {
				blocks.emplace_back(new CBlock(textures[current_drawing_texture]));
				blocks[blocks.size() - 1]->SetX(n);
				blocks[blocks.size() - 1]->SetY(m);
				blocks[blocks.size() - 1]->SetID(blocks.size() - 1);
			}
		}
	}
	return false;
}

bool CEditor::SetCurrentDrawingTexture(int passed_drawing_texture)
{
	current_drawing_texture = passed_drawing_texture;
	return true;
}

bool CEditor::HandleKeyboardInput(SDL_Event e)
{
	switch (e.key.keysym.scancode)
	{
	case SDL_SCANCODE_W:
		cameraY -= CAMERA_SPEED;
		break;
	case SDL_SCANCODE_A:
		cameraX -= CAMERA_SPEED;
		break;
	case SDL_SCANCODE_S:
		cameraY += CAMERA_SPEED;
		break;
	case SDL_SCANCODE_D:
		cameraX += CAMERA_SPEED;
		break;
	default:
		break;
	}
	return true;
}
