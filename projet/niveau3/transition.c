/**
 * \file transition.c
 * \brief Module gérant la transition entre les modules différents modules
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

#include <stdio.h>

void clean(SDL_Window *window, SDL_Renderer * renderer, resources_t *resources, world_t * world, gameinfo_t * game)
{
    clean_resources(resources);
    clean_sdl(renderer,window);
}

void init(SDL_Window **window, SDL_Renderer ** renderer, resources_t *resources, world_t * world, gameinfo_t *game, playerinfo_t *player)
{
    init_player(player);
    init_ttf();
    init_sdl(window,renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    init_resources(*renderer,resources);
    
    game->gamemode = 0; // On est dans le menu
    game->select = 0; // On sélectionne l'élement 0 du menu
}


void init_player(playerinfo_t *player)
{
    // Nom du joueur
    char Name[MAX_LENGTH_NAME]; // On définit à 50 le nombre de caractères maximal au nom du joueur
    printf("*SpaceCorridor*\n");
    printf("Enter your name (<%u char) : ", MAX_LENGTH_NAME);
    if(!fgets(player->name, sizeof(player->name)*sizeof(char), stdin))
        exit(1);

    // Informations sur le joueur : précédents scores
    FILE *fptr;   
    
    char* Score = concat_array_playername(player, "Score_", strlen("Score_"));
    fptr= fopen(Score,"r");
    free(Score);
    if (fptr != NULL) // déjà joué auparavant
    {
        // Dernier temps
        char ligne[MAX_LENGTH_NAME+TIME_LIMIT+4]; // On met en place un buffer pour pouvoir lire les document textes
        player->bestTime = TIME_LIMIT+1;

        while(fgets(ligne, sizeof(ligne), fptr)!=NULL) // Pour chaque ligne du document
        {
            unsigned int Temps = formatted_charArray_to_uint(ligne);
            if (Temps < player->bestTime) // On converti le string en unsigned int
                player->bestTime = Temps;
        } 
        player->lastTime = formatted_charArray_to_uint(ligne);
        fclose(fptr);
    }
    else // jamais joué auparavant ou fichier supprimé
    {
        player->lastTime = TIME_LIMIT+1;
        player->bestTime = TIME_LIMIT+1;
    }
    // étoiles et textures achetés : 

    char infoLigne[50];
    FILE *userConfigptr;  
    char* userConfig = concat_array_playername(player, "userInfo_", strlen("userInfo_"));
    userConfigptr = fopen(userConfig, "r");
    free(userConfig);
    if (userConfigptr != NULL) // déjà joué auparavant
    {
        for(int i = 0; i<6; i++) // Pour chaque ligne du document
        {
            if(fgets(infoLigne, sizeof(infoLigne), userConfigptr) != NULL) 
            {
                if (i == 0)
                    player->stars = formatted_charArray_to_uint(infoLigne);
                else if ( i == 5)
                    player->selectedShip = formatted_charArray_to_uint(infoLigne);
                else
                    player->hasShip[i-1] = formatted_charArray_to_uint(infoLigne);
            }
        }
        fclose(userConfigptr);
    }      
    else // jamais joué auparavant ou fichier supprimé
    {
        player->hasShip[0] = 1;
        player->hasShip[1] = 0;
        player->hasShip[2] = 0;
        player->hasShip[3] = 0;
        player->stars = 0;
    }
}

void print_credits()
{
    FILE* fptr;

     printf("\n***** Credits *****\n\n");

    fptr= fopen("ressources/Licences.txt","r");
    if (fptr != NULL)
    {
        char ligne[500]; // On met en place un buffer pour pouvoir lire les documents textes

        while(fgets(ligne, sizeof(ligne), fptr)!=NULL) // Pour chaque ligne du document
            printf("%s", ligne);
        fclose(fptr);
    }
    else
        printf("ERROR file not found\n");

    printf("\n*******************\n\n");
}

void handle_events(SDL_Event *event, world_t *world, gameinfo_t *game, playerinfo_t *player)
{
    Uint8 *keystates;
    while( SDL_PollEvent( event ) ) 
    {
        switch(event->type)
        {
            case SDL_QUIT : //Si l'utilisateur a cliqué sur le X de la fenêtre
                world->collision = 1; // On perd
                world->gameover = 1;  //On indique la fin du jeu
                game->close = 1; // On demande la fermeture de l'application
                break;
            case SDL_KEYDOWN :  // Si une touche est appuyée

                if(game->gamemode == 1) // On est en cours de jeu
                {
                    switch (event->key.keysym.sym)
                    {
                        case SDLK_RIGHT :
                            world->ship.x += MOVING_STEP;
                            break;
                        case SDLK_LEFT :
                            world->ship.x -= MOVING_STEP;
                            break;
                        case SDLK_UP :
                        if(world->vy < SPEED_MAX)
                            world->vy += 1;
                            break;
                        case SDLK_DOWN :
                            if (world->vy > 1) // Plus de difficulté
                                world->vy -= 1;
                            break;
                        case SDLK_SPACE :
                            shoot(world);
                            break;
                        default:
                        break;
                    }
                }
                else // On est dans le menu
                {
                    switch (event->key.keysym.sym)
                    {
                        case SDLK_UP :
                            if (game->select > 0)
                                game->select -= 1;
                            break;
                        case SDLK_DOWN :
                            if (game->select < 3)
                                game->select += 1;
                            break;
                        case SDLK_SPACE :
                            if(game->gamemode == 0)
                            {
                                if (game->select == 0) // On commence le jeu
                                {
                                     init_data(world);
                                     game->startTime=SDL_GetTicks();
                                     game->finishTime=0;
                                }
                                else if (game->select == 3)
                                    print_credits();

                                game->gamemode = game->select+1;
                                game->select = 0;
                            }
                            else if(game->gamemode == 2)
                                buy_select_ship(player, game->select);
                            break;
                        case SDLK_ESCAPE : 
                                if(game->gamemode != 0)
                                {
                                    game->select = game->gamemode-1;
                                    game->gamemode = 0; // On est dans le menu
                                }
                                else
                                    game->close = 1;
                            break;
                        default:
                        break;
                    }
                }
                break;
            default:
            break;
        }
    }
}

char* concat_array_playername(playerinfo_t *player, char *array, unsigned int arraySize)
{
    char *Concat = malloc(arraySize*sizeof(char) + strlen(player->name)*sizeof(char)); // On alloue la mémoire nécessaire
    strcpy(Concat, array);
    for(int i = 0; i < strlen(player->name)-1; i++) // On copie tout les éléments de player_name à la suite de Concat sauf le retour de ligne imposé par le fgets() à la position  player->name[strlen(player->name)-1]
        Concat[arraySize+i] = player->name[i]; 
    return Concat;
}


unsigned int formatted_charArray_to_uint(char *Array)
{
    unsigned int index_s;
    for(index_s = 0; Array[index_s]!= 's'; index_s++); // on regarde à quel index se trouve 's' (+1)
    char *Value = malloc(index_s*sizeof(char));  // On alloue la mémoire nécessaire
    for(int i = 2; i < index_s; i++) 
        Value[i-2] = Array[i];

    Value[index_s] = '\0'; // fin de lecture pour atoi()
    unsigned int uintValue = atoi(Value);
    free(Value); // On libère la mémoire
    return uintValue;
}


void save_score(world_t *world, gameinfo_t *game, playerinfo_t *player)
{
    if(world->gameover == 1 && game->gamemode == 1)
    {
        if (world->collision_finish_line == 1 && game->finishTime < TIME_LIMIT) // partie gagnée
        {
            if (player->stars < STARS_LIMIT) // ajout étoile(s) gagné(s)
                player->stars += STARS_GAME_WON;

            // Sauvegarde du score
            FILE *fptr;   
            char* Concat = concat_array_playername(player, "Score_", strlen("Score_"));
            fptr= fopen(Concat,"a");
            free(Concat); // On libère la mémoire
            if (fptr != NULL) 
            {
                fprintf(fptr, ": %us \n",game->finishTime);
                fclose(fptr);
            }
            player->lastTime = game->finishTime;
            if (player->lastTime < player->bestTime)
                player->bestTime = player->lastTime;
        }
        pause(2000); // Pause de 2000ms = 2sec après la détection de fin de jeu
    }
}

void save_info(playerinfo_t *player)
{
    FILE *userInfoptr;
    char* Concat = concat_array_playername(player, "userInfo_", strlen("userInfo_"));
    userInfoptr= fopen(Concat,"w");
    free(Concat); // On libère la mémoire
    if (userInfoptr != NULL) 
    {
        fprintf(userInfoptr, "$t%us ", player->stars);
        for(int i = 0; i<4; i++)
        {
            fprintf(userInfoptr, "\n$%d%us ",i, player->hasShip[i]);
        }
        fprintf(userInfoptr, "\n$t%us ", player->selectedShip);
        fclose(userInfoptr);
    }  
}
