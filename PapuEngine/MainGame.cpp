#include "MainGame.h"
#include "ImageLoader.h"
#include <iostream>
#include "ResourceManager.h"
#include "PapuEngine.h"
#include <random>
#include <ctime>

using namespace std;

void MainGame::run() {
	init();
	update();
}

void MainGame::init() {
	Papu::init();
	_window.create("Engine", _witdh, _height, 0);
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	initLevel();
	initShaders();
}

void MainGame::initLevel() {
	//NIVELES
	_levels.push_back(new Level("Levels/level1.txt"));

	//AUDIOS
	
	//arma
	_sound.addSoundEffect("Music/Kamehameha.wav");

	//niveles
	_sound.addSoundEffect("Music/TOTTFIY.wav");
	_sound.addSoundEffect("Music/BFG Division.wav");
	_sound.addSoundEffect("Music/Hell_on_Earth.wav");
	_sound.addSoundEffect("Music/Rip_&_Tear.wav");
	
	


	_player = new Player();
	_weapon = new Weapon();
	_currenLevel = 0;
	_player->init(3.5f, _levels[_currenLevel]->getPlayerPosition(), &_inputManager, &_sound, _weapon);
	//_humans.push_back(_player);
	_spriteBacth.init();

	std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int>randPosX(
		1, _levels[_currenLevel]->getWidth()-2);
	std::uniform_int_distribution<int>randPosY(
		1, _levels[_currenLevel]->getHeight()-2);

	for (size_t i = 0; i < _levels[_currenLevel]->getNumHumans(); i++)
	{
		_humans.push_back(new Human());
		glm::vec2 pos(randPosX(randomEngine)*TILE_WIDTH, 
							randPosY(randomEngine)*TILE_WIDTH);
		_humans.back()->init(1.0f, pos);
	}

	const std::vector<glm::vec2>& zombiePosition =
		_levels[_currenLevel]->getZombiesPosition();

	for (size_t i = 0; i < zombiePosition.size(); i++)
	{
		_zombies.push_back(new Zombie());
		_zombies.back()->init(1.3f, zombiePosition[i]);
	}

	//_sound.SDL2SoundEffect(2);


}

void MainGame::initShaders() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}


void MainGame::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();

	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, _texture.id);

	/*GLuint timeLocation = 
		_program.getUniformLocation("time");

	glUniform1f(timeLocation,_time);*/

	GLuint pLocation =
		_program.getUniformLocation("P");

	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1,GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);

	_spriteBacth.begin();
	_levels[_currenLevel]->draw();
	_player->draw(_spriteBacth, _player->spriteActual);

	if (_player->drawWeapon)
	{
		_weapon->draw(_spriteBacth, _player->getPosition().x, _player->getPosition().y);
	}
	else
	{
		_weapon->reset();
	}
	for (size_t i = 0; i < _humans.size(); i++)
	{
		_humans[i]->draw(_spriteBacth, "Textures/human.png");
	}

	for (size_t i = 0; i < _zombies.size(); i++)
	{
		_zombies[i]->draw(_spriteBacth, "Textures/zombie.png");
	}

	_spriteBacth.end();
	_spriteBacth.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);

	_program.unuse();
	_window.swapBuffer();
}

void MainGame::procesInput() {
	SDL_Event event;
	const float CAMERA_SPEED = 20.0f;
	const float SCALE_SPEED = 0.1f;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				_inputManager.setMouseCoords(event.motion.x,event.motion.y);
				break;
			case  SDL_KEYUP:
				_inputManager.releaseKey(event.key.keysym.sym);
				break;
			case  SDL_KEYDOWN:
				_inputManager.pressKey(event.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				_inputManager.pressKey(event.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				_inputManager.releaseKey(event.button.button);
				break;
		}

		/*if (_inputManager.isKeyPressed(SDLK_w)) {
			_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, CAMERA_SPEED));
		}
		if (_inputManager.isKeyPressed(SDLK_s)) {
			_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, -CAMERA_SPEED));
		}
		if (_inputManager.isKeyPressed(SDLK_a)) {
			_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0));
		}
		if (_inputManager.isKeyPressed(SDLK_d)) {
			_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0));
		}*/
		if (_inputManager.isKeyPressed(SDLK_q)) {
			_camera.setScale(_camera.getScale() + SCALE_SPEED);
		}
		if (_inputManager.isKeyPressed(SDLK_e)) {
			_camera.setScale(_camera.getScale() - SCALE_SPEED);
		}
	}
}

void MainGame::update() {

	while (_gameState != GameState::EXIT) {

		manageMusic();
		procesInput();
		draw();
		_camera.update();
		_time += 0.02f;
		updateAgents();
		_camera.setPosition(_player->getPosition());
		//cout << "Zombies: " << _zombies.size() << endl;
	}
}

void MainGame::manageMusic()
{
	if (_player->drawWeapon)
	{
		if (!_player->soundWeapon)
		{
			cout << "Playing weapon sound." << endl;
			_sound.SDL2SoundEffect(0);
			_player->soundWeapon = true;
		}
	}
}



void MainGame::updateAgents() {

	_player->update(_levels[_currenLevel]->getLevelData(), _humans, _zombies, glm::vec2());
	for (size_t i = 0; i < _humans.size(); i++)
	{
		_humans[i]->update(_levels[_currenLevel]->getLevelData(),_humans,_zombies, glm::vec2());
	}

	for (size_t i = 0; i < _zombies.size(); i++)
	{
		_zombies[i]->update(_levels[_currenLevel]->getLevelData(), _humans, _zombies, _player->getPosition());

		if (_zombies[i]->collideWithWeapon(_weapon->pos_x, _weapon->pos_y, _weapon->height, _weapon->width))
		{
			delete _zombies[i];
			_zombies[i] = _zombies.back();
			_zombies.pop_back();
		}
		else
		{
			for (size_t j = 0; j < _humans.size(); j++)
			{
				if (_zombies[i]->collideWithAgent(_humans[j])) {
					_zombies.push_back(new Zombie());
					_zombies.back()->init(1.3f, _humans[j]->getPosition());
					delete _humans[j];
					_humans[j] = _humans.back();
					_humans.pop_back();
				}
			}
		}
	}
}

MainGame::MainGame(): 
					  _witdh(800),
					  _height(600),
					  _gameState(GameState::PLAY),
					  _time(0),
					  _player(nullptr)
{
	_camera.init(_witdh, _height);
}


MainGame::~MainGame()
{
}
