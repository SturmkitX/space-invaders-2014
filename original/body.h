#ifndef _BODY_H

#define _BODY_H
//#include <SDL.h>
#include <SDL_image.h>
class Body
{
    public:

        Body();

        ~Body();

        void create(SDL_Renderer*, char*);

        void free();

        void setRect(int, int, int, int);

        void setRect(SDL_Rect*);

        SDL_Rect* getRect();

        int getWidth();

        int getHeight();

        int getX();

        int getY();

        void setX(int);

        void setY(int);

        void setPosition(int, int);

        void translate(int, int);

        void render(SDL_Renderer*);

        void render(SDL_Renderer*, SDL_Rect*, SDL_Rect*);

        void setRotation( double );

        double getRotation();

        void rotateIt( double );

        SDL_Texture* getTexture();

        void setCenter(int, int);

        void setCenter(SDL_Point*);

        SDL_Point* getCenter();

        void setTexture(SDL_Texture*);

    private:

        SDL_Rect rect;
        SDL_Texture* texture;
        double rotation;
        SDL_Point center;
        SDL_RendererFlip flip;
        int hDiff;
};

#endif // _BODY_H
