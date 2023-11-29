#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Projet VAL.h"

using namespace std;
using namespace sf;

#ifdef _MSC_VER 
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#define _PATH_IMG_ "C:/Program Files/SFML/img/"
#else
#define _PATH_IMG_ "../img/"
#endif

const std::string path_image(_PATH_IMG_);


int main() {
	const Vector2u WINDOW_SIZE(1200, 900);
	RenderWindow app(VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y, 32), "My Camera");
	app.setFramerateLimit(60);

	// Fond d'écran
	Texture backgroundImage, metroImage, stationImage;
	Sprite backgroundSprite, metroSprite, stationSprite;

	if (!backgroundImage.loadFromFile(path_image + "background1200.jpg") ||
		!metroImage.loadFromFile(path_image + "metro.png") ||!stationImage.loadFromFile(path_image+"station.png")){
		cerr << "Erreur pendant le chargement des images" << endl;
		return EXIT_FAILURE; // On ferme le programme
	}

	backgroundSprite.setTexture(backgroundImage);
	metroSprite.setTexture(metroImage);
	stationSprite.setTexture(stationImage);
	


	rame metro(300,400,5);
	station test(320, 450,'test');

	Vector2f center(0, 0);
	Vector2f halfSize(WINDOW_SIZE.x / 2.f, WINDOW_SIZE.y / 2.f);
	View view(center, halfSize);
	app.setView(view);

	metroSprite.setPosition(sf::Vector2f(20, 34));
	metroSprite.setScale(sf::Vector2f(0.2, 0.2));

	stationSprite.setPosition(sf::Vector2f(20, 34));
	stationSprite.setScale(sf::Vector2f(0.2, 0.2));



	while (app.isOpen()) // Boucle principale
	{
		Event event;
		while (app.pollEvent(event)) // Boucle des évènements de la partie pause
		{
			if ((event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || event.type == Event::Closed)
			{
				app.close();
			}
		}

		view.setCenter(halfSize);
		app.setView(view);

		app.clear();
		app.draw(backgroundSprite);
		stationSprite.setPosition(test.get_x(), test.get_y());
		app.draw(stationSprite);

		metroSprite.setPosition(metro.get_x(), metro.get_y());
		app.draw(metroSprite);

		app.display();
	}

	return EXIT_SUCCESS;
}
