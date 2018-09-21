#include "stage.h"

Stage::Stage(Screen *mScreen, bool online, int role)
{
    this->rnd = mScreen->getRenderer();
    this->state = SDL_GetKeyboardState( NULL );
    this->quit = false;
    this->paused = false;
    this->online = online;
    this->role = role;
}

Stage::~Stage()
{
    // empty
}

void Stage::mainLoop()
{
    this->init();
    while ( !this->quit )
    {
        this->key_events();
        this->others();
    }
}

void Stage::closeLoop()
{
    this->quit = true;
}

bool Stage::getPaused()
{
    return this->paused;
}

void Stage::setPaused(bool paused)
{
    this->paused = paused;
}

bool Stage::isOnline()
{
    return this->online;
}

int Stage::getRole()
{
    return this->role;
}

bool Stage::getCollision( SDL_Rect *r1, SDL_Rect *r2 )
{
    if( r1->y <= r2->y + r2->h )
    {
        if( r1->x + r1->w > r2->x && r1->x < r2->x + r2->w )
        {
            return true;
        }
    }
    return false;
}