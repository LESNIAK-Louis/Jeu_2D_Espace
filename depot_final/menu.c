/**
 * \file menu.c
 * \brief Module gérant le fonctionnement du menu
 * \author LESNIAK Louis & SLIMANI Kamelia
 * \version 3.0 + extensions
 * \date 23 mai 2021
 */

#include "sdl2-light.h"
#include "sdl2-ttf-light.h"

#include "transition.h"
#include "logique.h"
#include "graphique.h"
#include "definition.h"
#include "menu.h"

#include <stdlib.h>
#include <stdio.h>

void buy_select_ship(playerinfo_t *player, unsigned int ShipNumber)
{
    switch (ShipNumber)
    {
        case 0: 
            if (player->stars >= PRICE_SHIP_1 && player->hasShip[0] == 0)
            {
                player->stars-=PRICE_SHIP_1;
                player->hasShip[0] = 1;
            }
            else if (player->hasShip[0] == 1)
                player->selectedShip = 1;
        break;
        case 1: 
            if (player->stars >= PRICE_SHIP_2 && player->hasShip[1] == 0)
            {
                player->stars-=PRICE_SHIP_2;
                player->hasShip[1] = 1;
            }
            else if (player->hasShip[1] == 1)
                player->selectedShip = 2;
        break;
        case 2: 
            if (player->stars >= PRICE_SHIP_3 && player->hasShip[2] == 0)
            {
                player->stars-=PRICE_SHIP_3;
                player->hasShip[2] = 1;
            }
            else if (player->hasShip[2] == 1)
                player->selectedShip = 3;
        break;
        case 3: 
            if (player->stars >= PRICE_SHIP_4 && player->hasShip[3] == 0)
            {
                player->stars-=PRICE_SHIP_4;
                player->hasShip[3] = 1;
            }
            else if (player->hasShip[3] == 1)
                player->selectedShip = 4;
        break;
        default:
        break;
    }
}

void print_stars(SDL_Renderer *renderer, resources_t *resources, playerinfo_t *player, int x)
{
  apply_texture(resources->star, renderer, x-35,5);
  char starsNumber[10]; // buffer de 10 chars largement suffisant, peut représenter 9.999.999.999 étoiles
  sprintf(starsNumber,"%u",player->stars);
  apply_text(renderer, x, 10, 30, 30, starsNumber, resources->font_menu,255,228,54);
}

void print_select(SDL_Renderer *renderer, resources_t *resources, gameinfo_t *game, int x, int y)
{
    switch(game->select) // affichage de la sélection
  {
    case 0: apply_texture(resources->select, renderer, x , SCREEN_HEIGHT/2 - y);
      break;
    case 1: apply_texture(resources->select, renderer, x, SCREEN_HEIGHT/2);
      break;
    case 2: apply_texture(resources->select, renderer, x, SCREEN_HEIGHT/2 +  y);
      break;
    case 3: apply_texture(resources->select, renderer, x, SCREEN_HEIGHT/2 + y*2);
      break;
    default: break;
  }
}

