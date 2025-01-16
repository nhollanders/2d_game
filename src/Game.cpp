#include "Game.h"

using namespace sf;
using namespace std::chrono;

/*
* Initializers
*/
void Game::initVariables()
{
	this->window = nullptr;

	// FPS title displaying
	this->smoothedFPS = 0.5f;
	this->start = steady_clock::now();
	this->displayFpsTitle = false;
	this->fpsUpdateInterval = std::chrono::milliseconds(100);
}

// Game logic
void Game::initResources()
{
	bool noResourceLoadIssues = true;

	noResourceLoadIssues = this->windowIcon.loadFromFile("Resources/Images/balls_icon.png");
	noResourceLoadIssues = this->font.openFromFile("Resources/Fonts/pixelatedFont.ttf");

	if (!noResourceLoadIssues)
		std::cout << "Error loading resources!" << "\n";
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(18);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("N/A");
}

void Game::initWindow()
{
	this->videoMode.size.x = 640;
	this->videoMode.size.y = 480;
	this->window = new RenderWindow(this->videoMode, "Ball Simulator", Style::Titlebar | Style::Close | Style::Resize);
	this->window->setIcon(this->windowIcon.getSize(), this->windowIcon.getPixelsPtr());
}

void Game::PollEvents()
{
	while (const std::optional event = this->window->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			this->window->close();
			break;
		}
		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
				this->window->close();
				break;
		}
	}
}

void Game::calcFps() // ran right after rendering
{

	// FPS window title displaying
	this->end = steady_clock::now();
	if (this->nextUpdate <= this->end) // Update only at intervals
	{
		// Calculate frame duration in seconds
		float frameDurationSec = std::chrono::duration<float>(this->end - this->start).count();

		// Avoid division by zero
		if (frameDurationSec > 0.0f) // really should never reach 0 since thats just perfect frame duration so itll skip that frame of calc
		{
			float currentFPS = 1.0f / frameDurationSec;

			// Initialize smoothedFPS if not already done
			if (this->smoothedFPS < 0.0f) // Assuming smoothedFPS is initialized to -1 or an invalid FPS
			{
				this->smoothedFPS = currentFPS;
			}

			// Apply exponential moving average (EMA) smoothing
			constexpr float alpha = 0.1f; // Smoothing factor (adjust as needed)
			this->smoothedFPS = alpha * currentFPS + (1.0f - alpha) * this->smoothedFPS;

			// Format smoothed FPS
			std::stringstream stream;
			stream << std::fixed << std::setprecision(2) << this->smoothedFPS; // Precision to 2 decimal places
			std::string fpsString = stream.str();

			this->fps = fpsString;

			if (this->displayFpsTitle)
			{
				this->window->setTitle("FPS: " + fpsString);
			}
		}

		// Set the next update time
		this->nextUpdate = this->end + this->fpsUpdateInterval;
	}

	// Update start time for next frame
	this->start = steady_clock::now();
}

/*
* Constructors
*/
Game::Game()
{
	this->initVariables(); // initialize all variables
	this->initResources(); // initializes resources like textures
	this->initWindow(); // initialize window
	this->initText();
}

Game::~Game()
{
	delete this->window;
}

/*
* Accessors
*/
const bool Game::getIsRunning() const {
	return this->window->isOpen();
}
void Game::setDisplayTitleFps(bool boolPar) { // lets you set if the fps is displayed in the title or not
	this->displayFpsTitle = boolPar;
}
void Game::setFpsUpdateInterval(std::chrono::milliseconds msPar) { // lets you set how often the fps changes in the title in milliseconds
	this->fpsUpdateInterval = msPar;
}

/*
* Public functions
*/

void Game::update() // game logic and functionality
{
	this->PollEvents();
}

void Game::render() // rendering pixels on screen
{
	/*
	* Renders the game in order:
	* - clear window with color
	* - draw objects
	* - display window
	*/

	this->window->clear();

	// render here
	this->window->draw(this->uiText);

	this->window->display();
	this->calcFps();
}