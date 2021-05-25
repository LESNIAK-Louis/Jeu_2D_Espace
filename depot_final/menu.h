/**
 * \file menu.h
 * \brief Header regroupant toutes les fonctions appelant des fonctions graphique et logique
 * \author LESNIAK Louis & SLIMANI Kamelia
 * \version 3.0 + extensions
 * \date 23 mai 2021
 */

#ifndef menu_h
#define menu_h

#include "logique.h"
#include "graphique.h"

/**
 * \brief La fonction qui gère l'achat d'une texture de vaisseau
 * \param player les données du joueur
 * \param ShipNumber le numéro du vaisseau à acheter
 */
void buy_select_ship(playerinfo_t *player, unsigned int ShipNumber);


/**
 * \brief La fonction qui gère l'affichage du nombre d'étoiles du joueur dans le menu
 * \param renderer le renderer SDL
 * \param resources les ressources de l'application
 * \param player les données du joueur
 * \param x position du début de l'affichage
 */
void print_stars(SDL_Renderer *renderer, resources_t *resources, playerinfo_t *player, int x);

/**
 * \brief La fonction qui gère l'affichage de la sélection dans le menu
 * \param renderer le renderer SDL
 * \param resources les ressources de l'application
 * \param game les données du jeu
 * \param x position x du début de l'affichage
 * \param y position y du début de l'affichage
 */
void print_select(SDL_Renderer *renderer, resources_t *resources, gameinfo_t *game, int x, int y);

/**
 * \brief La fonction affiche le menu principal
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param resources les resources
 * \param game les données du jeu
 * \param player les données du joueur
 */

void menu_main(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t *game, playerinfo_t *player);

/**
 * \brief La fonction affiche le magasin
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param resources les resources
 * \param game les données du jeu
 */

void menu_shop(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t *game, playerinfo_t *player);

/**
 * \brief La fonction affiche les règles du jeu
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param resources les resources
 * \param game les données du jeu
 * \param player les données du joueur
 */

void menu_infos(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t *game);


/**
 * \brief La fonction affiche les crédits du jeu
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param resources les resources
 * \param game les données du jeu
 */

void menu_credits(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t *game);

/**
 * \brief La fonction gère l'appel des fonctions relatives au menu
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param resources les resources
 * \param game les données du jeu
 * \param player les données du joueur
 */

void apply_menu(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t *game, playerinfo_t *player);

#endif /* menu_h */
