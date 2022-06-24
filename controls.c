#include "controls.h"

struct KEY_ASSIGN {
	
	int key;
	char *action;
	
};

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

static int nk = 0;
static KEY_ASSIGN *key_assigns = NULL;

const char *
control_get_action (int k)
{
	if (k > nk - 1)
		return NULL;
		
	return key_assigns[k].action;
}

KEY_ASSIGN *
control_get_data (void)
{
	return key_assigns;
}

int
get_num_keys (void)
{	
	return nk;
}

void
free_key_assigns (void)
{
	int ca = 0;
	
	while (ca < nk)
		free (key_assigns[ca++].action);
	
	free (key_assigns);
	
	key_assigns = NULL;
}

void
populate_default_keys (void)
{
	int ca = 0;
	nk = 0;

	while (action_list[nk])
		nk++;


	key_assigns = (KEY_ASSIGN *) malloc (sizeof (KEY_ASSIGN) * nk);
		
	for (ca = 0; ca < nk; ca++){
		key_assigns[ca].key = action_default[ca];
		key_assigns[ca].action = (char *) malloc (strlen (action_list[ca]) + 1);
		strcpy (key_assigns[ca].action, action_list[ca]);
	}
}
