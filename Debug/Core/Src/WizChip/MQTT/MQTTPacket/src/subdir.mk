################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTConnectClient.c \
../Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTConnectServer.c \
../Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTDeserializePublish.c \
../Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTFormat.c \
../Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTPacket.c \
../Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTSerializePublish.c \
../Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTSubscribeClient.c \
../Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTSubscribeServer.c \
../Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.c \
../Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.c 

OBJS += \
./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTConnectClient.o \
./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTConnectServer.o \
./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTDeserializePublish.o \
./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTFormat.o \
./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTPacket.o \
./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTSerializePublish.o \
./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTSubscribeClient.o \
./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTSubscribeServer.o \
./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.o \
./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.o 

C_DEPS += \
./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTConnectClient.d \
./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTConnectServer.d \
./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTDeserializePublish.d \
./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTFormat.d \
./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTPacket.d \
./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTSerializePublish.d \
./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTSubscribeClient.d \
./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTSubscribeServer.d \
./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.d \
./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/WizChip/MQTT/MQTTPacket/src/%.o Core/Src/WizChip/MQTT/MQTTPacket/src/%.su Core/Src/WizChip/MQTT/MQTTPacket/src/%.cyclo: ../Core/Src/WizChip/MQTT/MQTTPacket/src/%.c Core/Src/WizChip/MQTT/MQTTPacket/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xE -c -I"/Users/sooyewguan/STM32CubeIDE/workspace_1.16.1/w5500-f303re/Core/Src/WizChip" -I"/Users/sooyewguan/STM32CubeIDE/workspace_1.16.1/w5500-f303re/Core/Src/WizChip/W5100" -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I"/Users/sooyewguan/STM32CubeIDE/workspace_1.16.1/w5500-f303re/Core/Src/WizChip/MQTT" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-WizChip-2f-MQTT-2f-MQTTPacket-2f-src

clean-Core-2f-Src-2f-WizChip-2f-MQTT-2f-MQTTPacket-2f-src:
	-$(RM) ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTConnectClient.cyclo ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTConnectClient.d ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTConnectClient.o ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTConnectClient.su ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTConnectServer.cyclo ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTConnectServer.d ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTConnectServer.o ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTConnectServer.su ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTDeserializePublish.cyclo ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTDeserializePublish.d ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTDeserializePublish.o ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTDeserializePublish.su ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTFormat.cyclo ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTFormat.d ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTFormat.o ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTFormat.su ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTPacket.cyclo ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTPacket.d ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTPacket.o ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTPacket.su ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTSerializePublish.cyclo ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTSerializePublish.d ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTSerializePublish.o ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTSerializePublish.su ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTSubscribeClient.cyclo ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTSubscribeClient.d ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTSubscribeClient.o ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTSubscribeClient.su ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTSubscribeServer.cyclo ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTSubscribeServer.d ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTSubscribeServer.o ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTSubscribeServer.su ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.cyclo ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.d ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.o ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.su ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.cyclo ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.d ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.o ./Core/Src/WizChip/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.su

.PHONY: clean-Core-2f-Src-2f-WizChip-2f-MQTT-2f-MQTTPacket-2f-src

