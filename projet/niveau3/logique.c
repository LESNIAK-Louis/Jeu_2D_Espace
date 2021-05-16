/**
 * \file logique.c
 * \brief Module gérant la partie logique du jeu
 * \author LESNIAK Louis & SLIMANI Kamelia
 * \version 3.0
 * \date 14 mai 2021
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

void init_walls(world_t * world)
{
    // premier mur
    init_sprite(&(world->meteorite[0]), 48, 0, 96, 192);
    // deuxième mur
    init_sprite(&(world->meteorite[1]), 252, 0, 96, 192);
    // troisième mur
    init_sprite(&(world->meteorite[2]), 16, -352, 32, 160);
    // quatrième mur
    init_sprite(&(world->meteorite[3]), 188, -352, 224, 160);
    // cinquième mur
    init_sprite(&(world->meteorite[4]), 48, -672, 96, 192);
    // sixième mur
    init_sprite(&(world->meteorite[5]), 252, -672, 96, 192);
}   

void init_data(world_t * world)
{

    //le mur de meteorites
    init_walls(world);

    init_sprite(&(world->ship), (SCREEN_WIDTH-SHIP_SIZE)/2, SCREEN_HEIGHT-SHIP_SIZE, SHIP_SIZE, SHIP_SIZE);
    init_sprite(&(world->finish_line), SCREEN_WIDTH-SCREEN_WIDTH/2, FINISH_LINE_Y_INIT, SCREEN_WIDTH, FINISH_LINE_HEIGHT);

    world->vy = INITIAL_SPEED;
    world->gameover = 0; // On commence le jeu
    world->collision_wall = 0; // Le vaisseau n'est pas entré en collision avec un mur.
    world->collision_finish_line = 0; // Le vaisseau n'est pas entré en collision avec la ligne d'arrivé.
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

int is_game_over(world_t *world, gameinfo_t *game)
{
    return game->close == 1;
}

void update_data(world_t *world, gameinfo_t *game)
{
    if (game->gamemode == 1)
    {
        if(world->gameover == 1)
            game->gamemode = 0;
        
        if(game->finishTime >= TIME_LIMIT)
            world->gameover = 1;

        world->finish_line.y += world->vy;

        update_walls(world);
        depassement_g(&(world->ship));
        depassement_d(&(world->ship));
        
        handle_sprites_collision(&(world->ship), &(world->finish_line), world, 0);
    }
}

void update_walls(world_t *world)
{   
    for (int i=0; i<6; i++)
    {  
        world->meteorite[i].y += world->vy;
        handle_sprites_collision(&(world->ship), &(world->meteorite[i]), world, 1);
    }
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

void handle_sprites_collision(sprite_t *sp1, sprite_t *sp2, world_t *world, int sprite_type)
{
    if(sprites_collide(sp1, sp2)==1)
    {   
        world->vy=0;
        if (sprite_type==0) // type du sprite est ligne d'arrivé
        {
            world->collision_finish_line = 1;
            world->gameover=1;  
        }
        else if(sprite_type==1) // type du sprite est wall
        {
            world->collision_wall=1;
            world->gameover=1;  
        } 
    }
}
