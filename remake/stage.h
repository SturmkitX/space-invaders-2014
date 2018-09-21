#ifndef _STAGE_H
#define _STAGE_H

#include <SDL.h>
#include "screen.h"

#define MULTIPLAYER_SERVER 0
#define MULTIPLAYER_CLIENT 1

class Stage
{
    protected:
        SDL_Event e;
        SDL_Renderer* rnd;
        const Uint8 *state;
        bool quit;
        bool paused;
        bool online;    // represents a multiplayer session
        int role;

    public:
        Stage(Screen*, bool, int);
        ~Stage();

        void mainLoop();
        void closeLoop();

        bool getPaused();
        void setPaused(bool);

        bool isOnline();

        int getRole();

        virtual void init() = 0;
        virtual void key_events() = 0;
        virtual void others() = 0;

        /** First Rect is the one below the second **/
        bool getCollision( SDL_Rect*, SDL_Rect* );

};

#endif