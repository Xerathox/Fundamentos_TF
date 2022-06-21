#pragma once
#include "Human.h"
#include "Weapon.h"
#include "Zombie.h"
#include "InputManager.h"

class Player: public Human
{
private:
	InputManager* _inputManager;

public:
	Weapon* _weapon;
	bool drawWeapon;
	Player();
	~Player();
	void init(float speed, glm::vec2 position, InputManager* inputManager, Weapon* weapon);
	void update(const std::vector<std::string>& levelData, std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies);
};

