#include "levels.h"
#include <cstdio>
#include <sstream>

SDL_Texture* afisare_status( int tip, int valoare, SDL_Renderer* rnd )
{
    //modificam viata
    SDL_Surface* oldSurf;
    SDL_Color color;
    TTF_Font* font;
    std::stringstream afisak;

    //afisak << "Scor: " << valoare;
    if( tip == 1 )
    {
        afisak << "Scor: " << valoare;
    }
    else
    {
        afisak << "Scorul tau este de " << valoare << " puncte";
    }
    color.a = 0;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    font = TTF_OpenFont( "media/font.ttf", 24 );

    oldSurf = TTF_RenderText_Solid( font, afisak.str().c_str(), color );

    return SDL_CreateTextureFromSurface( rnd, oldSurf );
}
