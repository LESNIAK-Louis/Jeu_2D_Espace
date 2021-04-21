/**
 * \file graphique.c
 * \brief Module gérant la partie graphique du jeu
 * \author LESNIAK Louis & SLIMANI Kamelia
 * \version 2.0
 * \date 15 avril 2021
 */

#include "sdl2-light.h"
#include "graphique.h"
#include "logique.h"
#include "definition.h"

#include <stdlib.h>
#include <stdio.h>


void clean_textures(textures_t *textures){
    clean_texture(textures->background);
    clean_texture(textures->vaisseau);
    clean_texture(textures->ligne_arrive);
    clean_texture(textures->meteorite);
    clean_font(textures->font);
}


void init_textures(SDL_Renderer *renderer, textures_t *textures){
    textures->background = load_image( "ressources/space-background.bmp",renderer);
    textures->vaisseau = load_image( "ressources/spaceship.bmp",renderer);
    textures->ligne_arrive = load_image( "ressources/finish_line.bmp",renderer);
    textures->meteorite = load_image( "ressources/meteorite.bmp",renderer);
    load_font(arial.ttf, 14);
}

void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite, int make_disappear) // ajout de make_disappear en paramètre afin de regrouper deux morceaux de code et de former un tout
{
    if (make_disappear == 0) 
      apply_texture(texture, renderer, sprite->x - sprite->w/2, sprite->y - sprite->h/2); // Le bas à gauche de la texture commence au point (x,y) ( pour que (x,y) soit le centre de celle-ci on retire la taille du sprite/2 en x et en y)
}

void apply_background(SDL_Renderer *renderer, SDL_Texture *texture)
{
    if(texture != NULL)
      apply_texture(texture, renderer, 0, 0);
}

/*void apply_meteorite(SDL_Renderer *renderer, world_t *world, textures_t *textures)
{
  for(int i=0; i < world->mur.h/METEORITE_SIZE; i++) // Ligne de taille METEORITE_SIZE
    {
      for(int j=0; j < world->mur.w/METEORITE_SIZE; j++) // Colonne de taille METEORITE_SIZE
      {
        apply_texture(textures->meteorite, renderer, (world->mur.x - world->mur.w/2)+METEORITE_SIZE*j, (world->mur.y - world->mur.h/2)+METEORITE_SIZE*i); // On place une texture de météorite au "tableau" à l'indice (i,j) 
      }
    }
}
*/

void  apply_walls(SDL_Renderer *renderer, world_t * world, textures_t *textures)
{

  for(int l=0; l < 6; l++) // Parcours du tableau de météorites 
  {
    for(int i=0; i < world->meteorite[l].h/METEORITE_SIZE; i++) // Ligne de taille METEORITE_SIZE
    {
      for(int j=0; j < world->meteorite[l].w/METEORITE_SIZE; j++) // Colonne de taille METEORITE_SIZE
      {
        apply_texture(textures->meteorite, renderer, (world->meteorite[l].x - world->meteorite[l].w/2)+METEORITE_SIZE*j, (world->meteorite[l].y - world->meteorite[l].h/2)+METEORITE_SIZE*i); // On place une texture de météorite au "tableau" à l'indice (i,j) 
      }
    }
  }
}

void refresh_graphics(SDL_Renderer *renderer, world_t *world, textures_t *textures)
{
    
    //on vide le renderer
    clear_renderer(renderer);
    
    //application des textures dans le renderer
    apply_background(renderer, textures->background);
    apply_sprite(renderer, textures->vaisseau, &(world->vaisseau), world->collision_mur);
    apply_sprite(renderer, textures->ligne_arrive, &(world->ligne_arrive), 0);
    //apply_meteorite(renderer, world, textures);
    apply_walls(renderer, world, textures);
    //temps ecoulé en haut à gauche 
    //apply_text(renderer, 1, 4, 7, 8, SDL_GetTicks, 12);
    // on met à jour l'écran
    update_screen(renderer);
}


