#ifndef __CONTROLS_H
#define __CONTROLS_H

#include <allegro.h>
#include "win.h"

typedef struct KEY_ASSIGN KEY_ASSIGN;

const char *
control_get_action (int k);

KEY_ASSIGN *
control_get_data (void);

int
get_num_keys (void);

void
free_key_assigns (void);

void
populate_default_keys (void);

#endif
