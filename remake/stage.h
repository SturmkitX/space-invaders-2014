#ifndef _STAGE_H
#define _STAGE_H

#include <SDL.h>
#include "screen.h"

class Stage
{
    protected:
        SDL_Event e;
        Screen *mScreen;
        SDL_Renderer* rnd;
        const Uint8 *state;
        bool quit;
        bool paused;
        static int DESK_W;
        static int DESK_H;

        void closeLoop();
        void forceClose();

        bool isPaused();
        void setPaused(bool);

        Screen* getScreen();

        /** First Rect is the one below the second **/
        bool getCollision( SDL_Rect*, SDL_Rect* );

        virtual void init() = 0;
        virtual void window_events() = 0;
        virtual void keyboard_events() = 0;
        virtual void others() = 0;
        virtual void render() = 0;

    public:
        Stage(Screen*);
        ~Stage();

        void mainLoop();

};

#endif
