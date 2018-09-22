#include "stage.h"

int Stage::DESK_W;
int Stage::DESK_H;

Stage::Stage(Screen *mScreen)
{
    this->mScreen = mScreen;
    this->rnd = mScreen->getRenderer();
    this->state = SDL_GetKeyboardState( NULL );
    this->quit = false;
    this->paused = false;
    Stage::DESK_W = mScreen->getDesktopWidth();
    Stage::DESK_H = mScreen->getDesktopHeight();
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
        while ( SDL_PollEvent(&e) )
        {
            this->window_events();
        }
        this->keyboard_events();
        if ( !paused ) continue;
        this->others();
        this->render();
    }
}

void Stage::closeLoop()
{
    this->quit = true;
}

void Stage::forceClose()
{
    mScreen->force_quit = true;
}

bool Stage::isPaused()
{
    return this->paused;
}

void Stage::setPaused(bool paused)
{
    this->paused = paused;
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

Screen* Stage::getScreen()
{
    return mScreen;
}
