#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "classe.h"
#include <thread>
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
	//création de la fênetre
	const Vector2u WINDOW_SIZE(1200, 800);
	RenderWindow app(VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y, 32), "My Camera");
	app.setFramerateLimit(60);

	sf::Font font;
	if (!font.loadFromFile("C:/Users/Admin/source/repos/EstebanPrzz/Projet-VAL/arial.ttf")) {
		cerr << "Erreur lors du chargement de la police" << endl;
		return EXIT_FAILURE;
	}

	// initialisation des sprites
	Texture backgroundImage, metroImage, stationImage, railImage;
	Sprite backgroundSprite, stationSprite, railSprite;
	Sprite metroSprite1, metroSprite2;

	if (!backgroundImage.loadFromFile(path_image + "background1200.jpg") ||
		!metroImage.loadFromFile(path_image + "test.png") || !stationImage.loadFromFile(path_image + "station.png") || !railImage.loadFromFile(path_image + "rail1.png")) {
		cerr << "Erreur pendant le chargement des images" << endl;
		return EXIT_FAILURE;
	}

	backgroundSprite.setTexture(backgroundImage);
	metroSprite1.setTexture(metroImage);
	metroSprite2.setTexture(metroImage);
	stationSprite.setTexture(stationImage);
	railSprite.setTexture(railImage);

	std::vector<Rail> rails;

	Vector2f center(0, 0);
	Vector2f halfSize(WINDOW_SIZE.x / 2.f, WINDOW_SIZE.y / 2.f);
	View view(center, halfSize);
	app.setView(view);
	metroSprite1.setScale(sf::Vector2f(0.02, 0.02));
	metroSprite2.setScale(sf::Vector2f(0.02, 0.02));
	stationSprite.setScale(sf::Vector2f(0.2, 0.2));
	railSprite.setScale(sf::Vector2f(2, 2));

	FloatRect M1bounds = metroSprite1.getLocalBounds();
	FloatRect M2bounds = metroSprite2.getLocalBounds();
	metroSprite1.setOrigin(M1bounds.width / 2, M1bounds.height / 2);
	metroSprite2.setOrigin(M2bounds.width / 2, M2bounds.height / 2);

	FloatRect Sbounds = stationSprite.getLocalBounds();
	stationSprite.setOrigin(Sbounds.width / 2, Sbounds.height / 2);
	stationSprite.setRotation(90);

	rame metro(0,0,0);
	rame metro2(0,0,0);
	station b(0, 0, 'voit');
	station c(1100, 100, 'abc');
	station d(220, 200, 'aaa');
	station *liste_station[3] = {&b,&c,&d} ;
	int taille_liste = sizeof(liste_station) / sizeof(liste_station[0]);

	thread thread_a(update_all, liste_station, taille_liste, metro);
	thread thread_nouvelle_rame(update_all, liste_station, taille_liste, metro2);

	//à partir d'ici tout change en fonction de quelles stations on veut être (donc dans la boucle)
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
		// Réglage de la caméra
		view.setCenter(halfSize);
		app.setView(view);
		// Affichage
		app.clear();
		// background
		app.draw(backgroundSprite);


		thread_a.join();
		thread_nouvelle_rame.join();

		app.display();
	}
	return EXIT_SUCCESS;
}
