/**
 * \file graphique.c
 * \brief Module gérant la partie graphique du jeu
 * \author LESNIAK Louis & SLIMANI Kamelia
 * \version 3.0 + extensions
 * \date 23 mai 2021
 */

#include "sdl2-light.h"
#include "sdl2-ttf-light.h"
#include "transition.h"
#include "graphique.h"
#include "logique.h"
#include "definition.h"
#include "menu.h"

#include <stdlib.h>
#include <stdio.h>

void clean_resources(resources_t *resources)
{
    clean_texture(resources->background);

    clean_texture(resources->ship);
    clean_texture(resources->ship2);
    clean_texture(resources->ship3);
    clean_texture(resources->ship4);

    clean_texture(resources->return_menu);
    clean_texture(resources->select);
    clean_texture(resources->selected);

    clean_texture(resources->finish_line);
    clean_texture(resources->meteorite);
    clean_texture(resources->star);
    clean_texture(resources->shield);
    clean_texture(resources->time);
    clean_texture(resources->missile);

    clean_texture(resources->ennemy_ship);

    clean_font(resources->font);
    clean_font(resources->font_menu);
}


void init_resources(SDL_Renderer *renderer, resources_t *resources)
{
    resources->background = load_image("ressources/space-background.bmp", renderer);

    resources->ship = load_image("ressources/spaceship.bmp",renderer);
    resources->ship2 = load_image("ressources/ship2.bmp",renderer);
    resources->ship3 = load_image("ressources/ship3.bmp",renderer);
    resources->ship4 = load_image("ressources/ship4.bmp",renderer);

    resources->return_menu = load_image("ressources/return.bmp", renderer);
    resources->select = load_image("ressources/select.bmp", renderer);
    resources->selected = load_image("ressources/selected.bmp", renderer);

    resources->finish_line = load_image( "ressources/finish_line.bmp",renderer);
    resources->meteorite = load_image( "ressources/meteorite.bmp",renderer);
    resources->star = load_image("ressources/star.bmp", renderer);
    resources->shield = load_image("ressources/shield.bmp", renderer);
    resources->time = load_image("ressources/time.bmp", renderer);
    resources->missile = load_image("ressources/missile.bmp", renderer);

    resources->ennemy_ship = load_image("ressources/ennemy_ship.bmp", renderer);

    resources->font = load_font("ressources/arial.ttf", 14);
    resources->font_menu = load_font("ressources/arial.ttf", 12);
    
}

void apply_sprite(SDL_Renderer *renderer, SDL_Texture *resource, sprite_t *sprite, unsigned int make_disappear) 
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

  for(int l=0; l < NB_WALLS; l++) // Parcours du tableau de météorites 
  {
    for(int i=0; i < world->meteorite[l].h/METEORITE_SIZE; i++) // Ligne de taille METEORITE_SIZE
    {
      for(int j=0; j < world->meteorite[l].w/METEORITE_SIZE; j++) // Colonne de taille METEORITE_SIZE
        apply_texture(resources->meteorite, renderer, (world->meteorite[l].x - world->meteorite[l].w/2)+METEORITE_SIZE*j, (world->meteorite[l].y - world->meteorite[l].h/2)+METEORITE_SIZE*i); // On place une resource de météorite au "tableau" à l'indice (i,j) 
    }
  }
}

void apply_missiles(SDL_Renderer *renderer, world_t * world, resources_t *resources)
{
  for(unsigned int i = 0; i < MISSILE_MAX; i++)
  {
    if (world->is_missile_free[i] == 0)
      apply_sprite(renderer, resources->missile, &(world->missile[i]), 0);
  }
}

void apply_ennemies(SDL_Renderer *renderer, world_t * world, resources_t *resources)
{
  for(unsigned int i = 0; i < ENNEMIES_MAX; i++)
  {
    if (world->is_ennemy_dead[i] == 0)
      apply_sprite(renderer, resources->ennemy_ship, &(world->ennemy[i]), 0);
  }
}

