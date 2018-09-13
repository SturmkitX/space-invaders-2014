#include "screen.h"
#include "levels.h"
#include <cstdio>
#include <cstring>

int main(int argc, char* argv[])
{
    Screen mScreen;
    Uint32 fullScreenActive;
    //SDL_SetRenderDrawColor( mScreen.getRenderer(), 255, 255, 255, 255 );

    if( !mScreen.init() )   //trebuie apelata inainte de toate
    {
        printf( "Am esuat!" );
    }
    else
    {
        printf( "Am reusit!" );
        SDL_SetRenderDrawColor( mScreen.getRenderer(), 255, 255, 255, 255 );

        mScreen.detect_music();
        mScreen.switch_song(1);
        Mix_VolumeMusic( 90 );
        //SDL_ShowCursor( 0 );

        //level5(&mScreen);
        //stage1( &mScreen );

        /*if( strcmp( argv[1], "1" ) == 0 )
        {
            nave_net( &mScreen, 1 );
        }
        else
        {
            nave_net( &mScreen, 2 );
        }*/

        /*choose_name( &mScreen );
        stage1( &mScreen );
        rezultate(2, "n", 8);   //extragere, n e doar de umplutura, primii 8 jucatori
        */

        menu1( &mScreen );

        mScreen.freeMusic();
    }

    mScreen.close();
    printf( "\nAm iesit cu succes!" );

    return 0;
}
