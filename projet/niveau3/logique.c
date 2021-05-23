/**
 * \file logique.c
 * \brief Module gérant la partie logique du jeu
 * \author LESNIAK Louis & SLIMANI Kamelia
 * \version 3.0 + extensions
 * \date 23 mai 2021
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

    for(int i = 0; i < NB_WALLS; i+=2) // On initialise les murs deux par deux pour obtenir un corridor 
    {

        int random_hole = rand() % HOLE_MAX +1; // Largueur de l'ouverture entre deux murs définie entre 1 et HOLE_MAX

        int random_width_wall1 = rand() % (SCREEN_WIDTH/METEORITE_SIZE-random_hole-1) + 1; // Nombre de météorite du côté gauche 
        int random_height_wall = rand() % random_width_wall1 + 1 ; // Hauteur des murs

        int random_width_wall2 = (SCREEN_WIDTH/METEORITE_SIZE - random_width_wall1-random_hole); // Nombre de météorite du côté droit

        init_sprite(&(world->meteorite[i]), (random_width_wall1*METEORITE_SIZE)/2, -(i)*SPACE_BETWEEN_WALLS, random_width_wall1*METEORITE_SIZE, random_height_wall*METEORITE_SIZE); // "-(i)*SPACE_BETWEEN_WALLS" : tous les SPACE_BETWEEN_WALLS on place un corridor aléatoire
        init_sprite(&(world->meteorite[i+1]),random_width_wall1*METEORITE_SIZE + (SCREEN_WIDTH-random_width_wall2*METEORITE_SIZE/2 - random_width_wall1*METEORITE_SIZE), -(i)*SPACE_BETWEEN_WALLS, random_width_wall2*METEORITE_SIZE, random_height_wall*METEORITE_SIZE); // x : "random_width_wall1*METEORITE_SIZE + (SCREEN_WIDTH-random_width_wall2*METEORITE_SIZE/2 - random_width_wall1*METEORITE_SIZE)" :  On place le mur à partir de la fin du mur 1 + la largueur du trou
    }
}   

void init_bonus(world_t * world)
{
    for(int i =0; i < NB_BONUS; i++)
    {
        unsigned int random_bonus = rand() % NB_BONUS_TYPE;
        int bonus_y;
        int bonus_x;
        unsigned int Getable;
        do
        {
            Getable = 1;
            bonus_y = - ((rand()% (SPACE_BETWEEN_WALLS/3) + SPACE_BETWEEN_WALLS/3) + (SPACE_BETWEEN_WALLS) * (rand() % NB_WALLS + 2)); // Dans la zone approximative entre deux murs (plus de probabilité)
            bonus_x = rand()% (SCREEN_WIDTH-SPRITE_SIZE*2) + SPRITE_SIZE*2; // dans la zone de l'écran
            init_sprite(&(world->bonus[i]), bonus_x, bonus_y, SPRITE_SIZE, SPRITE_SIZE);
            for(int j= 0; j < NB_WALLS; j++) // Si le bonus est en collision avec un autre sprite, on le réinitialise || Certain coût en performance mais le plus simple
            {
                if (sprites_collide(&(world->meteorite[j]), &(world->bonus[i])) || sprites_collide(&(world->meteorite[j%NB_BONUS]), &(world->bonus[i]))) // j%NB_BONUS nous évite ici de faire deux boucles pour gagner un peu de lignes au dépend d'un peu de performance. (NB_WALLS > NB_BONUS)
                    Getable = 0;
            }
        } while (Getable == 0);

        world->bonus_type[i]= random_bonus;
        world->is_bonus_available[i] = 1;
    }
}

void init_ennemies(world_t * world)
{
    for(int i =0; i < ENNEMIES_MAX; i++)
    {
        unsigned int Good;
        do
        {
        Good = 1;
        int which_wall = rand() % NB_WALLS/2;
        int position_y = world->meteorite[which_wall*2].y;
        int position_x = (SCREEN_WIDTH - world->meteorite[which_wall*2 +1].w - world->meteorite[which_wall*2].w )/2 + world->meteorite[which_wall*2].w; // On place l'ennemis dans le corridor
        init_sprite(&(world->ennemy[i]), position_x, position_y, SPRITE_SIZE, SPRITE_SIZE);
        world->is_ennemy_dead[i] = 0;

            for(int j =0; j < ENNEMIES_MAX; j++)
            {
                if (i != j && sprites_collide(&(world->ennemy[i]),  &(world->ennemy[j])))
                {
                    Good = 0;
                    break;
                }
            }
        } while (Good == 0);
    }
}

void init_missiles(world_t * world)
{
    for(int i = 0; i< MISSILE_MAX; i++) // Tous les missiles sont disponibles
        world->is_missile_free[i] = 1;
}

void init_data(world_t * world)
{

    
    init_walls(world); // Initialisation des murs
    init_bonus(world); // Initialisation des bonus
    init_ennemies(world); // Initialisation des ennemis 
    init_missiles(world); // Initialisation des missiles

    init_sprite(&(world->ship), (SCREEN_WIDTH-SPRITE_SIZE)/2, SCREEN_HEIGHT-SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);  // Initialisation du vaisseau
    init_sprite(&(world->finish_line), SCREEN_WIDTH-SCREEN_WIDTH/2, FINISH_LINE_Y_INIT, SCREEN_WIDTH, FINISH_LINE_HEIGHT);  // Initialisation de la ligne d'arrivé

    world->vy = INITIAL_SPEED; // Vitesse du jeu 
    world->gameover = 0; // On commence le jeu
    world->collision = 0; // Le vaisseau n'est pas entré en collision avec un mur ou un ennemi
    world->collision_finish_line = 0; // Le vaisseau n'est pas entré en collision avec la ligne d'arrivé
    world->hasShield = 0; // On n'a pas récupéré de bouclier

    
    
}

void print_sprite(sprite_t sprite) // Utile uniquement pour les tests
{
    printf("abscisse du sprite : %i\n", sprite.x);
    printf("ordonnée du sprite : %i\n", sprite.y);
    printf("largeur du sprite : %i\n", sprite.w);
    printf("hauteur du sprite : %i\n\n", sprite.h);
}


int is_game_over(world_t *world, gameinfo_t *game)
{
    return game->close == 1;
}

void update_data(world_t *world, gameinfo_t *game, playerinfo_t *player)
{
    if (game->gamemode == 1)
    {
        if(world->gameover == 1) // Si le jeu est fini, on retourne dans le menu
            game->gamemode = 0;
        
        if(game->finishTime >= TIME_LIMIT) // Si le temps limite est dépassé on met fin à la partie
            world->gameover = 1;

        world->finish_line.y += world->vy;

        update_sprites(world, player, game);
        depassement_g(&(world->ship));
        depassement_d(&(world->ship));
        
        handle_sprites_collision(&(world->ship), &(world->finish_line), world, player, game, 0);
    }
}

void update_sprites(world_t *world, playerinfo_t *player,  gameinfo_t *game)
{   
    for (unsigned int i=0; i<NB_WALLS; i++)
    {  
        world->meteorite[i].y += world->vy;
        handle_sprites_collision(&(world->ship), &(world->meteorite[i]), world, player, game, 1);
    }
    for (unsigned int i=0; i<NB_BONUS; i++)
    {  
        world->bonus[i].y += world->vy;
        handle_sprites_collision(&(world->ship), &(world->bonus[i]), world, player, game, 2);
    }
    for (unsigned int i=0; i < MISSILE_MAX; i++)
    {
        if (world->is_missile_free[i] == 0)
        {
            world->missile[i].y -= SPEED_MAX +5; // Le joueur ne peut jamais rattraper le missile
            if(world->missile[i].y - world->ship.y < -SCREEN_HEIGHT) // Si le missile dépasse l'écran; 
                world->is_missile_free[i] = 1; // la missile est libre
            for(int j = 0; j < ENNEMIES_MAX; j++)
                handle_sprites_collision(&(world->missile[i]), &(world->ennemy[j]), world, player, game, 3);
             for(int j = 0; j < NB_WALLS; j++)
                handle_sprites_collision(&(world->missile[i]), &(world->meteorite[j]), world, player, game, 4);
        }
    }
    for(unsigned int i=0; i < ENNEMIES_MAX; i++)
    {
        world->ennemy[i].y += world->vy;
        handle_sprites_collision(&(world->ship), &(world->ennemy[i]), world, player, game, 5);
    }
}

void depassement_g(sprite_t *sprite)
{
    if(sprite->w % 2 == 0)
    {
        if(sprite->x-sprite->w/2 < 0)
            sprite->x=0+sprite->w/2;
    }
    else // Si l'épaisseur du sprite est impair, il ne touchera pas la bordure de l'écran mais sera replacé à 0.5 de la bordure vu que l'on travaille avec des int 
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

void shoot(world_t *world)
{
    for(int i = 0; i < MISSILE_MAX; i++)
    {
        if (world->is_missile_free[i] == 1) // On prend le premier index disponible sur MISSILE_MAX
        {
            init_sprite(&(world->missile[i]), world->ship.x, world->ship.y-SPRITE_SIZE/2-5, 8, 8); // On initialise le missile au dessus du vaisseau
            world->is_missile_free[i] = 0; // On l'active
            break;
        }
    }
}

int abs(int a) { if(a < 0) a=-a; return a; }

int sprites_collide(sprite_t *sp1, sprite_t *sp2)
{
    if((abs(sp1->x - sp2->x) <= (sp1->w + sp2->w)/2) && (abs(sp1->y - sp2->y) <= (sp1->h + sp2->h)/2)) // expliqué dans le cours 
        return 1;
    return 0;
}

unsigned int retreive_index(sprite_t *sp1,  sprite_t *Array, unsigned int limit)
{
    unsigned int index;
    for(index = 0; index<limit; index++) // on retrouve l'indice du bonus à partir de l'adresse 
    {
        if(sp1 == &Array[index])// + index*sizeof(sprite_t)/16)
            break;
    }
    return index;
}

void handle_sprites_collision(sprite_t *sp1, sprite_t *sp2, world_t *world, playerinfo_t *player, gameinfo_t *game, int sprite_type)
{
    if(sprites_collide(sp1, sp2)==1) // deux sprites sont en collision
    {   
        switch (sprite_type)
        {
            case 0: // type du sprite est ligne d'arrivée
            {
                world->vy=0;
                world->collision_finish_line = 1;
                world->gameover=1;
            }
            break;
            case 1: // type du sprite est 'mur'
            {
                world->vy=0;
                world->collision=1;
                world->gameover=1;  
            break;
            }
            case 2:// type du sprite est bonus
            {
                unsigned int indice_bonus;
                indice_bonus = retreive_index(sp2, world->bonus, NB_BONUS);
                if(world->is_bonus_available[indice_bonus] == 1)
                {
                    switch (world->bonus_type[indice_bonus])
                    {
                        case 0: // étoile
                            player->stars++;
                        break;
                        case 1: // bouclier
                            world->hasShield = 1;
                        break;
                        case 2: // temps
                        if(game->finishTime > TIME_BONUS/1000)
                            game->startTime += TIME_BONUS;
                        else
                            game->startTime = game->finishTime*1000;
                        break;
                        default: break;
                    }
                    world->is_bonus_available[indice_bonus] = 0;
                }
            }
            break;
            case 3: // collision missile - ennemi
            {
                unsigned int index_missile = retreive_index(sp1, world->missile, MISSILE_MAX);
                unsigned int index_ennemy = retreive_index(sp2, world->ennemy, ENNEMIES_MAX);
                if ( world->is_ennemy_dead[index_ennemy] == 0 && world->is_missile_free[index_missile] == 0)
                {
                    world->is_ennemy_dead[index_ennemy] = 1;
                    world->is_missile_free[index_missile] = 1;   
                }
            }
            break;
            case 4: // missile-mur
            {
                unsigned int index_missile = retreive_index(sp1, world->missile, MISSILE_MAX);
                if (world->is_missile_free[index_missile] == 0)
                    world->is_missile_free[index_missile] = 1;   

            }
            break;
            case 5: // collision vaisseau - ennemi
            {
                unsigned int index_ennemy = retreive_index(sp2, world->ennemy, ENNEMIES_MAX);
                if(world->hasShield==1 && world->is_ennemy_dead[index_ennemy] == 0)
                {
                    world->is_ennemy_dead[index_ennemy] = 1;
                    world->hasShield = 0;
                }
                else if ( world->is_ennemy_dead[index_ennemy] == 0)
                {
                    world->vy=0;
                    world->collision=1;
                    world->gameover=1;
                }
            }
            break;
            default:
            break;
        }
    }
}
