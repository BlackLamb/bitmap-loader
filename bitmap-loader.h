/***
 * Bitmap Loader
 * Copyright © 2013 Matthew Tole
 *
 * Version 2.0.1
 ***/

#pragma once

#include <pebble.h>

void bitmaps_init(void);
GBitmap* bitmaps_get_bitmap(uint32_t res_id);
void bitmaps_cleanup(void);