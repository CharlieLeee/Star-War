#include "Game.h"


int main() 
{
	// Generate random seed
	srand(time(NULL));
	// Init window
	RenderWindow window(VideoMode(1920, 1080), "Star War v3.0", Style::Fullscreen);


	// Init textures
	Texture playerTex;
	playerTex.loadFromFile("Textures/ship1.png");
	Texture enemyTex;
	enemyTex.loadFromFile("Textures/enemy2.png");
	Texture bulletTex;
	bulletTex.loadFromFile("Textures/laser.png");
	Texture logoText;
	logoText.loadFromFile("Textures/logo.png");
	Texture explosion;
	explosion.loadFromFile("Textures/explosion.png");

	// Menu background
	Texture backgroundMenu;
	backgroundMenu.loadFromFile("Textures/menu.png");
	// Moving background
	Texture movingBack;
	movingBack.loadFromFile("Textures/back2.png");
	
	float shootLapse = 0.4f;

	Texture bomber;
	bomber.loadFromFile("Textures/enemy3.png");

	Texture addBullet;
	addBullet.loadFromFile("Textures/bullet.png");

	Texture addHP;
	addHP.loadFromFile("Textures/health.png");

	Texture bossTex;
	bossTex.loadFromFile("Textures/spaceship2.png");

	// Clock
	Clock clock;
	float deltaTime;

	// Init game
	Game game(&window, &playerTex, &bulletTex, &enemyTex, &logoText,shootLapse,
	&backgroundMenu, &explosion, &movingBack, &bomber, &addBullet, &addHP, &bossTex);


	while (window.isOpen())
	{
		// Calculate delta time between frames
		deltaTime = clock.restart().asSeconds();
		
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
			{
				window.close();
				break;
			}

		}
		game.Update(deltaTime);
		game.Draw(deltaTime);
		
	}
	return 0;
}
		