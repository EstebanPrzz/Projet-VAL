#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "classe.h"
#include <thread>
#include <vector>

using namespace std;
using namespace sf;



int main() {
	//création de la fênetre
	rame metro(0, 0, 0);
	rame metro2(0, 0, 0);
	rame* liste_rame[3] = { &metro,&metro2 };
	station b(600, 403, 'voit');
	station c(603, 403, 'abc');
	station d(800, 400, 'aaa');
	station* liste_station[3] = { &b,&c,&d };
	int taille_liste = sizeof(liste_station) / sizeof(liste_station[0]);
	int taille_rame = sizeof(liste_rame) / sizeof(liste_station[0]);

	const Vector2u WINDOW_SIZE(1200, 800);
	RenderWindow app(VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y, 32), "My Camera");
	


	thread thread_metro(update_all, ref(liste_station), ref(taille_liste), ref(metro));
	thread thread_metro2(update_all, ref(liste_station), ref(taille_liste), ref(metro2));
	thread thread_initapp(init_app, ref(liste_station), ref(taille_liste), ref(liste_rame), ref(taille_rame), &app);

	thread_metro.join();
	thread_metro2.join();
	thread_initapp.join();


}