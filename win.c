#include "win.h"

struct WIN {
	
	int x;
	int y;
	int w;
	int h;
	int sel;
	int type;
	int num_lines;
	void *data;
	
};

int
win_attach_data (WIN *win, char *data)
{
	if (!win) return 0;
	
	win->data = data;
	
	return 1;
}

int
win_process (WIN *win, int kp)
{
	switch (win->type){
		case WIN_CHOICE:
			if (kp == KEY_UP) win->sel--;
			if (kp == KEY_DOWN) win->sel++;
			
			if (win->sel > win->num_lines) win->sel = 0;
			if (win->sel < 0) win->sel = win->num_lines;
			break;
	}
	
	return 1;
}

int
win_set_xywh (WIN *win, int x, int y, int w, int h)
{
	
	if (!win) return 0;
	
	win->x = x;
	win->y = y;
	win->w = w;
	win->h = y;
	
	return 1;
}

WIN *
win_new (int type)
{
	WIN *win = NULL;
	
	if (type != WIN_CHOICE || type != WIN_KEYS)
		return NULL;
	
	win = (WIN *)malloc (sizeof (WIN));
	
	if (!win)
		return NULL;
	
	win->x = 1;
	win->y = 1;
	win->w = 12;
	win->h = 12;
	win->sel = 0;
	win->type = type;
	win->data = NULL;
	
	return win;
}

void
win_free (WIN *win)
{
	if (win) free (win);
}

static void
draw_border (int x, int y, int w, int h)
{
	int tx, ty, i;
	int left, right, temp;
	
	tx = x;
	ty = y;
	
	gotoxy (x, y);
	for (i = 0; i < w / 2; i++, tx++){
		textcolor (LIGHTGRAY);
		cprintf ("%c", 0xDB);
		gotoxy (tx++, ty);
		textcolor (LIGHTBLUE);
		gotoxy (tx, ty);
		cprintf ("%c", 0xDB);
	}
	
	tx = x + w - 1;
	ty = y + 1;
	
	for (i = 0, left = LIGHTBLUE, right = LIGHTGRAY; i < h - 2; i++, ty++){
		textcolor (left);
		gotoxy (x, ty);
		cprintf ("%c", 0xDB);
		textcolor (right);
		gotoxy (tx, ty);
		cprintf ("%c", 0xDB);
		temp = left;
		left = right;
		right = temp;
	}
	
	gotoxy (x, ty);
	for (i = 0; i < w / 2; i++, x++){
		textcolor (LIGHTBLUE);
		cprintf ("%c", 0xDB);
		gotoxy (x++, ty);
		textcolor (LIGHTGRAY);
		gotoxy (x, ty);
		cprintf ("%c", 0xDB);
	}
}

void
win_draw (WIN *win)
{
	int x, y, w, h;
	
	x = win->x;
	y = win->y;
	w = win->w;
	h = win->h;
	
	/* Clear screen */
	window (1, 1, 80, 25);
	textbackground (BLACK);
	clrscr ();

	/* Draw border */
	textcolor (WIN_TEXT_COLOR);
	textbackground (WIN_BACK_COLOR);
	draw_border (x, y, w, h);
	
	/* Finally, draw window */
	window (x+1, y+1, w+x-2, h+y-2);
	clrscr ();
	
	if (win->type == WIN_PROMPT){
		
	}

}
