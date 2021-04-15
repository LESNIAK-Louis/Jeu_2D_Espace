/**
 * \file logique.c
 * \brief Module gérant la partie logique du jeu
 * \author LESNIAK Louis & SLIMANI Kamelia
 * \version 2.0
 * \date 14 avril 2021
 */

#include "logique.h"
#include "definition.h"
#include <stdio.h>
#include <stdlib.h>


void init_sprite(sprite_t* sprite,int x,int y,int w,int h)
{
    sprite->x=x;
    sprite->y=y;
    sprite->w=w;
    sprite->h=h;
}

void init_data(world_t * world)
{
    init_sprite(&(world->vaisseau), (SCREEN_WIDTH-SHIP_SIZE)/2, SCREEN_HEIGHT-SHIP_SIZE, SHIP_SIZE, SHIP_SIZE);
    //print_sprite(world->vaisseau);
    init_sprite(&(world->ligne_arrive), SCREEN_WIDTH-SCREEN_WIDTH/2, FINISH_LINE_HEIGHT, SCREEN_WIDTH, FINISH_LINE_HEIGHT);
    //print_sprite(world->ligne_arrive);
    init_sprite(&(world->mur), SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 3*METEORITE_SIZE, 7*METEORITE_SIZE);
    //print_sprite(world->mur);

    world->vy = INITIAL_SPEED;

    //on n'est pas à la fin du jeu
    world->gameover = 0;

    //le vaisseau n'est pas entré en collision avec un mur
    world->collision_mur = 0;
}

void print_sprite(sprite_t sprite)
{
    printf("abscisse du sprite : %i\n", sprite.x);
    printf("ordonnée du sprite : %i\n", sprite.y);
    printf("largeur du sprite : %i\n", sprite.w);
    printf("hauteur du sprite : %i\n\n", sprite.h);
}

void clean_data(world_t *world)
{
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
}


int is_game_over(world_t *world)
{
    return world->gameover;
}



void update_data(world_t *world)
{
    world->ligne_arrive.y += world->vy;
    world->mur.y += world->vy;
    depassement_g(&(world->vaisseau));
    depassement_d(&(world->vaisseau));
    //print_sprite(world->vaisseau);
    handle_sprites_collision(&(world->vaisseau), &(world->mur), world, 1);
    handle_sprites_collision(&(world->vaisseau), &(world->ligne_arrive), world, 0);
}


void depassement_g(sprite_t *sprite)
{
    if(sprite->w % 2 == 0)
    {
        if(sprite->x-sprite->w/2 < 0)
            sprite->x=0+sprite->w/2;
    }
    else // Si l'épaisseur du sprite est impair, il ne touchera pas la bordure de l'écran mais seras replacé à 0.5 de la bordure vu que l'on travaille avec des int 
    {
        if(sprite->x - (sprite->w/2+1) < 0)
            sprite->x=0+sprite->w/2+1;
    }

}
void depassement_d(sprite_t *sprite)
{
    if(sprite->w % 2 == 0)
    {
        if(sprite->x+sprite->w/2 > SCREEN_WIDTH)
            sprite->x=SCREEN_WIDTH-sprite->w/2;
    }
    else // Même chose pour la droite
    {
        if(sprite->x + sprite->w/2 +1 > SCREEN_WIDTH)
            sprite->x=SCREEN_WIDTH-sprite->w/2-1;
    }
}

int abs(int a) 
{
    if(a < 0) 
        a=-a;
    return a;
}

int sprites_collide(sprite_t *sp1, sprite_t *sp2)
{
    if((abs(sp1->x - sp2->x) <= (sp1->w + sp2->w)/2) && (abs(sp1->y - sp2->y) <= (sp1->h + sp2->h)/2))
        return 1;
    return 0;
}

void handle_sprites_collision(sprite_t *sp1, sprite_t *sp2, world_t *world, int make_disappear)
{
    if(sprites_collide(sp1, sp2)==1)
    {
        world->vy=0;
        if(make_disappear!=0)
        {
            world->collision_mur=1;
        }
    }
}
