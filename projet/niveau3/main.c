/**
 * \file main.c
 * \brief Programme principal initial du niveau 2
 * \author LESNIAK Louis & SLIMANI Kamelia
 * \version 2.0
 * \date 15 avril 2021
 */



 
 //avanacement jusqu'à la question5.7  


#include "sdl2-light.h"
#include "sdl2-ttf-light.h"
#include <stdio.h>
#include <stdlib.h>

#include "logique.h"
#include "graphique.h"
#include "definition.h"

/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des resources, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param resources les resources
* \param world le monde
*/


void clean(SDL_Window *window, SDL_Renderer * renderer, resources_t *resources, world_t * world){
    clean_data(world);
    clean_resources(resources);
    clean_sdl(renderer,window);
}


/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des resources, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param resources les resources
 * \param world le monde
 */

void init(SDL_Window **window, SDL_Renderer ** renderer, resources_t *resources, world_t * world)
{
    init_ttf();
    init_sdl(window,renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_resources(*renderer,resources);

}

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
    resources_t resources;
    SDL_Renderer *renderer;
    SDL_Window *window;
    
    //initialisation du jeu
    init(&window,&renderer,&resources,&world);
  
    while(is_game_over(&world)==0){ //tant que le jeu n'est pas fini
        
        //gestion des évènements
        handle_events(&event,&world);
        
       
        //mise à jour des données liée à la physique du monde
        update_data(&world);

        //rafraichissement de l'écran
        refresh_graphics(renderer,&world,&resources);
        
        // pause de 10 ms pour controler la vitesse de rafraichissement
        pause(10);
        

    }
   
    if (world.collision_mur!=0){
      printf("You lost!\n");
       world.gameover=1;
    }
      
    printf("You finished in : %i ", SDL_GetTicks()/1000); 
    printf("secondes \n");
    
 

    
    exit(EXIT_SUCCESS);
   
    //nettoyage final
    clean(window,renderer,&resources,&world);
    
   
    return 0;
}
