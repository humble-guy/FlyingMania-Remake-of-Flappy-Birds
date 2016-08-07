#include "stdafx.h"
#include "Sprite.h"


CSprite::CSprite(SDL_Renderer * passed_renderer, string file_path, int x, int y, int w, int h, float *passed_camx, float *passed_camy,CCollisionRectangle passed_collision_rect)
{
	
		collision_rect = passed_collision_rect;
		

	camerax = passed_camx;
	cameray = passed_camy;
	
	renderer = passed_renderer;
	image = NULL;
	image = IMG_LoadTexture(renderer, file_path.c_str());

	if (image == NULL)
		cout << "Could not load image at specified file path:" << file_path.c_str();
	collision_image = NULL;
	collision_image = IMG_LoadTexture(renderer, "Data/collision_box.gif");
	if (collision_image == NULL)
		cout << "Could not load collision image at specified file path:" << file_path.c_str();



	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	debug_mainchar.x = x;
	debug_mainchar.y = y;
	debug_mainchar.w = w + 2;
	debug_mainchar.h = h + 2;


	framex = 0;
	framey = 0;

	SDL_QueryTexture(image, NULL, NULL, &image_width, &image_height);

	crop.x = 0;
	crop.y = 0;
	crop.w = image_width;
	crop.h = image_height;

	camera.x = rect.x + *camerax;
	camera.y = rect.y + *cameray;
	camera.w = rect.w;
	camera.h = rect.h;

	currentframe = 0;

	delay = 0;

	
}

void CSprite::setup_animation(int passed_framex,int passed_framey)
{
	framex = passed_framex;
	framey = passed_framey;
}


void CSprite::playanimation(int beginframe, int endframe, int row, float speed)
{


	if (delay + speed < SDL_GetTicks())
	{
		if (endframe <= currentframe || currentframe<beginframe)
				currentframe = beginframe;
		crop.w = image_width / framex;
		crop.h = image_height / framey;
		crop.x = currentframe*(image_width / framex);
		crop.y = row*(image_height / framey);
		delay = SDL_GetTicks();
	
				currentframe++;
	}
}



CSprite::~CSprite()
{
	SDL_DestroyTexture(image);

}

void CSprite::Draw()
{
	
	camera.x = rect.x + *camerax;
	camera.y = rect.y + *cameray;

	collision_rect.setx(rect.x + *camerax);
	collision_rect.sety(rect.y + *cameray);
	
	SDL_RenderCopy(renderer, image, &crop, &camera);

	
	//SDL_RenderCopy(renderer, collision_image, NULL, &collision_rect.getrect());
	

	
}

void CSprite::DrawSteady()
{
	

	SDL_RenderCopy(renderer, image, &crop, &rect);

	//SDL_RenderCopy(renderer, collision_image, NULL, &rect);

}

void CSprite::DrawFlipped()
{

	camera.x = rect.x + *camerax;
	camera.y = rect.y + *cameray;

	collision_rect.setx(rect.x + *camerax);
	collision_rect.sety(rect.y + *cameray);

	
    SDL_RenderCopyEx(renderer, image, &crop, &camera, 0, 0, SDL_FLIP_VERTICAL);
	//SDL_RenderCopy(renderer, collision_image, NULL, &collision_rect.getrect());
}

void CSprite::setx(int x)
{
	rect.x = x;
	debug_mainchar.x = x-2;
	
}
void CSprite::sety(int y)
{
	rect.y = y;
	debug_mainchar.y = y - 2;
	
}
void CSprite::setposition(int x, int y)
{
	rect.x = x;
	rect.y = y;
}
int CSprite::getx()
{
	return rect.x;
}
int CSprite::gety()
{
	return rect.y;
}

bool CSprite::is_colliding(CCollisionRectangle colrect)
{
	return !(rect.x + rect.w-8<colrect.getrect().x || rect.y + rect.h-8<colrect.getrect().y || rect.x+8>colrect.getrect().x + colrect.getrect().w || rect.y+8>colrect.getrect().y + colrect.getrect().h);
}
//addded +4 to each
int CSprite::if_passed_pipe()
{
	int score;

	return 0;
}

void CSprite::Draw_parameters(double angle)
{
	
	SDL_RenderCopyEx(renderer, image, &crop, &rect, angle, 0, SDL_FLIP_NONE);
	//SDL_RenderCopy(renderer, collision_image, NULL, &debug_mainchar);

	//Here changed &rect to &debug_mainchar so that collision image becomes small therefore chances of colliding decreases
}
