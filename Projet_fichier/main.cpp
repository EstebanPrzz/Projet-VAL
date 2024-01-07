#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "classe.h"
#include <thread>
#include <vector>

using namespace std;


int main() {

	rame a(0,0,0);
	rame nouvelle_rame(0,0,0);
	station b(0, 0, 'voit');
	station c(1100, 100, 'abc');
	station d(220, 200, 'aaa');
	station *liste_station[3] = {&b,&c,&d};
	int taille_liste = sizeof(liste_station) / sizeof(liste_station[0]);

	thread thread_a(update_all, liste_station, taille_liste, a);
	thread thread_nouvelle_rame(update_all, liste_station, taille_liste, nouvelle_rame);

	//à partir d'ici tout change en fonction de quelles stations on veut être (donc dans la boucle)
	for (int i = 0; i < 1; i++) {
		thread_a.join();
		thread_nouvelle_rame.join();
	}
}
