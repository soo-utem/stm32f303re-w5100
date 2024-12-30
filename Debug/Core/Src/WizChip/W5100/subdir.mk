################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/WizChip/W5100/w5100.c 

OBJS += \
./Core/Src/WizChip/W5100/w5100.o 

C_DEPS += \
./Core/Src/WizChip/W5100/w5100.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/WizChip/W5100/%.o Core/Src/WizChip/W5100/%.su Core/Src/WizChip/W5100/%.cyclo: ../Core/Src/WizChip/W5100/%.c Core/Src/WizChip/W5100/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xE -c -I"/Users/sooyewguan/STM32CubeIDE/workspace_1.16.1/w5500-f303re/Core/Src/WizChip" -I"/Users/sooyewguan/STM32CubeIDE/workspace_1.16.1/w5500-f303re/Core/Src/WizChip/W5100" -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I"/Users/sooyewguan/STM32CubeIDE/workspace_1.16.1/w5500-f303re/Core/Src/WizChip/MQTT" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-WizChip-2f-W5100

clean-Core-2f-Src-2f-WizChip-2f-W5100:
	-$(RM) ./Core/Src/WizChip/W5100/w5100.cyclo ./Core/Src/WizChip/W5100/w5100.d ./Core/Src/WizChip/W5100/w5100.o ./Core/Src/WizChip/W5100/w5100.su

.PHONY: clean-Core-2f-Src-2f-WizChip-2f-W5100

