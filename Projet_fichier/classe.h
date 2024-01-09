// Projet VAL.h : fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets.

#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>


struct Rail {
public:
	float x, y;
	Rail(int xCoord, int yCoord) : x(xCoord), y(yCoord) {}
};

class station {
private:
	char name;
	int passanger;
	int x;
	int y;
	bool rame_present;
public:

	station(int posx, int posy, char nom) {
		name = nom;
		passanger = 0;
		x = posx;
		y = posy;
		rame_present = false;
	}


	//Getters
	int get_x();
	int get_y();
	int get_passanger();
	char get_name();
	bool get_rame_present();

	//Setters
	void set_passanger(int nb);
	void set_rame_present(bool valeur);

	//Méthode d'instance à instaurer
	void add_passanger(int nb_passanger);
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
		bool arret_urgence; 
		double angle;
public:
	rame(float posx, float posy, int num) {
		number = num;
		speed = 0;
		x = posx;
		y = posy;
		passanger = 0;
		arret_urgence = false;
		angle = 0;
	}

	//Getters
	int get_number();
	float get_speed();
	float get_x();
	float get_y();
	int get_passanger();
	bool get_arret_urgence();
	double get_angle();

	//Setters
	void set_speed(float s);
	void set_position(float x, float y);
	void set_passanger(int nb);
	void set_arret_urgence(bool valeur);
	void set_angle(double agl);

	//Méthode d'instance à instaurer 
	void update_pos(int distance, float x, float y);
	void update_vitesse(int distance); //Fonction qui update la vitesse en fonction de la distance
	int distance_parcourir(int vitesse); // Permet de savoir la distance que va parcourire le train à une vitesse donnée
	void move(const int &vx, const int &vy);
	int is_on_rail(std::vector<Rail>& rails);
	void update_passanger(station &a);
};

//Fonction globale
void update_all(station *liste[], int taille_liste,rame &a);
void update_passanger_station(station* liste[], int taille_liste);
	//superviseur(int posx, int posy, char nom, int ramePosx, int ramePosy, int rameNum) {
	//}
// TODO: Référencez ici les en-têtes supplémentaires nécessaires à votre programme.;

void init_app(station *liste[], int taille_liste, rame* liste_rame[], int taille_rame);