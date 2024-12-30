/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

//#include "w5100_spi.h"
#include "wizchip_conf.h"
#include "socket.h"

//MQTT Related
#include "MQTTClient.h"
#include "mqtt_interface.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
int _write(int file, char *ptr, int len)
{
  /* Implement your write code here. This is
     used by puts and printf for example */
  for(int i = 0; i < len; i++)
    ITM_SendChar((*ptr++));

  return len;
}
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi2;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint8_t destination_ip[]={159,65,134,213};
uint16_t destination_port = 1883;

MQTTClient mqtt_client;
Network network;
MQTTPacket_connectData connect_data = MQTTPacket_connectData_initializer;

uint8_t sendbuff[256],receivebuff[256];

char* favoriotClientId = "";
char* favoriotUsername = "";
char* favoriotPassword = "";

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_SPI2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void cs_sel() {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET); //CS LOW
}

void cs_desel() {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET); //CS HIGH
}

uint8_t spi_rb(void) {
	uint8_t rbuf;
	HAL_SPI_Receive(&hspi2, &rbuf, 1, 0xFFFFFFFF);
	return rbuf;
}

void spi_wb(uint8_t b) {
	HAL_SPI_Transmit(&hspi2, &b, 1, 0xFFFFFFFF);
}

void OnMessageReceived(MessageData* md)
{
	char topic[(int)md->topicName->lenstring.len + 1];
	char payload[(int)md->message->payloadlen + 1];

//	MQTTString* topic = md->topicName;
//	MQTTMessage* message = md->message;

//	strncpy(topic, (char*)md->topicName->lenstring.data, (int)md->topicName->lenstring.len);
//	topic[(int)md->topicName->lenstring.len] = '\0';

//	strncpy(payload, (char*)md->message->payload, (int)md->message->payloadlen);
//	payload[(int)md->message->payloadlen] = '\0';

	strncpy(topic, (char*)md->topicName->lenstring.data, (int)md->topicName->lenstring.len);
	strncpy(payload, (char*)md->message->payload, (int)md->message->payloadlen);

	printf("topic\r\n%s\r\n", topic);
	printf("payload\r\n%s\r\n", payload);

}

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
//  W5500Init();
  uint8_t retVal, sockStatus;
  int16_t rcvLen;
  uint8_t rcvBuf[20], bufSize[] = {2, 2, 2, 2};

  reg_wizchip_cs_cbfunc(cs_sel, cs_desel);
  reg_wizchip_spi_cbfunc(spi_rb, spi_wb);

  wizchip_init(bufSize, bufSize);
  wiz_NetInfo netInfo = { .mac 	= {0x00, 0x08, 0xdc, 0xab, 0xcd, 0xef},	// Mac address
                          .ip 	= {192, 168, 31, 210},					// IP address
                          .sn 	= {255, 255, 255, 0},					// Subnet mask
                          .gw 	= {192, 168, 31, 1}};					// Gateway address

  wizchip_setnetinfo(&netInfo);
  HAL_Delay(1000);

  wizchip_getnetinfo(&netInfo);

  printf("MAC Address : %02x:%02x:%02x:%02x:%02x:%02x\n\r",netInfo.mac[0],netInfo.mac[1],netInfo.mac[2],netInfo.mac[3],netInfo.mac[4],netInfo.mac[5]);
  printf("IP  Address : %d.%d.%d.%d\n\r",netInfo.ip[0],netInfo.ip[1],netInfo.ip[2],netInfo.ip[3]);
  printf("Subnet Mask : %d.%d.%d.%d\n\r",netInfo.sn[0],netInfo.sn[1],netInfo.sn[2],netInfo.sn[3]);
  printf("Gateway     : %d.%d.%d.%d\n\r",netInfo.gw[0],netInfo.gw[1],netInfo.gw[2],netInfo.gw[3]);
  printf("DNS Server  : %d.%d.%d.%d\n\r",netInfo.dns[0],netInfo.dns[1],netInfo.dns[2],netInfo.dns[3]);

  connect_data.willFlag = 0;
  connect_data.MQTTVersion = 3;
  connect_data.clientID.cstring = favoriotClientId;
  connect_data.keepAliveInterval = 30;//seconds
  connect_data.cleansession = 1;
  connect_data.username.cstring = favoriotUsername;
  connect_data.password.cstring = favoriotPassword;

  NewNetwork(&network, 1);//1 is the socket number to use

  printf("Connecting to MQTT Broker ...");
  if(ConnectNetwork(&network, destination_ip, destination_port)!=SOCK_OK)
  {
	  printf("ERROR: Cannot connect with broker!\r\n");
	  //Broker (server) not reachable
	  while(1);
  }
  printf("MQTT Broker Connected\r\n");

  MQTTClientInit(&mqtt_client, &network, 200, sendbuff, 200, receivebuff, 2048);

  printf("Sending connect packet ...");

  if(MQTTConnect(&mqtt_client, &connect_data) != SUCCESS)
  {
	  printf("ERROR: Cannot send connect packet!\r\n");
//	  while(1);
  }

  printf("Connect packet sent successfully\r\n");


  //Subscribe to temperature sensor

  char mqttTopic[255];
  sprintf(mqttTopic, "%s/v2/streams/status", favoriotUsername);


  MQTTSubscribe(&mqtt_client, mqttTopic, QOS0, OnMessageReceived);
  printf(strcat("Subscribed to", mqttTopic));
  printf("\r\n\r\n");

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	 MQTTYield(&mqtt_client, 300);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

//	const char *data = ;
    char data[255];
    sprintf(data, "{\"device_developer_id\":\"iot_1_device@sooyewguan\",\"data\":{\"humidity\":\"%d\"}}\r\n", (rand() % 100));

	MQTTMessage msg;
	msg.payload = (void*)data;     // Set payload to the message string
	msg.payloadlen = strlen(data); // Set payload length
	printf("Sending payload %s", data);

//	MQTTMessage msg={ QOS0, 0, 0, 1, "{\"device_developer_id\":\"iot_1_device@sooyewguan\",\"data\":{\"humidity\":\"10\"}}",74};

	char mqttTopic[255];
	sprintf(mqttTopic, "%s/v2/streams", favoriotUsername);

	MQTTPublish(&mqtt_client, mqttTopic, &msg);
	HAL_Delay(5000);

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 7;
  hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 38400;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
