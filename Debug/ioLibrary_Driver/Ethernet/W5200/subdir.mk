################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ioLibrary_Driver/Ethernet/W5200/w5200.c 

OBJS += \
./ioLibrary_Driver/Ethernet/W5200/w5200.o 

C_DEPS += \
./ioLibrary_Driver/Ethernet/W5200/w5200.d 


# Each subdirectory must supply rules for building sources it contributes
ioLibrary_Driver/Ethernet/W5200/%.o ioLibrary_Driver/Ethernet/W5200/%.su ioLibrary_Driver/Ethernet/W5200/%.cyclo: ../ioLibrary_Driver/Ethernet/W5200/%.c ioLibrary_Driver/Ethernet/W5200/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../ioLibrary_Driver -I"../ioLibrary_Driver/Application/loopback" -I"../ioLibrary_Driver/Application/multicast" -I"../ioLibrary_Driver/Ethernet" -I../ioLibrary_Driver/Internet/httpServer -I../ioLibrary_Driver/Internet/MQTT -I"../ioLibrary_Driver/Internet" -I"D:/stm/Firmware/Drivers/wiznet" -O0 -ffunction-sections -fdata-sections -Wall -fcommon -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-ioLibrary_Driver-2f-Ethernet-2f-W5200

clean-ioLibrary_Driver-2f-Ethernet-2f-W5200:
	-$(RM) ./ioLibrary_Driver/Ethernet/W5200/w5200.cyclo ./ioLibrary_Driver/Ethernet/W5200/w5200.d ./ioLibrary_Driver/Ethernet/W5200/w5200.o ./ioLibrary_Driver/Ethernet/W5200/w5200.su

.PHONY: clean-ioLibrary_Driver-2f-Ethernet-2f-W5200

