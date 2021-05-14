/**
 * \file graphique.c
 * \brief Module gérant la partie graphique du jeu
 * \author LESNIAK Louis & SLIMANI Kamelia
 * \version 3.0
 * \date 14 mai 2021
 */

#include "sdl2-light.h"
#include "sdl2-ttf-light.h"
#include "transition.h"
#include "graphique.h"
#include "logique.h"
#include "definition.h"

#include <stdlib.h>
#include <stdio.h>

void clean_resources(resources_t *resources)
{
    clean_texture(resources->background);
    clean_texture(resources->vaisseau);
    clean_texture(resources->ligne_arrive);
    clean_texture(resources->meteorite);
    clean_font(resources->font);
}


void init_resources(SDL_Renderer *renderer, resources_t *resources)
{
    resources->background = load_image( "ressources/space-background.bmp",renderer);
    resources->vaisseau = load_image( "ressources/spaceship.bmp",renderer);
    resources->ligne_arrive = load_image( "ressources/finish_line.bmp",renderer);
    resources->meteorite = load_image( "ressources/meteorite.bmp",renderer);
    resources->font = load_font("ressources/arial.ttf", 14);
}

void apply_sprite(SDL_Renderer *renderer, SDL_Texture *resource, sprite_t *sprite, int make_disappear) // ajout de make_disappear en paramètre afin de regrouper deux morceaux de code et de former un tout
{
    if (make_disappear == 0) 
      apply_texture(resource, renderer, sprite->x - sprite->w/2, sprite->y - sprite->h/2); // Le bas à gauche de la resource commence au point (x,y) ( pour que (x,y) soit le centre de celle-ci on retire la taille du sprite/2 en x et en y)
}

void apply_background(SDL_Renderer *renderer, SDL_Texture *resource)
{
    if(resource != NULL)
      apply_texture(resource, renderer, 0, 0);
}


void apply_walls(SDL_Renderer *renderer, world_t * world, resources_t *resources)
{

  for(int l=0; l < 6; l++) // Parcours du tableau de météorites 
  {
    for(int i=0; i < world->meteorite[l].h/METEORITE_SIZE; i++) // Ligne de taille METEORITE_SIZE
    {
      for(int j=0; j < world->meteorite[l].w/METEORITE_SIZE; j++) // Colonne de taille METEORITE_SIZE
        apply_texture(resources->meteorite, renderer, (world->meteorite[l].x - world->meteorite[l].w/2)+METEORITE_SIZE*j, (world->meteorite[l].y - world->meteorite[l].h/2)+METEORITE_SIZE*i); // On place une resource de météorite au "tableau" à l'indice (i,j) 
    }
  }
}

void apply_texts(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t *game)
{
    apply_text(renderer, 20, 10, 60, 40, "Time :", resources->font);  // affichage du texte
    
    char timeString[10];
    game->time =SDL_GetTicks();

    sprintf(timeString,"%d",game->time/1000);
    apply_text(renderer, 90, 10, 20, 40, timeString , resources->font);  // affichage du texte

    if(world->gameover==1)//le joueur a atteint la ligne d'arriver
    {
      if(world->collision_mur==1)// collision avec un mur
          apply_text(renderer, (SCREEN_WIDTH-TEXT_WIN_WIDTH)/2, (SCREEN_HEIGHT-TEXT_WIN_HEIGHT)/2, TEXT_WIN_WIDTH, TEXT_WIN_HEIGHT, "You lost !", resources->font); // affichage du texte
      else
      {
        char message[50]; // 50 caractères est jugé largement suffisant
        sprintf(message,"You finished in %d s!",game->time/1000);
        apply_text(renderer, (SCREEN_WIDTH-TEXT_WIN_WIDTH)/2, (SCREEN_HEIGHT-TEXT_WIN_HEIGHT)/2, TEXT_WIN_WIDTH, TEXT_WIN_HEIGHT, message, resources->font); // affichage du texte
      }
    }
}

void refresh_graphics(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t *game)
{
    //on vide le renderer
    clear_renderer(renderer);
    
    //application des resources dans le renderer
    apply_background(renderer, resources->background);
    apply_sprite(renderer, resources->vaisseau, &(world->vaisseau), world->collision_mur);
    apply_sprite(renderer, resources->ligne_arrive, &(world->ligne_arrive), 0);
    apply_walls(renderer, world, resources);
    apply_texts(renderer, world, resources, game);
    
    // on met à jour l'écran
    update_screen(renderer);
}


