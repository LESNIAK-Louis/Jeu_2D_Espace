# methodo2021-MI-tp-4.1-LESNIAK-SLIMANI




----------------------------------------LANCER LE JEU------------------------------------------
-
- Se rendre dans le dossier contenant les fichiers sources du jeu et renommer "Makefile_jeu" en "Makefile".
- Ouvrir un terminal à cet emplacement.
- Entrez la commande "make" pour compiler le jeu.
- Entrez la commande "./spacecorridor" afin de lancer le jeu.
- Entrez un nom d'utilisateur.
- Une fenêtre de jeu doit s'ouvrir.
- Utilisez les commandes ci-dessous afin de d'accomplir les différentes actions que propose le jeu.

--------------------------------------COMMANDES MENU--------------------------------------
-
- Flèche du haut : déplacement vers le haut 
- Flèche du bas : déplacement vers le bas
- Echap : Revenir au menu principal ; quitter le jeu si on se trouve déjà dans le menu principal.
- Espace : Permet de rentrer dans les catégories du menu, d'acheter différentes textures de vaisseaux dans le menu Shop et de sélectionner un vaisseau déjà acheté pour jouer avec.

--------------------------------------COMMANDES JEU---------------------------------------
-
- Flèche du haut : Augmenter la vitesse du jeu.
- Flèche du bas : Diminuer la vitesse du jeu.
- Flèche de droite : Déplacement latéral à droite.
- Flèche de gauche : Déplacement latéral à gauche.

-------------------------------------LANCER LE TEST----------------------------------------
-
- Se rendre dans le dossier contenant les fichiers sources du jeu et renommer "Makefile_tests" en "Makefile".
- Ouvrir un terminal à cet emplacement.
- Entrez la commande "make" pour compiler le programme de tests.
- Entrez la commande "./test" afin de lancer le programme de tests.
- Une fenêtre qui affiche tous les résultats des tests doit s'ouvrir.

-------------------------------INFORMATIONS COMPLEMENTAIRES--------------------------------
-
- Les informations du joueur sont sauvegardées avant la fermeture du programme : veillez à entrer le même nom d'utilisateur à la prochaine réouverture du jeu afin de continuer votre progression.
- En cas de suppression des fichiers textes créés afin d'effectuer la sauvegarde, vous perdez votre progression.
- Vous pouvez modifier ces fichiers textes afin de tricher : ouvrez le fichier texte userInfo_NOM (où nom est le nom du joueur) et modifiez les informations comme le montre l'exemple ci-dessous : 

-$t144s : 144 crédits 
-$01s : Texture du vaisseau 0 possédé 
-$11s : Texture du vaisseau 1 possédé 
-$20s : Texture du vaisseau 2 non possédé 
-$30s : Texture du vaisseau 3 non possédé 
-$t1s : Texture du vaisseau 1 sélectionné 