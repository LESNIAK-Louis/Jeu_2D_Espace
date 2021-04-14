/**
 * \file logique.h
 * \brief Header du module logique
 * \author LESNIAK Louis & SLIMANI Kamelia
 * \version 2.0
 * \date 14 avril 2021
 */


#ifndef logique_h
#define logique_h


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
 * \brief Représentation du monde du jeu
*/

struct world_s{
  sprite_t vaisseau;  /*!< Champ représentant le sprite vaisseau */
  sprite_t ligne_arrive;  /*!< Champ représentant la ligne d'arrivée */
  sprite_t mur; /*!< Champ représentant un mur de météorites */
  int vy; /*! Champ représentant les vitesse du jeu*/
  int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
  int collision_mur; /*!< Champ indiquant si le vaisseau est rentré en colision avec un mur */
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

void init_sprite(sprite_t* sprite,int x,int y,int w,int h);

/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */

void init_data(world_t * world);


/**
 * \brief La fonction affiche la position du sprite
 * \param sprite vaisseau
 */

void print_sprite(sprite_t sprite);

/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */


void clean_data(world_t *world);

/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */

int is_game_over(world_t *world);
/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */

void update_data(world_t *world);

/**
 * \brief fonction qui verifie que le sprite ne depaase pas la limite gauche du jeu
 * \param sprite vaisseau
*/

void depassement_g(sprite_t *sprite);

/**
 * \brief fonction qui verifie que le sprite ne depaase pas la limite droite du jeu
 * \param sprite vaisseau
*/

void depassement_d(sprite_t *sprite);

/**
 * \brief fonction qui verifie que 2 sprite ne soit pas en collision
 * \param sp1 vaisseau
 * \param sp2 sprite (mur ou ligne arrivé)
*/

int sprites_collide(sprite_t *sp1, sprite_t *sp2);

/**
 * \brief fonction qui verifie que 2 sprite ne soit pas en collision
 * \param sp1 vaisseau
 * \param sp2 sprite (mur ou ligne arrivé)
 * \param world monde 
 * \param make_disappear sprite visible/invisible 
*/
void handle_sprites_collision(sprite_t *sp1, sprite_t *sp2, world_t *world, int make_disappear);

/**
 * \brief fonction qui retourne la valeur absolue d'un entier
 * \param a int
 * \return |a| : -a si a < 0 ou a si a > 0
*/
int abs(int a); 

#endif /* logique_h */