void menu_main(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t *game, playerinfo_t *player)
{
  apply_text(renderer, SCREEN_WIDTH/2-(TEXT_MENU_WIDTH+TEXT_MENU_WIDTH/2)/2, SCREEN_HEIGHT/4 - (TEXT_MENU_HIGHT+TEXT_MENU_HIGHT/2)/2, (TEXT_MENU_WIDTH+TEXT_MENU_WIDTH/2), (TEXT_MENU_HIGHT+TEXT_MENU_HIGHT/2), "Menu", resources->font_menu, 255, 255, 255); 
  apply_text(renderer, (SCREEN_WIDTH-TEXT_MENU_WIDTH)/2, SCREEN_HEIGHT/2 - (TEXT_MENU_HIGHT+TEXT_MENU_HIGHT/4), TEXT_MENU_WIDTH, TEXT_MENU_HIGHT, "Play", resources->font_menu,255 ,255 ,255); 
  apply_text(renderer, (SCREEN_WIDTH-TEXT_MENU_WIDTH)/2, SCREEN_HEIGHT/2, TEXT_MENU_WIDTH, TEXT_MENU_HIGHT, "Shop", resources->font_menu,255,255,255); 
  apply_text(renderer, (SCREEN_WIDTH-TEXT_MENU_WIDTH)/2, SCREEN_HEIGHT/2 +  (TEXT_MENU_HIGHT+TEXT_MENU_HIGHT/4), TEXT_MENU_WIDTH, TEXT_MENU_HIGHT, "Infos", resources->font_menu,255,255,255); 
  apply_text(renderer, (SCREEN_WIDTH-TEXT_MENU_WIDTH)/2, SCREEN_HEIGHT/2 + (TEXT_MENU_HIGHT+TEXT_MENU_HIGHT/4)*2, TEXT_MENU_WIDTH, TEXT_MENU_HIGHT, "Credits", resources->font_menu,255,255,255); 

  if (player->bestTime == TIME_LIMIT+1 || player->lastTime == TIME_LIMIT+1) // Si le joueur n'a jamais gagné de partie 
    apply_text(renderer, SCREEN_WIDTH/2-(TEXT_MENU_WIDTH+50)/2, SCREEN_HEIGHT-TEXT_MENU_HIGHT, TEXT_MENU_WIDTH+50, TEXT_MENU_HIGHT, "Welcome !", resources->font_menu,255,228,54); 
  else // Si le joueur a déjà gagné
  {
    char bestTime[TIME_LIMIT + 10];
    sprintf(bestTime,"Record : %us", player->bestTime);
    char lastTime[TIME_LIMIT+MAX_LENGTH_NAME+13];
    sprintf(lastTime,"Last game won : %us", player->lastTime);
    apply_text(renderer, 5, SCREEN_HEIGHT-30*2, TEXT_MENU_WIDTH, 25, bestTime, resources->font_menu,255,228,54); // affichage du meilleur temps
    apply_text(renderer, 5, SCREEN_HEIGHT-30, TEXT_MENU_WIDTH, 25, lastTime, resources->font_menu,255,228,54); // affichage du dernier temps (victoire)
  }

  print_select(renderer, resources, game, (SCREEN_WIDTH-TEXT_MENU_WIDTH)/2 - 50, (TEXT_MENU_HIGHT+TEXT_MENU_HIGHT/4));
  print_stars(renderer, resources , player, 40);
}

void menu_shop(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t *game, playerinfo_t *player)
{
  apply_text(renderer, SCREEN_WIDTH/2-(TEXT_MENU_WIDTH+TEXT_MENU_WIDTH/2)/2, SCREEN_HEIGHT/4 - (TEXT_MENU_HIGHT+TEXT_MENU_HIGHT/2)/2, (TEXT_MENU_WIDTH+TEXT_MENU_WIDTH/2), (TEXT_MENU_HIGHT+TEXT_MENU_HIGHT/2), "Shop", resources->font_menu,255,255,255);

  char Price1[10];
  sprintf(Price1,": %u", PRICE_SHIP_1);
  /* Change la couleur du texte en fonction de si la texture est déjà acheté et sinon en fonction de si l'achat est possible ou non*/
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
  

  switch (player->selectedShip) // On affiche une texture indiquant quel vaisseau est sélectionné en jeu
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

  print_select(renderer, resources, game, (SCREEN_WIDTH-TEXT_SHOP_HIGHT)/2 - 100, (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4));

  /* Affichage des textures de vaisseau achetable */
  apply_texture(resources->ship, renderer, SCREEN_WIDTH/2-TEXT_SHOP_WIDTH/2 -50, SCREEN_HEIGHT/2 - (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4));
  apply_texture(resources->ship2, renderer, SCREEN_WIDTH/2-TEXT_SHOP_WIDTH/2 -50, SCREEN_HEIGHT/2);
  apply_texture(resources->ship3, renderer, SCREEN_WIDTH/2-TEXT_SHOP_WIDTH/2 -50, SCREEN_HEIGHT/2 +  (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4));
  apply_texture(resources->ship4, renderer, SCREEN_WIDTH/2-TEXT_SHOP_WIDTH/2 -50,  SCREEN_HEIGHT/2 + (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4)*2);

  /* Affichage des textures des étoiles à côté des prix */
  apply_texture(resources->star, renderer, SCREEN_WIDTH/2+TEXT_SHOP_WIDTH/2 +15, SCREEN_HEIGHT/2 - (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4));
  apply_texture(resources->star, renderer, SCREEN_WIDTH/2+TEXT_SHOP_WIDTH/2 +15, SCREEN_HEIGHT/2);
  apply_texture(resources->star, renderer, SCREEN_WIDTH/2+TEXT_SHOP_WIDTH/2 +15, SCREEN_HEIGHT/2 +  (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4));
  apply_texture(resources->star, renderer, SCREEN_WIDTH/2+TEXT_SHOP_WIDTH/2 +15,  SCREEN_HEIGHT/2 + (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4)*2);


  apply_texture(resources->return_menu, renderer, 5,5);
  print_stars(renderer, resources , player, SCREEN_WIDTH-60);
}

