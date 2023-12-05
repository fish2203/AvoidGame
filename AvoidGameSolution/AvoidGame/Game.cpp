#include "Game.h"

// 윈도우 초기화 및 생성
Game::Game()
{
	// 윈도우 초기화 및 생성
	this->InitWindowPointer();
	this->InitWindow();

	// Player 초기화
	this->InitPlayer();

	// Enemy 초기화
	this->InitEnemy();
	this->InitSpawnValue();

	// Gun 초기화
	this->InitGun();
	this->InitBallSpawn();

	//Point 초기화
	this->Point = 0;

	this->InitFont();
	this->isAlive = true;


}

// 윈도우 제거
Game::~Game()
{
	this->DeleteWindow();
}

// 포인터 변수 초기화
void Game::InitWindowPointer()
{
	this->Window = nullptr;
}

// 윈도우 동적 생성,
void Game::InitWindow()
{
	this->Window = new RenderWindow(VideoMode(1280, 720), "Avoid Game", Style::Titlebar | Style::Close);

	// 일정하게 반복실행
	this->Window->setFramerateLimit(60);
}

// 윈도우 메모리에서 제거
void Game::DeleteWindow()
{
	delete this->Window;
}

// 윈도우가 실행중인지 체크
bool Game::Running() const
{
	return this->Window->isOpen();
}

// 이벤트 처리
void Game::EventHandler()
{
	while (this->Window->pollEvent(Event)) {
		//기능 구현
		switch (Event.type) {
		case Event::Closed:
			this->Window->close();
			break;
		case Event::KeyPressed:
			if (Event.key.code == Keyboard::Escape) 
				this->Window->close();
			break;
		}

	}
}

// 화면 생성
void Game::Render()
{
	// clear
	this->Window->clear(Color(99, 176, 242, 255));

	// Draw Player
	this->Window->draw(this->Player);
	
	// Draw Enemy
	for (int i = 0; i < this->EnemyArray.size(); i++) {
		this->Window->draw(this->EnemyArray[i]);
	}

	// Draw Ball
	for (int i = 0; i < this->Ball.size(); i++) {
		this->Window->draw(this->Ball[i]);
	}

	// Display
	this->Window->display();
}

void Game::Update() {
	this->EventHandler();
	if (this->isAlive) {
		this->UpdatePlayer();
		this->UpdateEnemy();
		this->CollisionCheck();
		this->UpdateBall();
		this->UpdatePointText();
	}
}


//Player
void Game::InitPlayer()
{
	this->Player.setRadius(30.0f);
	this->Player.setFillColor(Color(99, 242, 242, 255));
	this->Player.setPosition
	(
		float(this->Window->getSize().x/2) -30.0f, 
		float(this->Window->getSize().y/2) -30.0f
	);
}

void Game::UpdatePlayer()
{
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		this->Player.move(-1.0f * this->Speed, 0.0f);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		this->Player.move(1.0f * this->Speed, 0.0f);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		this->Player.move(0.0f, -1.0f * this->Speed);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		this->Player.move(0.0f, 1.0f * this->Speed);
	}

}

//Enemy
void Game::InitEnemy()
{
	this->Enemy.setSize(Vector2f(60.0f, 60.0f));
	this->Enemy.setFillColor(Color(242, 133, 133, 255));
}

void Game::InitSpawnValue()
{
	this->Count = 10;
	this->IntervalMax = 20.0f;
	this->IntervalStart = 0.0f;
}

void Game::SpawnEnemy()
{
	this->Enemy.setPosition(
		static_cast<float>(rand()%1280), 
		static_cast<float>((rand() % 720) <= 360 ? 0 : 720)
	);
	this->EnemyArray.push_back(this->Enemy);
}

//void Game::DeleteEnemy() {
//	float Playerx = this->Player.getPosition().x;
//	float Playery = this->Player.getPosition().y;
//
//	for (int i = 0; i < this->EnemyArray.size(); i++) {
//		float Enemyx = this->EnemyArray[i].getPosition().x;
//		float Enemyy = this->EnemyArray[i].getPosition().y;
//
//		if (abs(Playerx - Enemyx) < 60.0f) {
//			if (abs(Playery - Enemyy) < 60.0f) {
//				this->EnemyArray.erase(this->EnemyArray.begin() + i);
//			}
//		}
//	}
//	this->Point++;
//}

