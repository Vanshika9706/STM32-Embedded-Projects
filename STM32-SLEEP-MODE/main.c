#include "main.h"
#include <stdio.h>
#include <string.h>

UART_HandleTypeDef huart3;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);

int main(void)
{
  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_USART3_UART_Init();

  HAL_UART_Transmit(&huart3,(uint8_t*)"System Ready\r\n",strlen("System Ready\r\n"),100);

  while (1)
  {
      HAL_UART_Transmit(&huart3,(uint8_t*)"Going to sleep...\r\n",strlen("Going to sleep...\r\n"),100);

      HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);

      HAL_Delay(1000);

      HAL_SuspendTick();
      HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON,PWR_SLEEPENTRY_WFI);
      HAL_ResumeTick();

      HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);

      HAL_UART_Transmit(&huart3,(uint8_t*)"Woke up!\r\n",strlen("Woke up!\r\n"),100);
      HAL_Delay(3000);
  }
}

void SystemClock_Config(void)
{
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
}

static void MX_USART3_UART_Init(void)
{
  __HAL_RCC_USART3_CLK_ENABLE();

  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;

  HAL_UART_Init(&huart3);
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /* LED */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USART3 pins */
  GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* User button PC13 interrupt */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn,0,0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

/* Interrupt Handler */


/* Callback when button pressed */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == GPIO_PIN_13)
  {
      HAL_UART_Transmit(&huart3,(uint8_t*)"Button Interrupt\r\n",strlen("Button Interrupt\r\n"),100);
  }
}

void Error_Handler(void)
{
  while(1)
  {
  }
}
