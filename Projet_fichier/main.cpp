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
	rame metro(650, 600, 5);
	rame metro2(650, 600, 3);
	rame* liste_rame[2] = { &metro,&metro2 };
	station b(650, 600, 'voit');
	station c(1200, 600, 'abc');
	station d(930, 320, 'aaa');
	//station e(1130, 420, 'aba');
	station* liste_station[3] = { &b,&c,&d };
	int taille_liste = sizeof(liste_station) / sizeof(liste_station[0]);
	int taille_rame = sizeof(liste_rame) / sizeof(liste_station[0]);

	


	thread thread_metro(update_all, ref(liste_station), ref(taille_liste), ref(metro));
	thread thread_initapp(init_app, ref(liste_station), ref(taille_liste),ref (liste_rame), ref(taille_rame));
	thread update_all_stations(update_passanger_station, liste_station, taille_liste);
	_sleep(1000);
	thread thread_metro2(update_all, ref(liste_station), ref(taille_liste), ref(metro2));

	update_all_stations.join();
	thread_initapp.join();
	thread_metro.join();
	thread_metro2.join();



}