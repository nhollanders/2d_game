#ifndef GAME_H
#define GAME_H

// STL includes
#include <chrono>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <ctime>
#include <cmath>

// SFML includes
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
//#include <SFML/Network.hpp>

/*
* Primary Game Engine Wrapper Class
*/

class Game
{
private:
	// Variables

	// Windows
	sf::RenderWindow* window;
	sf::VideoMode videoMode;

	//Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Window FPS displaying
	std::chrono::steady_clock::time_point start, end, nextUpdate;
	std::chrono::milliseconds fpsUpdateInterval;
	bool displayFpsTitle;
	float smoothedFPS;
	std::string fps;

	// Private functions
	void initVariables();
	void initWindow();
	void initResources();
	void initText();

	// Pivate update functions
	void PollEvents();
	void calcFps();

	// Resources
	sf::Font font;
	sf::Image windowIcon;

	// Text
	sf::Text uiText = sf::Text(font);

public:
	// Constructors & Destructors
	Game();
	~Game();

	// Accessors
	const bool getIsRunning() const;
	void setDisplayTitleFps(bool boolPar);
	void setFpsUpdateInterval(std::chrono::milliseconds msPar);

	// Public functions
	void update();
	// Rendering
	void render();
};

#endif // !GAME_H