#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Projet VAL.h"
#include <vector>

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

	// Fond d'�cran
	Texture backgroundImage, metroImage, stationImage, railImage;
	Sprite backgroundSprite, metroSprite, stationSprite, railSprite;

	if (!backgroundImage.loadFromFile(path_image + "background1200.jpg") ||
		!metroImage.loadFromFile(path_image + "metro2.png") ||!stationImage.loadFromFile(path_image+"station.png") || !railImage.loadFromFile(path_image + "rail.png")){
		cerr << "Erreur pendant le chargement des images" << endl;
		return EXIT_FAILURE; // On ferme le programme
	}

	backgroundSprite.setTexture(backgroundImage);
	metroSprite.setTexture(metroImage);
	stationSprite.setTexture(stationImage);
	railSprite.setTexture(railImage);

	std::vector<Rail> rails;
	rails.push_back({ 600, 400 });
	rails.push_back({ 600, 375 });
	rails.push_back({ 600, 350 });
	rame metro(500,400,5);
	station test(320, 450,'test');

	Vector2f center(0, 0);
	Vector2f halfSize(WINDOW_SIZE.x / 2.f, WINDOW_SIZE.y / 2.f);
	View view(center, halfSize);
	app.setView(view);

	metroSprite.setPosition(sf::Vector2f(500, 400));
	metroSprite.setScale(sf::Vector2f(2, 2));

	stationSprite.setPosition(sf::Vector2f(20, 34));
	stationSprite.setScale(sf::Vector2f(0.2, 0.2));

	railSprite.setScale(sf::Vector2f(2, 2));

	while (app.isOpen()) // Boucle principale
	{
		Event event;
		while (app.pollEvent(event)) // Boucle des �v�nements de la partie pause
		{
			if ((event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || event.type == Event::Closed)
			{
				app.close();
			}
		}
		// R�glage de la cam�ra
		view.setCenter(halfSize);
		app.setView(view);
		int index = metro.is_on_rail(rails);
		if (metro.get_x() <= rails[index+2].x) {
			metro.move();
		}


		// Affichage
		app.clear();
		// background
		app.draw(backgroundSprite);
		// Station
		app.draw(stationSprite);
		stationSprite.setPosition(test.get_x(), test.get_y());
		// Rame
		app.draw(metroSprite);
		metroSprite.setPosition(metro.get_x(), metro.get_y());

		// affichage rail
		for (const Rail& rail : rails) {
			railSprite.setPosition(rail.x, rail.y);
			app.draw(railSprite);
		}


		app.display();
	}

	return EXIT_SUCCESS;
}
