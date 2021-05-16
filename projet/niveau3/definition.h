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
 * \brief Hauteur de la ligne d'arrivée
 */


#define FINISH_LINE_Y_INIT -960


/**
 * \brief Pas de déplacement horizontal du vaisseau
*/

#define MOVING_STEP 10


/**
  * \brief Vitesse initiale de déplacement vertical des éléments du jeu
*/

#define INITIAL_SPEED 2

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

#define TIME_LIMIT 10

/**
  * \brief Limite longueur nom utilisateur
*/

#define MAX_LENGTH_NAME 50

/**
  * \brief Nombre d'étoiles gagnés lors d'une victoire
*/

#define STARS_GAME_WON 1
/**
  * \brief Limite du nombre d'étoiles gagnable
*/

#define STARS_LIMIT 999

#endif /* definition_h */
