// Projet VAL.cpp : définit le point d'entrée de l'application.
//

#include "Projet VAL.h" // Projet qui a les déf de mes classes
#include <vector>


// Def des fonctions de la rame
int rame::get_number() {
	return this->number;
}

int rame::get_speed() {
	return this->speed;
}

int rame::get_passanger() {
	return this->passanger;
}

int rame::get_x() {
	return this->x;
}

int rame::get_y() {
	return this->y;
}

void rame::set_speed(int s) {
	this->speed = s;
}
void rame::set_position(int x, int y) {
	this->x = x;
	this->y = y;
}
void rame::set_passanger(int nb) {
	this->passanger = nb;
}

void rame::move() {
	x += (0,1);
	y += (0);
}

void
rame::speedUp()
{
	if (speed < 3.f)
		speed += 0.05f;
}

void
rame::speedDown()
{
	if (speed > 0.f)
		speed -= 0.05f;
	else
		speed = 0;
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

	// Si la rame n'est sur aucun rail
	return -1;
}
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

//Setters
void station::set_passanger(int nb) {
	this->passanger = nb;
}

//Def fonction superviseurs

