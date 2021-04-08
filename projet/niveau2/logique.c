//
//  logique.c
//  
//
//  Created by Kamelia Slimani on 07/04/2021.
//

#include "logique.h"
#include "graphique.h"
#include "definition.h"

void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite){
    SDL_Rect dst = {0, 0, 0, 0};
    
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    dst.x = sprite->x; dst.y=sprite->y;
    
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    
}


void init_sprite(sprite_t* sprite,int x,int y,int w,int h)
{
    sprite->x=x;
    sprite->y=y;
    sprite->w=w;
    sprite->h=h;
}

void init_data(world_t * world){

    world->vaisseau.h = SHIP_SIZE;
    world->vaisseau.w = SHIP_SIZE;
    world->vaisseau.x = (SCREEN_WIDTH-world->vaisseau.w)/2;
    world->vaisseau.y = SCREEN_HEIGHT-world->vaisseau.h;
    print_sprite(world->vaisseau);

    world->ligne_arrive.h = FINISH_LINE_HEIGHT;
    world->ligne_arrive.w = SCREEN_WIDTH;
    world->ligne_arrive.x = (SCREEN_WIDTH-world->ligne_arrive.w)/2;
    world->ligne_arrive.y = FINISH_LINE_HEIGHT;
    print_sprite(world->ligne_arrive);

    world->vy = INITIAL_SPEED;

    world->mur.h = 3*METEORITE_SIZE;
    world->mur.w = 7*METEORITE_SIZE;
    world->mur.x = (SCREEN_WIDTH-world->mur.w)/2;
    world->mur.y = (SCREEN_HEIGHT-world->mur.h)/2;
    print_sprite(world->mur);

    //on n'est pas à la fin du jeu
    world->gameover = 0;
}

/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */


void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
    
}


int is_game_over(world_t *world){
    return world->gameover;
}



void update_data(world_t *world){
    world->ligne_arrive.y += world->vy;
    world->mur.y += world->vy;
    depassement_g(world->vaisseau);
    depassement_d(world->vaisseau);
    handle_sprites_collision(world->vaisseau, world->mur, world_t *world);
}

