#ifndef __MAIN_H
#define __MAIN_H
#include <allegro.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "win.h"
#include "controls.h"
#include "choice.h"

/* Available windows */
#define WIN_MAIN			0
#define WIN_KEYS			1
#define WIN_QUIT			2

/* Color settings */
#define WIN_BACK_COLOR		BLUE
#define WIN_TEXT_COLOR		LIGHTGRAY
#define WIN_BORDER_COLOR	WHITE

/* Main menu positions and dimentions */
#define WIN_MAIN_X 			26
#define WIN_MAIN_Y 			8
#define WIN_MAIN_W 			30
#define WIN_MAIN_H 			10

#define WIN_KEYS_X			16
#define WIN_KEYS_Y			6
#define WIN_KEYS_W			50
#define WIN_KEYS_H			18

#define WIN_QUIT_X			16
#define WIN_QUIT_Y			6
#define WIN_QUIT_W			50
#define WIN_QUIT_H			13

void
init_setup (void);

void
uninit_setup (void);

#endif
