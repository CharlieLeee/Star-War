#include "Game.h"


int main() 
{
	// Generate random seed
	srand(time(NULL));
	// Init window
	RenderWindow window(VideoMode(1920, 1080), "Star War v3.0", Style::Fullscreen);
	
	sf::Image icon;
	icon.loadFromFile("Textures/icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	
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
	//explosion.loadFromFile("Textures/explosion.png");
	explosion.loadFromFile("Textures/explosion.png");

	// Menu background
	Texture backgroundMenu;
	backgroundMenu.loadFromFile("Textures/menu.png");
	// Moving background
	Texture movingBack;
	movingBack.loadFromFile("Textures/back2.png");
	
	float shootLapse = 0.35f;

	Texture bomber;
	bomber.loadFromFile("Textures/enemy3.png");

	Texture addBullet;
	addBullet.loadFromFile("Textures/bullet.png");

	Texture addHP;
	addHP.loadFromFile("Textures/health.png");

	Texture bossTex;
	bossTex.loadFromFile("Textures/spaceship2.png");


	// Init game
	Game game(&window, &playerTex, &bulletTex, &enemyTex, &logoText,shootLapse,
	&backgroundMenu, &explosion, &movingBack, &bomber, &addBullet, &addHP);


	// Clock
	Clock clock;
	float deltaTime = 0.f;

	game.Run();
	return 0;
}
		