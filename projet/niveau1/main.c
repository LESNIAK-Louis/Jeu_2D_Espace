/**
 * \file main.c
 * \brief Programme principal initial du niveau 1
 * \author SLIMANI Kamelia & LESNIAK Louis
 * \version 1.0
 * \date 15 Avril 2021
 */

#include "sdl2-light.h"
#include <stdio.h>


/**
 * \brief Largeur de l'écran de jeu
 */
#define SCREEN_WIDTH 300

/**
 * \brief Hauteur de l'écran de jeu
 */
#define SCREEN_HEIGHT 480


/**
 * \brief Taille d'un vaisseau
 */

#define SHIP_SIZE 32


/**
 * \brief Taille d'un météorite
*/

#define METEORITE_SIZE 32


/**
 * \brief Hauteur de la ligne d'arrivée
 */


#define FINISH_LINE_HEIGHT 10


/**
 * \brief Pas de déplacement horizontal du vaisseau
*/

#define MOVING_STEP 10


/**
  * \brief Vitesse initiale de déplacement vertical des éléments du jeu 
*/

#define INITIAL_SPEED 2


/**
 * \brief Représentation d'un sprite du jeu
*/

struct sprite_s {
    int x; /*!< Champ indiquant l'abscisse de la position */
    int y; /*!< Champ indiquant l'ordonnée de la position */
    int h; /*!< Champ indiquant la hauteur*/
    int w; /*!< Champ indiquant la largeur*/
};

/**
 * \brief Type qui correspond aux données du sprite
 */

typedef struct sprite_s sprite_t;

/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
*/

struct textures_s{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* vaisseau; /*!< Texture liée à l'image du vaisseau. */
    SDL_Texture* ligne_arrive; /*!< Texture liée à la ligne d'arrivée */
    SDL_Texture* meteorite; /*!< Texture liée à une météorite */
};


/**
 * \brief Type qui correspond aux textures du jeu
*/

typedef struct textures_s textures_t;


/**
 * \brief Représentation du monde du jeu
*/

struct world_s{
  sprite_t vaisseau;  /*!< Champ réprésentant le sprite vaisseau */
  sprite_t ligne_arrive;  /*!< Champ réprésentant la ligne d'arrivée */
  sprite_t mur; /*!< Champ réprésentant un mur de météorites */
  int vy;
  int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */

};

/**
 * \brief Type qui correspond aux données du monde
 */

typedef struct world_s world_t;

/**
 * \brief La fonction initialise la position du sprite
 * \param sprite vaisseau
 * \param x abscisse de la position du sprite
 * \param y ordonnée de la position du sprite
 * \param w largeur de la position du sprite
 * \param h hauteur de la position du sprite
 */
void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite){
    SDL_Rect dst = {0, 0, 0, 0};
    
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    dst.x = sprite->x - sprite->w/2; dst.y=sprite->y - sprite->h/2;
    
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    
}


/**
 * \brief La fonction initialise la position du sprite
 * \param sprite vaisseau
 * \param x abscisse de la position du sprite
 * \param y ordonnée de la position du sprite
 * \param w largeur de la position du sprite
 * \param h hauteur de la position du sprite
 */

void init_sprite(sprite_t* sprite,int x,int y,int w,int h)
{
    sprite->x=x;
    sprite->y=y;
    sprite->w=w;
    sprite->h=h;
}


/**
 * \brief La fonction affiche la position du sprite
 * \param sprite vaisseau
 */

void print_sprite(sprite_t sprite){
    printf("abscisse du sprite : %i\n",sprite.x);
    printf("ordonnée du sprite : %i\n",sprite.y);
    printf("hauteur du sprite : %i\n",sprite.h);
    printf("largeur du sprite : %i\n\n",sprite.w);
}


/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */


void init_data(world_t * world){

    world->vaisseau.h = SHIP_SIZE; 
    world->vaisseau.w = SHIP_SIZE; 
    world->vaisseau.x = (SCREEN_WIDTH-world->vaisseau.w)/2;
    world->vaisseau.y = SCREEN_HEIGHT-world->vaisseau.h;
    print_sprite(world->vaisseau);

    world->ligne_arrive.h = FINISH_LINE_HEIGHT;
    world->ligne_arrive.w = SCREEN_WIDTH;
    world->ligne_arrive.x = SCREEN_WIDTH-(world->ligne_arrive.w)/2;
    world->ligne_arrive.y = FINISH_LINE_HEIGHT;
    print_sprite(world->ligne_arrive);

    world->vy = INITIAL_SPEED;

    world->mur.h = 7*METEORITE_SIZE;
    world->mur.w = 3*METEORITE_SIZE;
    world->mur.x = SCREEN_WIDTH/2;
    world->mur.y = SCREEN_HEIGHT/2;
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



/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */

int is_game_over(world_t *world){
    return world->gameover;
}



/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */

void update_data(world_t *world){
    world->ligne_arrive.y += world->vy;
    world->mur.y += world->vy;
}



/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */

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

/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
*/

void clean_textures(textures_t *textures){
    clean_texture(textures->background);
    clean_texture(textures->vaisseau);
    clean_texture(textures->ligne_arrive);
    clean_texture(textures->meteorite);
}



/**
 * \brief La fonction initialise les textures nécessaires à l'affichage graphique du jeu
 * \param screen la surface correspondant à l'écran de jeu
 * \param textures les textures du jeu
*/

void init_textures(SDL_Renderer *renderer, textures_t *textures){
    textures->background = load_image( "ressources/space-background.bmp",renderer);
    textures->vaisseau = load_image( "ressources/sprite.bmp",renderer);
    textures->ligne_arrive = load_image( "ressources/finish_line.bmp",renderer);
    textures->meteorite = load_image( "ressources/meteorite.bmp",renderer);
}


/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param texture la texture liée au fond
*/

void apply_background(SDL_Renderer *renderer, SDL_Texture *texture){
    if(texture != NULL){
      apply_texture(texture, renderer, 0, 0);
    }
}


/**
 * \brief La fonction applique la texture des météorites sur le mur
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param textures les textures
*/
void apply_meteorite(SDL_Renderer *renderer, world_t *world, textures_t *textures)
{
  for(int i=0; i < world->mur.h/METEORITE_SIZE; i++)
    {
      for(int j=0; j < world->mur.w/METEORITE_SIZE; j++)
      {
        apply_texture(textures->meteorite, renderer, (world->mur.x - world->mur.w/2)+METEORITE_SIZE*j, (world->mur.y - world->mur.h/2)+METEORITE_SIZE*i);
      }
    }
}


/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param textures les textures
 */

void refresh_graphics(SDL_Renderer *renderer, world_t *world, textures_t *textures){
    
    //on vide le renderer
    clear_renderer(renderer);
    
    //application des textures dans le renderer
    apply_background(renderer, textures->background);

    apply_sprite(renderer, textures->vaisseau, &(world->vaisseau));
    apply_sprite(renderer, textures->ligne_arrive, &(world->ligne_arrive));
    apply_meteorite(renderer, world, textures);
    
    // on met à jour l'écran
    update_screen(renderer);
}



/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param textures les textures
* \param world le monde
*/

void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world){
    clean_data(world);
    clean_textures(textures);
    clean_sdl(renderer,window);
}



/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des textures, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param textures les textures
 * \param world le monde
 */

void init(SDL_Window **window, SDL_Renderer ** renderer, textures_t *textures, world_t * world)
{
    init_sdl(window,renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_textures(*renderer,textures);
}


/**
 *  \brief programme principal qui implémente la boucle du jeu
 */
int main( int argc, char* args[] )
{
    SDL_Event event;
    world_t world;
    textures_t textures;
    SDL_Renderer *renderer;
    SDL_Window *window;

    //initialisation du jeu
    init(&window,&renderer,&textures,&world);
    
    while(!is_game_over(&world)){ //tant que le jeu n'est pas fini
        
        //gestion des évènements
        handle_events(&event,&world);
        
        //mise à jour des données liée à la physique du monde
        update_data(&world);
        
        //rafraichissement de l'écran
        refresh_graphics(renderer,&world,&textures);
        
        // pause de 10 ms pour controler la vitesse de rafraichissement
        pause(10);
    }
    
    //nettoyage final
    clean(window,renderer,&textures,&world);
    
    
    return 0;
}
