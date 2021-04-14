/**
 * \file main.c
 * \brief Programme principal initial du niveau 2
 * \author LESNIAK Louis & SLIMANI Kamelia
 * \version 2.0
 * \date 14 avril 2021
 */

#include "sdl2-light.h"
//#include <stdio.h>

#include "logique.h"
#include "graphique.h"
#include "definition.h"

/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */

void handle_events(SDL_Event *event,world_t *world){
    Uint8 *keystates;
    while( SDL_PollEvent( event ) ) {
        
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            //On indique la fin du jeu
            world->gameover = 1;
        }
       
         //si une touche est appuyée
         if(event->type == SDL_KEYDOWN){
             if(event->key.keysym.sym == SDLK_RIGHT){
                 //printf("La touche -> est appuyée\n");
                 world->vaisseau.x += MOVING_STEP;
              }
              else if(event->key.keysym.sym == SDLK_LEFT){
                 //printf("La touche <- est appuyée\n");
                  world->vaisseau.x -= MOVING_STEP;
              }
              else if(event->key.keysym.sym == SDLK_UP){
                 //printf("La touche up est appuyée\n");
                  world->vy += 1;
              }
              else if(event->key.keysym.sym == SDLK_DOWN){
                 //printf("La touche down est appuyée\n");
                  world->vy -= 1;
              }
              else if(event->key.keysym.sym == SDLK_ESCAPE){
                //On indique la fin du jeu
                 world->gameover = 1;
              }
         }
    }
}


/**
 *  \brief programme principal qui implémente la boucle du jeu
 */
int main( int argc, char* args[] )
{
    SDL_Event event;
    world_t world;
    textures_t textures;
    SDL_Renderer *renderer;
    SDL_Window *window;

    //initialisation du jeu
    init(&window,&renderer,&textures,&world);
    
    while(!is_game_over(&world)){ //tant que le jeu n'est pas fini
        
        //gestion des évènements
        handle_events(&event,&world);
        
        //mise à jour des données liée à la physique du monde
        update_data(&world);
        
        //rafraichissement de l'écran
        refresh_graphics(renderer,&world,&textures);
        
        // pause de 10 ms pour controler la vitesse de rafraichissement
        pause(10);
    }
    
    //nettoyage final
    clean(window,renderer,&textures,&world);
    
    
    return 0;
}
