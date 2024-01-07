// Projet VAL.h : fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets.

#pragma once

#include <iostream>
#include <vector>

struct Rail {
	float x, y;
};

class station {
private:
	char name;
	int passanger;
	int x;
	int y;
	bool rame_present; // Permet de savoir si la rame est présente ou non au niveau de la station
	bool ready; // Permet de savoir si on peut envoyer ou non la rame 
public:

	station(int posx, int posy, char nom) {
		name = nom;
		passanger = 0;
		x = posx;
		y = posy;
		rame_present = false;
		ready = false;
	}


	//Getters
	int get_x();
	int get_y();
	int get_passanger();
	char get_name();

	//Setters
	void set_passanger(int nb);

	//Méthode d'instance à instaurer
	/*void update_passanger();*/ //permet juste de changer le nombre de passagers
	int distance(station a);
	int distance_x(station a);
	int distance_y(station a);
};


class rame {
private:
		int number;
		float speed; // vitesse en km/h
		float x;
		float y;
		int passanger;
public:
	rame(float posx, float posy,int num) {
		number = num;
		speed = 0;
		x = posx;
		y = posy;
		passanger = 0;
	}

	//Getters
	int get_number();
	float get_speed();
	float get_x();
	float get_y();
	int get_passanger();

	//Setters
	void set_speed(float s);
	void set_position(float x, float y);
	void set_passanger(int nb);

	//Méthode d'instance à instaurer 
	/*rame distance(get(x),get(y),station); //Comment savoir qu'elle station c'est?*/
	void update_pos(int distance, float x, float y);
	void update_vitesse(int distance); //Fonction qui update la vitesse en fonction de la distance
	int distance_parcourir(int vitesse); // Permet de savoir la distance que va parcourire le train à une vitesse donnée
	void move(const int &vx, const int &vy);
	int is_on_rail(std::vector<Rail>& rails);
};




	//superviseur(int posx, int posy, char nom, int ramePosx, int ramePosy, int rameNum) {
	//}

// TODO: Référencez ici les en-têtes supplémentaires nécessaires à votre programme.;
