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

class Game
{
public:
	Game(RenderWindow *window, Texture *playerTex, Texture *bulletTex, Texture *enemyText,
		Texture *logoText, float shootLapse, Texture *backgroundMenu, Texture *explosionTex, 
		Texture *movingBack, Texture *bomberTex, Texture *addBullet, Texture *addHP, Texture *bossTex);
	~Game();


	RenderWindow *window;
	
	void CounterReset();
	void CalculateIndex();

	void BackgroundUpdate(const float &dt);
	void GenerateEnemyBullet();

	void BomberUpdate(const float &dt);
	void BomberPlayerBulCollision();

	void PBulletEnemyCollision();
	void PlayerEnemyCollision();
	void PlayerBossCollision(Player &player);
	void PlayerBulletBossCollision(Player &player);

	void ExplosionUpdate(float speed, const float &dt);

	void ClearPlayerBullets();
	void ClearEnemy();
	void ClearBomber();
	void ClearEBullets(); 
	void ClearExplosion();
	void ClearBuff();
	void CLearOutBoundExplosion();
	void ClearState();
	void ClearBoss();

	void HPBuffUpdate(const float &dt);
	void BulletBuffUpdate(const float &dt);
	void ResetEnemy();
	void EnemyUpdate(const float &dt);
	void PlayerUpdate(const float &dt);
	void TextboxUpdate();

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
	bool gameIsOver;
	bool isMenu;
	bool isDrawCredits;
	bool isFifty;
	bool havePickedHP;
	bool havePickedBullet; // Used to control bullet buff time
	bool pickedBulletBuff; // Used to display buff info
	bool generateBoss; // Whether the boss has been generated
	
	//Boss
	std::vector<Boss> boss;

	// Fonts
	Font font;

	// Enemy
	float spawnCnt;
	float spawnLapse;
	float enemySpeed;
	std::vector<Enemy> enemies;
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
	float menuCnt;
	float menuDisplayMax;
	Text menuText;

	// Score text
	Text score;

	// GameLOGO text
	Text gameLOGOText;

	// Game over end score text
	Text endScoreText;

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
	

	// Textbox
	Textbox textbox;

	// Character texutres
	Texture father;

};

