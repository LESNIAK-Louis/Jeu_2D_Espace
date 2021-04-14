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
    sprite.x=5;
    sprite.y=4;
    sprite.h=2;
    sprite.w=10;
    test_depassement_g_param(&sprite);
    sprite.w=9;
    sprite.x=4;
    test_depassement_g_param(&sprite);
    sprite.x=5;
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
    sprite.x=SCREEN_WIDTH-2;
    sprite.y=4;
    sprite.h=2;
    sprite.w=10;
    test_depassement_d_param(&sprite);
    sprite.w=9;
    sprite.x=SCREEN_WIDTH-4;
    test_depassement_d_param(&sprite);
    sprite.x=SCREEN_WIDTH-3;
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
    sprite1.x=2;
    sprite1.y=2;
    sprite1.h=1;
    sprite1.w=1;

    sprite_t sprite2;
    sprite2.x=5;
    sprite2.y=2;
    sprite2.h=1;
    sprite2.w=1;

    test_sprites_collide_param(&sprite1, &sprite2);

    sprite2.x=3;
    sprite2.y=3;
    test_sprites_collide_param(&sprite1, &sprite2);

    sprite2.x=4;
    sprite2.y=2;
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
    sprite1.x=2;
    sprite1.y=2;
    sprite1.h=1;
    sprite1.w=1;

    sprite_t sprite2;

    sprite2.x=3;
    sprite2.y=10;
    sprite2.h=1;
    sprite2.w=1;

    test_handle_sprites_collision_param(&sprite1, &sprite2, &world);
    sprite2.y=3;
    test_handle_sprites_collision_param(&sprite1, &sprite2, &world);
}

int main()
{
    test_init_sprite();
    test_depassement_g();
    test_depassement_d();
    test_sprites_collide();
    test_handle_sprites_collision();

    getchar();
    return 1;
}

