// fifo.h

#ifndef FIFO_H
#define FIFO_H

#include <inttypes.h>


#define FIFO_MODULE_USE_INBUILT_BUFFER	1
#define FIFO_MODULE_SIZE				128


typedef struct
{
#if FIFO_MODULE_USE_INBUILT_BUFFER
	volatile uint8_t byteBuffer[FIFO_MODULE_SIZE];
#else
	uint8_t *byteBuffer;
	uint8_t length;
#endif
	volatile uint8_t tail;
	volatile uint8_t head;

} FifoModule;



void Fifo_init(volatile FifoModule * const fifo);

uint8_t Fifo_getNextByte(volatile FifoModule * const fifo);
uint8_t Fifo_peekNextByte(volatile FifoModule * const fifo);
uint8_t Fifo_setNextByte(volatile FifoModule * const fifo, uint8_t data);

uint8_t Fifo_isEmpty(volatile FifoModule * const fifo);

uint8_t Fifo_isFull(volatile FifoModule * const fifo);

void Fifo_clear(volatile FifoModule * const fifo);



#endif
