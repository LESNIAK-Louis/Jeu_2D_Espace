/**
 * \file definition.h
 * \brief Header regroupant toutes les constantes utiles au programme
 * \author LESNIAK Louis & SLIMANI Kamelia
 * \version 3.0
 * \date 14 mai 2021
 */

#ifndef definition_h
#define definition_h

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

#define SPRITE_SIZE 32


/**
 * \brief Taille d'un météorite
*/

#define METEORITE_SIZE 32

/**
 * \brief Taille de l'espacement maximal entre deux murs de météorites
*/

#define HOLE_MAX 2

/**
 * \brief Taille de l'espacement maximal entre deux murs de météorites
*/

#define SPACE_BETWEEN_WALLS 150

/**
 * \brief Nombre de murs
*/


#define NB_WALLS (-FINISH_LINE_Y_INIT/(SPACE_BETWEEN_WALLS*2))*2 // Varie en fonction de la distance à parcourir

/**
 * \brief Nombre de bonus
*/


#define NB_BONUS NB_WALLS/2/4 // Varie en fonction de la distance à parcourir

/**
 * \brief Nombre de type de bonus
*/


#define NB_BONUS_TYPE 3

/**
 * \brief Hauteur de la ligne d'arrivée
 */


#define FINISH_LINE_HEIGHT 10

/**
 * \brief Distance à parcourir pour atteindre la ligne d'arrivée
 */


#define FINISH_LINE_Y_INIT -3220 // Valeur changeable


/**
 * \brief Pas de déplacement horizontal du vaisseau
*/

#define MOVING_STEP METEORITE_SIZE/4


/**
  * \brief Vitesse initiale de déplacement vertical des éléments du jeu
*/

#define INITIAL_SPEED 2

/**
  * \brief Vitesse maximale de déplacement vertical des éléments du jeu
*/

#define SPEED_MAX 5

/**
  * \brief Hauteur du texte de fin de partie perdante
*/

#define TEXT_LOST_HEIGHT 40

/**
  * \brief Largeur du texte de fin de partie perdante
*/

#define TEXT_LOST_WIDTH 200

/**
  * \brief Hauteur du texte de fin de partie gagnante
*/

#define TEXT_WIN_HEIGHT 40

/**
  * \brief Largeur du texte de fin de partie gagnante
*/

#define TEXT_WIN_WIDTH 160


/**
  * \brief Largeur du texte dans le menu
*/

#define TEXT_MENU_WIDTH 130

/**
  * \brief Hauteur du texte dans le menu
*/

#define TEXT_MENU_HIGHT 40

/**
  * \brief Largeur du texte dans la catégorie "rules"
*/

#define TEXT_RULES_WIDTH 150


/**
  * \brief Largeur du texte dans le shop
*/

#define TEXT_SHOP_WIDTH 60

/**
  * \brief Hauteur du texte dans le shop
*/

#define TEXT_SHOP_HIGHT 30

/**
  * \brief Prix du vaisseau 1
*/

#define PRICE_SHIP_1 0

/**
  * \brief Prix du vaisseau 2
*/

#define PRICE_SHIP_2 20

/**
  * \brief Prix du vaisseau 3
*/

#define PRICE_SHIP_3 50

/**
  * \brief Prix du vaisseau 4
*/

#define PRICE_SHIP_4 100

/**
  * \brief Limite de temps (en secondes)
*/

#define TIME_LIMIT -FINISH_LINE_Y_INIT/(70*INITIAL_SPEED) + 10 // On estime que l'on parcours 70 de distance en vitesse 1 et on ajoute 5 secondes de battement

/**
  * \brief Limite longueur nom utilisateur
*/

#define MAX_LENGTH_NAME 50

/**
  * \brief Nombre d'étoiles gagnés lors d'une victoire
*/

#define STARS_GAME_WON 3

/**
  * \brief Limite du nombre d'étoiles à posséder
*/

#define STARS_LIMIT 999

/**
  * \brief Maximum de tir à l'écran
*/

#define MISSILE_MAX 5

/**
  * \brief Maximum d'ennemis
*/

#define ENNEMIES_MAX NB_WALLS/2

/**
  * \brief Temps à retirer lorsqu'on récupère un bonus temps
*/

#define TIME_BONUS 3000 // 3 secondes


#endif /* definition_h */
