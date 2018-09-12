//varianta originala, cu TCP

#include "levels.h"
#include "body.h"
#include <cstdio>
#include <vector>
#include <algorithm>
#include <SDL_net.h>

bool se_ating_again( SDL_Rect &r1, SDL_Rect &r2 )
{
    /**********************
    *
    * r1 e cel de jos, r2 e cel de sus
    *
    *///////////////////////

    if( r1.y <= r2.y + r2.h )
    {
        if( r1.x + r1.w > r2.x && r1.x < r2.x + r2.w )
        {
            return true;
        }
    }
    return false;
}

void solveConn(IPaddress* ip, TCPsocket* meSock, TCPsocket* outSock, int playerNumber,
               char* adresa)
{
    *meSock = NULL;
    *outSock = NULL;

    if(playerNumber == 1)
    {
        //Asta e server
        SDLNet_ResolveHost( ip, NULL, 5678 );

        *(meSock) = SDLNet_TCP_Open( ip );
    }
    else
    {
        //Asta e client
        /*FILE* fin = fopen( "adress.txt", "r" );
        char adresa[20];
        fgets( adresa, 20, fin );*/

        SDLNet_ResolveHost( ip, adresa, 5678 );

        *(outSock) = SDLNet_TCP_Open( ip );

        //fclose( fin );
    }
}

