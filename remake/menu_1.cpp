#include "levels.h"
#include "body.h"

void menu1(Screen* mScreen)
{
    SDL_Renderer* rnd = mScreen->getRenderer();
    SDL_Event e;
    bool quit = false;
    bool apasat = false;
    bool toRender = false;
    const Uint8 *state = SDL_GetKeyboardState( NULL );

    Body but1( rnd, "media/single player.png" );
    Body but2( rnd, "media/multiplayer client.png" );
    Body but3( rnd, "media/multiplayer host.png" );
    Body but4( rnd, "media/rank.png" );
    Body but5( rnd, "media/exit.png" );
    Body meniu( rnd, "media/meniu.png" );

    but1.setPosition( -5, 55 );
    but2.setPosition( -5, 155 );
    but3.setPosition( -5, 275 );
    but4.setPosition( -5, 395 );
    but5.setPosition( -5, 495 );

    SDL_RenderClear( rnd );
    meniu.render( rnd );
    but1.render( rnd );
    but2.render( rnd );
    but3.render( rnd );
    but4.render( rnd );
    but5.render( rnd );
    SDL_RenderPresent( rnd );

    while( !quit )
    {
        while( SDL_PollEvent( &e ) )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            else
            if( e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT )
            {
                apasat = true;
            }
            else
            if( e.type == SDL_WINDOWEVENT )
            {
                toRender = true;
            }
        }

        if( apasat )
        {
            if( e.button.y > but1.getY() && e.button.y < but1.getY() + but1.getHeight() )
            {
                //Singleplayer
                choose_name( mScreen, 1 );
                //stage1( mScreen );
                toRender = true;
            }
            else
            if( e.button.y > but2.getY() && e.button.y < but2.getY() + but2.getHeight() )
            {
                //Multiplayer Client
                choose_name( mScreen, 2 );
                //nave_net( mScreen, 2 );
                toRender = true;
            }
            else
            if( e.button.y > but3.getY() && e.button.y < but3.getY() + but3.getHeight() )
            {
                //Multiplayer Host
                // nave_net( mScreen, 1 );
                toRender = true;
            }
            else
            if( e.button.y > but4.getY() && e.button.y < but4.getY() + but4.getHeight() )
            {
                //Rankings
                // rezultate( 2, "n", 8 );
                //SDL_Delay( 1500 );
                rankings( mScreen );
                toRender = true;
            }
            else
            if( e.button.y > but5.getY() && e.button.y < but5.getY() + but5.getHeight() )
            {
                //Iesire
                quit = true;
            }

            apasat = false;
        }

        if( toRender )
        {
            SDL_RenderClear( rnd );
            meniu.render( rnd );
            but1.render( rnd );
            but2.render( rnd );
            but3.render( rnd );
            but4.render( rnd );
            but5.render( rnd );
            SDL_RenderPresent( rnd );
            toRender = false;
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

        if( mScreen->force_quit )
        {
            quit = true;
        }
    }
}
