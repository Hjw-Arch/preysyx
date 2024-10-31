#ifndef ringBuffer_H
#define ringBuffer_H


typedef struct ringBuffer{
    char *buffer;
    int length;
    int start;
    int end;
}ringbuffer;

ringbuffer *ringBuffer_create(int length);

void ringBuffer_destroy(ringbuffer *buffer);

int ringBuffer_read(ringbuffer *buffer, char *target, int amount);

int ringBuffer_write(ringbuffer *buffer, char *data, int length);

int ringBuffer_empty(ringbuffer *buffer);

int ringBuffer_full(ringbuffer *buffer);

int ringBuffer_available_data(ringbuffer *buffer);

int ringBuffer_available_space(ringbuffer *buffer);

// bstring ringBuffer_gets(ringbuffer *buffer, int amount);


#endif