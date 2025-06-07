// fifo.c

#include "fifo.h"


void Fifo_init(volatile FifoModule * const fifo) {
    if (fifo == 0) return;

    fifo->tail = 0;
    fifo->head = 0;

    return;
}


void Fifo_clear(volatile FifoModule * const fifo) {
    if (fifo == 0) return;

    fifo->tail = 0;
    fifo->head = 0;

    return;
}


uint8_t Fifo_getNextByte(volatile FifoModule * const fifo) {
    uint8_t data;

    if (Fifo_isEmpty(fifo)) {
        return 0;
    }

    data = fifo->byteBuffer[fifo->tail];
    fifo->tail++;

#if FIFO_MODULE_USE_INBUILT_BUFFER
    if (fifo->tail == FIFO_MODULE_SIZE) // loop
#else
    if (fifo->tail == fifo->length) // loop
#endif
    {
        fifo->tail = 0;
    }

    return data;
}


uint8_t Fifo_peekNextByte(volatile FifoModule * const fifo) {
    uint8_t data;

    if (Fifo_isEmpty(fifo)) {
        return 0;
    }

    data = fifo->byteBuffer[fifo->tail];

    return data;
}

uint8_t Fifo_setNextByte(volatile FifoModule * const fifo, uint8_t data) {
    if (Fifo_isFull(fifo)) {
        return 0;
    }

    fifo->byteBuffer[fifo->head] = data;
    fifo->head++;

#if FIFO_MODULE_USE_INBUILT_BUFFER
    if (fifo->head == FIFO_MODULE_SIZE) // loop
#else
    if (fifo->head == fifo->length) // loop
#endif
    {
        fifo->head = 0;
    }

    return 1;
}


uint8_t Fifo_isEmpty(volatile FifoModule * const fifo) {
    if (fifo->head == fifo->tail) {
        // Empty
        return 1;
    }

    return 0;
}


uint8_t Fifo_isFull(volatile FifoModule * const fifo) {
    if (fifo->head == (fifo->tail - 1)) {
        // Full
        return 1;
    }

#if FIFO_MODULE_USE_INBUILT_BUFFER
    if ((fifo->head == (FIFO_MODULE_SIZE - 1)) && (fifo->tail == 0))
#else
    if ((fifo->head == (fifo->length - 1)) && (fifo->tail == 0))
#endif
    {
        // Full
        return 1;
    }

    return 0;
}

