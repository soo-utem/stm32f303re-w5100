/*
 * w5500_spi.c
 *
 *  Created on: Oct 11, 2024
 *      Author: sooyewguan
 */


// PB1 SCS
// PB2 RST
#include "stm32f3xx_hal.h"
#include "wizchip_conf.h"
#include "stdio.h"

extern SPI_HandleTypeDef hspi1;

uint8_t SPIReadWrite(uint8_t data)
{
	while((hspi1.Instance->SR & SPI_FLAG_TXE) != SPI_FLAG_TXE);

	*(__IO uint8_t*)&hspi1.Instance->DR = data;

	while((hspi1.Instance->SR & SPI_FLAG_RXNE) != SPI_FLAG_RXNE);

	return (*(__IO uint8_t*)&hspi1.Instance->DR);
}

void wizchip_select() {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
}

void wizchip_deselect() {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
}

uint8_t wizchip_read() {
//	uint8_t rb;
//	rb = SPIReadWrite(0x00);
//	return rb;
	uint8_t rbuf;
	HAL_SPI_Receive(&hspi1, &rbuf, 1, 0xFFFFFFFF);
	return rbuf;
}

void wizchip_write(uint8_t wb) {
//	SPIReadWrite(wb);
	HAL_SPI_Transmit(&hspi1, &wb, 1, 0xFFFFFFFF);
}

void wizchip_readburst(uint8_t* pBuf, uint16_t len) {
	for(uint16_t i = 0; i < len; i++) {
//		*pBuf = SPIReadWrite(0x00);
		*pBuf = wizchip_read();
		pBuf++;
	}
}

void wizchip_writeburst(uint8_t* pBuf, uint16_t len) {
	for(uint16_t i = 0; i < len; i++) {
//		SPIReadWrite(*pBuf);
		wizchip_write(*pBuf);
		pBuf++;
	}
}

