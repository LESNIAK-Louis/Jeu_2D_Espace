/**
 * \file main.c
 * \brief Programme principal initial du niveau 2
 * \author LESNIAK Louis & SLIMANI Kamelia
 * \version 3.0
 * \date 14 mai 2021
 */
#include "sdl2-light.h"
#include "sdl2-ttf-light.h"

#include "logique.h"
#include "graphique.h"
#include "transition.h"

/**
 *  \brief programme principal qui implémente la boucle du jeu
 */
int main( int argc, char* args[] )
{
    SDL_Event event;
    world_t world;
    gameinfo_t game;
    resources_t resources;
    SDL_Renderer *renderer;
    SDL_Window *window;
    
    //initialisation du jeu
    init(&window,&renderer,&resources,&world);
    unsigned int startTime = SDL_GetTicks();
  
    while(is_game_over(&world)==0)
    { //tant que le jeu n'est pas fini
        
        //gestion des évènements
        handle_events(&event,&world);
        
       
        //mise à jour des données liée à la physique du monde
        update_data(&world);

        //rafraichissement de l'écran
        refresh_graphics(renderer,&world,&resources, &game);
        
        // pause de 10 ms pour controler la vitesse de rafraichissement
        pause(10);
    }

    pause(2000); // Pause de 2000ms = 2sec après la détection de fin de partie

    //nettoyage final
    clean(window,renderer,&resources,&world,&game);

    //sauvegarde du score (extension)
    save_score(world, game);
   
    return 0;
}
