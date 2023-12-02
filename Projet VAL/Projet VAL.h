// Projet VAL.h : fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets.

#pragma once

#include <iostream>
#include <vector>

struct Rail {
	float x, y;
};

class rame {
private:
		int number;
		int speed;
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
	int get_speed();
	int get_x();
	int get_y();
	int get_passanger();

	//Setters
	void set_speed(int s);
	void set_position(int x, int y);
	void set_passanger(int nb);

	//Méthode d'instance à instaurer 
	/*rame distance(get(x),get(y),station); //Comment savoir qu'elle station c'est?
	void update_vitesse(distance()); // ça c'est à la fin
	void update_pos();*/ //Tout les x temps on update sa position
	void speedUp();
	void speedDown();
	void move();
	int is_on_rail(std::vector<Rail>& rails);
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
	
	//Setters
	void set_passanger(int nb);

	//Méthode d'instance à instaurer
	/*void update_passanger();*/ //permet juste de changer le nombre de passagers

};



	//superviseur(int posx, int posy, char nom, int ramePosx, int ramePosy, int rameNum) {
	//}

// TODO: Référencez ici les en-têtes supplémentaires nécessaires à votre programme.;
