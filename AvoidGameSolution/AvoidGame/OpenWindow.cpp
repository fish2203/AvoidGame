#include "OpenWindow.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace sf;

void OpenWindow() {
	RenderWindow Window(VideoMode(1280,720), "Avoid Game", Style::Titlebar | Style::Close);

	Event Event;

	// 윈도우 창이 떠있을 때 프로그램이 종료되지 않게 만들기
	while(Window.isOpen()){
		while (Window.pollEvent(Event)) {
			//기능 구현
			switch (Event.type) {
				case Event::Closed:
					Window.close();
					break;
				case Event::KeyPressed:
					if(Event.key.code == Keyboard::Escape) Window.close();
					break;
			}
			
		}

		//색칠하기
		Window.clear(Color(30, 155, 90, 255));
		Window.display();
	}

}