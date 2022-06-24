#include "choice.h"

#define MAX_LINES  		100
#define MAX_CHARS		79

struct CHOICE {
	
	int len;
	char text[MAX_LINES][MAX_CHARS];
};

CHOICE *
choice_new (void)
{
	CHOICE *ch = (CHOICE *) malloc (sizeof (CHOICE));
	
	if (!ch) return NULL;
	
	ch->len = 0;
	
	return ch;
}

void
choice_free (CHOICE *ch)
{
	if (ch){ 
		free (ch);
		ch = NULL;
	}
}

int
choice_push_text (CHOICE *ch, char *text)
{
	int len = strlen (text) + 1;
	
	if (len > MAX_CHARS)
		return 0;
	
	strcpy (ch->text[ch->len], text);
	ch->len++;
	return 1;
}

int
choice_get_len (CHOICE *ch)
{
	return ch->len;
}

char *
choice_get_text (CHOICE *ch, int sel)
{
	if (sel < ch->len)
		return ch->text[sel];
	else
		return NULL;
}
