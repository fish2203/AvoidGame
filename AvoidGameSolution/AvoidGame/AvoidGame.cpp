#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Game.h"

int main()
{
	// Random value start : First Setup
	// use Time value : Change First Setup every starting
	srand(time(NULL));

	// start up
	Game Avoid;

	//Game Loop
	while (Avoid.Running()) {
		//Update
		Avoid.Update();

		//Render
		Avoid.Render();
	}
}
