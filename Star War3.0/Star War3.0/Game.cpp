#include "Game.h"



Game::Game(RenderWindow *window, Texture *playerTex, Texture *bulletTex, Texture *enemyText,
	Texture *logoText, float shootLapse, Texture *backgroundMenu, Texture *explosionTex,
	Texture *movingBack, Texture *bomberTex, Texture *addBullet, Texture *addHP, Texture *bossTex)
	:player(window, playerTex, bulletTex, shootLapse, true),
	logo(logoText, Vector2u(40, 1), 0.02f, Vector2f(800.f, 800.f), Vector2f(window->getSize().x / 2 - 400.f,
		window->getSize().y / 2 - 400.f)),
	playerA(window,playerTex, bulletTex, shootLapse, true),
	playerB(window, playerTex, bulletTex, shootLapse, false),
	menuBack(backgroundMenu, window),
	moving(movingBack, window)
{
	// Two Player mode
	this->isTwoPlayer = false;

	// Init Buff
	this->addBullet = addBullet;
	this->addHP = addHP;
	this->bulletBuffTimer = 0.f;
	this->bulletBuffMax = 8.f;

	// Init explosion Tex
	this->explosionTex = explosionTex;

	// Reset number counter
	this->bulletCnt = 0;
	this->enemyCnt = 0;
	this->ebulletCnt = 0;
	this->bomberCnt = 0;

	this->mult = 62.5f;

	// Init window
	this->window = window;
	//this->window->setFramerateLimit(60);

	// Init fonts
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");

	// Init States
	this->gameIsOver = true;
	this->isMenu = true;
	this->isDrawCredits = false;
	this->isFifty = false;
	this->havePickedHP = false;
	this->havePickedBullet = false;
	this->pickedBulletBuff = false;

	// Init logo
	this->logoTex = logoText;
	this->logoShape.setSize(Vector2f(800.f, 800.f));
	this->logoShape.setPosition(Vector2f(this->window->getSize().x / 2 - this->logoShape.getSize().x / 2,
		this->window->getSize().y / 2 - this->logoShape.getSize().y / 2));

	this->logoShape.setTexture(this->logoTex);

	// Init enemy texture
	this->enemyTex = *enemyText;
	this->ebulletTex.loadFromFile("Textures/Ebeam.png");

	// Init enemy
	this->enemySpeed = 10.f;
	this->enemies.push_back(Enemy(&enemyTex, this->window->getSize(), enemySpeed));
	this->enemy_bul_speed = 20.f;
	this->spawnLapse = 1.2f;
	this->spawnCnt = 0.f;
	this->enemyAcceleration = Vector2f(-1.0f, 0.f);
	this->eRegularDir = Vector2f(-1.f, 0.f);

	// Bomber enemy
	this->bomberTex = bomberTex;
	this->bomberTimer = 0.f;
	this->bomberLapse = 3.f;
	this->bomberSpeed = 8.f;

	// Init ebullet
	this->ebulletCntMax = 1.1f;
	this->offset2 = Vector2f(-10.f, 45.f);

	// Player
	this->initPos = Vector2f(0.f, 45.f);
	this->shootLapse = shootLapse;
	this->playerBulletSpeed = Vector2f(40.f, 0.01f);
	// Player Bullet acceleration
	this->regularBullet = Vector2f(2.0f, 0.f);
	this->strafetBullet = Vector2f(2.f, 1.f);
	this->shootingType = this->regularBullet;


	// Init BGM
	this->background.openFromFile("Audio/Electrix_NES.ogg");
	background.setLoop(true);
	background.setVolume(0.f);
	background.play();

	// Init welcome sound
	welcomeBuff.loadFromFile("Audio/captain.ogg");
	welcome.setBuffer(welcomeBuff);
	welcome.setVolume(70.f);

	// Init shoot sound
	this->shootBuffer.loadFromFile("Audio/shoot.ogg");
	this->shootSound.setBuffer(shootBuffer);
	this->shootSound.setVolume(20.f);

	// Init end sound
	this->endBuffer.loadFromFile("Audio/end.ogg");
	this->endSound.setBuffer(endBuffer);
	endSound.setVolume(30.f);

	// Init enemy shoot sound
	this->eshotBuffer.loadFromFile("Audio/eshot.wav");
	this->eshotSound.setBuffer(eshotBuffer);

	// Init credits texture
	this->creditsPic.loadFromFile("Textures/Credits.png");
	this->creditsPic.setSmooth(true);
	this->credits.setTexture(creditsPic);
	this->credits.setPosition(0.f, 0.f);

	// Init menu
	this->menuCnt = 0.f;
	this->menuDisplayMax = 2.5f;
	this->menuText.setFont(font);
	this->menuText.setCharacterSize(50);
	this->menuText.setFillColor(Color::White);
	this->menuText.setPosition(window->getSize().x / 2 - 160.f, 180.f);
	this->menuText.setString("     (N)EW GAME\n\n\n         (C)redits\n\n\n         (Q)uit");

	// Init score UI
	this->score.setFont(font);
	this->score.setCharacterSize(30);
	this->score.setFillColor(Color::White);
	this->score.setPosition(150.f, 150.f);

	// GameOver UI
	this->gameLOGOText.setFont(font);
	this->gameLOGOText.setCharacterSize(30);
	this->gameLOGOText.setFillColor(Color::Red);
	/*this->gameLOGOText.setPosition(window->getSize().x / 2 - 200,
		window->getSize().y / 2 - gameLOGOText.getGlobalBounds().height / 2);
	this->gameLOGOText.setString("WELCOME TO SPACE SHOOTER!!\n          PRESS SPACE TO START\n          PRESS K TO SHOOT\n\n          made by Charlie");*/

	// Endscore text
	this->endScoreText.setFont(font);
	this->endScoreText.setCharacterSize(30);
	this->endScoreText.setFillColor(Color::Red);

	// Background
	this->backgroundSpeed = Vector2f(-3.f, 0.f);

	// Init Textbox
	textbox.Setup(1, 18, 700, sf::Vector2f(500, 0));

	// Init boss
	this->generateBoss = false;
	this->bossTex.loadFromFile("Textures/spaceship2.png");

	// Init character textures
	this->son.loadFromFile("Textures/son.png");
	this->robot.loadFromFile("Textures/Robot.png");
	this->colonel.loadFromFile("Textures/colonel.png");
}


