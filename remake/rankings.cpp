#include <cstdio>
#include <cstring>

#include "levels.h"
#include "body.h"
#include "database.h"

void rankings(Screen* mScreen)
{
    SDL_Renderer* rnd = mScreen->getRenderer();
    SDL_Event e;
    bool quit = false;

    SDL_Surface *auxSurf;
    SDL_Texture* titluTex;
    SDL_Rect titluRect;
    TTF_Font* font;
    SDL_Color color;
    SDL_Texture* auxTex[10];
    SDL_Texture* inCase;
    Body meniu;
    const Uint8 *state = SDL_GetKeyboardState( NULL );

    SDL_Rect scorRect;
    char nume[25];
    int nr = 0;

    font = TTF_OpenFont( "media/font.ttf", 48 );
    color.a = 0;
    color.r = color.g = color.b = 255;
    auxSurf = TTF_RenderText_Solid( font, "Top 8 Scoruri:", color );
    titluTex = SDL_CreateTextureFromSurface( rnd, auxSurf );
    SDL_QueryTexture( titluTex, NULL, NULL, &titluRect.w, &titluRect.h );
    titluRect.x = 50;
    titluRect.y = 50;
    scorRect.x = 75;
    scorRect.y = 126;

    SDL_FreeSurface( auxSurf );
    TTF_CloseFont( font );

    font = TTF_OpenFont( "media/font.ttf", 24 );

    inCase = SDL_CreateTexture( rnd, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                               800, 600 );
    SDL_SetRenderTarget( rnd, inCase );
    meniu.create( rnd, "media/meniu.png" );

    SDL_RenderClear( rnd );
    meniu.render( rnd );

    SCORE_ARRAY *scores = get_score_db();
    printf(" Should print this shit\n ");
    nr = scores->size;
    memset( auxTex, 0, sizeof( auxTex ) );
    for ( int i=0; i<scores->size; i++ )
    {
        sprintf(nume, "%s ....... %d", scores->data[i].name, scores->data[i].score);
        // nume[strlen(nume)-1] = ' ';
        printf( "%d ", strlen(nume) );

        auxSurf = TTF_RenderText_Solid( font, nume, color );
        auxTex[i] = SDL_CreateTextureFromSurface( rnd, auxSurf );
        SDL_FreeSurface( auxSurf );
        SDL_QueryTexture( auxTex[i], NULL, NULL, &scorRect.w, &scorRect.h );

        scorRect.y += scorRect.h;
        SDL_RenderCopy( rnd, auxTex[i], NULL, &scorRect );
        scorRect.y += 10;
    }
    
    // free scores
    free( scores->data );
    free( scores );

    SDL_RenderCopy( rnd, titluTex, NULL, &titluRect );
    SDL_RenderPresent( rnd );

    SDL_SetRenderTarget( rnd, NULL );
    SDL_RenderClear( rnd );
    SDL_RenderCopy( rnd, inCase, NULL, NULL );
    SDL_RenderPresent( rnd );

    while( nr )
    {
        SDL_DestroyTexture( auxTex[nr - 1] );
        nr--;
    }

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
            if( e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_ESCAPE )
            {
                quit = true;
            }
            else
            if( e.type == SDL_WINDOWEVENT )
            {
                SDL_RenderClear( rnd );
                SDL_RenderCopy( rnd, inCase, NULL, NULL );
                SDL_RenderPresent( rnd );
                //printf( "111\n" );
            }
        }

        if( state[ SDL_SCANCODE_1 ] )
        {
            mScreen->switch_song( -1 );
        }
        else
        if( state[ SDL_SCANCODE_2 ] )
        {
            mScreen->switch_song( 1 );
        }

        if( state[ SDL_SCANCODE_0 ] )
        {
            mScreen->switchFullscreen();
        }
    }

    TTF_CloseFont( font );
    SDL_DestroyTexture( inCase );
    meniu.free();
}
