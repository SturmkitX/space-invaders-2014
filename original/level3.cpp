#include "levels.h"
#include "body.h"
#include <vector>   //original era cu list, se poate si cu vector
#include <cstdio>
#include <algorithm>

void level3(Screen* mScreen)
{
    int i;
    SDL_Event e;
    SDL_Renderer* rnd = mScreen->getRenderer();
    SDL_Rect bPos;
    bool quit = false;
    Body nava, glont;
    SDL_Texture* gTexture;
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    Uint32 tStart, tAct;

    std::vector<SDL_Rect> bul;
    std::vector<SDL_Rect>::iterator it;
    bul.push_back( bPos );
    tStart = tAct = SDL_GetTicks();

    nava.create( rnd, "media/nava.png" );
    glont.create( rnd, "media/bullet.png" );
    gTexture = glont.getTexture();
    SDL_QueryTexture( gTexture, NULL, NULL, &(bPos.w), &(bPos.h) );

    nava.setRect( 100, 300, nava.getWidth(), nava.getHeight() );
    nava.setCenter( -nava.getWidth()/2, nava.getHeight()/2 );

    while( !quit )
    {
        while( SDL_PollEvent( &e ) )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
        }

        tAct = SDL_GetTicks();

        if( state[ SDL_SCANCODE_LEFT ] )
        {
            nava.translate( -3, 0 );
        }
        if( state[ SDL_SCANCODE_RIGHT ] )
        {
            nava.translate( 3, 0 );
        }

        if( state[ SDL_SCANCODE_X ] && tAct-tStart > 500 )
        {
            bPos.x = nava.getX() + nava.getWidth()/2;
            bPos.y = nava.getY() - bPos.h + 5;
            bul.push_back( bPos );

            tStart = tAct;

            printf( "%d\n", bul.size()-1 );
        }
        if( state[ SDL_SCANCODE_A ] )
        {
            nava.rotateIt( 5 );
        }

        SDL_RenderClear( rnd );

        nava.render( rnd );

        for(i=1; i<bul.size(); i++)
        {
            if( bul[i].y + bul[i].h < 0 )
            {
                std::swap( bul[i], bul.back() );
                bul.pop_back();

                i--;

                printf( "%d\n", bul.size()-1 );
            }
            else
            {
                bul[i].y -= 5;
                glont.render( rnd, NULL, &bul[i] );
            }
        }

        SDL_RenderPresent( rnd );
    }

    nava.free();
    glont.free();
    bul.clear();

    rnd = NULL;
}