Game::~Game() { }

void Game::Run()
{
	Clock clock;
	float deltaTime = 0.f;

	while (this->window->isOpen())
	{
		ProcessEvent();
		deltaTime = clock.restart().asSeconds();
		this->Update(deltaTime);
		this->Draw(deltaTime);
	}
}

void Game::ProcessEvent()
{
	Event event;
	while (this->window->pollEvent(event))
	{
		if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
		{
			this->window->close();
			break;
		}
	}
}

void Game::Update(float dt)
{
	// Update logo
	logo.Update(0, dt);
	logoShape.setTextureRect(logo.uvRect);

	std::cout << enemyCnt << std::endl;

	if (!isMenu)
	{
		background.setVolume(10.f);
		if (gameIsOver)
		{
			CounterReset();

			// Clear screen & reset properties
			enemySpeed = 0.f;
			player.ResetVelocity();
			background.setVolume(5.f);
			textbox.Clear();
			ClearEnemy(enemies);
			ClearBomber();
			ClearBuff();
			ClearState();
			// Clear Enemy bullets
			ClearEBullets();
			ResetEnemy();
			ClearPlayerBullets(player);
			ClearExplosion();
			ClearBoss();

			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				welcome.play();
				background.setVolume(10.f);
				gameIsOver = false;
				textbox.Add("Aye Captain! Welcome on board", true, &son);

				player.Reset();
			}

		}
		else // Game starts here
		{
			// Calculate Index
			CalculateIndex();

			// Update background
			BackgroundUpdate(dt);
			
			// Update timer
			PlayerTimerUpdate(dt, player);

			// Update Boss
			BossUpdate(dt, player);

			// Update Textbox
			TextboxUpdate();

			// Update Buffs
			BuffUpdate(dt, player);

			// Update player
			PlayerUpdate(dt, player, enemies);
						
			// Update enemies movement & hp
			EnemyUpdate(dt, enemies);
			
			// Bomber update
			BomberUpdate(dt, player);

			// Explosion Update
			ExplosionUpdate(enemySpeed / 2, dt);
		}
	}

	else // IsMenu
	{
		if (isDrawCredits)
		{
			if (Keyboard::isKeyPressed(Keyboard::B))
			{
				isDrawCredits = false;
			}
		}

		else
		{
			if (Keyboard::isKeyPressed(Keyboard::N))
			{
				isMenu = false;
				gameIsOver = false;
				textbox.Clear();
				textbox.Add("Aye Captain! Welcome on board\nPress K to shoot\nPress WASD to move", true);

				welcome.play();
			}

			else if (Keyboard::isKeyPressed(Keyboard::C))
			{
				isDrawCredits = true;
			}

			else if (Keyboard::isKeyPressed(Keyboard::Q))
			{
				window->close();
			}
		}

	}
}

