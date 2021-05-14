/**
 * \file transition.h
 * \brief Header regroupant toutes les fonctions appelant des fonctions graphique et logique
 * \author LESNIAK Louis & SLIMANI Kamelia
 * \version 3.0
 * \date 14 mai 2021
 */

#ifndef Transition_h
#define Transition_h

#include "logique.h"
#include "graphique.h"

/**
 * \brief Stockage des informations du jeu en cours (extension)
*/

struct gameinfo_t{
    unsigned int time; /*!< Temps écoulé jusqu'à la fin de partie */
};

/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des resources, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param resources les resources
* \param world le monde
* \param game données du jeu
*/

void clean(SDL_Window *window, SDL_Renderer * renderer, resources_t *resources, world_t * world, gameinfo_t * game);

/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des resources, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param resources les resources
 * \param world le monde
 */

void init(SDL_Window **window, SDL_Renderer ** renderer, resources_t *resources, world_t * world);

/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */

void handle_events(SDL_Event *event,world_t *world);

/**
 * \brief La fonction demade à l'utilisateur son nom et créer un fichier sauvegardant le score. (extension)
 * \param world les données du monde
 * \param game les données du jeu
 */
void save_score(world_t world, gameinfo_t game);


#endif /* Transition_h */
