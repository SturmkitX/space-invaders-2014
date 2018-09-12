#include "levels.h"
#include "body.h"

void level1(Screen* mScreen)
{
    SDL_Event e;
    Body bg;
    SDL_Renderer* rnd = mScreen->getRenderer();
    SDL_Rect rect;
    const Uint8* state;
    bool quit = false;

    bg.create( rnd, "media/poza.png" );
    SDL_SetRenderDrawColor( rnd, 255, 255, 255, 255 );
    rect.x = rect.y = 0;
    rect.w = bg.getWidth();
    rect.h = bg.getHeight();
    state = SDL_GetKeyboardState( NULL );

    while(!quit)
    {
        while( SDL_PollEvent( &e ) )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }

            if( state[ SDL_SCANCODE_RIGHT ] )
            {
                rect.x ++;
            }

            if( state[ SDL_SCANCODE_LEFT ] )
            {
                rect.x --;
            }

            SDL_RenderClear( rnd );
            bg.render( rnd, NULL, &rect );
            SDL_RenderPresent( rnd );
        }
    }

    bg.free();
    rnd = NULL;
}
