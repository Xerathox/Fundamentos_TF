#pragma once
#include <glm\glm.hpp>
#include "SpriteBacth.h"
#include "GLTexture.h"
#include <string>

enum class Direction {
	UP, DOWN, LEFT, RIGHT
};
class Weapon{

protected:
	int default_HEIGHT;
	int default_WIDTH;
	
public:
	Direction direccion;
	Weapon();
	~Weapon();
	void draw(SpriteBacth& spritebatch, int x, int y);
	int get_default_HEIGHT();
	int get_default_WIDTH();
	int get_pos_x(int x, int width);
	int get_pos_y(int y, int height);
};