void nave_net(Screen* mScreen, int playerNumber)
{
    /**********************
    *
    * Variabile esentiale
    *
    **********************/
    SDL_Event e;
    SDL_Renderer* rnd = mScreen->getRenderer();
    const Uint8 *state = SDL_GetKeyboardState( NULL );
    bool quit = false;
    int i;
    int enemyNumber = ((playerNumber == 1) ? 2 : 1);
    bool hasShot = false;
    Uint32 countDown = (1<<31);

    SDL_Texture* text;
    SDL_Surface* textSurface;
    TTF_Font* font;
    SDL_Color color;
    SDL_Rect textRect;

    /**********************
    *
    * Player si altele
    *
    **********************/
    SDL_Point p;
    int pHealth[3];
    Uint32 lastShot = 0;
    Body nava[3], glont_p1, glont_p2;
    SDL_Rect gPos;
    std::vector<SDL_Rect> pBul[3];
    std::vector<SDL_Rect>::iterator it;
    Body space;
    SDL_Rect spaceRect;
    Mix_Chunk *laser = Mix_LoadWAV( "media/sound.ogg" );
    Body healthBar[3];
    bool paused = false;

    /**********************
    *
    * Network
    *
    **********************/
    IPaddress ip;
    TCPsocket meSock, outSock;
    int received;   //nr de bytes primiti
    SDL_Point packet;    //ceea ce se da/primeste
    SDL_Point lastSent;   //pentru debug
    int apSent = 0;


    /*******************
    *
    * Initializari
    *
    *******************/

    space.create( rnd, "media/meniu.png" );
    spaceRect.x = 0;
    spaceRect.y = 0;
    SDL_GetWindowSize( mScreen->getWindow(), &(spaceRect.w), &(spaceRect.h) );

    nava[1].create( rnd, "media/nava player 1.png" );
    nava[1].setPosition( -200, 520 );

    nava[2].create( rnd, "media/nava player 2.png" );
    nava[2].setPosition( 2200, 50 );

    glont_p1.create( rnd, "media/bullet 1.png" );
    glont_p2.create( rnd, "media/bullet 2.png" );

    SDL_QueryTexture( glont_p1.getTexture(), NULL, NULL, &(gPos.w), &(gPos.h) );

    pBul[1].push_back( gPos );
    pBul[2].push_back( gPos );

    pHealth[1] = pHealth[2] = 1000;

    solveConn( &ip, &meSock, &outSock, playerNumber, mScreen->getPlayer() );

    printf("\nMacar aici am ajuns!\n");

    packet.x = packet.y = 0;

    text = NULL;
    textSurface = NULL;
    font = TTF_OpenFont( "media/font.ttf", 36 );
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 0;
    lastSent.x = lastSent.y = 0;

    /***********************
    *
    *
    ***********************/

    healthBar[1].create( rnd, "media/blue_dot.png" );
    healthBar[2].create( rnd, "media/red_dot.png" );

    healthBar[1].getRect()->w = pHealth[1] * 2 / 3;
    healthBar[1].getRect()->h = 24;
    healthBar[1].setPosition( 10, 565 );

    healthBar[2].getRect()->w = pHealth[2] * 2 / 3;
    healthBar[2].getRect()->h = 24;
    healthBar[2].setPosition( 10, 10 );

    Mix_VolumeChunk( laser, 50 );

    SDL_ShowCursor( 0 );

    while( !quit )
    {
        /*******************
        *
        * Evenimentele
        *
        *******************/

        while( SDL_PollEvent( &e ) )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
                mScreen->force_quit = true;
            }
            else
            if( e.button.button == SDL_BUTTON_LEFT && SDL_GetTicks() - lastShot >= 250 )
            {
                gPos.x = nava[playerNumber].getX() + nava[playerNumber].getWidth()/2
                 - gPos.w/2;

                if( playerNumber == 1 )
                {
                    gPos.y = nava[playerNumber].getY() + 6;
                }
                else
                {
                    gPos.y = nava[playerNumber].getY() + nava[playerNumber].getHeight() - 6;
                }

                pBul[playerNumber].push_back( gPos );

                Mix_PlayChannel( -1, laser, 0 );

                lastShot = SDL_GetTicks();

                hasShot = true;
            }
            else
            if( e.type == SDL_WINDOWEVENT )
            {
                if( e.window.event == SDL_WINDOWEVENT_MINIMIZED )
                {
                    paused = true;
                }
                else
                if( e.window.event == SDL_WINDOWEVENT_EXPOSED )
                {
                    paused = false;
                }
            }
        }

        /*****************
        *
        *
        *****************/

        if( (pHealth[1]==0 || pHealth[2]==0) && countDown==(1<<31) )
        {
            countDown = SDL_GetTicks();
            if(pHealth[1] == 0)
            {
                textSurface = TTF_RenderText_Solid( font, "Player 2 a castigat", color );
            }
            else
            {
                textSurface = TTF_RenderText_Solid( font, "Player 1 a castigat", color );
            }

            text = SDL_CreateTextureFromSurface( rnd, textSurface );
            SDL_QueryTexture( text, NULL, NULL, &(textRect.w), &(textRect.h) );
            textRect.x = 320 - textRect.w/2;
            textRect.y = 240 - textRect.h/2;

        }

        /********************
        *
        * Asteptam conexiune (daca suntem server)
        *
        ********************/
        if( outSock == NULL )
        {
            outSock = SDLNet_TCP_Accept( meSock );
        }

        /*******************
        *
        * Luam toate gloantele inamicilor
        *
        *******************/

        for( i=1; i<pBul[2].size(); i++)
        {
            //printf( "%d %d\n", (*it).w, (*it).h );

            if( pBul[2][i].y > 600 )
            {
                std::swap( pBul[2][i], pBul[2].back() );
                pBul[2].pop_back();
                i--;

            }
            else
            {
                pBul[2][i].y += 6;

                if( se_ating_again( *(nava[1].getRect()), pBul[2][i] ) )
                {
                    pHealth[1] -= 20;
                    std::swap( pBul[2][i], pBul[2].back() );
                    pBul[2].pop_back();
                    i--;

                    printf("%d\t%d\n", pHealth[1], pHealth[2]);
                }
            }

        }

        /**********************
        *
        * Luam toate gloantele jucatorului (verif daca ating inamicii)
        *
        **********************/

        for( i=1; i<pBul[1].size(); i++)
        {
            pBul[1][i].y -= 6;
            if( se_ating_again( pBul[1][i], *(nava[2].getRect()) ) )
            {
                pHealth[2] -= 20;


                printf("%d\t%d\n", pHealth[1], pHealth[2]);

                std::swap( pBul[1][i], pBul[1].back() );
                pBul[1].pop_back();
                i--;

                //break;
            }
        }

        /********************
        *
        * Luam toate gloantele jucatorului (verif daca au iesit din ecran)
        *
        ********************/

        for( i=1; i<pBul[1].size(); i++)
        {
            if( pBul[1][i].y + pBul[1][i].h < 0 )
            {
                std::swap( pBul[1][i], pBul[1].back() );
                pBul[1].pop_back();
                i--;

            }
        }

        /*****************
        *
        * Miscam nava
        *
        *****************/

        SDL_GetMouseState( &(p.x), &(p.y) );

        nava[playerNumber].setX( p.x - nava[playerNumber].getWidth()/2 );

        /******************
        *
        * Trimitem si primim informatiile
        *
        ******************/
        if( outSock )
        {
            p.x = p.x*10 + hasShot;
            p.y = pHealth[playerNumber];
            SDLNet_TCP_Send( outSock, &p, sizeof(p) );
            if( p.x == lastSent.x && p.y == lastSent.y )
            {
                apSent++;
            }
            else
            {
                //printf( "%d\n", apSent );
                apSent = 1;
                lastSent = p;
            }

            if( hasShot )
            {
                //pBul[playerNumber].push_back( gPos );
                hasShot = false;
            }

            //printf( "%d ", received );

            received = SDLNet_TCP_Recv( outSock, &packet, sizeof(packet) );
            if( received == sizeof(SDL_Point) )
            {
                nava[enemyNumber].setX( packet.x/10 - nava[enemyNumber].getWidth()/2 );
                pHealth[enemyNumber] = packet.y;

                if( packet.x%10 == 1 )
                {
                    //Inamicul a tras
                    gPos.x = nava[enemyNumber].getX() + nava[enemyNumber].getWidth()/2
                     - gPos.w/2;

                    if( enemyNumber == 1 )
                    {
                        gPos.y = nava[enemyNumber].getY() + 6;
                    }
                    else
                    {
                        gPos.y = nava[enemyNumber].getY() +
                            nava[enemyNumber].getHeight() - 6;
                    }

                    pBul[enemyNumber].push_back( gPos );
                }
            }
        }


        /******************
        *
        * Afisam totul pe ecran
        *
        ******************/

        if( pHealth[1] * pHealth[2] >= 0 )
        {
            healthBar[1].getRect()->w = pHealth[1] * 2 / 3;
            healthBar[2].getRect()->w = pHealth[2] * 2 / 3;
        }

        if( paused ) continue;

        SDL_RenderClear( rnd );
        //printf( "%d %d %d %d\n", spaceRect.x, spaceRect.y, spaceRect.w, spaceRect.h );
        space.render( rnd, &spaceRect, NULL );
        nava[1].render( rnd );
        nava[2].render( rnd );

        it = pBul[2].begin();
        it++;

        for( ; it!=pBul[2].end(); it++)
        {
            glont_p2.render( rnd, NULL, &(*it) );
        }

        it = pBul[1].begin();
        it++;

        for( ; it!=pBul[1].end(); it++)
        {
            glont_p1.render( rnd, NULL, &(*it) );
        }

        if( countDown < (1<<31) )
        {
            SDL_RenderCopy( rnd, text, NULL, &textRect );
        }

        healthBar[1].render( rnd );
        healthBar[2].render( rnd );


        SDL_RenderPresent( rnd );

        if( countDown + 5000 < SDL_GetTicks() )
        {
            quit = true;
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

        if( state[ SDL_SCANCODE_ESCAPE ] )
        {
            quit = true;
        }
    }

    /***********************
    *
    * Eliberam memoria
    *
    ***********************/

    nava[playerNumber].free();
    nava[enemyNumber].free();
    glont_p1.free();
    glont_p2.free();
    space.free();
    healthBar[1].free();
    healthBar[2].free();
    pBul[playerNumber].clear();
    pBul[enemyNumber].clear();
    Mix_FreeChunk( laser );
    rnd = NULL;

    if( playerNumber == 1 )
    {
        if(outSock) SDLNet_TCP_Close( outSock );
        SDLNet_TCP_Close( meSock );
        outSock = meSock = NULL;
    }
    else
    {
        SDLNet_TCP_Close( outSock );
        outSock = NULL;
    }

    if( textSurface ) SDL_FreeSurface( textSurface );
    if( text ) SDL_DestroyTexture( text );
    TTF_CloseFont( font );

    SDL_ShowCursor( 1 );

    /********************
    *
    * Aici se termina
    *
    ********************/
}
