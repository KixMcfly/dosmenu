#ifndef __CHOICE_H
#define __CHOICE_H

#include <allegro.h>
#include <stdio.h>

typedef struct CHOICE CHOICE;

CHOICE *
choice_new (void);

void
choice_free (CHOICE *ch);

int
choice_push_text (CHOICE *ch, char *text);

int
choice_get_len (CHOICE *ch);

char *
choice_get_text (CHOICE *ch, int sel);

#endif
