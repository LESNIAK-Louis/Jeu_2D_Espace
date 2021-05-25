/**
 * \file graphique.h
 * \brief Header du module graphique
 * \author LESNIAK Louis & SLIMANI Kamelia
 * \version 3.0 + extensions
 * \date 23 mai 2021
 */

#ifndef graphique_h
#define graphique_h
#include "logique.h"

/**
 * \brief Stockage des ressources nécessaires à l'affichage graphique
*/

struct resources_s{
    SDL_Texture* background_menu; /*!< ressource liée à l'image du fond du menu. */
    SDL_Texture* background; /*!< ressource liée à l'image du fond de l'écran de jeu. */
    SDL_Texture* ship; /*!< ressource liée à l'image du vaisseau de base. */
    SDL_Texture* ship1; /*!< ressource liée à l'image du vaisseau 1. */
    SDL_Texture* ship2; /*!< ressource liée à l'image du vaisseau 2. */
    SDL_Texture* ship3; /*!< ressource liée à l'image du vaisseau 3. */
    SDL_Texture* ship4; /*!< ressource liée à l'image du vaisseau 4. */
    SDL_Texture* finish_line; /*!< ressource liée à la ligne d'arrivée */
    SDL_Texture* meteorite; /*!< ressource liée à une météorite */
   	TTF_Font * font; /*!< police d'affichage du jeu */
    TTF_Font * font_menu; /*!< police d'affichage du menu */
    SDL_Texture* star; /*!< ressource liée à une étoile  */
    SDL_Texture* return_menu; /*!< ressource liée au retour dans le menu */
    SDL_Texture* select; /*!< ressource liée à la sélection dans le menu */
    SDL_Texture* selected; /*!< ressource liée au vaisseau selectionné dans le shop */
    SDL_Texture* shield; /*!< ressource liée à l'image d'un bouclier */
    SDL_Texture* time; /*!< ressource liée à l'image d'un symbole de temps */
    SDL_Texture* missile; /*!< ressource liée à l'image d'un missile */
    SDL_Texture* ennemy_ship; /*!< ressource liée à l'image d'un vaisseau ennemi */
};


/**
 * \brief Type qui correspond aux ressources du jeu
*/

typedef struct resources_s resources_t;


/**
 * \brief La fonction nettoie les ressources
 * \param resources les ressources
*/

void clean_resources(resources_t *resources);

/**
 * \brief La fonction initialise les ressources nécessaires à l'affichage graphique du jeu
 * \param renderer le renderer SDL
 * \param resources les ressources du jeu
*/

void init_resources(SDL_Renderer *renderer, resources_t *resources);

/**
 * \brief La fonction positionne la texture à la position du sprite
 * \param renderer le renderer SDL
 * \param resource les ressources du jeu
 * \param sprite sprite à afficher
 * \param make_disappear affiche ou non la texture
 */
void apply_sprite(SDL_Renderer *renderer, SDL_Texture *resource, sprite_t *sprite, unsigned int make_disappear);

/**
 * \brief La fonction applique la ressource du fond
 * \param renderer le renderer SDL
 * \param resource la ressource liée au fond
*/

void apply_background(SDL_Renderer *renderer, SDL_Texture *resource);

/**
 * \brief La fonction applique la ressource des couloirs de météorites
 * \param renderer le renderer SDL
 * \param world les données du monde
 * \param resources les ressources 
*/
void  apply_walls(SDL_Renderer *renderer, world_t *world, resources_t *resources);

/**
 * \brief La fonction applique la ressource aux différents missiles
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param resources les ressources
*/

void apply_missiles(SDL_Renderer *renderer, world_t * world, resources_t *resources);

/**
 * \brief La fonction applique la ressource aux différents ennemis
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param resources les ressources
*/

void apply_ennemies(SDL_Renderer *renderer, world_t * world, resources_t *resources);
/**
 * \brief La fonction applique la ressource aux différents bonus
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param resources les ressources
*/
void  apply_bonus(SDL_Renderer *renderer, world_t *world, resources_t *resources);

/**
 * \brief La fonction affiche les textes à l'écran et gère le temps
 * \param renderer le renderer SDL
 * \param world les données du monde
 * \param resources les ressources
 * \param game les données du jeu
*/
void apply_texts(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t *game);

/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer renderer SDL
 * \param world les données du monde
 * \param resources les ressources
 * \param game données du jeu
 * \param player données du joueur
 */

void refresh_graphics(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t * game, playerinfo_t *player);


#endif /* graphique_h */
