﻿// Projet VAL.cpp : définit le point d'entrée de l'application.
//

#include "classe.h" // Projet qui a les déf de mes classes
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

#pragma once
using namespace std;
using namespace sf;


#ifdef _MSC_VER 
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#define _PATH_IMG_ "C:/Program Files/SFML/img/"
#else
#define _PATH_IMG_ "../img/"
#endif

const sf::Vector2u WINDOW_SIZE(1200, 800); // Define WINDOW_SIZE here



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

void rame::update_passanger(station &a) {
    srand(time(0));
    int nb_aleatoire = rand() %10;
    if (this->passanger <= nb_aleatoire) { //Si tous les passagers sortes
        this->passanger = 0;
    }
    else { // Sinon on enlève que ceux qui sortent
        this->passanger -= nb_aleatoire;
    }
    if (this->passanger + a.get_passanger() <= 10) { //Si il y'a assez de place pour les passagers
        this->passanger += a.get_passanger();
    }
    else { // Sinon on en prend le plus possible et on laisse les autres sur le banc
        int nb_places = 10 - this->passanger;
        this->passanger = 10;
        a.add_passanger(-nb_places);
    }
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
int station::get_passanger(){
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

void station::update_passanger() {
    srand(time(0));
    this->passanger += rand() % 10;
}

void station::add_passanger(int nb_passanger) {
    this->passanger += nb_passanger;
}


//Def fonction autre
void update_all(station* liste[], int taille_liste, rame& a) {
    int distance_entre_stations = 0;
    int distance_entre_stations_x = 0;
    int distance_entre_stations_y = 0;
    int distance = 0;
    int actuelle = 0;
    Texture metroImage;
    Sprite metroSprite;
    metroSprite.setTexture(metroImage);
    if (!metroImage.loadFromFile(path_image)) {
        cerr << "Erreur pendant le chargement des images" << endl;
    }
    metroSprite.setScale(sf::Vector2f(0.02, 0.02));
    
    while (true) {
        for (int i = 0; i < 2 * (taille_liste - 1); i++) {// ligne compliqué juste pour dire que je fais toutes les stations
            int b = 0;
            if (i < (taille_liste - 1)) { // ici chemin de l'aller 
                distance_entre_stations = liste[i]->distance(*liste[i + 1]);
                distance_entre_stations_x = liste[i]->distance_x(*liste[i + 1]);
                distance_entre_stations_y = liste[i]->distance_y(*liste[i + 1]);
                distance = liste[i]->distance(*liste[i + 1]);
                a.update_passanger(*liste[i]);
            }
            else { // ici s'occupe du chemin retour soit quand le i est suppérieur à i-1 taille du tab
                actuelle = i - (i + 1 - (taille_liste)) * 2;//calcul de golmon imcompréhensible
                distance_entre_stations = liste[actuelle]->distance(*liste[actuelle - 1]);
                distance_entre_stations_x = liste[actuelle]->distance_x(*liste[actuelle - 1]);
                distance_entre_stations_y = liste[actuelle]->distance_y(*liste[actuelle - 1]);
                distance = liste[actuelle]->distance(*liste[actuelle - 1]);
                a.update_passanger(*liste[actuelle]);
            }
            while (distance) { // Boucle qui s'occupe de gerer le train sur une distance entre deux stations
                a.update_vitesse(distance);
                distance -= a.get_speed() * 3.6;
                a.update_pos(distance_entre_stations, distance_entre_stations_x, distance_entre_stations_y);
                
            }
            a.set_speed(0);// ligne qui permet de réinitialiser la vitesse qui bug
            a.set_position(round(a.get_x()), round(a.get_y()));
        }
    }
}

void init_app(station *liste[], int taille_liste, rame *liste_rame[], int taille_rame, sf::RenderWindow* app) {
    
    app->setFramerateLimit(60);

    // initialisation des sprites
    Texture backgroundImage, metroImage, stationImage, railImage;
    Sprite backgroundSprite, stationSprite, railSprite;
    

    if (!backgroundImage.loadFromFile(path_image + "background1200.jpg") ||
        !metroImage.loadFromFile(path_image + "test.png") || !stationImage.loadFromFile(path_image + "station.png") || !railImage.loadFromFile(path_image + "rail1.png")) {
        cerr << "Erreur pendant le chargement des images" << endl;
       
    }


    sf::Font font;
    if (!font.loadFromFile("C:/Users/Admin/source/repos/EstebanPrzz/Projet-VAL/arial.ttf")) {
        cerr << "Erreur lors du chargement de la police" << endl;
    }
    sf::Text indexText;
    indexText.setFont(font);
    indexText.setCharacterSize(24);
    indexText.setFillColor(sf::Color::White);

    backgroundSprite.setTexture(backgroundImage);
    
    stationSprite.setTexture(stationImage);
    railSprite.setTexture(railImage);

    std::vector<Rail> rails;

    Vector2f center(0, 0);
    Vector2f halfSize(WINDOW_SIZE.x / 2.f, WINDOW_SIZE.y / 2.f);
    View view(center, halfSize);
    app->setView(view);
    
    stationSprite.setScale(sf::Vector2f(0.2, 0.2));
    railSprite.setScale(sf::Vector2f(2, 2));





    //à partir d'ici tout change en fonction de quelles stations on veut être (donc dans la boucle)
    while (app->isOpen()) // Boucle principale
    {
        Event event;
        while (app->pollEvent(event)) // Boucle des évènements de la partie pause
        {
            if ((event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || event.type == Event::Closed)
            {
                app->close();
            }
        }
        // Réglage de la caméra
        view.setCenter(halfSize);
        app->setView(view);
        // Affichage
        app->clear();
        // background
        app->draw(backgroundSprite);
        
        for (int i = 0;i < taille_liste;i++) {
            stationSprite.setPosition(liste[i]->get_x(), liste[i]->get_y());
            FloatRect Sbounds = stationSprite.getLocalBounds();
            stationSprite.setOrigin(Sbounds.width / 2, Sbounds.height / 2);
            app->draw(stationSprite);
        }
        

        /*indexText.setString("position x de la station 2: " + to_string(liste[1]->get_x()));
        indexText.setPosition(500, 400); // Position du texte sur l'écran
        // Afficher le texte à l'écran
        app->draw(indexText);*/


        app->display();// soucis juste ici quanbd 
    }
}



