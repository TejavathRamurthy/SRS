#include "main.h"
#include <string.h>
#include <stdio.h>

UART_HandleTypeDef huart2;
uint8_t rx_data;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART2_UART_Init();

  HAL_UART_Receive_IT(&huart2, &rx_data, 1); // Start UART RX interrupt

  while (1)
  {
    // Loop empty — we handle commands in the RX callback
  }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART2)
  {
    switch(rx_data)
    {
      case 0x01: // Command 1 - e.g., "Light ON"
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
        break;
      case 0x02: // Command 2 - e.g., "Light OFF"
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
        break;
      // Add more cases for other commands
    }

    HAL_UART_Receive_IT(&huart2, &rx_data, 1); // Re-enable RX
  }
}
void MX_GPIO_Init(void)
{
  __HAL_RCC_GPIOB_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