void apply_bonus(SDL_Renderer *renderer, world_t *world, resources_t *resources)
{
  for(int i=0; i < NB_BONUS; i++)
  {
    switch(world->bonus_type[i])
    {
      case 0: apply_sprite(renderer, resources->star, &(world->bonus[i]), !world->is_bonus_available[i]);
      break;
      case 1: apply_sprite(renderer, resources->shield, &(world->bonus[i]), !world->is_bonus_available[i]);
      break;
      case 2: apply_sprite(renderer, resources->time, &(world->bonus[i]), !world->is_bonus_available[i]);
      break;
      default: break;
    }
  }
}

void apply_texts(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t *game)
{
    apply_text(renderer, 20, 10, 80, 40, "Time left :", resources->font, 255, 0 , 255);  // affichage du texte "Time left :" en haut à gauche de l'écran 
    
    char timeString[500];
    game->finishTime = (SDL_GetTicks()-game->startTime)/1000;
    sprintf(timeString,"%u",TIME_LIMIT - game->finishTime);
    apply_text(renderer, 110, 10, 20, 40, timeString , resources->font, 255, 0, 255);  // temps restant valeur 

    if(world->gameover==1)//la partie est finie
    {
      if(world->collision==1) // collision avec un mur
          apply_text(renderer, (SCREEN_WIDTH-TEXT_LOST_WIDTH)/2, (SCREEN_HEIGHT-TEXT_LOST_HEIGHT)/2, TEXT_LOST_WIDTH, TEXT_LOST_HEIGHT, "You lost !", resources->font, 255, 0 ,255); // affichage du texte "You lost" au millieu de l'écran
      else if(game->finishTime >= TIME_LIMIT)
        apply_text(renderer, (SCREEN_WIDTH-TEXT_LOST_WIDTH)/2, (SCREEN_HEIGHT-TEXT_LOST_HEIGHT)/2, TEXT_LOST_WIDTH, TEXT_LOST_HEIGHT, "You took too much time !", resources->font, 255, 0 ,255); // affichage du texte
      else // le joueur a atteint la ligne d'arriver
      {
        char message[50]; // 50 caractères est jugé largement suffisant
        sprintf(message,"You finished in %d s!", game->finishTime);
        apply_text(renderer, (SCREEN_WIDTH-TEXT_WIN_WIDTH)/2, (SCREEN_HEIGHT-TEXT_WIN_HEIGHT)/2, TEXT_WIN_WIDTH, TEXT_WIN_HEIGHT, message, resources->font, 255, 0, 255); // affichage du texte "You finished in %d s!" au millieu de l'écran
      }
    }
}

void refresh_graphics(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t *game, playerinfo_t *player)
{
    //on vide le renderer
    clear_renderer(renderer);

    //On applique les ressources au renderer 

    apply_background(renderer, resources->background);

    if(game->gamemode != 1)
    {
      apply_menu(renderer, world, resources, game, player);
    }  
    else if(game->gamemode == 1)
    {
      switch (player->selectedShip) // texture du vaisseau choisie
      {
      case 1: apply_sprite(renderer, resources->ship, &(world->ship), world->collision);
      break;
      case 2: apply_sprite(renderer, resources->ship2, &(world->ship), world->collision);
      break;
      case 3: apply_sprite(renderer, resources->ship3, &(world->ship), world->collision);
      break;
      case 4: apply_sprite(renderer, resources->ship4, &(world->ship), world->collision);
      break;  
      default: apply_sprite(renderer, resources->ship, &(world->ship), world->collision);
      break;
      }
      apply_sprite(renderer, resources->finish_line, &(world->finish_line), 0);
      apply_missiles(renderer, world, resources);
      apply_ennemies(renderer, world, resources);
      apply_walls(renderer, world, resources);
      apply_bonus(renderer, world, resources);
      apply_texts(renderer, world, resources, game);
    }

    // on met à jour l'écran
    update_screen(renderer);
}


