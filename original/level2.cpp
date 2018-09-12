#include "levels.h"
#include "body.h"

/*
* Asta e un meniu cu rezolutii, ar putea fi adaugat la joc
*/

int collides( Body r[], SDL_Point &p )
{
    int i;

    for(i=1; i<=6; i++)
    {
        if( r[i].getX()<=p.x && p.x<=r[i].getX()+r[i].getWidth() )
        {
            if( r[i].getY()<=p.y && p.y<=r[i].getY()+r[i].getHeight() )
            {
                return i;
            }
        }
    }

    return 0;
}

void redraw( Body r[], int &w, int &h, int col, SDL_Window* wind )
{
    SDL_Rect e;
    int TARGET_W, TARGET_H;
    Uint32 flags;
    int i;

    switch( col )
    {
        case 1:
            {
                TARGET_W = 640;
                TARGET_H = 480;
                flags = SDL_GetWindowFlags( wind ) & SDL_WINDOW_FULLSCREEN;
            } break;
        case 2:
            {
                TARGET_W = 800;
                TARGET_H = 600;
                flags = SDL_GetWindowFlags( wind ) & SDL_WINDOW_FULLSCREEN;
            } break;
        case 3:
            {
                TARGET_W = 1024;
                TARGET_H = 768;
                flags = SDL_GetWindowFlags( wind ) & SDL_WINDOW_FULLSCREEN;
            } break;
        case 4:
            {
                TARGET_W = 1152;
                TARGET_H = 864;
                flags = SDL_GetWindowFlags( wind ) & SDL_WINDOW_FULLSCREEN;
            } break;
        case 5:
            {
                TARGET_W = w;
                TARGET_H = h;
                flags = 0;
            } break;
        case 6:
            {
                TARGET_W = w;
                TARGET_H = h;
                flags = SDL_WINDOW_FULLSCREEN;
            } break;
    }

    for(i=1; i<=6; i++)
    {
        e.x = TARGET_W * r[i].getX() / w;
        e.y = TARGET_H * r[i].getY() / h;
        e.w = TARGET_W * r[i].getWidth() / w;
        e.h = TARGET_H * r[i].getHeight() / h;

        r[i].setRect( &e );
    }

    if( flags )
    {
        SDL_SetWindowFullscreen( wind, 0 );
    }

    SDL_SetWindowSize( wind, TARGET_W, TARGET_H );
    SDL_SetWindowFullscreen( wind, flags );
}

void level2(Screen* mScreen)
{
    SDL_Event e;
    SDL_Point p;
    SDL_Renderer* rnd = mScreen->getRenderer();
    bool quit = false;
    int w,h;
    Body res[7];    //5 si 6 sunt wind si full

    res[1].create( rnd, "media/res1.png" );
    res[2].create( rnd, "media/res2.png" );
    res[3].create( rnd, "media/res3.png" );
    res[4].create( rnd, "media/res4.png" );
    res[5].create( rnd, "media/wind.png" );
    res[6].create( rnd, "media/full.png" );

    res[1].setRect( 50, 50, res[1].getWidth(), res[1].getHeight() );
    res[2].setRect( 300, 50, res[2].getWidth(), res[2].getHeight() );
    res[3].setRect( 50, 150, res[3].getWidth(), res[3].getHeight() );
    res[4].setRect( 300, 150, res[4].getWidth(), res[4].getHeight() );

    res[5].setRect( 400, 275, res[5].getWidth(), res[5].getHeight() );
    res[6].setRect( 400, 375, res[6].getWidth(), res[6].getHeight() );

    //SDL_GetWindowSize( mScreen->getWindow(), &w, &h );

    while(!quit)
    {
        while( SDL_PollEvent( &e ) )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            else
            if( e.type == SDL_MOUSEBUTTONDOWN )
            {
                SDL_GetMouseState( &(p.x), &(p.y) );
                SDL_GetWindowSize( mScreen->getWindow(), &w, &h );


                redraw( res, w, h, collides( res, p ), mScreen->getWindow() );

                //SDL_SetWindowSize( mScreen->getWindow(), 800, 600 );
            }

            SDL_RenderClear( rnd );
            res[1].render( rnd );
            res[2].render( rnd );
            res[3].render( rnd );
            res[4].render( rnd );
            res[5].render( rnd );
            res[6].render( rnd );
            SDL_RenderPresent( rnd );
        }
    }

    res[1].free();
    res[2].free();
    res[3].free();
    res[4].free();
    res[5].free();
    res[6].free();
    rnd = NULL;
}

