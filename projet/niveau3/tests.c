/**
 * \file tests.c
 * \brief Programme testant la partie logique du jeu
 * \author LESNIAK Louis & SLIMANI Kamelia
 * \version 2.0
 * \date 14 avril 2021
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
    printf("Vitesse Avant : %d | Valeur world.collision_mur : %d\n", world->vy, world->collision_mur);
    handle_sprites_collision(sp1, sp2, world, 1);
    printf("Vitesse Après : %d | Valeur world.collision_mur : %d\n", world->vy, world->collision_mur);
}

void test_handle_sprites_collision()
{

    world_t world;
    world.vy = 15;
    world.collision_mur = 0;

    sprite_t sprite1;
    init_sprite(&sprite1, 2, 2, 1, 1);

    sprite_t sprite2;
    init_sprite(&sprite2, 3, 10, 1, 1);

    test_handle_sprites_collision_param(&sprite1, &sprite2, &world);
    init_sprite(&sprite2, 3, 2, 1, 1);
    test_handle_sprites_collision_param(&sprite1, &sprite2, &world);
}

void test_init_walls_param(world_t * world)
{
    printf("Position des murs \n");
    init_walls(world);
}

void test_init_walls()
{
    world_t * world;

    test_init_walls_param(world);

}

int main()
{
    test_init_sprite();
    test_depassement_g();
    test_depassement_d();
    test_sprites_collide();
    test_handle_sprites_collision();
    test_init_walls();

    getchar();
    return 1;
}

