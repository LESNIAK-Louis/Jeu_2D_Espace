/**
 * \file transition.c
 * \brief Module gérant la transition entre les modules logique et graphique
 * \author LESNIAK Louis & SLIMANI Kamelia
 * \version 3.0
 * \date 14 mai 2021
 */

#include "sdl2-light.h"
#include "sdl2-ttf-light.h"

#include "transition.h"
#include "logique.h"
#include "graphique.h"
#include "definition.h"

#include <stdio.h>

void clean(SDL_Window *window, SDL_Renderer * renderer, resources_t *resources, world_t * world, gameinfo_t * game)
{
    clean_data(world);
    clean_resources(resources);
    clean_sdl(renderer,window);
}

void init(SDL_Window **window, SDL_Renderer ** renderer, resources_t *resources, world_t * world)
{
    init_ttf();
    init_sdl(window,renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_resources(*renderer,resources);
}

void handle_events(SDL_Event *event,world_t *world)
{
    Uint8 *keystates;
    while( SDL_PollEvent( event ) ) 
    {
        
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) 
        {
            world->collision_mur = 1; // On perd
            world->gameover = 1;  //On indique la fin du jeu
        }
       
        //si une touche est appuyée
        if(event->type == SDL_KEYDOWN)
        {
            if(event->key.keysym.sym == SDLK_RIGHT)
            {
                world->vaisseau.x += MOVING_STEP;
            }
            else if(event->key.keysym.sym == SDLK_LEFT)
            {
                world->vaisseau.x -= MOVING_STEP;
            }
            else if(event->key.keysym.sym == SDLK_UP)
            {
                world->vy += 1;
            }
            else if(event->key.keysym.sym == SDLK_DOWN)
            {
                if (world->vy > 1) // Plus de difficulté
                    world->vy -= 1;
            }
            else if(event->key.keysym.sym == SDLK_ESCAPE)
            {
                world->collision_mur = 1; // On perd
                world->gameover = 1; // Le jeu est fini
            }
        }
    }
}

void save_score(world_t world, gameinfo_t game)
{
    if(world.collision_mur == 0)
    {
        char Name[50]; // On définit à 50 le nombre de caractères maximal au nom du joueur
        printf("*Score Saver*\n");
        printf("Enter your name (<50 char) : ");
        if (fgets(Name, sizeof(Name), stdin) != NULL)
        {
            FILE *fptr;   
            fptr= fopen("Score","a");
            if (fptr != NULL) 
            {
                fprintf(fptr, "%us- ", game.time/1000);
                fprintf(fptr, "%s", Name);
            }

            fclose(fptr);
        }
    }
}