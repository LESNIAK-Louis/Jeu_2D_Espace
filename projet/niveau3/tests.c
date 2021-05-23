/**
 * \file tests.c
 * \brief Programme testant la partie logique du jeu
 * \author LESNIAK Louis & SLIMANI Kamelia
 * \version 3.0 + extensions
 * \date 23 mai 2021
 */

#include "definition.h"
#include "logique.h"
#include <stdio.h>
#include <stdlib.h>

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


void test_init_walls_param(world_t *world)
{
    init_walls(world);
    for (int i=0; i < 6; i++){
        print_sprite(world->meteorite[i]);
    }
}

void test_init_walls()
{
    printf("\n**** test_init_walls ****\n\n");
    world_t  world;
    test_init_walls_param(&world);

}
/* remplacé par update_sprites

void test_update_walls_param(world_t  world){
    printf("Mise à jour des murs \n");
    world.vy=INITIAL_SPEED;
    update_walls(&world);
    for (int i=0; i < NB_WALLS; i++)
        print_sprite(world.meteorite[i]);
}

void test_update_walls()
{
    printf("\n**** test_update_walls ****\n\n");
    world_t  world;
    init_walls(&world);
    test_update_walls_param(world);
}
*/

void test_init_bonus_param(world_t *world)
{
    init_bonus(world);
    for (int i=0; i < NB_BONUS; i++)
    {
        printf("Bonus type : %u\n", world->bonus_type[i]);
        print_sprite(world->bonus[i]);
    }
}

void test_init_bonus()
{
    printf("\n**** test_init_bonus ****\n\n");
    world_t world;
    test_init_bonus_param(&world);
}


void test_init_ennemies_param(world_t * world)
{
    init_ennemies(world);
     for (int i=0; i < ENNEMIES_MAX; i++)
     {
        printf("Ennemy dead ? : %u\n", world->is_ennemy_dead[i]);
        print_sprite(world->ennemy[i]);
     }
}
void test_init_ennemies()
{
    printf("\n**** test_init_ennemis ****\n\n");
    world_t world;
    test_init_ennemies_param(&world);
}

void test_init_missiles_param(world_t * world)
{
    init_missiles(world);
    for (int i=0; i < MISSILE_MAX; i++)
    {
        printf("Missile available ? : %u\n", world->is_missile_free[i]);
        print_sprite(world->missile[i]);
    }
}

void test_init_missiles()
{
    printf("\n**** test_init_missiles ****\n\n");
    world_t world;
    test_init_missiles_param(&world);
}

void test_shoot_param(world_t *world)
{
    init_data(world);
    for(int i = 0 ; i < MISSILE_MAX; i++)
    {
        shoot(world);
        print_sprite(world->missile[i]);
    }

}

void test_shoot()
{
    printf("\n**** test_shoot ****\n\n");
    world_t world;
    test_shoot_param(&world);
}


void test_update_sprites_param(world_t *world, playerinfo_t *player,  gameinfo_t *game)
{
    printf("Mise à jour des sprites \n\n\n");
    update_sprites(world, player, game);
    for (int i=0; i < NB_WALLS; i++)
    {
        printf("Meteorites : \n");
        print_sprite(world->meteorite[i]);
    }
    for (int i=0; i < NB_BONUS; i++)
    {
        printf("Bonus : \n");
        print_sprite(world->bonus[i]);
    }
    for (int i=0; i < ENNEMIES_MAX; i++)
    {
        printf("Ennemy : \n");
        print_sprite(world->ennemy[i]);
    }
    for (int i=0; i < MISSILE_MAX; i++)
    {
        printf("Missile : \n");
        print_sprite(world->missile[i]);
    }
}

void test_update_sprites()
{
    printf("\n**** test_update_sprites ****\n\n");
    world_t  world;
    playerinfo_t player;
    gameinfo_t game;
    init_data(&world);
    test_update_sprites_param(&world, &player, &game);
}


void test_handle_sprites_collision_param(sprite_t sp1, sprite_t sp2, world_t world, playerinfo_t player, gameinfo_t game, int sprite_type)
{
    if (sprite_type == 1)
    {
        printf("\nship-Wall : \n");
        printf("Vitesse Avant : %d | Valeur world.collision : %u\n", world.vy, world.collision);
        handle_sprites_collision(&sp1, &sp2, &world, &player, &game, sprite_type);
        printf("Vitesse Après : %d | Valeur world.collision : %u\n", world.vy, world.collision);
    }
    else if (sprite_type == 5)
    {
        printf("\nship-ennemy : \n");
        printf("Vitesse Avant : %d | Valeur world.collision : %u\n", world.vy, world.collision);
        handle_sprites_collision(&sp1, &sp2, &world, &player, &game, sprite_type);
        printf("Vitesse Après : %d | Valeur world.collision : %u\n", world.vy, world.collision);
    }
    
}

void test_handle_sprites_collision()
{
    printf("\n**** test_handle_sprites_collision ****\n\n");
    world_t world;
    playerinfo_t player;
    gameinfo_t game;
    init_data(&world);
    
    sprite_t sprite1;
    init_sprite(&sprite1, 2, 2, 1, 1);

    sprite_t sprite2;
    init_sprite(&sprite2, 3, 10, 1, 1);

    init_sprite(&world.ennemy[0], 3, 2, 1, 1);

    world.is_ennemy_dead[0] = 0;
    
    test_handle_sprites_collision_param(sprite1, sprite2, world, player, game, 1);
    init_sprite(&sprite2, 2, 2, 1, 1);
    test_handle_sprites_collision_param(sprite1, sprite2, world, player, game, 1);
    
}



int main()
{
    test_init_sprite();
    test_depassement_g();
    test_depassement_d();
    test_sprites_collide();
    
    test_init_walls();
    //test_update_walls(); // Remplacé
    test_init_bonus();
    test_init_ennemies();
    test_shoot();

    test_update_sprites();
    test_handle_sprites_collision();

    getchar();
    return 1;
}

