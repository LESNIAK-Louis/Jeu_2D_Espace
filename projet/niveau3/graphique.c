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

    clean_texture(resources->ship);
    clean_texture(resources->ship2);
    clean_texture(resources->ship3);
    clean_texture(resources->ship4);

    clean_texture(resources->return_menu);
    clean_texture(resources->select);

    clean_texture(resources->finish_line);
    clean_texture(resources->meteorite);
    clean_texture(resources->star);
    clean_texture(resources->heart);

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
    resources->heart = load_image("ressources/heart.bmp", renderer);

    resources->font = load_font("ressources/arial.ttf", 14);
    resources->font_menu = load_font("ressources/arial.ttf", 12);
    
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
    apply_text(renderer, 20, 10, 60, 40, "Time :", resources->font, 255, 0 , 255);  // affichage du texte
    
    char timeString[500];
    game->finishTime = (SDL_GetTicks()-game->startTime)/1000;
    sprintf(timeString,"%u",game->finishTime);
    apply_text(renderer, 90, 10, 20, 40, timeString , resources->font, 255, 0, 255);  // affichage du texte

    if(world->gameover==1)//la partie est finie
    {
      if(world->collision_wall==1) // collision avec un mur
          apply_text(renderer, (SCREEN_WIDTH-TEXT_LOST_WIDTH)/2, (SCREEN_HEIGHT-TEXT_LOST_HEIGHT)/2, TEXT_LOST_WIDTH, TEXT_LOST_HEIGHT, "You lost !", resources->font, 255, 0 ,255); // affichage du texte
      else if(game->finishTime >= TIME_LIMIT)
        apply_text(renderer, (SCREEN_WIDTH-TEXT_LOST_WIDTH)/2, (SCREEN_HEIGHT-TEXT_LOST_HEIGHT)/2, TEXT_LOST_WIDTH, TEXT_LOST_HEIGHT, "You took too much time !", resources->font, 255, 0 ,255); // affichage du texte
      else // le joueur a atteint la ligne d'arriver
      {
        char message[50]; // 50 caractères est jugé largement suffisant
        sprintf(message,"You finished in %d s!", game->finishTime);
        apply_text(renderer, (SCREEN_WIDTH-TEXT_WIN_WIDTH)/2, (SCREEN_HEIGHT-TEXT_WIN_HEIGHT)/2, TEXT_WIN_WIDTH, TEXT_WIN_HEIGHT, message, resources->font, 255, 0, 255); // affichage du texte
      }
    }
}

