#ifndef _SCREEN_H

#define _SCREEN_H
//#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_net.h>
#include <windows.h>
#include <vector>
#include <string>
#include <cstring>

class Screen
{
    public:

        Screen();

        ~Screen();

        bool init();

        void close();

        SDL_Window* getWindow();

        SDL_Surface* getWindowSurface();

        SDL_Renderer* getRenderer();

        int getDesktopWidth();

        char* getPlayer();

        void setMusic();

        void freeMusic();

        void detect_music();

        void switch_song(int);

        void increaseVolume(int);

        void switchFullscreen();

        bool force_quit;

    private:

        SDL_Window* mWindow;
        SDL_Surface* mSurface;
        SDL_Renderer* mRenderer;
        int DEF_W;
        int DEF_H;
        SDL_DisplayMode display;
        int DESK_W;
        bool server;
        char playerName[20];
        Mix_Music* bgMusic;
        std::vector<std::string> music_path;
        int total_songs, curr_song, last_changed_mus, mus_volume;
        Uint32 fullScreenActive, last_screen_switch;
};

#endif // _SCREEN_H
