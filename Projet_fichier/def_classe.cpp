// Projet VAL.cpp : définit le point d'entrée de l'application.
//

#include "classe.h" // Projet qui a les déf de mes classes
#include <vector>
#include <math.h>
#pragma once


// Def des fonctions de la rame
int rame::get_number() {
	return this->number;
}

float rame::get_speed() {
	return this->speed;
}

int rame::get_passanger() {
	return this->passanger;
}

float rame::get_x() {
	return this->x;
}

float rame::get_y() {
	return this->y;
}

void rame::set_speed(float s) {
	this->speed = s;
}
void rame::set_position(float x, float y) {
	this->x = x;
	this->y = y;
}
void rame::set_passanger(int nb) {
	this->passanger = nb;
}

void rame::move(const int &vx,const int &vy) {
	x += vx;
	y += vy;
}

int rame::distance_parcourir(int vitesse) {
    int distance = 0;
    int i = vitesse;
    while (i > 0) {
        distance += i * 3.6;
        i -= 5;
    }
    return(distance);
}

void rame::update_vitesse(int distance) { // s'est déjà déplacé plus qu'à actualiser sa vitesse 
    if (distance - this->distance_parcourir(this->speed) - (this->speed * 3.6) <= (this->speed * 3.6)) {// Tant que l'écart et inférieur à une étape
        if (this->speed <= 5) {//phase ou le train arrive devant la fin
            if (this->speed != 0) {
                this->speed = distance / 3.6;
            }
        }
        else if (distance < this->distance_parcourir(this->speed)) { //
            this->speed -= 5;
        }
    }
    else if(distance > this->distance_parcourir(this->speed)) { // phase d'accélération
        if (this->speed < 80) { // limite de vitesse à 80 km/h
            this->speed += 5; // le train accélère 5km/h par 5km/h
        }
    }
}

void rame::update_pos(int distance, float x, float y) { // distance entre deux stations
    float distance_parcouru = this->speed * 3.6; // Je prend la distance que mon vehicule parcours en une seconde
    float rapport = distance_parcouru / distance; // je prend le rapport de la distance parcouru sur la distance totale
    this->x += rapport * x; // D'après thalès si distance parcouru = 1/10 alors je prend 1/10 de x total
    this->y += rapport * y;
}

int rame::is_on_rail(std::vector<Rail>& rails) {
    // On regarde chaque rail installé
    for (size_t i = 0; i < rails.size(); ++i) {
        const Rail& rail = rails[i];

        // On analyse la position de la rame en fonction de la positions des rails 
        if ((this->get_x() >= rail.x && this->get_x() <= rail.x + 1) && (this->get_y() >= rail.y && this->get_y() <= rail.y + 1)) {
            // renvoie l'index du rail dans le tableau de position des Sprites
            return static_cast<int>(i);
        }
    }

    // Si la rame n'est sur aucun rail, on renvoie l'index du rail le plus proche
    int closestIndex = 0;
    float closestDistance = std::numeric_limits<float>::max();

    for (size_t i = 0; i < rails.size(); ++i) {
        const Rail& rail = rails[i];
        float distance = std::abs(this->get_x() - rail.x) + std::abs(this->get_y() - rail.y);

        if (distance < closestDistance) {
            closestDistance = distance;
            closestIndex = static_cast<int>(i);
        }
    }

    return closestIndex;
}


/*rame distance(get(x), get(y), station); //Comment savoir qu'elle station c'est?
void update_vitesse(distance()); // ça c'est à la fin
void update_pos(); */ //Tout les x temps on update sa position


//Def des fonctions de la station

//Getters
int station::get_x() {
	return this->x;
}
int station::get_y() {
	return this->y;
}
int station::get_passanger() {
	return this->passanger;
}

char station::get_name() {
    return this->name;
}

//Setters
void station::set_passanger(int nb) {
	this->passanger = nb;
}

int station::distance(station a) { //Distance la plus rapide entre les deux stations
    return 10 * (sqrt(pow(a.get_x() - this->get_x(), 2) + pow(a.get_y() - this->get_y(), 2)));
    // facteur 10 parce que distance mettre à pixel 
}

int station::distance_x(station a) {
    return a.get_x() - this->get_x();
}

int station::distance_y(station a) {
    return a.get_y() - this->get_y();
}


//Def fonction superviseurs

