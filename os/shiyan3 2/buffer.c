#include "buffer.h"

buffer_t buffer = {
    .len = 0,
    .head = 0,
    .end = 0
};

int insert_item(buffer_item item)
{
    if (buffer.len >= BUFFER_SIZE){
        return -1;
    }else{
        buffer.len++;
        buffer.buf[buffer.end] = item;
        buffer.end = (buffer.end + 1) % BUFFER_SIZE;
        return 0;
    }

    return -1;
}

int remove_item(buffer_item* item)
{
    if (buffer.len <= 0){
        return -1;
    }else{
        buffer.len--;
        (*item) = buffer.buf[buffer.head];
        buffer.head = (buffer.head + 1) % BUFFER_SIZE;
        return 0;
    }
    return -1;
}