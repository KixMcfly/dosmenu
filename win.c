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

static int cur_win = 0, prev_win = 0;

void
win_set_cur (int win)
{
	prev_win = cur_win;
	cur_win = win;
}

int
win_get_prev (void)
{
	return prev_win;
}

int
win_get_cur (void)
{
	return cur_win;
}

int
win_attach_data (WIN *win, void *data)
{
	
	if (!win) return 0;
		
	win->num_lines = 0;
	win->data = NULL;

	switch (win->type){
		case WIN_KEYS:
			win->num_lines = get_num_keys ();
			
			break;
		case WIN_CHOICE:
			win->num_lines = choice_get_len((CHOICE *)data);
			break;
	}
	
	win->data = data;
	
	return 1;
}

int
win_process (WIN *win, int kp)
{
	
	if (kp == KEY_ESC)
		return RES_BACK;
	
	switch (win->type){
		case WIN_CHOICE:
			if (kp == KEY_UP) win->sel--;
			if (kp == KEY_DOWN) win->sel++;
			
			if (win->sel == win->num_lines) win->sel = 0;
			if (win->sel < 0) win->sel = win->num_lines - 1;
			
			if (kp == KEY_ENTER)
				return win->sel;
				
			break;
	}
	
	
	
	return RES_NOOP;
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
	
	if (type != WIN_CHOICE && type != WIN_PROMPT && type != WIN_KEYS )
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
	int x, y, w, h, i;
	CHOICE *t_choice = NULL;
	char *t_prompt = NULL;
	
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

	switch (win->type){
		case WIN_CHOICE:
			t_choice = win->data;
			for (i = 0, x = 3, y = 3; i < win->num_lines; i++, y++){
				gotoxy (x, y);
				if (i == win->sel) cprintf ("%c%s", 0x10, 
					choice_get_text (t_choice, i));
				else cprintf (" %s", choice_get_text (t_choice, i));
			}
			break;
		case WIN_KEYS:

			for (i = 0, x = 3, y = 3; i < win->num_lines; i++, y++){
				gotoxy (x, y);
				if (i == win->sel)
					cprintf ("%c%s", 0x10, control_get_action (i));
				else
					cprintf (" %s", control_get_action (i));
			}
			
			break;
		case WIN_PROMPT:
			t_prompt = win->data;
			x = 3;
			y = 1;
			gotoxy (x, y);
			cprintf ("%s", t_prompt);
			gotoxy (x+4, y+2);
			cprintf ("Y/N");
			break;
	}
}
