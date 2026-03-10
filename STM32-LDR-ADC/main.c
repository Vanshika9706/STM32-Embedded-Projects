#include "main.h"
#include <stdio.h>
#include <string.h>

ADC_HandleTypeDef hadc1;
UART_HandleTypeDef huart3;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART3_UART_Init(void);

int main(void)
{
  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_USART3_UART_Init();

  while (1)
  {
	  BSP_LED_Toggle(LED_GREEN);

	    HAL_ADC_Start(&hadc1);
	    HAL_ADC_PollForConversion(&hadc1,100);

	    uint32_t value = HAL_ADC_GetValue(&hadc1);

	    char msg[40];
	    sprintf(msg,"LDR: %lu\r\n",value);

	    HAL_UART_Transmit(&huart3,(uint8_t*)msg,strlen(msg),100);

	    HAL_Delay(100);

  }
}
void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {BSP_LED_Toggle(LED_RED);
  HAL_Delay(200);
  }
}

void SystemClock_Config(void)
{
}

static void MX_ADC1_Init(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};

  hadc1.Instance = ADC1;
  hadc1.Init.Resolution = ADC_RESOLUTION_16B;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;

  HAL_ADC_Init(&hadc1);

  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_387CYCLES_5;

  HAL_ADC_ConfigChannel(&hadc1, &sConfig);
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

  HAL_UART_Init(&huart3);
}

static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	    __HAL_RCC_GPIOD_CLK_ENABLE();
	    __HAL_RCC_GPIOB_CLK_ENABLE();

	    /* UART3 pins */
	    GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
	    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	    /* LED pins */
	    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_7 | GPIO_PIN_14;
	    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	    __HAL_RCC_GPIOA_CLK_ENABLE();

	    GPIO_InitStruct.Pin = GPIO_PIN_0;
	    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
