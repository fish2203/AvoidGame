#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <vector>
#include <cmath>
#include <iostream>

using namespace sf;
using namespace std;

class Game
{
private:
	RenderWindow* Window;
	Event Event;

	//Player
	CircleShape Player;
	float Speed = 5.0f;

	//Enemy
	RectangleShape Enemy;
	vector<RectangleShape> EnemyArray;
	int Count;
	float IntervalMax;
	float IntervalStart;

	// Point
	int Point;

	// Font
	Font Font;

	//Text
	Text PointText;
	Text GameOverText;

	bool isAlive;

	// Gun
	CircleShape Gun;
	vector<CircleShape> Ball;
	int BallMax;
	float BallTimeMax;
	float BallTimeStart;
	vector<Vector2f> Position;

public:
	// start uo
	Game();
	void InitWindow();
	void InitWindowPointer();
	
	//Update
	bool Running() const;
	void EventHandler();
	void Update();

	//Render
	void Render();

	// Stop Game
	~Game();
	void DeleteWindow();

	//Player
	void InitPlayer();
	void UpdatePlayer();

	//Enemy
	void InitEnemy();
	void InitSpawnValue();
	void SpawnEnemy();
	void DeleteEnemy();
	void UpdateEnemy();

	// Gun
	void InitGun();
	void InitBallSpawn();
	void ShootGun();
	void UpdateBall();

	//
	void CollisionCheck();

	// Font
	void InitFont();

	//Text
	void InitPointText();
	void UpdatePointText();
	void InitGameOverText();
};