#include "levels.h"
#include "body.h"
#include <cstdio>
#include <string>
#include <cstring>

void choose_name( Screen* mScreen, int tip )
{
    SDL_Renderer* rnd = mScreen->getRenderer();
    std::string nume;
    SDL_Texture* rand1, *rand2;
    SDL_Rect tRect1, tRect2;
    SDL_Surface* oldSurf;
    TTF_Font* font = TTF_OpenFont( "media/font.ttf", 72 );
    SDL_Color color;
    SDL_Event e;
    bool quit = false;
    bool toRender = false;
    int limita;
    char cerinta[20];
    Body meniu;

    if( tip == 1 )
    {
        limita = 8;
        strcpy( cerinta, "Alege un nume:" );
    }
    else
    {
        limita = 15;
        strcpy( cerinta, "IP Server:" );
    }

    color.a = 0;
    color.r = color.g = color.b = 255;

    oldSurf = TTF_RenderText_Solid( font, cerinta, color);
    rand1 = SDL_CreateTextureFromSurface( rnd, oldSurf );
    SDL_FreeSurface( oldSurf );

    TTF_CloseFont( font );
    font = TTF_OpenFont( "media/font.ttf", 48 );

    oldSurf = TTF_RenderText_Solid( font, nume.c_str(), color );
    rand2 = SDL_CreateTextureFromSurface( rnd, oldSurf );
    SDL_FreeSurface( oldSurf );

    SDL_QueryTexture( rand1, NULL, NULL, &tRect1.w, &tRect1.h );
    SDL_QueryTexture( rand2, NULL, NULL, &tRect2.w, &tRect2.h );

    tRect1.x = 50;
    tRect1.y = 100;

    tRect2.x = 75;
    tRect2.y = 200;

    meniu.create( rnd, "media/meniu.png" );

    SDL_RenderClear( rnd );

    meniu.render( rnd );
    SDL_RenderCopy( rnd, rand1, NULL, &tRect1 );
    SDL_RenderCopy( rnd, rand2, NULL, &tRect2 );

    SDL_RenderPresent( rnd );

    while( !quit )
    {
        while( SDL_PollEvent( &e ) )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
                mScreen->force_quit = true;
            }
            else
            if( e.type == SDL_KEYDOWN && (e.key.keysym.scancode == SDL_SCANCODE_KP_ENTER ||
                                        e.key.keysym.scancode == SDL_SCANCODE_RETURN)
                                    && !nume.empty() )
            {
                quit = true;

                strcpy( mScreen->getPlayer(), nume.c_str() );
                //printf( "%s\n", mScreen->getPlayer() );

                if( tip == 1 )
                {
                    stage1( mScreen );
                }
                else
                {
                    nave_net( mScreen, 2 );
                }
            }
            else
            if( e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_BACKSPACE )
            {
                if( nume.size() > 0 )
                {
                    std::string::iterator it = nume.end();
                    it--;
                    nume.erase( it );

                    printf( "%s\n", nume.c_str() );
                    toRender = true;
                }
            }
            else
            if( e.type == SDL_TEXTINPUT && nume.size() < limita )
            {
                //printf( "%s\n", e.text.text );
                if( e.text.text[0] != ' ' )
                {
                    nume += e.text.text;
                    printf( "%s\n", nume.c_str() );
                    toRender = true;
                }
            }
            else
            if( e.type == SDL_WINDOWEVENT )
            {
                toRender = true;
            }
            else
            if( e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_ESCAPE )
            {
                quit = true;
            }
        }

        if( toRender )
        {
            oldSurf = TTF_RenderText_Solid( font, nume.c_str(), color );
            SDL_DestroyTexture( rand2 );
            rand2 = SDL_CreateTextureFromSurface( rnd, oldSurf );
            SDL_FreeSurface( oldSurf );
            SDL_QueryTexture( rand2, NULL, NULL, &tRect2.w, &tRect2.h );

            SDL_RenderClear( rnd );
            meniu.render( rnd );

            SDL_RenderCopy( rnd, rand1, NULL, &tRect1 );
            SDL_RenderCopy( rnd, rand2, NULL, &tRect2 );

            SDL_RenderPresent( rnd );

            toRender = false;
        }
    }


    //Eliberare
    meniu.free();
    SDL_DestroyTexture( rand1 );
    SDL_DestroyTexture( rand2 );
    TTF_CloseFont( font );
    nume.clear();
}