void Game::PlayerTimerUpdate(const float & dt, Player &player)
{
	if (player.shootCnt < this->shootLapse)
		player.shootCnt += dt;
}

void Game::EnemyTimerUpdate(const float & dt, std::vector<Enemy> &enemies)
{
	// Update enemy spawn lapse
	if (this->spawnCnt < this->spawnLapse)
		spawnCnt += dt;

	// Spawn enemies when it's time
	if (spawnCnt > spawnLapse)
	{
		enemies.push_back(Enemy(&enemyTex, window->getSize(), enemySpeed));
		spawnCnt -= spawnLapse;
		enemyCnt++;
	}
	
	// Update enemies' timers
	for (size_t i = enemyIndex; i < enemies.size(); i++)
	{
		enemies[i].bulletTimer += dt;
	}
}

void Game::BomberTimerUpdate(const float & dt)
{
	if (this->bomberTimer < this->bomberLapse)
		bomberTimer += dt;

	// Generate bomber
	if (bomberTimer > bomberLapse)
	{
		bomber.push_back(Bomber(bomberTex, this->window->getSize()));
		bomberTimer -= bomberLapse;
		this->bomberCnt++;
	}
}

void Game::BuffTimerUpdate(const float & dt)
{
	// Update Buff timer
	if (havePickedBullet)
	{
		bulletBuffTimer += dt;
	}

	if (bulletBuffTimer > bulletBuffMax)
	{
		bulletBuffTimer = 0.f;
		havePickedBullet = false;
	}
}

void Game::BossTimerUpdate(const float & dt)
{
	// Update boss timer
	for (size_t i = 0; i < boss.size(); i++)
	{
		if (boss[i].IsInScene(this->window))
			boss[i].shootTimer += dt;
	}
}

void Game::GenerateBoss()
{
	if (player.score % 50 == 0 && player.score != 0 && !generateBoss)
	{
		boss.push_back(Boss(6.f, &bossTex, 20, this->window->getSize()));
		this->generateBoss = true;
	}
}

