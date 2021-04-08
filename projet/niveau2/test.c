//
//  test.c/Users/kamelia/Desktop/Methodo2/methodo2021-mi-tp-4.1-lesniak-slimani/projet/niveau1/main.c
//  
//
//  Created by Kamelia Slimani on 07/04/2021.
//

#include <stdio.h>
#include "definition.h"
#include "logique.h"
 
test_init_sprite_param(sprite_t sprite, int x, int y, int h, int w){
    init_sprite;
    print_sprite;
}

test_init_sprite(){
    sprite_t sprite;
    sprite.x=3;
    sprite.y=1;
    sprite.h=6;
    sprite.w=5;
    test_init_sprite_param(sprite, sprite.x, sprite.y, sprite.h, sprite.w);
}
test_depassement_g_param(sprite_t sprite){
    test_depassement_d(sprite);
    
}

test_depassement_g(){
    sprite_t sprite;
    sprite.x=7;
    sprite.y=4;
    sprite.h=2;
    sprite.w=9;
    test_depassement_g_param(sprite);
}

test_depassement_d_param(sprite_t sprite){
    test_depassement_d(sprite2);
    
}

test_depassement_g(){
    sprite_t sprite2;
    sprite2.x=7;
    sprite2y=4;
    sprite2.h=2;
    sprite2.w=9;
    test_depassement_d_param(sprite2);
}
test_sprites_collide_param(sprite_t *sprite1, sprite_t *sprite2){
    sprites_collide(sprite1, sprite2);
}
test_sprites_collide(){
    test_depassement_d_param(sprite2);
}

int main()
{
    test_init_sprite();
    test_depassement_g();
    test_depassement_d();
    test_sprites_collide();
}

