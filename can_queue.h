#ifndef _CAN_QUEUE_H_
#define _CAN_QUEUE_H_
 
#include "stm32f10x_can.h"
#include "type.h"
 
#define CAN_TX_SIZE      0x25
 
typedef enum
{
  CAN_ERROR = 0,
  CAN_OK    = 1,
  CAN_BUSY  = 2,
} can_queue_status_t;
 
typedef CanTxMsg  can_frame_t;
 
typedef struct
{
  uint32_t write;
  uint32_t read;
  boolean is_full;
  uint32_t length;
  can_frame_t *frame;
} can_queue_t;
 
extern can_queue_t can_queue_send;
 
void CanQueueInit(void);
uint8_t CanQueueRead(can_queue_t *q, can_frame_t *frame);
uint8_t CanQueueWrite(can_queue_t *q, can_frame_t *frame);
 
#endif /* _CAN_QUEUE_H_ */
