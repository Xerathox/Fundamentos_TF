#include "ScreenList.h"
#include "IGameScreen.h"

ScreenList::ScreenList() {
}

ScreenList::~ScreenList()
{
}

IGameScreen* ScreenList::moveNext()
{
	IGameScreen* currentScreen = getCurrent();
	if (currentScreen->getNextScreen() != -1) {
		_currentIndex = currentScreen->getNextScreen();
	}
	return getCurrent();
}

IGameScreen* ScreenList::movePrevious()
{
	IGameScreen* currentScreen = getCurrent();
	if (currentScreen->getPreviousScreen() != -1) {
		_currentIndex = currentScreen->getPreviousScreen();
	}
	return getCurrent();
}

void ScreenList::setScreen(int nextScreen) {
	_currentIndex = nextScreen;
}

void ScreenList::addScreen(IGameScreen* newScreen)
{
	newScreen->_screenIndex = _screens.size();
	_screens.push_back(newScreen);
	newScreen->build();
	newScreen->setParent();
}

void ScreenList::destroy()
{
	for (size_t i = 0; i < _screens.size(); i++)
	{
		_screens[i]->destroy();
	}
	_currentIndex = -1;
	_screens.resize(0);
}

IGameScreen* ScreenList::getCurrent()
{
	return _currentIndex == -1 ? nullptr : _screens[_currentIndex];
}