void Game::BossShoot(const float &dt)
{
	for (size_t i = 0; i < boss.size(); i++)
	{
		boss[i].Update(window, dt);
		if (boss[i].shootTimer > boss[i].shootTimerMax)
		{
			int control = rand() % 3;

			if (control == 1)
			{
				ebullets.push_back(eBullets(&ebulletTex, Vector2f(boss[i].shape.getPosition().x, boss[i].shape.getPosition().y + 10.f), Vector2f(-1.f, 0.f)));
				ebullets.push_back(eBullets(&ebulletTex, Vector2f(boss[i].shape.getPosition().x, boss[i].shape.getPosition().y + 40.f), Vector2f(-1.f, 0.f)));
				ebullets.push_back(eBullets(&ebulletTex, Vector2f(boss[i].shape.getPosition().x, boss[i].shape.getPosition().y + 70.f), Vector2f(-1.f, 0.f)));
				ebullets.push_back(eBullets(&ebulletTex, Vector2f(boss[i].shape.getPosition().x, boss[i].shape.getPosition().y - 20.f), Vector2f(-1.f, 0.f)));
				ebullets.push_back(eBullets(&ebulletTex, Vector2f(boss[i].shape.getPosition().x, boss[i].shape.getPosition().y - 50.f), Vector2f(-1.f, 0.f)));
				ebulletCnt += 5;
			}
			else if (control == 2)
			{
				ebullets.push_back(eBullets(&ebulletTex, Vector2f(boss[i].shape.getPosition().x, boss[i].shape.getPosition().y + 10.f), Vector2f(-1 / 2.f, 1.732f / 2)));
				ebullets.push_back(eBullets(&ebulletTex, Vector2f(boss[i].shape.getPosition().x, boss[i].shape.getPosition().y + 10.f), Vector2f(-1.732f / 2, 1 / 2.f)));
				ebullets.push_back(eBullets(&ebulletTex, Vector2f(boss[i].shape.getPosition().x, boss[i].shape.getPosition().y + 10.f), Vector2f(-1.f, 0.f)));
				ebullets.push_back(eBullets(&ebulletTex, Vector2f(boss[i].shape.getPosition().x, boss[i].shape.getPosition().y + 10.f), Vector2f(-1.732f / 2, -1 / 2.f)));
				ebullets.push_back(eBullets(&ebulletTex, Vector2f(boss[i].shape.getPosition().x, boss[i].shape.getPosition().y + 10.f), Vector2f(-1 / 2.f, -1.732f / 2)));

				ebulletCnt += 5;
			}
			else if (control == 0)
			{
				ebullets.push_back(eBullets(&ebulletTex, Vector2f(boss[i].shape.getPosition().x, boss[i].shape.getPosition().y + 40.f), Vector2f(-1.f, 0.f)));
				ebullets.push_back(eBullets(&ebulletTex, Vector2f(boss[i].shape.getPosition().x, boss[i].shape.getPosition().y + 50.f), Vector2f(-1.f, 0.f)));
				ebullets.push_back(eBullets(&ebulletTex, Vector2f(boss[i].shape.getPosition().x, boss[i].shape.getPosition().y - 40.f), Vector2f(-1.f, 0.f)));
				ebullets.push_back(eBullets(&ebulletTex, Vector2f(boss[i].shape.getPosition().x, boss[i].shape.getPosition().y - 50.f), Vector2f(-1.f, 0.f)));
				ebulletCnt += 4;
			}
			boss[i].shootTimer -= boss[i].shootTimerMax;
		}
	}
}

void Game::BossUpdate(const float & dt, Player &player)
{
	this->BossTimerUpdate(dt);

	// Generate Boss
	this->GenerateBoss();

	// Update Boss
	this->BossShoot(dt);

	this->PlayerBossCollision(player);

	this->PlayerBulletBossCollision(player);
}

// Reset counter
void Game::CounterReset()
{
	this->bulletCnt = 0;
	this->enemyCnt = 0;
	this->ebulletCnt = 0;
	this->bomberCnt = 0;

	this->bulletIndex = 0;
	this->enemyIndex = 0;
	this->ebulletIndex = 0;
	this->bomberIndex = 0;
}

// Use counter to calculate starting index(length 30)
void Game::CalculateIndex()
{
	if (enemyCnt <= 30)
		enemyIndex = 0;
	else
		enemyIndex = enemyCnt - 30;

	if (bulletCnt <= 30)
		bulletIndex = 0;
	else
		bulletIndex = bulletCnt - 30;

	if (ebulletCnt <= 30)
		ebulletIndex = 0;
	else
		ebulletIndex = ebulletCnt - 30;

	if (bomberCnt <= 30)
		bomberIndex = 0;
	else
		bomberIndex = bomberCnt - 30;
}

void Game::BackgroundUpdate(const float & dt)
{
	moving.UpdateMovingBack(this->window, dt, Vector2f(backgroundSpeed.x - abs(player.currentV.x) / 4, 0.f));
}

void Game::GenerateEnemyBullet(const float &dt, std::vector<Enemy> &enemies)
{
	// Timer
	EnemyTimerUpdate(dt, enemies);
	
	// Enemy bullets generate
	for (size_t i = enemyIndex; i < enemies.size(); i++)
	{
		if (enemies[i].bulletTimer > ebulletCntMax)
		{
			int temp = rand() % 10 + 1;
			if (temp == 1)
			{
				ebullets.push_back(eBullets(&ebulletTex, enemies[i].shape.getPosition() + offset2, eRegularDir));
				// Add to ebullets number
				this->ebulletCnt++;
				enemies[i].bulletTimer -= ebulletCntMax;
				break;
			}
		}
	}
}

