#include "Game.h"
#include"ScreenList.h"
#include "IGameScreen.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::run()
{
}

void Game::exit()
{
}

void Game::onSDLEvent(SDL_Event& event)
{
}

bool Game::init()
{
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    initSystems();
    onInit();
    addScreens();
    _currentScreen = _screenList->getCurrent();
    _currentScreen->onEntry();
    _currentScreen->setRunning();
    return true;
}


void Game::draw()
{
    glViewport(0, 0, _window.getScreenWidth(), _window.getScreenHeight());
    if (_currentScreen && _currentScreen->getState() == ScreenState::RUNNING) {
        _currentScreen->draw();
    }
}

void Game::update()
{
}


bool Game::initSystems()
{
    return false;
}