void menu_infos(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t *game)
{

  apply_text(renderer, (SCREEN_WIDTH-TEXT_RULES_WIDTH)/2, SCREEN_HEIGHT/2 - (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4), TEXT_RULES_WIDTH, TEXT_SHOP_HIGHT, "Meteorites", resources->font_menu,255,0,0);
  apply_text(renderer, (SCREEN_WIDTH-TEXT_RULES_WIDTH)/2, SCREEN_HEIGHT/2, TEXT_RULES_WIDTH, TEXT_SHOP_HIGHT, "Ennemies", resources->font_menu,255,0,0); 
  apply_text(renderer, (SCREEN_WIDTH-TEXT_RULES_WIDTH)/2, SCREEN_HEIGHT/2 +  (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4), TEXT_RULES_WIDTH, TEXT_SHOP_HIGHT, "Proctections", resources->font_menu,0,255,0);
  apply_text(renderer, (SCREEN_WIDTH-TEXT_RULES_WIDTH)/2, SCREEN_HEIGHT/2 + (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4)*2, TEXT_RULES_WIDTH, TEXT_SHOP_HIGHT, "3s bonus", resources->font_menu,0,255,0);
  apply_text(renderer, (SCREEN_WIDTH-TEXT_RULES_WIDTH)/2, SCREEN_HEIGHT/2 + (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4)*3, TEXT_RULES_WIDTH, TEXT_SHOP_HIGHT, "Stars to grab", resources->font_menu,255,228,54);
  
  /* Affichage des textures de vaisseau achetable */
  apply_texture(resources->meteorite, renderer, SCREEN_WIDTH/2-TEXT_RULES_WIDTH/2 -50, SCREEN_HEIGHT/2 - (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4));
  apply_texture(resources->ennemy_ship, renderer, SCREEN_WIDTH/2-TEXT_RULES_WIDTH/2 -50, SCREEN_HEIGHT/2);
  apply_texture(resources->shield, renderer, SCREEN_WIDTH/2-TEXT_RULES_WIDTH/2 -50, SCREEN_HEIGHT/2 +  (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4));
  apply_texture(resources->time, renderer, SCREEN_WIDTH/2-TEXT_RULES_WIDTH/2 -50,  SCREEN_HEIGHT/2 + (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4)*2);
  apply_texture(resources->star, renderer, SCREEN_WIDTH/2-TEXT_RULES_WIDTH/2 -50,  SCREEN_HEIGHT/2 + (TEXT_SHOP_HIGHT+TEXT_SHOP_HIGHT/4)*3);

  apply_text(renderer, SCREEN_WIDTH/2-(TEXT_MENU_WIDTH+TEXT_MENU_WIDTH/2)/2, SCREEN_HEIGHT/4 - (TEXT_MENU_HIGHT+TEXT_MENU_HIGHT/2)/2, (TEXT_MENU_WIDTH+TEXT_MENU_WIDTH/2), (TEXT_MENU_HIGHT+TEXT_MENU_HIGHT/2), "Infos", resources->font_menu,255,255,255); 

  apply_texture(resources->return_menu, renderer, 5,5);
}

void menu_credits(SDL_Renderer *renderer, world_t *world, resources_t *resources, gameinfo_t *game)
{
  apply_text(renderer, SCREEN_WIDTH/2-(TEXT_MENU_WIDTH+TEXT_MENU_WIDTH/2)/2, SCREEN_HEIGHT/4 - (TEXT_MENU_HIGHT+TEXT_MENU_HIGHT/2)/2, (TEXT_MENU_WIDTH+TEXT_MENU_WIDTH/2), (TEXT_MENU_HIGHT+TEXT_MENU_HIGHT/2), "Credits", resources->font_menu,255,255,255); 
  apply_text(renderer, SCREEN_WIDTH/2-(TEXT_MENU_WIDTH+TEXT_MENU_WIDTH/2)/2, SCREEN_HEIGHT/2, (TEXT_MENU_WIDTH+TEXT_MENU_WIDTH/2), (TEXT_MENU_HIGHT+TEXT_MENU_HIGHT/2), "(View in console)", resources->font_menu,255,255,255); 

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
      case 3: menu_infos(renderer, world, resources, game);
        break;
      case 4: menu_credits(renderer, world, resources, game);
        break;
      default: game->gamemode = 0;
        break;
    }

}