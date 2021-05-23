/**
 * \file transition.h
 * \brief Header regroupant toutes les fonctions appelant des fonctions graphique et logique
 * \author LESNIAK Louis & SLIMANI Kamelia
 * \version 3.0 + extensions
 * \date 23 mai 2021
 */

#ifndef transition_h
#define transition_h

#include "logique.h"
#include "graphique.h"

/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des ressources, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param resources les ressources
* \param world le monde
* \param game données du jeu
*/

void clean(SDL_Window *window, SDL_Renderer * renderer, resources_t *resources, world_t * world, gameinfo_t * game);

/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des resources, initialisation des données (du jeu, du monde et du joueur)
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param resources les ressources
 * \param world le monde
 * \param game les données du jeu
 * \param player les données du joueur
 */

void init(SDL_Window **window, SDL_Renderer ** renderer, resources_t *resources, world_t * world, gameinfo_t *game, playerinfo_t *player);

/**
 * \brief La fonction initialise les données joueurs (extension)
 * \param player les données du joueur
 */
void init_player(playerinfo_t *player);

/**
 * \brief Affiche dans la console le fichier texte des crédits
*/
void print_credits();

/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 * \param game les données du jeu
 * \param player les données du joueur
 */

void handle_events(SDL_Event *event, world_t *world, gameinfo_t *game, playerinfo_t *player);

/**
 * \brief La fonction concatène une chaine de caractères avec le nom du joueur
 * \param player les données du joueur
 * \param array chaine de caractères
 * \param arraySize taille de array
 * \return pointeur vers la chaine de caractères produite
 */
char* concat_array_playername(playerinfo_t *player, char *array, unsigned int arraySize);

/**
 * \brief La fonction transforme un tableau de char (formaté pour) en int 
 * \param Array tableau de char formaté SSXXXXS où les X sont des chiffres et les S représentent le formatage réalisé
 */
unsigned int formatted_charArray_to_uint(char *Array);

/**
 * \brief La fonction demande à l'utilisateur son nom et créer un fichier sauvegardant le score. (extension)
 * \param world les données du monde
 * \param game les données du jeu
 * \param player les données du joueur
 */
void save_score(world_t *world, gameinfo_t *game, playerinfo_t *player);

/**
 * \brief La fonction sauvegarde les données du joueur (extension)
 * \param player les données du joueur
 */
void save_info(playerinfo_t *player);


#endif /* transition_h */
