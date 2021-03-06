#include <pebble.h>
#include "pebble-extra.h"

typedef struct Persist Persist;

typedef enum PersistType {
  DATA, NUMBER, STRING
} PersistType;

struct Persist {
  uint32_t key;
  PersistType type;
  void* data;
  uint32_t number;
  char* str;
  Persist* next;
};

static Persist* persist_read(uint32_t key);
static bool persist_write(Persist* persist);

Persist* persistence = NULL;

bool persist_exists(const uint32_t key) {
  return NULL != persist_read(key);
}

int persist_read_data(const uint32_t key, void *buffer, const size_t buffer_size) {
  Persist* persist = persist_read(key);
  if (! persist) {
    return -1;
  }
  if (DATA != persist->type) {
    return -1;
  }
  buffer = malloc(buffer_size);
  memcpy(buffer, persist->data, buffer_size);
  return buffer_size;
}

int32_t persist_read_int(const uint32_t key) {
  Persist* persist = persist_read(key);
  if (! persist) {
    return -1;
  }
  if (NUMBER != persist->type) {
    return -1;
  }
  return persist->number;
}

status_t persist_write_int(const uint32_t key, const int32_t value) {
  persist_delete(key);
  Persist* persist = malloc(sizeof(Persist));
  persist->key = key;
  persist->type = NUMBER;
  persist->number = value;
  persist->next = NULL;
  persist_write(persist);
  return 0;
}

int persist_write_data(const uint32_t key, const void *data, const size_t size) {
  persist_delete(key);
  Persist* persist = malloc(sizeof(Persist));
  persist->key = key;
  persist->type = DATA;
  persist->data = malloc(size);
  memcpy(persist->data, data, size);
  persist->next = NULL;
  persist_write(persist);
  return size;
}

static bool persist_write(Persist* persist) {
  if (NULL == persistence) {
    persistence = persist;
  }
  else {
    Persist* ptr = persistence;
    while (NULL != ptr->next) {
      ptr = ptr->next;
    }
    ptr->next = persist;
  }
  return true;
}

static Persist* persist_read(uint32_t key) {
  Persist* ptr = persistence;
  while (NULL != ptr) {
    if (key == ptr->key) {
      return ptr;
    }
    ptr = ptr->next;
  }
  return NULL;
}

status_t persist_delete(uint32_t key) {
  return S_SUCCESS;
}

GBitmap* gbitmap_create_with_resource(uint32_t resource_id) {
  GBitmap* bitmap = malloc(sizeof(GBitmap));
  bitmap->addr = malloc(32);
  bitmap->reserved = (uint16_t)resource_id;
  return bitmap;
}

GBitmap* gbitmap_create_as_sub_bitmap(const GBitmap *base_bitmap, GRect sub_rect) {
  GBitmap* bitmap = malloc(sizeof(GBitmap));
  bitmap->addr = (void*)base_bitmap;
  bitmap->bounds = sub_rect;
  return bitmap;
}

void gbitmap_destroy(GBitmap* bitmap) {
  free(bitmap->addr);
  free(bitmap);
}

bool grect_equal(const GRect* const r0, const GRect* const r1) {
  return ((r0->origin.x == r1->origin.x) &&
          (r0->origin.y == r1->origin.y) &&
          (r0->size.w == r1->size.w) &&
          (r0->size.h == r1->size.h));
}


void app_log(uint8_t log_level, const char* src_filename, int src_line_number, const char* fmt, ...) {

}

void resources_add_bitmap(uint32_t resource_id) {
}