#include "Game.h"

// 윈도우 초기화 및 생성
Game::Game()
{
	// 윈도우 초기화 및 생성
	this->InitWindowPointer();
	this->InitWindow();

	// Player 초기화
	this->InitPlayer();
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
	this->Window->clear(Color(30, 155, 90, 255));

	// Draw
	this->Window->draw(this->Player);

	// Display
	this->Window->display();
}


//Player
void Game::InitPlayer()
{
	this->Player.setRadius(50.0f);
	this->Player.setFillColor(Color(100, 30, 130, 255));
	this->Player.setPosition(100, 100);
}