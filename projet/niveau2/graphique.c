/**
 * \file graphique.c
 * \brief Module gérant la partie graphique du jeu
 * \author LESNIAK Louis & SLIMANI Kamelia
 * \version 2.0
 * \date 14 avril 2021
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
}


void init_textures(SDL_Renderer *renderer, textures_t *textures){
    textures->background = load_image( "ressources/space-background.bmp",renderer);
    textures->vaisseau = load_image( "ressources/spaceship.bmp",renderer);
    textures->ligne_arrive = load_image( "ressources/finish_line.bmp",renderer);
    textures->meteorite = load_image( "ressources/meteorite.bmp",renderer);
}

void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite, int make_disappear) // ajout de make_disappear en paramètre afin de regrouper deux morceaux de code et de former un tout
{
    if (make_disappear == 0)
    {
      SDL_Rect dst = {0, 0, 0, 0};
      
      SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
      dst.x = sprite->x - sprite->w/2; dst.y=sprite->y - sprite->h/2;
      
      SDL_RenderCopy(renderer, texture, NULL, &dst);
    }
    else
      clean_texture(texture);
    
}

void apply_background(SDL_Renderer *renderer, SDL_Texture *texture){
    if(texture != NULL){
      apply_texture(texture, renderer, 0, 0);
    }
}

void apply_meteorite(SDL_Renderer *renderer, world_t *world, textures_t *textures)
{
  for(int i=0; i < world->mur.h/METEORITE_SIZE; i++)
    {
      for(int j=0; j < world->mur.w/METEORITE_SIZE; j++)
      {
        apply_texture(textures->meteorite, renderer, (world->mur.x - world->mur.w/2)+METEORITE_SIZE*j, (world->mur.y - world->mur.h/2)+METEORITE_SIZE*i);
      }
    }
}


void refresh_graphics(SDL_Renderer *renderer, world_t *world, textures_t *textures){
    
    //on vide le renderer
    clear_renderer(renderer);
    
    //application des textures dans le renderer
    apply_background(renderer, textures->background);
    apply_sprite(renderer, textures->vaisseau, &(world->vaisseau), world->collision_mur);
    apply_sprite(renderer, textures->ligne_arrive, &(world->ligne_arrive), 0);
    apply_meteorite(renderer, world, textures);
    
    // on met à jour l'écran
    update_screen(renderer);
}


void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world){
    clean_data(world);
    clean_textures(textures);
    clean_sdl(renderer,window);
}



void init(SDL_Window **window, SDL_Renderer ** renderer, textures_t *textures, world_t * world)
{
    init_sdl(window,renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_textures(*renderer,textures);
}
