/***
 * Bitmap Loader
 * Copyright © 2013 Matthew Tole
 ***/

#pragma once

#include <pebble.h>

void bitmaps_init(void);
GBitmap* bitmaps_get_bitmap(uint32_t res_id);
void bitmaps_cleanup(void);
