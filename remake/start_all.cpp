#include "screen.h"
#include "levels.h"
#include <cstdio>
#include <cstring>

int main(int argc, char* argv[])
{
    Screen mScreen;
    Uint32 fullScreenActive;

    if( !mScreen.init() )   //trebuie apelata inainte de toate
    {
        fprintf( stderr, "Am esuat!" );
    }
    else
    {
        fprintf( stderr, "Am reusit!" );
        SDL_SetRenderDrawColor( mScreen.getRenderer(), 255, 255, 255, 255 );

        mScreen.detect_music();
        mScreen.switch_song(1);
        Mix_VolumeMusic( 90 );

        menu1( &mScreen );

        mScreen.freeMusic();
    }

    mScreen.close();
    fprintf( stderr, "\nAm iesit cu succes!\n" );

    return 0;
}
