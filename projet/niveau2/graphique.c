//
//  graphique.c
//  
//
//  Created by Kamelia Slimani on 07/04/2021.
//

#include "graphique.h"
#include "logique.h"
#include "definition.h"
#include <stdlib>


void print_sprite(sprite_t sprite){
    printf("abscisse du sprite : %i\n",sprite.x);
    printf("ordonnée du sprite : %i\n",sprite.y);
    printf("hauteur du sprite : %i\n",sprite.h);
    printf("largeur du sprite : %i\n\n",sprite.w);
}



void handle_events(SDL_Event *event,world_t *world){
    Uint8 *keystates;
    while( SDL_PollEvent( event ) ) {
        
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            //On indique la fin du jeu
            world->gameover = 1;
        }
       
         //si une touche est appuyée
         if(event->type == SDL_KEYDOWN){
             if(event->key.keysym.sym == SDLK_RIGHT){
                 printf("La touche -> est appuyée\n");
                 world->vaisseau.x += MOVING_STEP;
              }
              else if(event->key.keysym.sym == SDLK_LEFT){
                 printf("La touche <- est appuyée\n");
                  world->vaisseau.x -= MOVING_STEP;
              }
              else if(event->key.keysym.sym == SDLK_UP){
                 printf("La touche up est appuyée\n");
                  world->vy += 1;
              }
              else if(event->key.keysym.sym == SDLK_DOWN){
                 printf("La touche down est appuyée\n");
                  world->vy -= 1;
              }
              else if(event->key.keysym.sym == SDLK_ESCAPE){
                //On indique la fin du jeu
                 world->gameover = 1;
              }
         }
    }
}


void clean_textures(textures_t *textures){
    clean_texture(textures->background);
    clean_texture(textures->vaisseau);
    clean_texture(textures->ligne_arrive);
    clean_texture(textures->meteorite);
}


void init_textures(SDL_Renderer *renderer, textures_t *textures){
    textures->background = load_image( "ressources/space-background.bmp",renderer);
    textures->vaisseau = load_image( "ressources/sprite.bmp",renderer);
    textures->ligne_arrive = load_image( "ressources/finish_line.bmp",renderer);
    textures->meteorite = load_image( "ressources/meteorite.bmp",renderer);
}


void apply_background(SDL_Renderer *renderer, SDL_Texture *texture){
    if(texture != NULL){
      apply_texture(texture, renderer, 0, 0);
    }
}


void apply_meteorite(SDL_Renderer *renderer, world_t *world, textures_t *textures, int hauteur, int largeur)
{
  for(int i=0; i < hauteur; i++)
    {
      for(int j=0; j < largeur; j++)
      {
        apply_texture(textures->meteorite, renderer, world->mur.x+METEORITE_SIZE*j, world->mur.y+METEORITE_SIZE*i);
      }
    }
}


void refresh_graphics(SDL_Renderer *renderer, world_t *world, textures_t *textures){
    
    //on vide le renderer
    clear_renderer(renderer);
    
    //application des textures dans le renderer
    apply_background(renderer, textures->background);

    apply_sprite(renderer, textures->vaisseau, &(world->vaisseau));
    apply_sprite(renderer, textures->ligne_arrive, &(world->ligne_arrive));
    apply_meteorite(renderer, world, textures, 3, 7);
    
    // on met à jour l'écran
    update_screen(renderer);
}



void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world){
    clean_data(world);
    clean_textures(textures);
    clean_sdl(renderer,window);
}



void init(SDL_Window **window, SDL_Renderer ** renderer, textures_t *textures, world_t * world)
{
    init_sdl(window,renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_textures(*renderer,textures);
}

void depassement_g(sprite_t sprite){
    if(sprite.x-sprite.w/2 < 0){
        sprite.x=0;
    }
}
void depassement_d(sprite_t sprite){
    if(sprite.x+sprite.w/2 >SCREEN_WIDTH){
        sprite.x=SCREEN_WIDTH-1;
    }
}

int sprites_collide(sprite_t *sp1, sprite_t *sp2){
    if((abs(x1 −x2) <= (w1 +w2)/2)&&(abs(y1 −y2) <= (h1 +h2)/2)){
        return 1;
    }
    return 0;
}

int handle_sprites_collision(sprite_t *sp1, sprite_t *sp2, world_t *world,int make_disappear){
    if(sprites_collide(sp1, sp2)==1){
        world->vy=0;
        if(make_disappear!=0){
//            il faut faire disparaitre SP1
        }
    }
    return EXIT_SUCCESS;
}
