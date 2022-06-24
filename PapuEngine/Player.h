#pragma once
#include "Human.h"
#include "Weapon.h"
#include "Zombie.h"
#include "InputManager.h"
#include "Sound.h"


class Zombie;
class Human;

class Player: public Human
{
private:
	InputManager* _inputManager;
	Music* _soundManager;

public:
	std::string spriteActual;
	std::string spriteDer;
	std::string spriteIzq;
	std::string spriteArr;
	std::string spriteAba;
	Weapon* _weapon;
	bool drawWeapon;
	bool soundWeapon;
	bool stunned;
	float stunnedTime;
	Player();
	~Player();
	void init(float speed, glm::vec2 position, InputManager* inputManager, Music* _soundManager, Weapon* weapon);
	void update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies, glm::vec2 player_position);
	void collideWithZombies(std::vector<Zombie*>& zombies);
};

