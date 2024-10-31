#include "ringbuffer.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <assert.h>

#define mu_assert(cond, ...)    \
do {    \
    if (!(cond)) {  \
        printf(__VA_ARGS__);   \
    }    \
} while(0)



// 创建一个环形缓冲区
ringbuffer *ringBuffer_create(int length) {
    ringbuffer *rb = (ringbuffer *)calloc(1, sizeof(ringbuffer));
    if (rb == NULL) {
        return NULL; // 分配失败
    }
    rb->buffer = calloc(length, 1);
    if (rb->buffer == NULL) {
        free(rb);
        return NULL;
    }
    rb->length = length;
    rb->start = 0;
    rb->end = 0;
    return rb;
}


// 销毁环形缓冲区
void ringBuffer_destroy(ringbuffer *buffer) {
    if (buffer) {
        free(buffer->buffer);
        free(buffer);
    }
}

// 判断环形缓冲区是否为空
int ringBuffer_empty(ringbuffer *buffer) {
    return buffer->start == buffer->end;
}

// 判断环形缓冲区是否为满
int ringBuffer_full(ringbuffer *buffer) {
    return (buffer->end + 1) % buffer->length == buffer->start;
}

// 获取环形缓冲区中的可用数据量
int ringBuffer_available_data(ringbuffer *buffer) {
    if (buffer->end >= buffer->start) {
        return buffer->end - buffer->start;
    } else {
        return buffer->length - buffer->start + buffer->end;
    }
}


// 获取环形缓冲区中的可用空间
int ringBuffer_available_space(ringbuffer *buffer) {
    return buffer->length - ringBuffer_available_data(buffer);
}


// 向环形缓冲区写入数据
int ringBuffer_write(ringbuffer *buffer, char *data, int length) {
    if (ringBuffer_available_space(buffer) < length) {
        return -1; // 空间不足，写入失败
    }
    for (int i = 0; i < length; i++) {
        buffer->buffer[buffer->end] = data[i];
        buffer->end = (buffer->end + 1) % buffer->length;
    }
    return length; // 写入成功，返回写入字节数
}


// 从环形缓冲区获取指定数量的数据，但不删除
int ringBuffer_gets(ringbuffer *buffer, int amount) {
    if (ringBuffer_available_data(buffer) < amount) {
        return -1; // 数据不足，读取失败
    }
    for (int i = 0; i < amount; i++) {
        printf("%c", buffer->buffer[(buffer->start + i) % buffer->length]);
    }
    printf("\n");
    return amount; // 成功获取数据
}

// 从环形缓冲区读取数据
int ringBuffer_read(ringbuffer *buffer, char *target, int amount) {
    if (ringBuffer_available_data(buffer) < amount) {
        return -1; // 数据不足，读取失败
    }
    for (int i = 0; i < amount; i++) {
        target[i] = buffer->buffer[buffer->start];
        buffer->start = (buffer->start + 1) % buffer->length;
    }
    return amount; // 读取成功，返回读取字节数
}


int main() {
    // 创建并测试环形缓冲区
    ringbuffer *rb = ringBuffer_create(15);
    if (!rb) {
        printf("缓冲区创建失败！\n");
        return -1;
    }

    // 写入数据
    char data[] = "hello World!";
    if (ringBuffer_write(rb, data, strlen(data)) == -1) {
        printf("写入失败，空间不足！\n");
    }

    // 读取数据
    char target[6] = {0};
    if (ringBuffer_read(rb, target, 5) == -1) {
        printf("读取失败，数据不足！\n");
    } else {
        printf("读取的数据: %s\n", target);
    }

    // 查看当前缓冲区内容
    printf("缓冲区内容: ");
    ringBuffer_gets(rb, 6);

    // 销毁缓冲区
    ringBuffer_destroy(rb);
    return 0;
}