void menu_main(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t *game, playerinfo_t *player)
{
  apply_text(renderer, SCREEN_WIDTH/2-(TEXT_MENU_WIDTH+TEXT_MENU_WIDTH/2)/2, SCREEN_HEIGHT/4 - (TEXT_MENU_HIGHT+TEXT_MENU_HIGHT/2)/2, (TEXT_MENU_WIDTH+TEXT_MENU_WIDTH/2), (TEXT_MENU_HIGHT+TEXT_MENU_HIGHT/2), "Menu", resources->font_menu, 255, 255, 255); // affichage du texte
  apply_text(renderer, (SCREEN_WIDTH-TEXT_MENU_WIDTH)/2, SCREEN_HEIGHT/2 - (TEXT_MENU_HIGHT+TEXT_MENU_HIGHT/4), TEXT_MENU_WIDTH, TEXT_MENU_HIGHT, "Play", resources->font_menu,255 ,255 ,255); // affichage du texte
  apply_text(renderer, (SCREEN_WIDTH-TEXT_MENU_WIDTH)/2, SCREEN_HEIGHT/2, TEXT_MENU_WIDTH, TEXT_MENU_HIGHT, "Shop", resources->font_menu,255,255,255); // affichage du texte
  apply_text(renderer, (SCREEN_WIDTH-TEXT_MENU_WIDTH)/2, SCREEN_HEIGHT/2 +  (TEXT_MENU_HIGHT+TEXT_MENU_HIGHT/4), TEXT_MENU_WIDTH, TEXT_MENU_HIGHT, "Rules", resources->font_menu,255,255,255); // affichage du texte
  apply_text(renderer, (SCREEN_WIDTH-TEXT_MENU_WIDTH)/2, SCREEN_HEIGHT/2 + (TEXT_MENU_HIGHT+TEXT_MENU_HIGHT/4)*2, TEXT_MENU_WIDTH, TEXT_MENU_HIGHT, "Credits", resources->font_menu,255,255,255); // affichage du texte

  if (player->bestTime == TIME_LIMIT+1 || player->lastTime == TIME_LIMIT+1)
    apply_text(renderer, SCREEN_WIDTH/2-(TEXT_MENU_WIDTH+50)/2, SCREEN_HEIGHT-TEXT_MENU_HIGHT, TEXT_MENU_WIDTH+50, TEXT_MENU_HIGHT, "Welcome !", resources->font_menu,255,228,54); // affichage du texte
  else
  {
    char bestTime[TIME_LIMIT + 10];
    sprintf(bestTime,"Record : %us", player->bestTime);
    char lastTime[TIME_LIMIT+MAX_LENGTH_NAME+13];
    sprintf(lastTime,"Last game won : %us", player->lastTime);
    apply_text(renderer, 5, SCREEN_HEIGHT-30*2, TEXT_MENU_WIDTH, 25, bestTime, resources->font_menu,255,228,54); // affichage du texte
    apply_text(renderer, 5, SCREEN_HEIGHT-30, TEXT_MENU_WIDTH, 25, lastTime, resources->font_menu,255,228,54); // affichage du texte
  }
  switch(game->select)
  {
    case 0: apply_texture(resources->select, renderer, (SCREEN_WIDTH-TEXT_MENU_WIDTH)/2 - 50 , SCREEN_HEIGHT/2 - (TEXT_MENU_HIGHT+TEXT_MENU_HIGHT/4));
      break;
    case 1: apply_texture(resources->select, renderer, (SCREEN_WIDTH-TEXT_MENU_WIDTH)/2 - 50, SCREEN_HEIGHT/2);
      break;
    case 2: apply_texture(resources->select, renderer, (SCREEN_WIDTH-TEXT_MENU_WIDTH)/2 - 50, SCREEN_HEIGHT/2 +  (TEXT_MENU_HIGHT+TEXT_MENU_HIGHT/4));
      break;
    case 3: apply_texture(resources->select, renderer, (SCREEN_WIDTH-TEXT_MENU_WIDTH)/2 - 50, SCREEN_HEIGHT/2 + (TEXT_MENU_HIGHT+TEXT_MENU_HIGHT/4)*2);
      break;
    default: break;
  }


  apply_texture(resources->star, renderer, 5,5);
  char starsNumber[500];
  sprintf(starsNumber,"%u",player->stars);
  apply_text(renderer, 40, 10, 30, 30, starsNumber, resources->font_menu,255,228,54);
}

