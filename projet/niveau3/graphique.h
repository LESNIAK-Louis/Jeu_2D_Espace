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
    SDL_Texture* background_menu; /*!< resource liée à l'image du fond du menu. */
    SDL_Texture* background; /*!< resource liée à l'image du fond de l'écran de jeu. */
    SDL_Texture* ship; /*!< resource liée à l'image du vaisseau de base. */
    SDL_Texture* ship1; /*!< resource liée à l'image du vaisseau 1. */
    SDL_Texture* ship2; /*!< resource liée à l'image du vaisseau 2. */
    SDL_Texture* ship3; /*!< resource liée à l'image du vaisseau 3. */
    SDL_Texture* ship4; /*!< resource liée à l'image du vaisseau 4. */
    SDL_Texture* finish_line; /*!< resource liée à la ligne d'arrivée */
    SDL_Texture* meteorite; /*!< resource liée à une météorite */
   	TTF_Font * font;/*!< font liée à la police d'affichage du jeu */
    TTF_Font * font_menu; /*!< font liée à la police d'affichage du menu */
    SDL_Texture* heart; /*!< resource liée à un coeur */
    SDL_Texture* star; /*!< resource liée à une étoile  */
    SDL_Texture* return_menu; /*!< resource liée au retour dans le menu */
    SDL_Texture* select; /*!< resource liée à la sélection dans le menu */
    SDL_Texture* selected; /*!< resource liée au vaisseau selectionné dans le shop */
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
* \param player données du joueur
 */

void refresh_graphics(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t * game, playerinfo_t *player);

/**
 * \brief La fonction affiche le menu principal
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param resources les resources
 * \param game données du jeu
 * \param player données du joueur
 */

void menu_main(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t *game, playerinfo_t *player);

/**
 * \brief La fonction affiche le magasin
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param resources les resources
 * \param game données du jeu
 */

void menu_shop(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t *game, playerinfo_t *player);

/**
 * \brief La fonction affiche les règles du jeu
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param resources les resources
 * \param game données du jeu
 * \param player données du joueur
 */

void menu_rules(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t *game);


/**
 * \brief La fonction affiche les crédits du jeu
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param resources les resources
 * \param game données du jeu
 */

void menu_credits(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t *game);

/**
 * \brief La fonction affiche gère l'appel des fonctions relatives au menu
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param resources les resources
 * \param game données du jeu
 * \param player données du joueur
 */

void apply_menu(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t *game, playerinfo_t *player);


#endif /* graphique_h */
