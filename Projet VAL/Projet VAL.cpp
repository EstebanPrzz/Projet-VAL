// Projet VAL.cpp : définit le point d'entrée de l'application.
//

#include "Projet VAL.h" // Projet qui a les déf de mes classes
#include "rame.c" // Projet qui s'occupe de tout exécuter
#pragma once
using namespace std;


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
