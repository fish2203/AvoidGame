#include "Game.h"

// ������ �ʱ�ȭ �� ����
Game::Game()
{
	// ������ �ʱ�ȭ �� ����
	this->InitWindowPointer();
	this->InitWindow();

	// Player �ʱ�ȭ
	this->InitPlayer();
}

// ������ ����
Game::~Game()
{
	this->DeleteWindow();
}

// ������ ���� �ʱ�ȭ
void Game::InitWindowPointer()
{
	this->Window = nullptr;
}

// ������ ���� ����,
void Game::InitWindow()
{
	this->Window = new RenderWindow(VideoMode(1280, 720), "Avoid Game", Style::Titlebar | Style::Close);
}

// ������ �޸𸮿��� ����
void Game::DeleteWindow()
{
	delete this->Window;
}

// �����찡 ���������� üũ
bool Game::Running() const
{
	return this->Window->isOpen();
}

// �̺�Ʈ ó��
void Game::EventHandler()
{
	while (this->Window->pollEvent(Event)) {
		//��� ����
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

// ȭ�� ����
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