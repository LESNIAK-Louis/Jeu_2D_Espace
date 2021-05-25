/**
 * \file sdl2-ttf-light.c
 * \brief sur-couche de SDL2_ttf pour simplifier son utilisation pour le projet (modifié)
 * \author LESNIAK Louis & SLIMANI Kamelia (modification du document de CONSTANT Mathieu)
 * \version 3.0 + extensions
 * \date 23 mai 2021
*/

#include "sdl2-ttf-light.h"

void init_ttf(){
    if(TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
    }
}

TTF_Font * load_font(const char *path, int font_size){
    TTF_Font *font = TTF_OpenFont(path, font_size);
    if(font == NULL){
        fprintf(stderr, "Erreur pendant chargement font: %s\n", SDL_GetError());
    }
    return font;
}

void apply_text(SDL_Renderer *renderer,int x, int y, int w, int h, const char *text, TTF_Font *font, int red, int green, int blue){
    SDL_Color color = { red, green, blue };
    
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
     
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dstrect2 = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect2);
    SDL_DestroyTexture(texture);  // Free up texture
    SDL_FreeSurface(surface);    // Free up surface
}

void clean_font(TTF_Font * font){
    TTF_CloseFont(font);
}
