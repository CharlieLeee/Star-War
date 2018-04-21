#pragma once
#include "Player.h"
#include "eBullets.h"
#include "Enemy.h"
#include "eBullets.h"
#include "Animation.h"
#include "Background.h"
#include "Boss.h"
#include "Bomber.h"
#include "Buff.h"
#include "Textbox.h"
#include "Collision.h"
#include "Menu.h"

class Game
{
public:
	Game(RenderWindow *window, Texture *playerTex, Texture *bulletTex, Texture *enemyText,
		Texture *logoText, float shootLapse, Texture *backgroundMenu, Texture *explosionTex, 
		Texture *movingBack, Texture *bomberTex, Texture *addBullet, Texture *addHP);
	~Game();


	RenderWindow *window;
	Menu menu;

	// Timers
	void PlayerTimerUpdate(const float &dt, Player &player);
	void EnemyTimerUpdate(const float & dt, std::vector<Enemy> &enemies);
	void BomberTimerUpdate(const float &dt);
	void BuffTimerUpdate(const float &dt);
	void BossTimerUpdate(const float &dt);

	// Boss
	void GenerateBoss();
	void BossShoot(const float &dt);
	void BossUpdate(const float &dt, Player &player);

	// Index calculation
	void CounterReset();
	void CalculateIndex(int limit);

	// Backgrounds
	void BackgroundUpdate(const float &dt);
	
	// EBullets
	void GenerateEnemyBullet(const float &dt, std::vector<Enemy> &enemies);
	void EbulletsMovement(const float &dt, std::vector<Enemy> &enemies);
	void EbulletsUpdate(const float &dt, std::vector<Enemy> &enemies);

	// Bomber
	void BomberUpdate(const float &dt, Player &player);
	void BomberPlayerBulCollision(Player &player);

	// Collisions
	void PBulletEnemyCollision(Player &player, std::vector<Enemy> &enemies);
	void PlayerEnemyCollision(Player &player, std::vector<Enemy> &enemies);
	void PlayerBossCollision(Player &player);
	void PlayerBulletBossCollision(Player &player);
	void PlayerEbulletsCollision(Player &player);
	void PlayerPlayerCollision(Player &playerA, Player &playerB, float dt);
	void PBulletPlayerCollision(Player &playerMain, Player &oppPlayer);

	void ExplosionUpdate(float speed, const float & dt, std::vector<Animation> &explosion);

	// Enemy
	void ResetEnemy();
	void EnemyUpdate(const float &dt, std::vector<Enemy> &enemies);

	// Player
	void ResetPlayer(Player &player);
	void PlayerUpdate(const float & dt, Player &player, std::vector<Enemy> &enemies, bool isTwo, Keyboard::Key Shooting, Player *oppPlayer = nullptr);
	void PlayerStateUpdate(Player &player);
	void PlayerScoreUpdate(Player &player);

	void TwoPlayerScoreUpdate(Player &playerA, Player &playerB);

	void ClearPlayerBullets(Player &player);
	void ClearEnemy(std::vector<Enemy> &enemies);
	void ClearBomber();
	void ClearEBullets(); 
	void ClearExplosion();
	void ClearBuff();
	void CLearOutBoundExplosion();
	void ClearState();
	void ClearBoss();

	// Buffs
	void HPBuffUpdate(const float &dt, Player &player);
	void BulletBuffUpdate(const float &dt, Player &player);
	void BuffUpdate(const float &dt, Player &player);
	
	// Draw
	void DrawMenu(RenderWindow *window);
	void DrawLogo(RenderWindow *window);
	void DrawBackground(Background & back, RenderWindow *window, bool isMoving);
	void DrawPlayer(RenderWindow *window, Player &player);
	void DrawPlayerBullet(RenderWindow *window, Player &player);
	void DrawEnemies(RenderWindow *window, std::vector<Enemy> enemies);
	void DrawBomber(RenderWindow *window, std::vector<Bomber> &bomber);
	void DrawEBullet(RenderWindow *window);
	void DrawExplosion(RenderWindow *window, std::vector<Animation> &explosion);
	void DrawBuff(RenderWindow *window, std::vector<Buff> &buff);
	void DrawBoss(RenderWindow *window, std::vector<Boss> &boss);


	void TextboxUpdate();

	// Game
	void Run();
	void ProcessEvent();
	void Update(float dt);
	void Draw(float dt);

private:
	// Counter
	size_t bulletCnt;
	size_t bulletIndex;

	size_t enemyCnt;
	size_t enemyIndex;

	size_t ebulletCnt;
	size_t ebulletIndex;

	size_t bomberCnt;
	size_t bomberIndex;

	// Backgrounds
	Background menuBack;
	Background moving;
	Vector2f backgroundSpeed;

	// Animation
	Animation logo;
	Texture *logoTex;
	RectangleShape logoShape;

	// dt
	float mult;

	// States
	bool isLOGO;
	bool gameIsOver;
	bool isMenu;
	bool isDrawCredits;
	bool isHundred;
	bool havePickedHP;
	bool havePickedBullet; // Used to control bullet buff time
	bool pickedBulletBuff; // Used to display buff info
	bool generateBoss; // Whether the boss has been generated
	// 2P is collide
	bool isCollide;

	//Boss
	std::vector<Boss> boss;

	// Fonts
	Font font;

	// Enemy
	float spawnCnt;
	float spawnLapse;
	float enemySpeed;
	std::vector<Enemy> enemies;
	std::vector<Enemy> enemiesB;
	Vector2f enemyAcceleration;
	Vector2f enemyBulletSpeed;
	Vector2f eRegularDir;
	
	// Bomber enemy
	Texture *bomberTex;
	float bomberTimer;
	float bomberLapse;
	float bomberSpeed;// Positive number
	std::vector<Bomber> bomber;

	// eBullet init
	std::vector<eBullets> ebullets;
	float enemy_bul_speed;
	float ebulletCntMax;
	Vector2f offset2;

	// Player
	Player player;

	// Two player mode
	Player playerA;
	Player playerB;
	Vector2f initPos;
	bool isTwoPlayer;

	// player Bullet acceleration type
	Vector2f shootingType;
	Vector2f regularBullet;
	Vector2f strafetBullet;

	
	float shootLapse; // give to init player 
	Vector2f playerBulletSpeed;


	// Damage
	const int collideDamage = 1;

	// Sound
	Music background;
	SoundBuffer welcomeBuff;
	Sound welcome;

	SoundBuffer shootBuffer;
	Sound shootSound;

	SoundBuffer endBuffer;
	Sound endSound;

	SoundBuffer eshotBuffer;
	Sound eshotSound;

	// Textures
	Texture playerTex;
	Texture enemyTex;
	Texture bulletTex;
	Texture ebulletTex;
	Texture bossTex;

	// Menu
	float logoCnt;
	float logoDisplayMax;
	Text menuText;

	// Score text
	Text score;

	// GameLOGO text
	Text gameLOGOText;

	// Game over end score text
	Text endScoreText;
	Text twoPText;

	// Credits texture
	Texture creditsPic;
	Sprite credits;

	// Explosion texture
	Texture *explosionTex;	
	std::vector<Animation> explosion;

	// Buff
	std::vector<Buff> BuffBullet;
	std::vector<Buff> BuffHP;
	Texture *addBullet;
	Texture *addHP;
	
	float bulletBuffTimer;
	float bulletBuffMax;
	
	// 2P collide timer
	float collideTimer;

	// Textbox
	Textbox textbox;

	// Character texutres
	Texture son;
	Texture robot;
	Texture colonel;
};

