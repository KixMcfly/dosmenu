#ifndef __WIN_H
#define __WIN_H

#include <allegro.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "controls.h"
#include "choice.h"

/* Color settings */
#define WIN_BACK_COLOR		BLUE
#define WIN_TEXT_COLOR		LIGHTGRAY
#define WIN_BORDER_COLOR	WHITE

#define SCR_W				80
#define SCR_H				25

typedef struct WIN WIN;

/* Window types */
enum {
	WIN_CHOICE,
	WIN_KEYS,
	WIN_PROMPT
};

/* Window responses */
enum {
	RES_NOOP,
	RES_QUIT,
	RES_BACK,
	RES_N,
	RES_Y
};

void
win_set_cur (int win);

int
win_get_prev (void);

int
win_get_cur (void);

int
win_attach_data (WIN *win, void *data);

int
win_process (WIN *win, int kp);

int
win_set_xywh (WIN *win, int x, int y, int w, int h);

WIN *
win_new (int type);

void
win_free (WIN *win);

void
win_draw (WIN *win);

#endif
