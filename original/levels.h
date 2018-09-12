#ifndef _LEVELS_H

#define _LEVELS_H
#include "screen.h"
void level1(Screen*);

void level2(Screen*);

void level3(Screen*);

void level4();

void level5(Screen*);

void stage1(Screen*);

void test_net(Screen*, bool);

void nave_net(Screen*, int);

void rezultate(int, char*, int);

SDL_Texture* afisare_status(int, int, SDL_Renderer*);

void choose_name(Screen*, int);

void menu1(Screen*);

void rankings(Screen*);

#endif // _LEVELS_H
