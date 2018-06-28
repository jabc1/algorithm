#include "can.h"
#include "stm32f10x_can.h"
#include "stm32f10x.h"
#include "delay.h"
#include "target.h"
#include "string.h"
 
static void can_gpio_clk_init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap2_CAN1, ENABLE);
}
 
static void can_gpio_init(void)
{
  can_gpio_clk_init();
 
  CAN_TX_CONFIG();
  CAN_RX_CONFIG();
}
 
static void can_mode_init(void)
{
  CAN_InitTypeDef CAN_InitStructure;
 
  CAN_DeInit(CAN_CHANNEL);
 
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = ENABLE ;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = ENABLE ;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;  // baund = APB1/((tbs1+1+tbs2+1+1)*brp)  --- APB1 = 36K
  CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;
  CAN_InitStructure.CAN_Prescaler = 8;
  CAN_Init(CAN_CHANNEL, &CAN_InitStructure);
}
 
static void can_nvic_init(void)
{
  NVIC_InitTypeDef  NVIC_InitStructure;
 
  CAN_ITConfig(CAN_CHANNEL, CAN_IT_FMP0, ENABLE);
 
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
 
static void can_filter_init(void)
{
  CAN_FilterInitTypeDef  CAN_FilterInitStructure;
 
  CAN_FilterInitStructure.CAN_FilterNumber = 0;
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
}
 
void CANInit(void)
{
  can_gpio_init();
  can_mode_init();
  can_filter_init();
  can_nvic_init();
}
 
void CanSendMsg(can_frame_t *frame)
{
  int i;
  CAN_Transmit(CAN_CHANNEL, frame);
  for(i=0;i<1000;++i);
}
 
void CAN1_RX0_IRQHandler(void)
{
  CanRxMsg RxMessage;
  CanTxMsg TxMessage;
  int i = 0;
  CAN_Receive(CAN_CHANNEL, 0, &RxMessage);
 
#if 1
  TxMessage.StdId = 0x101;
  TxMessage.IDE = CAN_Id_Standard;
  TxMessage.RTR = CAN_RTR_Data;
  TxMessage.DLC = RxMessage.DLC;
  for(i = 0; i < TxMessage.DLC; i++)
  {
    TxMessage.Data[i] = RxMessage.Data[i];
  }
  CanQueueWrite(&can_queue_send, &TxMessage);
#endif
}
 
#ifdef CONFIG_CAN
void can_general(void)
{
  int i;
  can_frame_t frame;
  uint8_t buffer[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
 
  frame.StdId = 0x11;
  frame.DLC = 6;
  frame.IDE = CAN_Id_Standard;
  frame.RTR = CAN_RTR_Data;
  memcpy(frame.Data, buffer, 6);
 
  //CanQueueWrite(&can_queue_send, &frame);
  for(i = 0; i < 7000; ++i);
}
#endif
