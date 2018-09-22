#ifndef _STAGE_1_H
#define _STAGE_1_H

#include <list>
#include "stage.h"
#include "body.h"

class SinglePlayer_Stage1 : public Stage
{
    private:
        // Inamici
        Body *enemy;
        std::list<SDL_Rect> *eBul;
        std::list<SDL_Rect> *ePos;
        std::list<Uint32> *eTim;

        // Player si altele
        SDL_Point *p, *pausedPos;
        int pHealth;
        bool movableNava;
        Uint32 lastShot;
        Body *nava, *glont_nava, *glont_enemy;
        SDL_Rect glont_rect;    // used as an utility variable
        std::list<SDL_Rect> *pBul;
        Body *space;
        Mix_Chunk *laser;

        //Misc. stuff
        int vSpatiu;
        Uint32 eShot;
        int deParcurs;
        int parcurs;
        int pScore;
        int maxEnemies;
        Body *healthBody;
        SDL_Texture* scoreTex;
        SDL_Rect *scoreRect;

        // static const
        static const int BULLET_VELOCITY = 6;

        void compute_difficulty();
        void compute_enemy_spawn();
        void update_enemy_bullets();
        void update_enemy_positions();
        void update_player_bullets();
        void update_player_position();

    public:
        SinglePlayer_Stage1(Screen *mScreen);
        ~SinglePlayer_Stage1();

    protected:
        void init();
        void window_events();
        void keyboard_events();
        void others();
        void render();
};

#endif
