#include <cstdio>
#include <list>
#include <ctime>

#include "levels.h"
#include "body.h"
#include "database.h"
#include "stage1.h"

void SinglePlayer_Stage1::compute_difficulty()
{
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
        maxEnemies = 3;
    }
}

void SinglePlayer_Stage1::compute_enemy_spawn()
{
    if( parcurs > deParcurs )
    {
        int toSpawn = rand() % maxEnemies + 1;
        int portion = DESK_W / toSpawn;
        SDL_Rect enemyShip;
        for(int i = 0; i < toSpawn; i++)
        {
            enemyShip.x = rand() % portion + portion * i + 50;
            enemyShip.y = -( rand() % 200 + 300 );
            ePos->push_back( enemyShip );
            eTim->push_back( SDL_GetTicks() );
        }
        parcurs = 0;
    }
}

void SinglePlayer_Stage1::update_enemy_bullets()
{
    for( std::list<SDL_Rect>::iterator it = eBul->begin(); it != eBul->end(); )
    {
        if( it->y > DESK_H )
        {
            eBul->erase( it );
        }
        else
        {
            it->y += vSpatiu * 2;

            // https://stackoverflow.com/questions/16072486/cannot-cast-list-iterator-to-an-object
            // that explains why I did this reference / dereference session
            if( getCollision( nava->getRect(), &(*it) ) )
            {
                eBul->erase( it );

                printf("%d\n", pHealth);
            }
            else
            {
                it++;   // nothing special happens to this bullet
            }
        }
    }
}

void SinglePlayer_Stage1::update_enemy_positions()
{
    std::list<SDL_Rect>::iterator itPos;
    std::list<Uint32>::iterator itTim;
    for( itPos = ePos->begin(), itTim = eTim->begin();
        itPos != ePos->end(), itTim != eTim->end(); )
    {
        itPos->y += vSpatiu;
        if( SDL_GetTicks() - (*itTim) >= eShot )
        {
            *itTim = SDL_GetTicks();
            glont_rect.x = itPos->x + itPos->w / 2 - glont_rect.w / 2;
            glont_rect.y = itPos->y + itPos->h;

            eBul->push_back( glont_rect );

            //printf( "\t%d\n", eBul.size() );
        }

        if( itPos->y > DESK_H )
        {
            ePos->erase( itPos );
            eTim->erase( itTim );

            pHealth -= 20;
            printf( "%d\n", pHealth );
        }
        else
        if( getCollision( nava->getRect(), &( *itPos ) ) )
        {
            pHealth -= 20;

            ePos->erase( itPos );
            eTim->erase( itTim );
            printf( "%d\n", pHealth );
        }
        else
        {
            itPos++;
            itTim++;
        }
    }
}

void SinglePlayer_Stage1::update_player_bullets()
{
    for( std::list<SDL_Rect>::iterator it = pBul->begin(); it != pBul->end(); )
    {
        it->y -= vSpatiu * 2;

        if( it->y + it->h < 0 )
        {
            pBul->erase( it );
            continue;
        }

        for( std::list<SDL_Rect>::iterator itEnemy = ePos->begin();
            itEnemy != ePos->end(); )
        {
            if( getCollision( &( *it ), &( *itEnemy ) ) )
            {
                ePos->erase( itEnemy );
                pBul->erase( it );

                pScore++;
                scoreTex = afisare_status( 1, pScore, rnd );
                SDL_QueryTexture( scoreTex, NULL, NULL, &(scoreRect->w), NULL );
                scoreRect->x = 790 - scoreRect->w;

                break;  // break enemy iteration
            }
        }
    }
}

void SinglePlayer_Stage1::update_player_position()
{
    SDL_GetMouseState( &(p->x), &(p->y) );

    if( movableNava )
    {
        nava->setPosition( p->x - nava->getWidth() / 2, 520 );
    }
    else
    {
        nava->translate( 0, -5 );
    }
}

SinglePlayer_Stage1::SinglePlayer_Stage1(Screen *mScreen) : Stage(mScreen)
{
    enemy = new Body( rnd, "media/Inamici.png" );
    eBul = new std::list<SDL_Rect>();
    ePos = new std::list<SDL_Rect>();
    eTim = new std::list<Uint32>();
    p = new SDL_Point();
    pausedPos = new SDL_Point();
    movableNava = true;
    lastShot = 0;
    nava = new Body( rnd, "media/nava player 1.png" );
    glont_nava = new Body( rnd, "media/bullet 1.png" );
    glont_enemy = new Body( rnd, "media/inamici bullet.png" );
    pBul = new std::list<SDL_Rect>();
    space = new Body( rnd, "media/meniu.png" );
    laser = Mix_LoadWAV( "media/sound.ogg" );

    healthBody = new Body( rnd, "media/blue_dot.png" );
    scoreRect = new SDL_Rect();

    vSpatiu = 2;
    // eShot = 800;

    nava->setPosition( 0, 520 );

    SDL_QueryTexture( glont_nava->getTexture(),
        NULL, NULL, &(glont_rect.w), &(glont_rect.h) );

    // eBul->push_back( gPos );
    // pBul->push_back( gPos );

    deParcurs = 400;
    parcurs = 0;
    // ePos->push_back( *(enemy.getRect()) );
    // eTim->push_back( eShot );
    pHealth = 400;
    maxEnemies = 1;

    srand( time( 0 ) );

    healthBody->getRect()->w = pHealth;
    healthBody->getRect()->h = 24;
    healthBody->setPosition( 10, 10 );

    pScore = 0;
    scoreTex = afisare_status( 1 , pScore, rnd );
    SDL_QueryTexture( scoreTex, NULL, NULL, &(scoreRect->w), &(scoreRect->h) );
    scoreRect->x = 790 - scoreRect->w;
    scoreRect->y = 10;

    Mix_VolumeChunk( laser, 50 );

    SDL_ShowCursor( 0 );
}

