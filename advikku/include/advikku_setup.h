#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tonc.h>

#ifndef ADVIKKU_SETUP
#define ADVIKKU_SETUP

void cell_song_setup(advikSongStruct setsong);

void cell_sfx_setup(advikSFXStruct setsfx, uint16_t sfx_chan);

#endif