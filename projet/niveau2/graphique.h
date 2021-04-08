//
//  graphique.h
//  
//
//  Created by Kamelia Slimani on 07/04/2021.
//

#ifndef graphique_h
#define graphique_h

#include "sdl2-light.h"
#include <stdio.h>
#include "logique.h"
#include "definition.h"


/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
*/

struct textures_s{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* vaisseau; /*!< Texture liée à l'image du vaisseau. */
    SDL_Texture* ligne_arrive; /*!< Texture liée à la ligne d'arrivée */
    SDL_Texture* meteorite; /*!< Texture liée à une météorite */
};


/**
 * \brief Type qui correspond aux textures du jeu
*/

typedef struct textures_s textures_t;

/**
 * \brief La fonction affiche la position du sprite
 * \param sprite vaisseau
 */

void print_sprite(sprite_t sprite);
/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */

void handle_events(SDL_Event *event,world_t *world);

/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
*/

void clean_textures(textures_t *textures);

/**
 * \brief La fonction initialise les textures nécessaires à l'affichage graphique du jeu
 * \param screen la surface correspondant à l'écran de jeu
 * \param textures les textures du jeu
*/

void init_textures(SDL_Renderer *renderer, textures_t *textures);

/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param texture la texture liée au fond
*/

void apply_background(SDL_Renderer *renderer, SDL_Texture *texture);

/**
 * \brief La fonction applique la texture des météorites sur le mur
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param textures les textures
*/
void apply_meteorite(SDL_Renderer *renderer, world_t *world, textures_t *textures, int hauteur, int largeur);

/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param textures les textures
 */

void refresh_graphics(SDL_Renderer *renderer, world_t *world, textures_t *textures);

/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param textures les textures
* \param world le monde
*/

void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world);

/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des textures, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param textures les textures
 * \param world le monde
 */

void init(SDL_Window **window, SDL_Renderer ** renderer, textures_t *textures, world_t * world);
/**
 * \brief fonction qui verifie que le sprite ne depaase pas la limite gauche du jeu
 * \param sprite vaisseau
*/
void depassement_g(sprite_t sprite);

/**
 * \brief fonction qui verifie que le sprite ne depaase pas la limite droite du jeu
 * \param sprite vaisseau
*/
void depassement_d(sprite_t sprite);

/**
 * \brief fonction qui verifie que 2 sprite ne soit pas en collision
 * \param sp1 vaisseau 2
 * \param sp2 vaisseau 2
*/

int sprites_collide(sprite_t *sp1, sprite_t *sp2);
#endif /* graphique_h */