void Game::UpdateEnemy()
{
	if (this->EnemyArray.size() < this->Count)
	{
		if (this->IntervalMax <= this->IntervalStart) {
			this->SpawnEnemy();
			this->IntervalStart = 0.0f;
		}
		else {
			this->IntervalStart += 1.0f;
		}
	}

	for (int i = 0; i < this->EnemyArray.size(); i++) {
		this->EnemyArray[i].move(
			(this->Player.getPosition().x - this->EnemyArray[i].getPosition().x) / 300,
			(this->Player.getPosition().y - this->EnemyArray[i].getPosition().y) / 300
		);
	}

	//this->DeleteEnemy();
}

void Game::CollisionCheck()
{

	for (int i = 0; i < this->EnemyArray.size(); i++) {
		if (this->Player.getGlobalBounds().intersects(this->EnemyArray[i].getGlobalBounds())) {
			this->isAlive = false;
		}
	}
}

void Game::InitGun()
{
	this->Gun.setRadius(10.0f);
	this->Gun.setFillColor(Color(160, 242, 102, 255));
	this->Gun.setPosition(this->Player.getPosition());
}

void Game::InitBallSpawn()
{
	this->BallMax = 100;
	this->BallTimeMax = 5.0f;
	this->BallTimeStart = 0.0f;
}

void Game::ShootGun()
{
	this->Gun.setPosition(this->Player.getPosition());
	this->Ball.push_back(this->Gun);
}

void Game::UpdateBall()
{
	if (this->Ball.size() < this->BallMax)
	{
		if (this->BallTimeMax <= this->BallTimeStart) {
			this->ShootGun();
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				this->Position.push_back(Vector2f(-10.0f, 0.0f));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				this->Position.push_back(Vector2f(10.0f, 0.0f));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				this->Position.push_back(Vector2f(0.0f, -10.0f));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				this->Position.push_back(Vector2f(0.0f, 10.0f));
			}
			else
			{
				if (Position.size() == 0) {
					this->Position.push_back(Vector2f(0.0f, 10.0f));
				}
				else {
					this->Position.push_back(Position[Position.size() - 1]);
				}
			}
			this->BallTimeStart = 0.0f;
		}
		else {
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				this->Position[Position.size() - 1] = (Vector2f(-10.0f, 0.0f));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				this->Position[Position.size() - 1] = (Vector2f(10.0f, 0.0f));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				this->Position[Position.size() - 1] = (Vector2f(0.0f, -10.0f));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				this->Position[Position.size() - 1] = (Vector2f(0.0f, 10.0f));
			}
			this->BallTimeStart += 1.0f;
		}
	}


	for (int i = 0; i < this->Position.size(); i++) {
		this->Ball[i].move(this->Position[i]);
	}

	for (int i = 0; i < this->Ball.size(); i++) 
	{
		if (Ball[i].getPosition().x > 1400 || Ball[i].getPosition().x < -100
			|| Ball[i].getPosition().y > 850 || Ball[i].getPosition().y < -100)
		{
			this->Ball.erase(this->Ball.begin() + i);
			this->Position.erase(this->Position.begin() + i);
		}

		for (int j = 0; j < this->EnemyArray.size(); j++) {
			if (this->Ball[i].getGlobalBounds().intersects(this->EnemyArray[j].getGlobalBounds())) {
				this->Ball.erase(this->Ball.begin() + i);
				this->Position.erase(this->Position.begin() + i);
				this->EnemyArray.erase(this->EnemyArray.begin() + j);
				break;
			}
		}
	}
}

//Font
void Game::InitFont()
{
	if (this->Font.loadFromFile("")) {
		cout << "Load Complete" << endl;
	}
	else {
		cout << "Load Fail" << endl;
	}
}

//Text
void Game::InitPointText()
{

}

void Game::UpdatePointText()
{
	
}