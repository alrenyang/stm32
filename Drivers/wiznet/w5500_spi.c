/*
 * w5500_spi.c
 *
 *  Created on: Oct 21, 2023
 *      Author: alren
 */
#include "stm32f1xx_hal.h"
#include "wizchip_conf.h"
#include "stdio.h"

extern SPI_HandleTypeDef hspi2;

uint8_t SPIReadWrite(uint8_t data)
{
  //wait till FIFO has a free slot
  while((hspi2.Instance->SR & SPI_FLAG_TXE) != SPI_FLAG_TXE);

  *(__IO uint8_t*)&hspi2.Instance->DR=data;

  //Now wait till data arrives
  while((hspi2.Instance->SR & SPI_FLAG_RXNE) != SPI_FLAG_RXNE);

  return (*(__IO uint8_t*)&hspi2.Instance->DR);
}

void wizchip_select(void)
{
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
}

void wizchip_deselect(void)
{
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
}

uint8_t wizchip_read()
{
  uint8_t rb;
  rb = SPIReadWrite(0x00);

  return rb;
}

void wizchip_wrie(uint8_t wb)
{
  SPIReadWrite(wb);
}

void wizchip_readburst(uint8_t* pBuf, uint16_t len)
{
  for(uint16_t i=0; i<len; i++)
  {
    *pBuf = SPIReadWrite(0x00);
    pBuf++;
  }
}

void wizchip_writeburst(uint8_t* pBuf, uint16_t len)
{
  for(uint16_t i=0; i<len; i++)
  {
    SPIReadWrite(*pBuf);
    pBuf++;
  }
}

void W5500IO_Init()
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void w5500Init()
{
  uint8_t tmp;
  uint8_t W5x00_AdrSet[2][8] = {{2, 2, 2, 2, 2, 2, 2, 2},{2, 2, 2, 2, 2, 2, 2, 2},};

  W5500IO_Init();

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);// spi cs hight

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET); //w5500 reset pin
  tmp = 0xFF;
  while(tmp--);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);

  reg_wizchip_cs_cbfunc(wizchip_select, wizchip_deselect);
  reg_wizchip_spi_cbfunc(wizchip_read, wizchip_wrie);
  reg_wizchip_spiburst_cbfunc(wizchip_readburst, wizchip_writeburst);

  // WIZchip Initialize
  if(ctlwizchip(CW_INIT_WIZCHIP, (void*) W5x00_AdrSet) == -1){
    printf("Wizchip Initialize failed..\r\n");
    while(1);
  }
  printf("Wizchip Initialize Success..\r\n");
}