void menu_shop(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t *game, playerinfo_t *player)
{
  apply_text(renderer, SCREEN_WIDTH/2-(TEXT_MENU_WIDTH+TEXT_MENU_WIDTH/2)/2, SCREEN_HEIGHT/4 - (TEXT_MENU_HIGHT+TEXT_MENU_HIGHT/2)/2, (TEXT_MENU_WIDTH+TEXT_MENU_WIDTH/2), (TEXT_MENU_HIGHT+TEXT_MENU_HIGHT/2), "Shop", resources->font_menu,255,255,255);

  char Price1[10];
  sprintf(Price1,": %u", PRICE_SHIP_1);
  if(player->hasShip[0] == 1)
    apply_text(renderer, (SCREEN_WIDTH-TEXT_SHOP_WIDTH)/2, SCREEN_HEIGHT/2 - (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4), TEXT_SHOP_WIDTH, TEXT_SHOP_HIGHT, Price1, resources->font_menu,128,128,128);
  else if (player->stars >= PRICE_SHIP_1)
    apply_text(renderer, (SCREEN_WIDTH-TEXT_SHOP_WIDTH)/2, SCREEN_HEIGHT/2 - (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4), TEXT_SHOP_WIDTH, TEXT_SHOP_HIGHT, Price1, resources->font_menu,0,255,0);
  else
    apply_text(renderer, (SCREEN_WIDTH-TEXT_SHOP_WIDTH)/2, SCREEN_HEIGHT/2 - (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4), TEXT_SHOP_WIDTH, TEXT_SHOP_HIGHT, Price1, resources->font_menu,255,0,0);
    
  char Price2[10];
  sprintf(Price2,": %u", PRICE_SHIP_2);
  if(player->hasShip[1] == 1)
    apply_text(renderer, (SCREEN_WIDTH-TEXT_SHOP_WIDTH)/2, SCREEN_HEIGHT/2, TEXT_SHOP_WIDTH, TEXT_SHOP_HIGHT, Price2, resources->font_menu,128,128,128);
  else if (player->stars >= PRICE_SHIP_2)
    apply_text(renderer, (SCREEN_WIDTH-TEXT_SHOP_WIDTH)/2, SCREEN_HEIGHT/2, TEXT_SHOP_WIDTH, TEXT_SHOP_HIGHT, Price2, resources->font_menu,0,255,0); 
  else
    apply_text(renderer, (SCREEN_WIDTH-TEXT_SHOP_WIDTH)/2, SCREEN_HEIGHT/2, TEXT_SHOP_WIDTH, TEXT_SHOP_HIGHT, Price2, resources->font_menu,255,0,0); 

  char Price3[10];
  sprintf(Price3,": %u", PRICE_SHIP_3);
  if(player->hasShip[2] == 1)
    apply_text(renderer, (SCREEN_WIDTH-TEXT_SHOP_WIDTH)/2, SCREEN_HEIGHT/2 +  (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4), TEXT_SHOP_WIDTH, TEXT_SHOP_HIGHT, Price3, resources->font_menu,128,128,128);
  else if (player->stars >= PRICE_SHIP_3)
    apply_text(renderer, (SCREEN_WIDTH-TEXT_SHOP_WIDTH)/2, SCREEN_HEIGHT/2 +  (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4), TEXT_SHOP_WIDTH, TEXT_SHOP_HIGHT, Price3, resources->font_menu,0,255,0);
  else
    apply_text(renderer, (SCREEN_WIDTH-TEXT_SHOP_WIDTH)/2, SCREEN_HEIGHT/2 +  (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4), TEXT_SHOP_WIDTH, TEXT_SHOP_HIGHT, Price3, resources->font_menu,255,0,0);
  
  char Price4[10];
  sprintf(Price4,": %u", PRICE_SHIP_4);
  if(player->hasShip[3] == 1)
    apply_text(renderer, (SCREEN_WIDTH-TEXT_SHOP_WIDTH)/2, SCREEN_HEIGHT/2 + (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4)*2, TEXT_SHOP_WIDTH, TEXT_SHOP_HIGHT, Price4, resources->font_menu,128,128,128); 
  else if (player->stars >= PRICE_SHIP_4)
    apply_text(renderer, (SCREEN_WIDTH-TEXT_SHOP_WIDTH)/2, SCREEN_HEIGHT/2 + (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4)*2, TEXT_SHOP_WIDTH, TEXT_SHOP_HIGHT, Price4, resources->font_menu,0,255,0);
  else
    apply_text(renderer, (SCREEN_WIDTH-TEXT_SHOP_WIDTH)/2, SCREEN_HEIGHT/2 + (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4)*2, TEXT_SHOP_WIDTH, TEXT_SHOP_HIGHT, Price4, resources->font_menu,255,0,0);
  

  switch (player->selectedShip)
      {
      case 1: apply_texture(resources->selected, renderer, (SCREEN_WIDTH+TEXT_SHOP_HIGHT)/2 + 100 , SCREEN_HEIGHT/2 - (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4));
      break;
      case 2: apply_texture(resources->selected, renderer, (SCREEN_WIDTH+TEXT_SHOP_HIGHT)/2 + 100, SCREEN_HEIGHT/2);
      break;
      case 3: apply_texture(resources->selected, renderer, (SCREEN_WIDTH+TEXT_SHOP_HIGHT)/2 + 100, SCREEN_HEIGHT/2 +  (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4));
      break;
      case 4: apply_texture(resources->selected, renderer, (SCREEN_WIDTH+TEXT_SHOP_HIGHT)/2 + 100, SCREEN_HEIGHT/2 + (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4)*2);
      break;  
      default: apply_texture(resources->selected, renderer, (SCREEN_WIDTH+TEXT_SHOP_HIGHT)/2 + 100 , SCREEN_HEIGHT/2 - (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4));
      break;
      }

  switch(game->select)
  {
    case 0: apply_texture(resources->select, renderer, (SCREEN_WIDTH-TEXT_SHOP_HIGHT)/2 - 100 , SCREEN_HEIGHT/2 - (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4));
      break;
    case 1: apply_texture(resources->select, renderer, (SCREEN_WIDTH-TEXT_SHOP_HIGHT)/2 - 100, SCREEN_HEIGHT/2);
      break;
    case 2: apply_texture(resources->select, renderer, (SCREEN_WIDTH-TEXT_SHOP_HIGHT)/2 - 100, SCREEN_HEIGHT/2 +  (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4));
        break;
    case 3: apply_texture(resources->select, renderer, (SCREEN_WIDTH-TEXT_SHOP_HIGHT)/2 - 100, SCREEN_HEIGHT/2 + (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4)*2);
      break;
    default:
        break;
  }

  apply_texture(resources->ship, renderer, SCREEN_WIDTH/2-TEXT_SHOP_WIDTH/2 -50, SCREEN_HEIGHT/2 - (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4));
  apply_texture(resources->ship2, renderer, SCREEN_WIDTH/2-TEXT_SHOP_WIDTH/2 -50, SCREEN_HEIGHT/2);
  apply_texture(resources->ship3, renderer, SCREEN_WIDTH/2-TEXT_SHOP_WIDTH/2 -50, SCREEN_HEIGHT/2 +  (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4));
  apply_texture(resources->ship4, renderer, SCREEN_WIDTH/2-TEXT_SHOP_WIDTH/2 -50,  SCREEN_HEIGHT/2 + (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4)*2);

  apply_texture(resources->star, renderer, SCREEN_WIDTH/2+TEXT_SHOP_WIDTH/2 +15, SCREEN_HEIGHT/2 - (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4));
  apply_texture(resources->star, renderer, SCREEN_WIDTH/2+TEXT_SHOP_WIDTH/2 +15, SCREEN_HEIGHT/2);
  apply_texture(resources->star, renderer, SCREEN_WIDTH/2+TEXT_SHOP_WIDTH/2 +15, SCREEN_HEIGHT/2 +  (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4));
  apply_texture(resources->star, renderer, SCREEN_WIDTH/2+TEXT_SHOP_WIDTH/2 +15,  SCREEN_HEIGHT/2 + (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4)*2);


  apply_texture(resources->return_menu, renderer, 5,5);
  apply_texture(resources->star, renderer, SCREEN_WIDTH-100,5);
  char starsNumber[500];
  sprintf(starsNumber,"%u",player->stars);
  apply_text(renderer, SCREEN_WIDTH-60, 10, 30, 30, starsNumber, resources->font_menu,255,228,54);
}

