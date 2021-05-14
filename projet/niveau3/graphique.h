/**
 * \file graphique.h
 * \brief Header du module graphique
 * \author LESNIAK Louis & SLIMANI Kamelia
 * \version 3.0
 * \date 14 mai 2021
 */

#ifndef graphique_h
#define graphique_h
#include "logique.h"

/**
 * \brief Stockage des resources nécessaires à l'affichage graphique
*/

struct resources_s{
    SDL_Texture* background; /*!< resource liée à l'image du fond de l'écran. */
    SDL_Texture* vaisseau; /*!< resource liée à l'image du vaisseau. */
    SDL_Texture* ligne_arrive; /*!< resource liée à la ligne d'arrivée */
    SDL_Texture* meteorite; /*!< resource liée à une météorite */
   	TTF_Font * font;/*!< font liée à la police d'affichage */
};


/**
 * \brief Type qui correspond aux resources du jeu
*/

typedef struct resources_s resources_t;


/**
 * \brief La fonction nettoie les resources
 * \param resources les resources
*/

void clean_resources(resources_t *resources);

/**
 * \brief La fonction initialise les resources nécessaires à l'affichage graphique du jeu
 * \param screen la surface correspondant à l'écran de jeu
 * \param resources les resources du jeu
*/

void init_resources(SDL_Renderer *renderer, resources_t *resources);

/**
 * \brief La fonction initialise la position du sprite
 * \param sprite vaisseau
 * \param x abscisse de la position du sprite
 * \param y ordonnée de la position du sprite
 * \param w largeur de la position du sprite
 * \param h hauteur de la position du sprite
 */
void apply_sprite(SDL_Renderer *renderer, SDL_Texture *resource, sprite_t *sprite, int make_disappear);

/**
 * \brief La fonction applique la resource du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param resource la resource liée au fond
 * \param sprite sprite
 * \param make_disappear permet de faire disparaitre ou non le sprite
*/

void apply_background(SDL_Renderer *renderer, SDL_Texture *resource);


/**
 * \brief La fonction applique la resource des couloirs de météorites
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param resources les resources
*/
void  apply_walls(SDL_Renderer *renderer, world_t *world, resources_t *resources);

/**
 * \brief La fonction affiche les textes à l'écran et gère le temps
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param resources les resources
 * \param game données du jeu
*/
void apply_texts(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t *game);

/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param resources les resources
 * \param game données du jeu
 */

void refresh_graphics(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t * game);


#endif /* graphique_h */
