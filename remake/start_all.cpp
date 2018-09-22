#include <cstdio>
#include <cstring>

#include "screen.h"
// #include "levels.h"
#include "stage.h"
#include "stage1.h"

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

        // menu1( &mScreen );
        Stage *stg;
        SinglePlayer_Stage1 *stg1 = new SinglePlayer_Stage1( &mScreen );
        stg = stg1;
        stg->mainLoop();
        delete stg;

        mScreen.freeMusic();
    }

    mScreen.close();
    fprintf( stderr, "\nAm iesit cu succes!\n" );

    return 0;
}
