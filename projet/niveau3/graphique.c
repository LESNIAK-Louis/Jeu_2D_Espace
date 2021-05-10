/**
 * \file graphique.c
 * \brief Module gérant la partie graphique du jeu
 * \author LESNIAK Louis & SLIMANI Kamelia
 * \version 2.0
 * \date 15 avril 2021
 */

#include "sdl2-light.h"
#include "sdl2-ttf-light.h"
#include "graphique.h"
#include "logique.h"
#include "definition.h"

#include <stdlib.h>
#include <stdio.h>


void clean_resources(resources_t *resources){
    clean_texture(resources->background);
    clean_texture(resources->vaisseau);
    clean_texture(resources->ligne_arrive);
    clean_texture(resources->meteorite);
    clean_font(resources->font);
}


void init_resources(SDL_Renderer *renderer, resources_t *resources){
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

/*void apply_meteorite(SDL_Renderer *renderer, world_t *world, resources_t *resources)
{
  for(int i=0; i < world->mur.h/METEORITE_SIZE; i++) // Ligne de taille METEORITE_SIZE
    {
      for(int j=0; j < world->mur.w/METEORITE_SIZE; j++) // Colonne de taille METEORITE_SIZE
      {
        apply_texture(resources->meteorite, renderer, (world->mur.x - world->mur.w/2)+METEORITE_SIZE*j, (world->mur.y - world->mur.h/2)+METEORITE_SIZE*i); // On place une resource de météorite au "tableau" à l'indice (i,j) 
      }
    }
}
*/

void  apply_walls(SDL_Renderer *renderer, world_t * world, resources_t *resources)
{

  for(int l=0; l < 6; l++) // Parcours du tableau de météorites 
  {
    for(int i=0; i < world->meteorite[l].h/METEORITE_SIZE; i++) // Ligne de taille METEORITE_SIZE
    {
      for(int j=0; j < world->meteorite[l].w/METEORITE_SIZE; j++) // Colonne de taille METEORITE_SIZE
      {
        apply_texture(resources->meteorite, renderer, (world->meteorite[l].x - world->meteorite[l].w/2)+METEORITE_SIZE*j, (world->meteorite[l].y - world->meteorite[l].h/2)+METEORITE_SIZE*i); // On place une resource de météorite au "tableau" à l'indice (i,j) 
      }
    }
  }
}

void refresh_graphics(SDL_Renderer *renderer, world_t *world, resources_t *resources)
{
    
    //on vide le renderer
    clear_renderer(renderer);
    
    //application des resources dans le renderer
    apply_background(renderer, resources->background);
    apply_sprite(renderer, resources->vaisseau, &(world->vaisseau), world->collision_mur);
    apply_sprite(renderer, resources->ligne_arrive, &(world->ligne_arrive), 0);
    //apply_meteorite(renderer, world, resources);
    apply_walls(renderer, world, resources);
    //temps ecoulé en haut à gauche 
    char Temp[255];
    
    
    apply_text(renderer, 20, 10, 60, 40, "Time :", resources->font);  
    char chaine[10];
    sprintf(chaine,"%d",SDL_GetTicks()/1000);
    apply_text(renderer, 90, 10, 20, 40, chaine , resources->font);  

    if(world->collision_mur==1){
      apply_text(renderer, SCREEN_WIDTH/3, SCREEN_HEIGHT/3, 90, 40, "You lost !", resources->font);
      world->gameover=1;
      
    }
    if(is_game_over(world)!=0){

    apply_text(renderer, SCREEN_WIDTH/3, SCREEN_HEIGHT/3, 90, 40, "You finished in  ", resources->font);
    char ch[10];
    sprintf(ch,"%d",SDL_GetTicks()/1000);
    apply_text(renderer, SCREEN_WIDTH/3, SCREEN_HEIGHT/3, 40, 20, ch , resources->font);
    world->gameover=1;
      
     
}
    // on met à jour l'écran
    update_screen(renderer);
}