void menu_rules(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t *game)
{
  apply_text(renderer, SCREEN_WIDTH/2-(TEXT_MENU_WIDTH+TEXT_MENU_WIDTH/2)/2, SCREEN_HEIGHT/4 - (TEXT_MENU_HIGHT+TEXT_MENU_HIGHT/2)/2, (TEXT_MENU_WIDTH+TEXT_MENU_WIDTH/2), (TEXT_MENU_HIGHT+TEXT_MENU_HIGHT/2), "Rules", resources->font_menu,255,255,255); // affichage du texte

  apply_texture(resources->return_menu, renderer, 5,5);
}

void menu_credits(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t *game)
{
  apply_text(renderer, SCREEN_WIDTH/2-(TEXT_MENU_WIDTH+TEXT_MENU_WIDTH/2)/2, SCREEN_HEIGHT/4 - (TEXT_MENU_HIGHT+TEXT_MENU_HIGHT/2)/2, (TEXT_MENU_WIDTH+TEXT_MENU_WIDTH/2), (TEXT_MENU_HIGHT+TEXT_MENU_HIGHT/2), "Credits", resources->font_menu,255,255,255); // affichage du texte

  apply_texture(resources->return_menu, renderer, 5,5);
}

void apply_menu(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t *game, playerinfo_t *player)
{
    switch (game->gamemode)
    {
      case 0: menu_main(renderer, world, resources, game, player);
        break;
      case 2: menu_shop(renderer, world, resources, game, player);
        break;
      case 3: menu_rules(renderer, world, resources, game);
        break;
      case 4: menu_credits(renderer, world, resources, game);
        break;
      default: game->gamemode = 0;
        break;
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
      switch (player->selectedShip)
      {
      case 1: apply_sprite(renderer, resources->ship, &(world->ship), world->collision_wall);
      break;
      case 2: apply_sprite(renderer, resources->ship2, &(world->ship), world->collision_wall);
      break;
      case 3: apply_sprite(renderer, resources->ship3, &(world->ship), world->collision_wall);
      break;
      case 4: apply_sprite(renderer, resources->ship4, &(world->ship), world->collision_wall);
      break;  
      default: apply_sprite(renderer, resources->ship, &(world->ship), world->collision_wall);
      break;
      }
        
      apply_sprite(renderer, resources->finish_line, &(world->finish_line), 0);
      apply_walls(renderer, world, resources);
      apply_texts(renderer, world, resources, game);
    }

    // on met à jour l'écran
    update_screen(renderer);
}


