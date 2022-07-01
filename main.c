#include "main.h"

int
main (void)
{
	int quit = FALSE, res = RES_NOOP, kp = 0, edit_key = FALSE;
	WIN *win_main, *win_keys, *win_quit;
	CHOICE *choice_main;

	init_setup ();
	
	/* Create main menu and add options */
	choice_main = choice_new ();
	choice_push_text (choice_main, "Keyboard Setup");
	choice_push_text (choice_main, "Quit");

	/* Create windows */
	win_main = win_new (WIN_CHOICE);
	win_keys = win_new (WIN_KEYS);
	win_quit = win_new (WIN_PROMPT);
	
	/* Attach data to windows */
	win_attach_data (win_main, choice_main);
	win_attach_data (win_keys, control_get_data ());
	win_attach_data (win_quit, "Quit? Are you sure?");
	
	/* Set window sizes */
	win_set_xywh (win_main,
				  WIN_MAIN_X, WIN_MAIN_Y,
				  WIN_MAIN_W, WIN_MAIN_H);
				  
	win_set_xywh (win_quit,
				  WIN_QUIT_X, WIN_QUIT_Y,
				  WIN_QUIT_W, WIN_QUIT_H);
				  
	win_set_xywh (win_keys,
				  WIN_KEYS_X, WIN_KEYS_Y,
				  WIN_KEYS_W, WIN_KEYS_H);
	
	
	/* Set starting active window */
	win_set_cur (WIN_MAIN);
	
	/* MAIN LOOP */
	while (quit == FALSE){
	
		/* Draw active window */
		switch (win_get_cur ()){
			case WIN_MAIN:
				
				win_draw (win_main);
				break;
			case WIN_QUIT:
				
				win_draw (win_quit);
				break;
			case WIN_KEYS:
				
				win_draw (win_keys);
				break;
		}
		
		/* Wait for user input */
		kp = readkey () >> 8;
		
		/* Process active window */
		switch (win_get_cur ()){
			case WIN_MAIN:
				res = win_process (win_main, kp);
				
				/* Keyboard controls pressed */
				if (res == 0)
					win_set_cur (WIN_KEYS);
				
				/* Quit pressed */
				if (res == 1)
					win_set_cur (WIN_QUIT);

				break;
			case WIN_KEYS:
				
				
				res = win_process (win_keys, kp);
				
				if (res == RES_BACK)
					win_set_cur (win_get_prev ());
			

				break;
			case WIN_QUIT:
		
				if (kp == KEY_Y) quit = TRUE;
				else if (kp == KEY_ESC || kp == KEY_N)
					win_set_cur (win_get_prev ());
				
				break;
		}
		
		
		
	}
	
	choice_free (choice_main);
	
	win_free (win_main);
	win_free (win_keys);
	win_free (win_quit);

	uninit_setup ();
	return 0;
}

void
init_setup (void)
{
	allegro_init ();
	install_keyboard ();
	
	populate_default_keys ();
	
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
	
	free_key_assigns ();
	
	remove_keyboard ();
	allegro_exit ();
}