void W5500IOInit() {
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void W5500Init() {
//	uint8_t tmp = 0xFF;
//	uint8_t memSize[2][8] = {{ 2,2,2,2,2,2,2,2}, {2,2,2,2,2,2,2,2}};
//	uint8_t memSize[] = {2,2,2,2};

	intr_kind temp = IK_DEST_UNREACH;
	int8_t phy_link =0;
	uint8_t W5x00_AdrSet[2][8] = {{2,2,2,2,2,2,2,2},{2,2,2,2,2,2,2,2}};

//	W5500IOInit();

//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);

//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);


//	while(tmp--);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);

	reg_wizchip_cs_cbfunc(wizchip_select, wizchip_deselect);
	reg_wizchip_spi_cbfunc(wizchip_read, wizchip_write);
	reg_wizchip_spiburst_cbfunc(wizchip_readburst, wizchip_writeburst);

	printf("WIZCHIP Initiated start!. \r\n");

//	if(ctlwizchip(CW_INIT_WIZCHIP, (void*) memSize) == -1) {
//		printf("WIZCHIP Initiated failed!. \r\n");
//		while(1);
//	}

	if(ctlwizchip(CW_INIT_WIZCHIP,(void*)W5x00_AdrSet) == -1)
	{
		printf("W5x00 initialized fail.\r\n");
	}

	if(ctlwizchip(CW_SET_INTRMASK,&temp) == -1)
	{
		printf("W5x00 interrupt\r\n");
	}

//	wizchip_init(memSize, memSize);
	wiz_NetInfo gWIZNETINFO = { .mac = {0x00, 0x08, 0xdc, 0xab, 0xcd, 0xef},
	.ip = {192, 168, 68, 197},
	.sn = {255, 255, 255, 0},
	.gw = {192, 168, 68, 1}};
//
	wizchip_setnetinfo(&gWIZNETINFO);

	do {//check phy status.
		if(ctlwizchip(CW_GET_PHYLINK,&phy_link) == -1){
			printf("Unknown PHY link status.\r\n");
			HAL_Delay(10);
		}

	} while(phy_link == PHY_LINK_OFF);

	printf("WIZCHIP Initiated successfully!. \r\n");

	wizchip_getnetinfo(&gWIZNETINFO);
	printf("MAC Address : %02x:%02x:%02x:%02x:%02x:%02x\n\r",gWIZNETINFO.mac[0],gWIZNETINFO.mac[1],gWIZNETINFO.mac[2],gWIZNETINFO.mac[3],gWIZNETINFO.mac[4],gWIZNETINFO.mac[5]);
	printf("IP  Address : %d.%d.%d.%d\n\r",gWIZNETINFO.ip[0],gWIZNETINFO.ip[1],gWIZNETINFO.ip[2],gWIZNETINFO.ip[3]);
	printf("Subnet Mask : %d.%d.%d.%d\n\r",gWIZNETINFO.sn[0],gWIZNETINFO.sn[1],gWIZNETINFO.sn[2],gWIZNETINFO.sn[3]);
	printf("Gateway     : %d.%d.%d.%d\n\r",gWIZNETINFO.gw[0],gWIZNETINFO.gw[1],gWIZNETINFO.gw[2],gWIZNETINFO.gw[3]);
	printf("DNS Server  : %d.%d.%d.%d\n\r",gWIZNETINFO.dns[0],gWIZNETINFO.dns[1],gWIZNETINFO.dns[2],gWIZNETINFO.dns[3]);

//	DHCP_init(0, ethBuf0);

//	while(1){
//		if(process_dhcp() == DHCP_IP_LEASED){
//			printf("DHCP Success\r\n");
//			break;
//		}
//		else
//			printf("Try.....\r\n");
//	}

}

//int process_dhcp(void){
//	int8_t ret =0;
//	while(1){
//		ret = DHCP_run();
//		if(ret == DHCP_IP_LEASED)
//		{
//			#ifdef _MAIN_DEBUG_
//				printf(" - DHCP Success\r\n");
//			#endif
//				printf("=============================\r\n");
//				print_network_information();
//				printf("=============================\r\n");
//				break;
//		}
//		else if(ret == DHCP_FAILED)
//		{
//			dhcp_retry++;
//			#ifdef _MAIN_DEBUG_
//				if(dhcp_retry <= 3) printf(" - DHCP Timeout occurred and retry [%d]\r\n", dhcp_retry);
//			#endif
//		}
//
//
//		if(dhcp_retry > 3)
//		{
//			#ifdef _MAIN_DEBUG_
//				printf(" - DHCP Failed\r\n\r\n");
//			#endif
//			DHCP_stop();
//			break;
//		}
//	}
//	return ret;
//}

//void print_network_information(void)
//{
//	memset(&gWIZNETINFO,0,sizeof(gWIZNETINFO));
//
//	wizchip_getnetinfo(&gWIZNETINFO);
//	printf("MAC Address : %02x:%02x:%02x:%02x:%02x:%02x\n\r",gWIZNETINFO.mac[0],gWIZNETINFO.mac[1],gWIZNETINFO.mac[2],gWIZNETINFO.mac[3],gWIZNETINFO.mac[4],gWIZNETINFO.mac[5]);
//	printf("IP  Address : %d.%d.%d.%d\n\r",gWIZNETINFO.ip[0],gWIZNETINFO.ip[1],gWIZNETINFO.ip[2],gWIZNETINFO.ip[3]);
//	printf("Subnet Mask : %d.%d.%d.%d\n\r",gWIZNETINFO.sn[0],gWIZNETINFO.sn[1],gWIZNETINFO.sn[2],gWIZNETINFO.sn[3]);
//	printf("Gateway     : %d.%d.%d.%d\n\r",gWIZNETINFO.gw[0],gWIZNETINFO.gw[1],gWIZNETINFO.gw[2],gWIZNETINFO.gw[3]);
//	printf("DNS Server  : %d.%d.%d.%d\n\r",gWIZNETINFO.dns[0],gWIZNETINFO.dns[1],gWIZNETINFO.dns[2],gWIZNETINFO.dns[3]);
//}
