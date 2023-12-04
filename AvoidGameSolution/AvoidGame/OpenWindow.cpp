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

	// ������ â�� ������ �� ���α׷��� ������� �ʰ� �����
	while(Window.isOpen()){
		while (Window.pollEvent(Event)) {
			//��� ����
			switch (Event.type) {
				case Event::Closed:
					Window.close();
					break;
				case Event::KeyPressed:
					if(Event.key.code == Keyboard::Escape) Window.close();
					break;
			}
			
		}

		//��ĥ�ϱ�
		Window.clear(Color(30, 155, 90, 255));
		Window.display();
	}

}