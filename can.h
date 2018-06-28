#ifndef _CAN_H_
#define _CAN_H_
 
#include "can_queue.h"
#include "type.h"
#include "debug.h"
 
void CANInit(void);
void CanSendMsg(can_frame_t *frame);
 
#ifdef CONFIG_CAN
void can_general(void);
#endif
 
#endif /* _CAN_H_ */
