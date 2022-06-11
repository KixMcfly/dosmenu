#include "controls.h"

typedef struct {
	
	int key;
	char *action;
	
} KEY_ASSIGN;

static const char *action_list[] = {
		
		"Move Up",
		"Move Down",
		"Move Left",
		"Move Right",
		NULL
};

static const int action_default[] = {
		KEY_UP,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT
	
};

/* Keyboard assign positions and dimentions */


static KEY_ASSIGN *key_assigns = NULL;

static int
get_num_actions (void)
{
	int na = 0;
	while (action_list[na])
		na++;
		
	return na;
}

void
free_key_assigns (void)
{
	int na, ca = 0;
	
	na = get_num_actions ();
	
	while (ca < na)
		free (key_assigns[ca++].action);
	
	free (key_assigns);
	
	key_assigns = NULL;
}

void
populate_default_keys (void)
{
	int na = 0, ca = 0;

	na = get_num_actions ();

	key_assigns = (KEY_ASSIGN *) malloc (sizeof (KEY_ASSIGN) * na);
		
	for (ca = 0; ca < na; ca++){
		key_assigns[ca].key = action_default[ca];
		key_assigns[ca].action = (char *) malloc (strlen (action_list[ca]) + 1);
		strcpy (key_assigns[ca].action, action_list[ca]);
	}
}
