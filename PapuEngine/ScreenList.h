#pragma once
#include <vector>
class IGameScreen;

class ScreenList
{
public:
	ScreenList();
	~ScreenList();
	IGameScreen* moveNext();
	IGameScreen* movePrevious();
	void setScreen(int nextScreen);
	void addScreen(IGameScreen* newScreen);
	void destroy();
	IGameScreen* getCurrent();
protected:
	std::vector<IGameScreen*> _screens;
	int _currentIndex = -1;
};

