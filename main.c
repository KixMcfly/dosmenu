#include "main.h"

const char *main_menu_option[] = {
		
	"Keyboard Setup",
	"Quit",
	NULL
};

int active_win = WIN_MAIN, prev_win = WIN_MAIN;

int
main (void)
{
	int res = 0, kp = 0;
	WIN *win_main, *win_quit;

	init_setup ();
	
	win_main = win_new (WIN_CHOICE);
	win_quit = win_new (WIN_QUIT);
	
	win_set_xywh (win_main,
				  WIN_MAIN_X, WIN_MAIN_Y,
				  WIN_MAIN_W, WIN_MAIN_H);
				  
	win_set_xywh (win_quit,
				  WIN_QUIT_X, WIN_QUIT_Y,
				  WIN_QUIT_W, WIN_QUIT_H);

	while (res != RES_QUIT){

		/* Draw active window */
		switch (active_win){
			case WIN_MAIN:
				
				win_draw (win_main);
				break;
			case WIN_QUIT:
				
				win_draw (win_quit);
				break;
		}
		
		kp = readkey () >> 8;
		
		/* Process active window */
		switch (active_win){
			case WIN_MAIN:
				res = win_process (win_main, kp);
				break;
			case WIN_QUIT:
				res = win_process (win_quit, kp);
				break;
		}
	}

	win_free (win_main);
	win_free (win_quit);

	uninit_setup ();
	return 0;
}

void
init_setup (void)
{
	allegro_init ();
	install_keyboard ();
	
	//populate_default_keys ();
	
	/* Turn off cursor and scrolling */
	_setcursortype (_NOCURSOR);
	_wscroll = 0;
	
	clrscr ();

}

void
uninit_setup (void)
{
	_setcursortype (_NORMALCURSOR);
	textbackground (BLACK);
	textcolor (LIGHTGRAY);
	window (1, 1, 80, 25);
	gotoxy (1, 1);
	clrscr ();
	
	//free_key_assigns ();
	
	remove_keyboard ();
	allegro_exit ();
}
