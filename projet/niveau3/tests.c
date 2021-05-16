/**
 * \file tests.c
 * \brief Programme testant la partie logique du jeu
 * \author LESNIAK Louis & SLIMANI Kamelia
 * \version 3.0
 * \date 14 mai 2021
 */

#include "definition.h"
#include "logique.h"
#include <stdio.h>

void test_init_sprite_param(sprite_t *sprite, int x, int y, int w, int h)
{
    init_sprite(sprite, x, y, w, h);
    print_sprite(*sprite);
}

void test_init_sprite()
{
    printf("\n**** test_init_sprite ****\n\n");
    sprite_t sprite;
    test_init_sprite_param(&sprite, 3, 1, 6, 5);
    test_init_sprite_param(&sprite, 6, 4, 2, 1);
    test_init_sprite_param(&sprite, 2, 2, 2, 2);
}



void test_depassement_g_param(sprite_t *sprite)
{
    printf("Avant test depassement g :\n");
    print_sprite(*sprite);
    depassement_g(sprite);
    printf("Après test depassement g :\n");
    print_sprite(*sprite);
}

void test_depassement_g() 
{  
    printf("\n**** test_depassement_g ****\n\n");
    sprite_t sprite;
    init_sprite(&sprite, 5, 4, 10, 2);
    test_depassement_g_param(&sprite);
    init_sprite(&sprite, 4, 4, 9, 2);
    test_depassement_g_param(&sprite);
    init_sprite(&sprite, 5, 4, 9, 2);
    test_depassement_g_param(&sprite);
}



void test_depassement_d_param(sprite_t *sprite)
{
    printf("Avant test depassement d :\n");
    print_sprite(*sprite);
    depassement_d(sprite);
    printf("Après test depassement d :\n");
    print_sprite(*sprite);
    
}

void test_depassement_d()
{
    printf("\n**** test_depassement_d ****\n\n");
    sprite_t sprite;
    init_sprite(&sprite, SCREEN_WIDTH-2, 4, 10, 2);
    test_depassement_d_param(&sprite);
    init_sprite(&sprite, SCREEN_WIDTH-4, 4, 9, 2);
    test_depassement_d_param(&sprite);
    init_sprite(&sprite, SCREEN_WIDTH-3, 4, 9, 2);
    test_depassement_d_param(&sprite);
}



void test_sprites_collide_param(sprite_t *sprite1, sprite_t *sprite2)
{
    if(sprites_collide(sprite1, sprite2) == 1)
        printf("Collision\n");
    else
        printf("Pas Collision\n");
}

void test_sprites_collide()
{
    printf("\n**** test_sprites_collide ****\n\n");
    sprite_t sprite1;
    init_sprite(&sprite1, 2, 2, 1, 1);

    sprite_t sprite2;
    init_sprite(&sprite2, 5, 2, 1, 1);

    test_sprites_collide_param(&sprite1, &sprite2);

    init_sprite(&sprite2, 3, 3, 1, 1);
    test_sprites_collide_param(&sprite1, &sprite2);

    init_sprite(&sprite2, 4, 2, 1, 1);
    test_sprites_collide_param(&sprite1, &sprite2);
}



void test_handle_sprites_collision_param(sprite_t *sp1, sprite_t *sp2, world_t *world)
{
    printf("Vitesse Avant : %d | Valeur world.collision_wall : %d\n", world->vy, world->collision_wall);
    handle_sprites_collision(sp1, sp2, world, 1);
    printf("Vitesse Après : %d | Valeur world.collision_wall : %d\n", world->vy, world->collision_wall);
}

void test_handle_sprites_collision()
{
    printf("\n**** test_handle_sprites_collision ****\n\n");
    world_t world;
    world.vy = 15;
    world.collision_wall = 0;

    sprite_t sprite1;
    init_sprite(&sprite1, 2, 2, 1, 1);

    sprite_t sprite2;
    init_sprite(&sprite2, 3, 10, 1, 1);

    test_handle_sprites_collision_param(&sprite1, &sprite2, &world);
    init_sprite(&sprite2, 3, 2, 1, 1);
    test_handle_sprites_collision_param(&sprite1, &sprite2, &world);
}



void test_init_walls_param(world_t  world)
{
    for (int i=0; i < 6; i++){
        print_sprite(world.meteorite[i]);
    }
}

void test_init_walls()
{
    printf("\n**** test_init_walls ****\n\n");
    world_t  world;
    init_walls(&world);
    test_init_walls_param(world);

}



void test_update_walls_param(world_t  world){
    printf("Mise à jour des murs \n");
    world.vy=INITIAL_SPEED;
    update_walls(&world);
    for (int i=0; i < 6; i++){
        print_sprite(world.meteorite[i]);
    }
    
}

void test_update_walls()
{
    printf("\n**** test_update_walls ****\n\n");
    world_t  world;
    init_walls(&world);
  
    test_update_walls_param(world);
}



int main()
{
    test_init_sprite();
    test_depassement_g();
    test_depassement_d();
    test_sprites_collide();
    test_handle_sprites_collision();
    
    test_init_walls();
    test_update_walls();
    getchar();
    return 1;
}

