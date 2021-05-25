/**
 * \file logique.h
 * \brief Header du module logique
 * \author LESNIAK Louis & SLIMANI Kamelia
 * \version 3.0 + extensions
 * \date 23 mai 2021
 */


#ifndef logique_h
#define logique_h

#include  "definition.h"

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
 * \brief Stockage des informations du jeu en cours (extension)
*/

struct gameinfo_s{
    unsigned int startTime; /*!< Temps du début de partie */
    unsigned int finishTime; /*!< Temps de fin de partie */
    unsigned int gamemode; /*!< Mode du jeu en cours */
    unsigned int close; /*!< Gère la demande de fermeture du jeu */
    unsigned int select; /*!< Gère la sélection du menu */
    unsigned int enter; /*!< Gère l'entrée dans une section du menu */
};

/**
 * \brief Stockage des informations du joueur(extension)
*/

struct playerinfo_s{
    char name[50]; /*!< Nom du joueur */
    unsigned int stars; /*!< Nombre d'étoiles du joueur */
    unsigned int bestTime; /*!< Meilleur temps du joueur */
    unsigned int lastTime; /*!< Dernier temps effectué par le joueur */
    unsigned int hasShip[4]; /*!< Indique si le joueur possède déjà la texture du vaisseau i */
    unsigned int selectedShip; /*!< Indique la texture du vaisseau à utiliser en jeu */
};


/**
 * \brief Type qui correspond aux données du sprite
 */

typedef struct sprite_s sprite_t;

/**
 * \brief Type qui correspond aux données du jeu
 */
typedef struct gameinfo_s gameinfo_t;

/**
 * \brief Type qui correspond aux données du joueur
 */

typedef struct playerinfo_s playerinfo_t;


/**
 * \brief Représentation du monde du jeu
*/

struct world_s{
  sprite_t ship;  /*!< Champ représentant le sprite vaisseau */
  sprite_t finish_line;  /*!< Champ représentant la ligne d'arrivée */
  int vy; /*! Champ représentant la vitesse du jeu*/
  int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
  int collision; /*!< Champ indiquant si le vaisseau est rentré en colision avec un mur ou un ennemi */
  int collision_finish_line; /*!< Champ indiquant si le vaisseau est rentré en colision avec la ligne d'arrivée */
  sprite_t meteorite[NB_WALLS]; /*!< Champ représentant un tableau de murs de météorites*/

  sprite_t bonus[NB_BONUS];   /*!< Champ représentant un tableau de sprite de type bonus*/
  unsigned int bonus_type[NB_BONUS]; /*!< Champ représentant un tableau indiquant le type du bonus associé au même indice*/
  unsigned int is_bonus_available[NB_BONUS]; /*!< Champ représentant un tableau indiquant si le bonus associé au même indice est disponible*/
  unsigned char hasShield;  /*!< Champ si le joueur possède ou non un bouclier */

  sprite_t missile[MISSILE_MAX]; /*!< Champ représentant un tableau de sprite de type missile*/
  unsigned char is_missile_free[MISSILE_MAX]; /*!< Champ représentant un tableau indiquant si le missile associé au même indice est disponible*/
  sprite_t ennemy[ENNEMIES_MAX]; /*!< Champ représentant un tableau de sprite de type ennemi */
  unsigned char is_ennemy_dead[MISSILE_MAX]; /*!< Champ représentant un tableau indiquant si l'ennemi associé au même indice est mort ou vivant*/

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
 * \brief La fonction qui génère aléatoirement la position des murs de météorites
 * \param world les données du monde
 */
void init_walls(world_t * world);

/**
 * \brief La fonction qui génère aléatoirement la position des bonus
 * \param world les données du monde
 */
void init_bonus(world_t * world);

/**
 * \brief La fonction qui génère aléatoirement la position des ennemis entre les murs
 * \param world les données du monde
 */
void init_ennemies(world_t * world);

/**
 * \brief La fonction qui rend disponible tous les missiles
 * \param world les données du monde
 */
void init_missiles(world_t * world);

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
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \param game les données du jeu
 * \return 1 si le jeu est fini, 0 sinon
 */

int is_game_over(world_t *world, gameinfo_t *game);

/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param world les données du monde
 * \param game les données du jeu
 * \param player les données du joueur
 */

void update_data(world_t *world, gameinfo_t *game, playerinfo_t *player);

/**
 * \brief La fonction met à jour les données des sprites (sauf le vaisseau)
 * \param world les données du monde
 * \param player  les données du joueur
 * \param game les données du jeu
 */
void update_sprites(world_t *world, playerinfo_t *player, gameinfo_t *game);

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
 * \brief fonction qui initialise un missile devant le vaisseau si il y en a un qui est disponible 
 * \param world les données du monde
*/

void shoot(world_t *world);

/**
 * \brief fonction qui retourne la valeur absolue d'un entier
 * \param a int
 * \return |a| : -a si a < 0 ou a si a > 0
*/
int abs(int a); 

/**
 * \brief fonction qui verifie que 2 sprite ne soit pas en collision
 * \param sp1 vaisseau
 * \param sp2 sprite (mur ou ligne arrivé)
 * \return 1 si collision 0 sinon
*/
int sprites_collide(sprite_t *sp1, sprite_t *sp2);

/**
 * \brief La fonction retrouve l'index d'un élément d'une array à partir de l'adresse de son élément
 * \param sp1 adresse d'un sprite
 * \param Array adresse d'un sprite Array
 * \param limit nombre d'index de l'array pour ne pas faire de dépassements
 * \return l'index (unsigned int)
*/

unsigned int retreive_index(sprite_t *sp1,  sprite_t *Array, unsigned int limit);

/**
 * \brief fonction qui verifie que 2 sprite ne soit pas en collision
 * \param sp1 vaisseau
 * \param sp2 sprite (mur ou ligne arrivé)
 * \param world monde 
 * \param player les données du joueur
 * \param game les données du jeu
 * \param make_disappear sprite visible/invisible 
*/
void handle_sprites_collision(sprite_t *sp1, sprite_t *sp2, world_t *world, playerinfo_t *player, gameinfo_t *game, int make_disappear);


#endif /* logique_h */
