#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <unistd.h>

#define BUFFER_SIZE 5

typedef int buffer_item;
typedef int buffer_idx;
typedef struct {
    buffer_item buf[BUFFER_SIZE];
    size_t len;
    buffer_idx head;
    buffer_idx end;
} buffer_t;

extern buffer_t buffer;

int insert_item(buffer_item item);
int remove_item(buffer_item* item);

#endif