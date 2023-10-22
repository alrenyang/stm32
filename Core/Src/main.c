/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "w5500_spi.h"
#include "wizchip_conf.h"
#include "socket.h"
#include "inttypes.h"
#include "Internet/MQTT/MQTTClient.h"
#include "Internet/DNS/dns.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint8_t rx_data;

wiz_NetInfo gWIZNETINFO  = {
    .mac = {0x00,0x08,0xdc,0x78,0x91,0x71},
    .ip = {192,168,0,15},
    .sn = {255, 255, 255, 0},
    .gw = {192, 168, 0, 1},
    .dns = {168, 126, 63, 1},
    .dhcp = NETINFO_STATIC
};

#define ETH_MAX_BUF_SIZE  2048
#define PUBLISH_MYSELF 1

unsigned char ethBuf0[ETH_MAX_BUF_SIZE];
unsigned char ethBuf1[ETH_MAX_BUF_SIZE];
unsigned char ethBuf2[ETH_MAX_BUF_SIZE];
unsigned char ethBuf3[ETH_MAX_BUF_SIZE];

uint8_t bLoopback = 1;
uint8_t bRandomPacket = 0;
uint8_t bAnyPacket = 0;
uint16_t pack_size = 0;

const uint8_t URL[] = "test.mosquitto.org";
uint8_t dns_server_ip[4] = {168,126,63,1};
uint8_t dnsclient_ip[4] = {0,};
unsigned int targetPort = 1883; // mqtt server port
unsigned char targetIP[4] = {0x00, 0x00, 0x00, 0x00}; // mqtt server IP

uint8_t IP_TYPE;

const uint8_t MQTT_TOPIC[]="W5x00";
unsigned char tempBuffer[1024*2] = {};

void print_network_information(void);
void delay(unsigned int count);
void MQTT_run(void);
void messageArrived(MessageData* md);


struct opts_struct
{
  char* clientid;
  int nodelimiter;
  char* delimiter;
  enum QoS qos;
  char* username;
  char* password;
  char* host;
  int port;
  int showtopics;
} opts ={ (char*)"stdout-subscriber", 0, (char*)"\n", QOS0, NULL, NULL, targetIP, 1883, 0 };
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
int __io_putchar(int ch)
{
	 (void) HAL_UART_Transmit(&huart2, (uint8_t*) &ch, 1, 100);
	 return ch;
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_SPI2_Init();

  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart2, &rx_data, 1);

  printf("System start.\r\n");
  w5500Init();
  wizchip_setnetinfo(&gWIZNETINFO);
  print_network_information();
  DNS_init(0,ethBuf0);
  IP_TYPE = 0x1c;
  while (DNS_run(dns_server_ip, URL, dnsclient_ip) != 1);
  MQTT_run();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
	  HAL_Delay(500);
	  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
	  HAL_Delay(500);

	  //printf("test code\r\n");
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART2) {
		printf("Key Pressed: %c\r\n", rx_data);
		if(rx_data == 'a')
		{
			printf("ok\r\n");
		}
		HAL_UART_Receive_IT(&huart2, &rx_data, 1);
	}
}

void MQTT_run(void){

  int rc = 0;
  uint8_t buf[100];
  uint8_t pubbuf[100];
  Network n;
  MQTTClient c;
  MQTTMessage m;
  uint32_t ck_timer;

  NewNetwork(&n, 0);
  ConnectNetwork(&n, dnsclient_ip, targetPort);
  MQTTClientInit(&c, &n, 1000, buf, sizeof(buf), tempBuffer, sizeof(tempBuffer));

  MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
  data.willFlag = 0;
  data.MQTTVersion = 3;
  data.clientID.cstring = opts.clientid;
  data.username.cstring = opts.username;
  data.password.cstring = opts.password;

  data.keepAliveInterval = 60;
  data.cleansession = 1;

  rc = MQTTConnect(&c, &data);
  printf("Connected %d\r\n", rc);
  opts.showtopics = 1;

  printf("Subscribing to %s\r\n", MQTT_TOPIC);
  rc = MQTTSubscribe(&c, MQTT_TOPIC, opts.qos, messageArrived);
  printf("Subscribed %d\r\n", rc);

#if PUBLISH_MYSELF == 1
  m.qos = QOS0;
  m.retained = 0;
  m.dup = 0;

  //ck_timer = TIM2_gettimer();
#endif

  while(1)
  {
    MQTTYield(&c, data.keepAliveInterval);


#if PUBLISH_MYSELF == 1
    //if(ck_timer + 10000 < TIM2_gettimer())
    {
      //ck_timer = TIM2_gettimer();

      //printf("Publishing to %s\r\n", MQTT_TOPIC);

      sprintf(pubbuf, "Hello, W5x00!" );
      m.payload = pubbuf;
      m.payloadlen = strlen(pubbuf);

      rc = MQTTPublish(&c, MQTT_TOPIC, &m);
      printf("Published %d\r\n", rc);
    }
#endif
  }
}

void print_network_information(void)
{
  memset(&gWIZNETINFO,0,sizeof(gWIZNETINFO));

  wizchip_getnetinfo(&gWIZNETINFO);
  printf("MAC Address : %02x:%02x:%02x:%02x:%02x:%02x\n\r",gWIZNETINFO.mac[0],gWIZNETINFO.mac[1],gWIZNETINFO.mac[2],gWIZNETINFO.mac[3],gWIZNETINFO.mac[4],gWIZNETINFO.mac[5]);
  printf("IP  Address : %d.%d.%d.%d\n\r",gWIZNETINFO.ip[0],gWIZNETINFO.ip[1],gWIZNETINFO.ip[2],gWIZNETINFO.ip[3]);
  printf("Subnet Mask : %d.%d.%d.%d\n\r",gWIZNETINFO.sn[0],gWIZNETINFO.sn[1],gWIZNETINFO.sn[2],gWIZNETINFO.sn[3]);
  printf("Gateway     : %d.%d.%d.%d\n\r",gWIZNETINFO.gw[0],gWIZNETINFO.gw[1],gWIZNETINFO.gw[2],gWIZNETINFO.gw[3]);
  printf("DNS Server  : %d.%d.%d.%d\n\r",gWIZNETINFO.dns[0],gWIZNETINFO.dns[1],gWIZNETINFO.dns[2],gWIZNETINFO.dns[3]);
}

// @brief messageArrived callback function
void messageArrived(MessageData* md)
{
  unsigned char testbuffer[100];
  uint32_t rd_size;
  uint32_t rd_pt;
  uint32_t rdmore_size;

  MQTTMessage* message = md->message;
  MQTTString* topic = md->topicName;

  rdmore_size = (int)topic->lenstring.len;
  rd_pt = 0;

  while(rdmore_size != 0)
  {
    if(rdmore_size > sizeof(testbuffer) - 1)
    {
      rd_size = sizeof(testbuffer) - 1;
    }
    else
    {
      rd_size = rdmore_size;
    }

    memset(testbuffer, 0, rd_size + 1);

    memcpy(testbuffer, ((char*)topic->lenstring.data) + rd_pt, rd_size);
    printf("SubScribe Topic : %s\r\n", testbuffer);

    rd_pt += rd_size;
    rdmore_size -= rd_size;
  }

  if (opts.nodelimiter)
  {
    printf("Message : %.*s\r\n", (int)message->payloadlen, (char*)message->payload);
  }
  else
  {
    printf("Message : %.*s%s\r\n", (int)message->payloadlen, (char*)message->payload, opts.delimiter);
  }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
