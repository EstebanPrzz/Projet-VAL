#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "classe.h"
#include <vector>

using namespace std;


int main() {

	rame a(0,0,0);
	station b(0, 0, 'voit');
	station c(1100, 100, 'abc');
	station d(220, 200, 'aaa');
	station liste_station[3] = {b,c,d};

	//truc qui doivent �tre absolument pr�d�fini avant la boucle principale
	int distance_entre_stations = 0;
	int distance_entre_stations_x = 0;
	int distance_entre_stations_y = 0;
	int distance = 0;
	int actuelle = 0;
	int taille_liste = (sizeof(liste_station) / sizeof(station));

	//� partir d'ici tout change en fonction de quelles stations on veut �tre (donc dans la boucle)
	while (true){
		for (int i = 0; i < 2 * (taille_liste - 1); i++) {// ligne compliqu� juste pour dire que je fais toutes les stations
			if (i < (taille_liste - 1)) { // ici chemin de l'aller 
				distance_entre_stations = liste_station[i].distance(liste_station[i + 1]);
				distance_entre_stations_x = liste_station[i].distance_x(liste_station[i + 1]);
				distance_entre_stations_y = liste_station[i].distance_y(liste_station[i + 1]);
				distance = liste_station[i].distance(liste_station[i + 1]);
			}
			else{ // ici s'occupe du chemin retour soit quand le i est supp�rieur � i-1 taille du tab
				actuelle = i - (i + 1 - (taille_liste)) * 2;//calcul de golmon imcompr�hensible
				distance_entre_stations = liste_station[actuelle].distance(liste_station[actuelle - 1]);
				distance_entre_stations_x = liste_station[actuelle].distance_x(liste_station[actuelle - 1]);
				distance_entre_stations_y = liste_station[actuelle].distance_y(liste_station[actuelle - 1]);
				distance = liste_station[actuelle].distance(liste_station[actuelle - 1]);;
			}
			while (distance) { // Boucle qui s'occupe de gerer le train sur une distance entre deux stations
				a.update_vitesse(distance);
				distance -= a.get_speed() * 3.6;
				a.update_pos(distance_entre_stations, distance_entre_stations_x, distance_entre_stations_y);
			 }
			a.set_speed(0);// ligne qui permet de r�initialiser la vitesse qui bug
			cout << "Le train est arriv� � la gare :"; // probl�me � voir avec EDGAR je sais pas utiliser un char
			cout << liste_station[i+1].get_name() <<endl;
			printf("%c", liste_station[i + 1].get_name());
		}
	}
}
