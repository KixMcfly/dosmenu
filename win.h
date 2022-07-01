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

/* Window responses */
#define RES_NOOP			0xFFFF0000
#define RES_QUIT			0xFFFF0001
#define	RES_BACK			0xFFFF0002
#define	RES_N				0xFFFF0003
#define RES_Y				0xFFFF0004

typedef struct WIN WIN;

/* Window types */
enum {
	WIN_CHOICE,
	WIN_KEYS,
	WIN_PROMPT
};

unsigned int
win_get_sel (WIN *win);

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