SinglePlayer_Stage1::~SinglePlayer_Stage1()
{
    delete enemy;
    eBul->clear(); delete eBul;
    ePos->clear(); delete ePos;
    eTim->clear(); delete eTim;

    delete p;
    delete pausedPos;
    delete nava;
    delete glont_nava;
    delete glont_enemy;

    pBul->clear(); delete pBul;
    delete space;
    Mix_FreeChunk( laser );
    SDL_DestroyTexture( scoreTex );
    delete healthBody;
    delete scoreRect;
}

void SinglePlayer_Stage1::init()
{
    // nothing to pre-render in this screen
}

void SinglePlayer_Stage1::window_events()
{
    if( e.type == SDL_QUIT )
    {
        closeLoop();
        forceClose();
    }
    else
    if( e.button.button == SDL_BUTTON_LEFT &&
        SDL_GetTicks() - lastShot >= 350 && !isPaused() )
    {
        glont_rect.x = nava->getX() + nava->getWidth()/2 - glont_rect.w/2;
        glont_rect.y = nava->getY() + BULLET_VELOCITY;

        pBul->push_back( glont_rect );

        Mix_PlayChannel( -1, laser, 0 );

        lastShot = SDL_GetTicks();
    }
    else
    if( e.type == SDL_WINDOWEVENT )
    {
        if( e.window.event == SDL_WINDOWEVENT_MINIMIZED )
        {
            setPaused( true );
        }
        else
        if( e.window.event == SDL_WINDOWEVENT_EXPOSED )
        {
            setPaused( false );
        }
    }
}

void SinglePlayer_Stage1::keyboard_events()
{
    if( state[ SDL_SCANCODE_X ] && !isPaused() )
    {
        setPaused( true );
        *pausedPos = *p;
    }
    if( state[ SDL_SCANCODE_C ] && isPaused() )
    {
        setPaused( false );
        SDL_WarpMouseInWindow( NULL, pausedPos->x, pausedPos->y );
        *p = *pausedPos;
        // continue;   //pentru ca altfel nu apuca sa mute mouse-ul, rezultand flicker
    }

    if( state[ SDL_SCANCODE_1 ] )
    {
        getScreen()->switch_song( -1 );
    }
    else
    if( state[ SDL_SCANCODE_2 ] )
    {
        getScreen()->switch_song( 1 );
    }

    if( state[ SDL_SCANCODE_0 ] )
    {
        getScreen()->switchFullscreen();
    }

    if( state[ SDL_SCANCODE_ESCAPE ] )
    {
        closeLoop();
    }
}

void SinglePlayer_Stage1::others()
{
    compute_difficulty();
    parcurs += vSpatiu;
    compute_enemy_spawn();
    update_enemy_bullets();
    update_enemy_positions();
    update_player_bullets();
    update_player_position();
}

void SinglePlayer_Stage1::render()
{
    SDL_RenderClear( rnd );
    space->render( rnd );
    nava->render( rnd );
    for( std::list<SDL_Rect>::iterator it = ePos->begin(); it != ePos->end(); it++ )
    {
        enemy->render( rnd, NULL, &( *it ) );
    }

    for( std::list<SDL_Rect>::iterator it = eBul->begin(); it != eBul->end(); it++ )
    {
        glont_enemy->render( rnd, NULL, &( *it ) );
    }

    for( std::list<SDL_Rect>::iterator it = pBul->begin(); it != pBul->end(); it++ )
    {
        glont_nava->render( rnd, NULL, &( *it ) );
    }

    healthBody->getRect()->w = pHealth;
    healthBody->render( rnd );

    SDL_RenderCopy( rnd, scoreTex, NULL, scoreRect );

    SDL_RenderPresent( rnd );

    // if( pHealth <= 0 )
    // {
    //     add_score_db( mScreen->getPlayer(), pScore );
    //     setPaused( true );
    //     SDL_Delay( 2000 );
    //     closeLoop();
    // }

    if( pHealth <= 0 )
    {
        //rezultate( 1, mScreen->getPlayer(), pScore );
        scoreTex = afisare_status( 2, pScore, rnd );
        SDL_QueryTexture( scoreTex, NULL, NULL, &(scoreRect->w), NULL );
        scoreRect->x = 790 - scoreRect->w;
    }
}
