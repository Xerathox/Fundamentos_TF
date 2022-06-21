#include "Player.h"
#include <SDL\SDL.h>


void Player::init(float speed, glm::vec2 position, InputManager* inputManager, Weapon* weapon) {
	_speed = speed;
	_position = position;
	_inputManager = inputManager;
	_weapon = weapon;
	color.set(0, 0, 185, 255);
}
void Player::update(const std::vector<std::string>& levelData, 
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies) {
	
	
	//arma
	if (_inputManager->isKeyPressed(SDLK_UP)) {
		_weapon->direccion = Direction::UP;		
		drawWeapon = true;
	}
	if (_inputManager->isKeyPressed(SDLK_DOWN)) {
		_weapon->direccion = Direction::DOWN;
		drawWeapon = true;
	}
	if (_inputManager->isKeyPressed(SDLK_LEFT)) {
		_weapon->direccion = Direction::LEFT;
		drawWeapon = true;
	}
	if (_inputManager->isKeyPressed(SDLK_RIGHT)) {
		_weapon->direccion = Direction::RIGHT;
		drawWeapon = true;
	}

	if (!drawWeapon)
	{
		if (_inputManager->isKeyPressed(SDLK_w)) {
			_position.y += _speed;
		}
		if (_inputManager->isKeyPressed(SDLK_s)) {
			_position.y -= _speed;
		}
		if (_inputManager->isKeyPressed(SDLK_a)) {
			_position.x -= _speed;
		}
		if (_inputManager->isKeyPressed(SDLK_d)) {
			_position.x += _speed;
		}
	}
	collideWithLevel(levelData);
}


Player::Player()
{
	drawWeapon = false;
}


Player::~Player()
{
}
