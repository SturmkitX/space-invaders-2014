#include "levels.h"
#include "body.h"
#include <cstdio>
#include <vector>
#include <algorithm>
#include <ctime>

bool se_ating( SDL_Rect &r1, SDL_Rect &r2 )
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

void stage1(Screen* mScreen)
{
    // Variabile esentiale
    SDL_Event e;
    SDL_Renderer* rnd = mScreen->getRenderer();
    const Uint8 *state = SDL_GetKeyboardState( NULL );
    bool quit = false;
    int i,j;
    bool paused = false;

    // Inamici
    Body enemy;
    std::vector<SDL_Rect> eBul;
    std::vector<SDL_Rect> ePos;
    std::vector<Uint32> eTim;

    // Player si altele
    SDL_Point p, pausedPos;
    int pHealth;
    bool movableNava = true;
    Uint32 lastShot = 0;
    Body nava, glont_nava, glont_enemy;
    SDL_Rect gPos;
    std::vector<SDL_Rect> pBul;
    Body space;
    Mix_Chunk *laser = Mix_LoadWAV( "media/sound.ogg" );

    //Misc. stuff
    int vSpatiu;
    Uint32 eShot;
    SDL_Rect eShip;
    int deParcurs;
    int parcurs;
    int pScore;
    int maxEnemies,toSpawn;
    Body healthBody;
    SDL_Texture* scoreTex;
    SDL_Rect scoreRect;

    /*******************
    *
    * Initializari
    *
    *******************/

    space.create( rnd, "media/meniu.png" );

    nava.create( rnd, "media/nava player 1.png" );
    nava.setPosition( 0, 520 );

    glont_nava.create( rnd, "media/bullet 1.png" );
    glont_enemy.create( rnd, "media/inamici bullet.png" );

    enemy.create( rnd, "media/Inamici.png" );
    SDL_QueryTexture( glont_nava.getTexture(), NULL, NULL, &(gPos.w), &(gPos.h) );

    eBul.push_back( gPos );
    pBul.push_back( gPos );

    vSpatiu = 2;
    eShot = 800;
    eShip = *(enemy.getRect());
    deParcurs = parcurs = 400;
    ePos.push_back( eShip );
    eTim.push_back( eShot );
    pHealth = 400;
    maxEnemies = 1;

    srand( time( 0 ) );

    healthBody.create( rnd, "media/blue_dot.png" );
    healthBody.getRect()->w = pHealth;
    healthBody.getRect()->h = 24;
    healthBody.setPosition( 10, 10 );

    pScore = 0;
    scoreTex = afisare_status( 1 , 0, rnd );
    SDL_QueryTexture( scoreTex, NULL, NULL, &scoreRect.w, &scoreRect.h );
    scoreRect.x = 790 - scoreRect.w;
    scoreRect.y = 10;

    Mix_VolumeChunk( laser, 50 );

    SDL_ShowCursor( 0 );


    /***********************
    *
    *
    ***********************/

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
            if( e.button.button == SDL_BUTTON_LEFT &&
                SDL_GetTicks() - lastShot >= 350 && !paused )
            {
                gPos.x = nava.getX() + nava.getWidth()/2 - gPos.w/2;
                gPos.y = nava.getY() + 6;

                pBul.push_back( gPos );

                Mix_PlayChannel( -1, laser, 0 );

                lastShot = SDL_GetTicks();
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

        /******************
        *
        * Pauza jocului
        *
        ******************/

        if( state[ SDL_SCANCODE_X ] && !paused )
        {
            paused = true;
            pausedPos = p;
        }
        if( state[ SDL_SCANCODE_C ] && paused )
        {
            paused = false;
            SDL_WarpMouseInWindow( NULL, pausedPos.x, pausedPos.y );
            p = pausedPos;
            continue;   //pentru ca altfel nu apuca sa mute mouse-ul, rezultand flicker
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

        if( paused ) continue;

        /*****************
        *
        *
        *****************/

        if( SDL_GetTicks() < 5000 )
        {
            vSpatiu = 2;
            eShot = 1800;
            deParcurs = 500;
            maxEnemies = 1;
        }
        else
        if( SDL_GetTicks() < 10000 )
        {
            vSpatiu = 3;
            eShot = 1750;
            deParcurs = 600;
            maxEnemies = 2;
        }
        else
        if( SDL_GetTicks() < 15000 )
        {
            vSpatiu = 4;
            eShot = 1750;
            deParcurs = 650;
            maxEnemies = 2;
        }
        else
        {
            vSpatiu = 5;
            eShot = 1650;
            deParcurs = 800;
            maxEnemies = 2;
        }

        parcurs -= vSpatiu;

        if( parcurs < 0 )
        {
            toSpawn = rand()%2 + 1;
            for(i=1; i<=toSpawn; i++)
            {
                /*if(i == 1) eShip.x = rand() % 150;
                else eShip.x = rand() % 150 + 300;*/
                if( toSpawn == 1 )
                {
                    eShip.x = rand() % 750;
                }
                else
                {
                    if(i == 1) eShip.x = rand() % 350;
                    else eShip.x = rand() % 350 + eShip.x + 50;
                }

                eShip.y = -( rand() % 200 + 300 );
                ePos.push_back( eShip );
                eTim.push_back( SDL_GetTicks() );
            }
            parcurs = deParcurs;
        }

        /*******************
        *
        * Luam toate gloantele inamicilor
        *
        *******************/

        for( i=1; i<eBul.size(); i++)
        {
            if( eBul[i].y > 600 )
            {
                //eBul.erase( it );
                std::swap( eBul[i], eBul.back() );
                eBul.pop_back();
                i--;

            }
            else
            {
                eBul[i].y += vSpatiu*2;

                if( se_ating( *(nava.getRect()), eBul[i] ) )
                {
                    pHealth -= 20;
                    std::swap( eBul[i], eBul.back());
                    eBul.pop_back();
                    i--;

                    printf("%d\n", pHealth);
                }
            }

        }

        for( i=1; i<ePos.size(); i++ )
        {
            ePos[i].y += vSpatiu;
            if( SDL_GetTicks() - eTim[i] >= eShot )
            {
                eTim[i] = SDL_GetTicks();
                gPos.x = ePos[i].x + ePos[i].w/2 - glont_nava.getWidth()/2;
                gPos.y = ePos[i].y + ePos[i].h;

                eBul.push_back( gPos );

                //printf( "\t%d\n", eBul.size() );
            }

            if( ePos[i].y > 600 )
            {
                std::swap( ePos[i], ePos.back() );
                ePos.pop_back();

                std::swap( eTim[i], eTim.back() );
                eTim.pop_back();
                i--;

                pHealth -= 20;
                printf( "%d\n", pHealth );
            }

            if( se_ating( *(nava.getRect()), ePos[i] ) )
            {
                pHealth -= 20;

                std::swap( ePos[i], ePos.back() );
                ePos.pop_back();
                i--;
                printf( "%d\n", pHealth );
            }
        }

        /*for( i=1; i<eTim.size(); i++ )
        {
            if( SDL_GetTicks() - eTim[i] >= eShot )
            {
                eTim[i] = SDL_GetTicks();
                gPos.x = ePos[i].x + ePos[i].w/2 - glont.getWidth()/2;
                gPos.y = ePos[i].y + ePos[i].h;

                eBul.push_back( gPos );

                printf( "\t%d\n", eBul.size() );
            }
        }*/

        /**********************
        *
        * Luam toate gloantele jucatorului (verif daca ating inamicii)
        *
        **********************/

        for( j=1; j<pBul.size(); j++)
        {
            pBul[j].y -= vSpatiu*2;
            for( i=1; i<ePos.size(); i++ )
            {
                if( se_ating( pBul[j], ePos[i] ) )
                {
                    std::swap( ePos[i], ePos.back() );
                    ePos.pop_back();
                    i--;

                    std::swap( pBul[j], pBul.back() );
                    pBul.pop_back();
                    j--;

                    //printf( "%d\n", ePos.size() );

                    pScore++;
                    scoreTex = afisare_status( 1, pScore, rnd );
                    SDL_QueryTexture( scoreTex, NULL, NULL, &scoreRect.w, NULL );
                    scoreRect.x = 790 - scoreRect.w;

                    break;
                }
            }
        }

        /********************
        *
        * Luam toate gloantele jucatorului (verif daca au iesit din ecran)
        *
        ********************/

        for( i=1; i<pBul.size(); i++)
        {
            if( pBul[i].y + pBul[i].h < 0 )
            {
                std::swap( pBul[i], pBul.back() );
                pBul.pop_back();
                i--;

            }
        }

        /*****************
        *
        * Miscam nava
        *
        *****************/

        SDL_GetMouseState( &(p.x), &(p.y) );

        if( movableNava )
        {
            nava.setPosition( p.x - nava.getWidth()/2, 520 );
        }
        else
        {
            nava.translate( 0, -5 );
            /*if( pHealth <= 0 )
            {
                rezultate(1, "Gica", 35);
            }*/
        }

        /*if( pHealth <= 0 )
        {
            rezultate(1, "Gica", 35);
            break;
        }*/

        /******************
        *
        * Afisam totul pe ecran
        *
        ******************/

        if( pHealth <= 0 )
        {
            //rezultate( 1, mScreen->getPlayer(), pScore );
            scoreTex = afisare_status( 2, pScore, rnd );
            SDL_QueryTexture( scoreTex, NULL, NULL, &scoreRect.w, NULL );
            scoreRect.x = 790 - scoreRect.w;
        }

        SDL_RenderClear( rnd );
        space.render( rnd );
        nava.render( rnd );
        for( i=1; i<ePos.size(); i++ )
        {
            enemy.render( rnd, NULL, &ePos[i] );
        }

        for( i=1; i<eBul.size(); i++)
        {
            glont_enemy.render( rnd, NULL, &eBul[i] );
        }

        for( i=1; i<pBul.size(); i++)
        {
            glont_nava.render( rnd, NULL, &pBul[i] );
        }

        healthBody.getRect()->w = pHealth;
        healthBody.render( rnd );

        SDL_RenderCopy( rnd, scoreTex, NULL, &scoreRect );

        SDL_RenderPresent( rnd );

        if( pHealth <= 0 )
        {
            rezultate( 1, mScreen->getPlayer(), pScore );
            paused = true;
            SDL_Delay( 2000 );
            quit = true;
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

    nava.free();
    enemy.free();
    glont_nava.free();
    glont_enemy.free();
    space.free();
    healthBody.free();
    eTim.clear();
    ePos.clear();
    eBul.clear();
    pBul.clear();
    Mix_FreeChunk( laser );
    SDL_DestroyTexture( scoreTex );
    rnd = NULL;

    SDL_ShowCursor( 1 );

    /********************
    *
    * Aici se termina
    *
    ********************/
}