void Game::EbulletsMovement(const float & dt, std::vector<Enemy> &enemies)
{
	for (size_t i = ebulletIndex; i < ebullets.size(); i++)
	{
		ebullets[i].Move(enemy_bul_speed, dt);
	}
}

void Game::EbulletsUpdate(const float & dt, std::vector<Enemy> &enemies)
{
	this->GenerateEnemyBullet(dt, enemies);
	this->EbulletsMovement(dt, enemies);
}

void Game::BomberUpdate(const float &dt, Player &player)
{
	//Update timer
	BomberTimerUpdate(dt);
	
	// Bomber Player collision
	for (size_t i = bomberIndex; i < bomber.size(); i++)
	{
		bomber[i].Move(bomberSpeed, dt, player.shape.getPosition(), this->window);
	}

	for (size_t i = bomberIndex; i < bomber.size(); i++)
	{
		if (bomber[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
		{
			player.HP--;
			this->bomberCnt--;
			explosion.push_back(Animation(explosionTex, Vector2u(8, 8), 0.01f, Vector2f(100.f, 100.f), Vector2f(bomber[i].shape.getPosition().x + 2.f, bomber[i].shape.getPosition().y - 18.f)));
			endSound.play();
			bomber.erase(bomber.begin() + i);
			break;
		}
	}

	BomberPlayerBulCollision(player);
}

void Game::BomberPlayerBulCollision(Player &player)
{
	bool bulletErased = false;
	bool bomberErased = false;

	for (size_t i = bulletIndex; i < player.bullets.size() && !bulletErased; i++)
	{
		for (size_t j = bomberIndex; j < bomber.size() && !bomberErased; j++)
		{
			if (player.bullets[i].shape.getGlobalBounds().intersects(bomber[j].shape.getGlobalBounds()))
			{
				eshotSound.play();
				if (!gameIsOver)
					player.score += 5;

				if (enemySpeed < 15.0f)
					enemySpeed += 0.1f;

				if (spawnLapse >= 1.5f)
					spawnLapse -= 0.2f;

				bomberErased = true;
				explosion.push_back(Animation(explosionTex, Vector2u(8, 8), 0.01f, Vector2f(100.f, 100.f), Vector2f(bomber[j].shape.getPosition().x + 2.f, bomber[j].shape.getPosition().y - 18.f)));
				int tmp = rand() % 5 + 1;
				if (tmp == 1)
				{
					BuffBullet.push_back(Buff(addBullet, Vector2f(bomber[j].shape.getPosition().x + 2.f, bomber[j].shape.getPosition().y - 18.f)));
				}
				bomberCnt--;

				bulletErased = true;
				this->bulletCnt--;
			}
			if (bomberErased)
			{
				bomber.erase(bomber.begin() + j);
			}
		}
		if (bulletErased)
		{
			player.bullets.erase(player.bullets.begin() + i);
		}
	}
}

void Game::PBulletEnemyCollision(Player &player, std::vector<Enemy> &enemies)
{
	bool bulletErased = false;
	bool enemyErased = false;

	for (size_t i = bulletIndex; i < player.bullets.size() && !bulletErased; i++)
	{
		for (size_t j = enemyIndex; j < enemies.size() && !enemyErased; j++)
		{
			if (player.bullets[i].shape.getGlobalBounds().intersects(enemies[j].shape.getGlobalBounds()))
			{
				enemies[j].HP--;
				eshotSound.play();
				if (!gameIsOver)
					player.score += 5;

				if (enemySpeed < 15.0f)
					enemySpeed += 0.1f;

				if (spawnLapse >= 1.5f)
					spawnLapse -= 0.2f;

				if (enemies[j].HP <= 0)
				{
					enemyErased = true;
					enemyCnt--;
					explosion.push_back(Animation(explosionTex, Vector2u(8, 8), 0.01f, Vector2f(150.f, 150.f), Vector2f(enemies[j].shape.getPosition().x, enemies[j].shape.getPosition().y)));
					int tmp = rand() % 10 + 1;
					if (tmp == 1)
					{
						BuffHP.push_back(Buff(addHP, Vector2f(enemies[j].shape.getPosition().x, enemies[j].shape.getPosition().y)));
					}
					//std::cout << "push";
				}

				bulletErased = true;
				this->bulletCnt--;
			}
			if (enemyErased)
			{
				enemies.erase(enemies.begin() + j);
				endSound.play();
			}
		}
		if (bulletErased)
		{
			player.bullets.erase(player.bullets.begin() + i);
		}
	}
}

void Game::PlayerEnemyCollision(Player &player, std::vector<Enemy> &enemies)
{
	// Check player & enemies collision
	for (size_t i = enemyIndex; i < enemies.size(); i++)
	{
		if (enemies[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
		{
			enemyCnt--;
			explosion.push_back(Animation(explosionTex, Vector2u(8, 8), 0.01f, Vector2f(150.f, 150.f), Vector2f(enemies[i].shape.getPosition().x, enemies[i].shape.getPosition().y)));

			enemies.erase(enemies.begin() + i);
			// Player take damage
			player.HP -= collideDamage;
			endSound.play();

			// Change difficulty
			if (enemySpeed >= 20.3f)
				enemySpeed -= 2.0f;
			if (spawnLapse <= 1.f)
				spawnLapse += 1.f;
			break;
		}
	}
}

void Game::PlayerBossCollision(Player &player)
{
	for (size_t i = 0; i < boss.size(); i++)
	{
		if (boss[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
		{
			endSound.play();
			player.HP = 0;
		}
	}

}

void Game::PlayerBulletBossCollision(Player & player)
{
	bool bulletErased = false;
	bool bossErased = false;

	for (size_t i = bulletIndex; i < player.bullets.size() && !bulletErased; i++)
	{
		for (size_t j = 0; j < boss.size() && !bossErased; j++)
		{
			if (player.bullets[i].shape.getGlobalBounds().intersects(boss[j].shape.getGlobalBounds()) && boss[j].IsInScene(this->window))
			{
				boss[j].HP--;
				eshotSound.play();
				if (!gameIsOver)
					player.score += 5;

				if (boss[j].HP <= 0)
				{
					bossErased = true;
					explosion.push_back(Animation(explosionTex, Vector2u(8, 8), 0.01f, Vector2f(800.f, 800.f), Vector2f(boss[j].shape.getPosition().x - 250.f, boss[j].shape.getPosition().y - 250.f)));

					BuffHP.push_back(Buff(addHP, Vector2f(boss[j].shape.getPosition().x, boss[j].shape.getPosition().y)));
					BuffBullet.push_back(Buff(addBullet, Vector2f(boss[j].shape.getPosition().x + 20.f, boss[j].shape.getPosition().y + 20.f)));

					//std::cout << "push";
				}

				bulletErased = true;
				this->bulletCnt--;
			}
			if (bossErased)
			{
				boss.erase(boss.begin() + j);
				endSound.play();
				generateBoss = false;
			}
		}
		if (bulletErased)
		{
			player.bullets.erase(player.bullets.begin() + i);
		}
	}
}

void Game::PlayerEbulletsCollision(Player & player)
{
	for (size_t i = ebulletIndex; i < ebullets.size(); i++)
	{
		// Player collison

		if (ebullets[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
		{
			player.HP--;
			eshotSound.play();

			ebullets.erase(ebullets.begin() + i);
			this->ebulletCnt--;
			break;
		}
	}
}

void Game::ExplosionUpdate(float speed, const float & dt)
{
	for (size_t i = 0; i < explosion.size(); i++)
	{
		explosion[i].shape.move(-speed * dt * mult, 0.f);
		explosion[i].UpdateAll(dt);
		explosion[i].shape.setTextureRect(explosion[i].uvRect);
	}

	// Handle animations
	CLearOutBoundExplosion();
}

void Game::ClearPlayerBullets(Player &player)
{
	for (size_t i = 0; i < player.bullets.size(); i++)
	{
		player.bullets.erase(player.bullets.begin() + i);
	}
}

void Game::ClearEnemy(std::vector<Enemy> &enemies)
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies.erase(enemies.begin() + i);
	}
}

void Game::ClearBomber()
{
	for (size_t i = 0; i < bomber.size(); i++)
	{
		bomber.erase(bomber.begin() + i);
	}
}

void Game::ClearEBullets()
{
	for (size_t i = 0; i < this->ebullets.size(); i++)
	{
		ebullets.erase(ebullets.begin() + i);
	}
}

void Game::ClearExplosion()
{
	for (size_t i = 0; i < explosion.size(); i++)
	{
		explosion.erase(explosion.begin() + i);
	}
}

void Game::ClearBuff()
{
	for (size_t i = 0; i < BuffHP.size(); i++)
	{
		BuffHP.erase(BuffHP.begin() + i);
	}

	for (size_t i = 0; i < BuffBullet.size(); i++)
	{
		BuffBullet.erase(BuffBullet.begin() + i);
	}
}

void Game::CLearOutBoundExplosion()
{
	for (size_t i = 0; i < explosion.size(); i++)
	{
		if (explosion[i].shape.getPosition().x + explosion[i].shape.getGlobalBounds().width < 0)
			explosion.erase(explosion.begin() + i);
		break;
	}
}

void Game::ClearState()
{
	this->isFifty = false;
	this->havePickedHP = false;
	this->generateBoss = false;
	this->shootingType = this->regularBullet;
}

void Game::ClearBoss()
{
	for (size_t i = 0; i < boss.size(); i++)
	{
		boss.erase(boss.begin() + i);
	}
}

void Game::HPBuffUpdate(const float &dt, Player &player)
{
	for (size_t i = 0; i < BuffHP.size(); i++)
	{
		BuffHP[i].Update(enemySpeed / 2.2f, dt);
	}
	for (size_t i = 0; i < BuffHP.size(); i++)
	{
		if (BuffHP[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
		{
			if (player.HP != player.HPMax)
				player.HP++;

			havePickedHP = true;

			BuffHP.erase(BuffHP.begin() + i);
			break;
		}

	}

	for (size_t i = 0; i < BuffHP.size(); i++)
	{
		if (BuffHP[i].shape.getPosition().x + BuffHP[i].shape.getGlobalBounds().width < 0)
			BuffHP.erase(BuffHP.begin() + i);
		break;
	}
}

void Game::BulletBuffUpdate(const float & dt, Player &player)
{
	for (size_t i = 0; i < BuffBullet.size(); i++)
	{
		BuffBullet[i].Update(enemySpeed / 2.2f, dt);
	}
	for (size_t i = 0; i < BuffBullet.size(); i++)
	{
		if (BuffBullet[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
		{
			havePickedBullet = true;
			pickedBulletBuff = true;
			BuffBullet.erase(BuffBullet.begin() + i);
			break;
		}

	}

	for (size_t i = 0; i < BuffBullet.size(); i++)
	{
		if (BuffBullet[i].shape.getPosition().x + BuffBullet[i].shape.getGlobalBounds().width < 0)
			BuffBullet.erase(BuffBullet.begin() + i);
		break;
	}
}

void Game::BuffUpdate(const float & dt, Player & player)
{
	// Timer
	BuffTimerUpdate(dt);
	
	// HP Buff Update
	HPBuffUpdate(dt, player);

	// Bullet Buff Update
	BulletBuffUpdate(dt, player);
}

void Game::ResetEnemy()
{
	this->enemySpeed = 10.f;
	this->spawnLapse = 2.1f;
}

void Game::EnemyUpdate(const float & dt, std::vector<Enemy> &enemies)
{
	for (size_t i = enemyIndex; i < enemies.size(); i++)
	{
		enemies[i].Update(dt);
	}

	// Update ebullets
	EbulletsUpdate(dt, enemies);
}

void Game::PlayerUpdate(const float & dt, Player &player, std::vector<Enemy> &enemies)
{
	// Player Update position
	player.Update(*window, dt);

	// Player shoot
	if (Keyboard::isKeyPressed(Keyboard::K) && player.shootCnt > this->shootLapse)
	{
		switch (havePickedBullet)
		{
		case true:
			this->shootingType = this->strafetBullet;
			break;
		default:
			this->shootingType = this->regularBullet;
		}
		player.shoot(this->playerBulletSpeed, this->shootingType);
		shootSound.play();
		player.shootCnt -= this->shootLapse;
		// Add bullet number
		if (this->shootingType == this->regularBullet)
			this->bulletCnt += 1;
		else
			this->bulletCnt += 2;
	}

	// Player bullets move
	for (size_t i = bulletIndex; i < player.bullets.size(); i++)
	{
		// Move change to methods later
		player.bullets[i].Move(dt);
	}

	// Player Bullets & Enemies Collision
	PBulletEnemyCollision(player, enemies);
	// Player & Enemies Collison
	PlayerEnemyCollision(player, enemies);
	//Player & Ebullets collision
	PlayerEbulletsCollision(player);

	PlayerScoreUpdate(player);

	PlayerStateUpdate(player);
}

void Game::PlayerStateUpdate(Player & player)
{
	// Update player state
	if (player.HP == 0)
	{
		player.hpBar.setSize(Vector2f(20.f * player.HP, 5.f));

		this->endScoreText.setPosition(Vector2f(window->getSize().x / 2 - 200.f,
			window->getSize().y / 2.f - endScoreText.getGlobalBounds().height / 2));

		this->endScoreText.setString("    GAME OVER!\n      SCORE: " + std::to_string(player.score) +
			"\nPress space to restart or ESC to exit");

		ClearEnemy(enemies);
		gameIsOver = true;
	}
}

void Game::PlayerScoreUpdate(Player & player)
{
	// Update score
	score.setString("SCORE: " + std::to_string(player.score));
}

void Game::TextboxUpdate()
{
	if (player.score >= 50 && !isFifty)
	{
		this->textbox.Add("You've reached 50pt, watch out for the BOSS!!", true, &robot);
		this->isFifty = true;
	}

	if (havePickedHP)
	{
		this->textbox.Add("You've picked one HP Buff: health +1.     Your HP: " + std::to_string(player.HP), true, &colonel);
		this->havePickedHP = false;
	}

	if (pickedBulletBuff)
	{
		this->textbox.Add("You've picked one Bullet Buff: Your shooting mode: strafet", true, &colonel);
		this->pickedBulletBuff = false;
	}
}

void Game::Draw(float dt)
{
	if (isMenu)
	{
		// White background in menu
		window->clear(Color::White);
		menuCnt += dt;
		if (gameIsOver)
		{
			if (menuCnt > menuDisplayMax)
			{
				menuBack.DrawStatic(this->window);
				window->draw(menuText);
			}
			else
			{
				window->draw(logoShape);
			}
		}
		if (isDrawCredits)
		{
			window->draw(credits);
		}
	}
	else
	{
		window->clear();

		if (!gameIsOver)
		{
			// Draw game loop

			// Draw background
			moving.DrawMoving(this->window);

			// Player's bullets
			for (size_t i = bulletIndex; i < player.bullets.size(); i++)
			{
				window->draw(player.bullets[i].shape);
			}
			// Player
			player.Draw(*window);

			// Enemy
			for (size_t i = enemyIndex; i < enemies.size(); i++)
			{
				enemies[i].Draw(*window);
			}

			// Bomber
			for (size_t i = bomberIndex; i < bomber.size(); i++)
			{
				bomber[i].Draw(this->window);
			}

			// Draw boss
			for (size_t i = 0; i < boss.size(); i++)
			{
				boss[i].Draw(window);
			}

			// Draw enemy bullets
			for (size_t i = ebulletIndex; i < ebullets.size(); i++)
			{
				window->draw(ebullets[i].shape);
			}

			// Draw explosion
			for (size_t i = 0; i < explosion.size(); i++)
			{
				explosion[i].Draw(this->window);
			}

			// Draw Buff
			for (size_t i = 0; i < BuffBullet.size(); i++)
			{
				BuffBullet[i].Draw(window);
			}

			for (size_t i = 0; i < BuffHP.size(); i++)
			{
				BuffHP[i].Draw(window);
			}

			// Draw Textbox
			textbox.Render(*window);

			// Score
			window->draw(score);
		}
		else
		{
			window->draw(endScoreText);
		}
	}

	window->display();
}
