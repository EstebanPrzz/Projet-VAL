// Projet VAL.cpp : définit le point d'entrée de l'application.
//

#include "classe.h" // Projet qui a les déf de mes classes
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#pragma once
using namespace std;
using namespace sf;


#ifdef _MSC_VER 
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#define _PATH_IMG_ "C:/Program Files/SFML/img/"
#else
#define _PATH_IMG_ "../img/"
#endif

const std::string path_image(_PATH_IMG_);
const sf::Vector2u WINDOW_SIZE(1920, 1080); // Define WINDOW_SIZE here
const float RAIL_THICKNESS = 2.0f;



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

bool rame::get_arret_urgence() {
    return this->arret_urgence;
}

double rame::get_angle() {
    return this->angle;
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

void rame::set_arret_urgence(bool valeur) {
    this->arret_urgence = valeur;
}

void rame::set_angle(double agl) {
    this->angle = agl;
}

void rame::update_passanger(station &a) {
    srand(time(0));
    int nb_aleatoire = rand() %20;
    if (this->passanger <= nb_aleatoire) { //Si tous les passagers sortes
        this->passanger = 0;
        _sleep(500);
    }
    else { // Sinon on enlève que ceux qui sortent
        this->passanger -= nb_aleatoire;
        _sleep(50 * nb_aleatoire);
    }
    if (this->passanger + a.get_passanger() <= 20) { //Si il y'a assez de place pour les passagers
        this->passanger += a.get_passanger();
        _sleep(50 * a.get_passanger());
    }
    else { // Sinon on en prend le plus possible et on laisse les autres sur le banc
        int nb_qui_rentre = 20 - this->passanger;
        this->passanger = 20;
        a.add_passanger(-nb_qui_rentre);
        _sleep(50 * nb_qui_rentre);
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

        // On analyse la position de la rame en fonction de la positions des rails i
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

bool station::get_rame_present() {
    return this->rame_present;
}

//Setters
void station::set_passanger(int nb) {
	this->passanger = nb;
}

void station::set_rame_present(bool valeur) {
    this->rame_present = valeur;
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
    int indice = 0;
    
    while (true) {
        for (int i = 0; i < taille_liste; i++) {// ligne compliqué juste pour dire que je fais toutes les stations
            if (i < taille_liste - 1) { // ici chemin de l'aller 
                distance_entre_stations = liste[i]->distance(*liste[i + 1]);
                distance_entre_stations_x = liste[i]->distance_x(*liste[i + 1]);
                distance_entre_stations_y = liste[i]->distance_y(*liste[i + 1]);
                distance = liste[i]->distance(*liste[i + 1]);
                a.update_passanger(*liste[i]);
                liste[i]->set_rame_present(false);
                indice = i + 1;
                a.set_angle(atan2(liste[i]->get_y() - liste[i+1]->get_y(), liste[i]->get_x() - liste[i+1]->get_x()) * (180.0 / M_PI));
            }
            else { // ici s'occupe du chemin retour soit quand le i est suppérieur à i-1 taille du tab
                distance_entre_stations = liste[i]->distance(*liste[0]);
                distance_entre_stations_x = liste[i]->distance_x(*liste[0]);
                distance_entre_stations_y = liste[i]->distance_y(*liste[0]);
                distance = liste[i]->distance(*liste[0]);
                a.update_passanger(*liste[i]);
                liste[i]->set_rame_present(false);
                indice = 0;
                a.set_angle(atan2(liste[i]->get_y() - liste[0]->get_y(), liste[i]->get_x() - liste[0]->get_x()) * (180.0 / M_PI));
            }
            while (distance) { // Boucle qui s'occupe de gerer le train sur une distance entre deux stations
                if (!a.get_arret_urgence()) {
                    a.update_vitesse(distance);
                    distance -= a.get_speed() * 3.6;
                    a.update_pos(distance_entre_stations, distance_entre_stations_x, distance_entre_stations_y);
                    _sleep(50);
                }
                else {
                    if (liste[indice]->get_rame_present()) {
                        if (a.get_speed() >= 40) {
                            while (a.get_speed() >= 10) {
                                a.set_speed(round(a.get_speed() / 2));
                                distance -= a.get_speed() * 3.6;
                                a.update_pos(distance_entre_stations, distance_entre_stations_x, distance_entre_stations_y);
                                _sleep(50);
                            }
                        }
                        else {
                            a.set_speed(0);
                        }
                    }
                    else {
                        a.set_arret_urgence(false);
                    }
                }
                if (liste[indice]->get_rame_present() && distance < (liste[i]->distance(*liste[indice]) / 2)) {
                    printf("%d", distance); // à supprimer
                    a.set_arret_urgence(true);
                }
            }
            a.set_speed(0);// ligne qui permet de réinitialiser la vitesse qui bug
            a.set_position(round(a.get_x()), round(a.get_y()));
            liste[indice]->set_rame_present(true);
        }
    }
}

void update_passanger_station(station* liste[], int taille_liste) {
    srand(time(0));
    while (true) {
        for (int i = 0; i < taille_liste; i++) {
            liste[i]->add_passanger(rand() % 5); //à changer si y'a plus de train
        }
        _sleep(2000);
    }
}

void init_app(station *liste[], int taille_liste, rame * liste_rame[], int taille_rame) {
    
    const Vector2u WINDOW_SIZE(1920, 1080);
    RenderWindow app(VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y, 32), "My Camera");
    app.setFramerateLimit(60);

    // initialisation des sprites
    Texture backgroundImage, metroImage, stationImage, railImage;
    Sprite backgroundSprite, stationSprite, railSprite;
    Sprite metroSprite;
    //CHARGEMENT DES SPRITES
    if (!backgroundImage.loadFromFile(path_image + "background1.png") ||
        !metroImage.loadFromFile(path_image + "metro1.png") || !stationImage.loadFromFile(path_image + "station1.png") || !railImage.loadFromFile(path_image + "rail1.png")) {
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

    //INITIALISATION DES SPRITES
    backgroundSprite.setTexture(backgroundImage);
    metroSprite.setTexture(metroImage);
    stationSprite.setTexture(stationImage);
    railSprite.setTexture(railImage);

    std::vector<Rail> rails;

    Vector2f center(0, 0);
    Vector2f halfSize(WINDOW_SIZE.x / 2.f, WINDOW_SIZE.y / 2.f);
    View view(center, halfSize);
    app.setView(view);
    backgroundSprite.setScale(sf::Vector2f(6.5, 6.5));
    metroSprite.setScale(sf::Vector2f(-0.10, -0.10));
    stationSprite.setScale(sf::Vector2f(0.2, 0.2));
    railSprite.setScale(sf::Vector2f(2, 2));

    FloatRect Sbounds = stationSprite.getLocalBounds();
    stationSprite.setOrigin(Sbounds.width / 2, Sbounds.height / 2);
    FloatRect Mbounds = metroSprite.getLocalBounds();
    metroSprite.setOrigin(Mbounds.width / 2, Mbounds.height / 2);

    int k = 0;



    //à partir d'ici tout change en fonction de quelles stations on veut être (donc dans la boucle)
    while (app.isOpen()) // Boucle principale
    {
        Event event;
        while (app.pollEvent(event)) // Boucle des évènements de la partie pause
        {
            if ((event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || event.type == Event::Closed)
            {
                app.close();
            }

        }
        // Réglage de la caméra
        view.setCenter(halfSize);
        app.setView(view);
        // Affichage
        app.clear();
        // background
        app.draw(backgroundSprite);
        double angle = 0;
        for (int i = 0;i < taille_liste;i++) {
            stationSprite.setPosition(liste[i]->get_x(), liste[i]->get_y());

            app.draw(stationSprite);
        }

        //affichage rails


// Dessiner des lignes (rails) entre les stations
        for (int i = 0; i < taille_liste; i++) {
            // Calculer la position de la ligne (rail) entre deux stations
            sf::Vector2f positionStation1(liste[i]->get_x(), liste[i]->get_y());
            sf::Vector2f positionStation2(liste[(i + 1) % taille_liste]->get_x(), liste[(i + 1) % taille_liste]->get_y());

            // Calculer l'angle entre deux stations
            float angle = atan2(positionStation2.y - positionStation1.y, positionStation2.x - positionStation1.x);

            // Calculer la distance entre deux stations
            float distance = sqrt(pow(positionStation2.x - positionStation1.x, 2) + pow(positionStation2.y - positionStation1.y, 2));

            // Créer un rectangle représentant le rail
            sf::RectangleShape rail(sf::Vector2f(distance, 5)); // Ajuster l'épaisseur si nécessaire
            rail.setPosition(positionStation1);
            rail.setRotation(angle * 180 / M_PI); // Convertir l'angle en degrés

            // Définir la couleur du rail
            sf::Color couleurRail(200, 200, 200); // Ajuster la couleur si nécessaire
            rail.setFillColor(couleurRail);

            // Dessiner le rail
            app.draw(rail);
        }

        // Affichage métro
        for (int i = 0; i < taille_rame; i++) {  // Notez le changement dans la condition de la boucle
            metroSprite.setPosition(liste_rame[i]->get_x(), liste_rame[i]->get_y());

            // Calculer l'angle entre la station actuelle et la suivante
            metroSprite.setRotation(liste_rame[i]->get_angle());  // Définir la rotation
            if (i == 0) {
                //DEBUG
                //indexText.setString("position x de la station 2 : " + to_string(angle));
                //indexText.setPosition(500, 400); // Position du texte sur l'écran
                //app.draw(indexText);
            }
            app.draw(metroSprite);
        }

        //DEBUG
        //indexText.setString("position x de la station 2: " + to_string( liste_rame[taille_rame - 1]->get_y()));
        //indexText.setPosition(500, 400); // Position du texte sur l'écran
        // Afficher le texte à l'écran
        //app.draw(indexText);


        app.display();// soucis juste ici quanbd 
    }
}



