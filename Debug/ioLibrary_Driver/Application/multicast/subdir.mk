################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ioLibrary_Driver/Application/multicast/multicast.c 

OBJS += \
./ioLibrary_Driver/Application/multicast/multicast.o 

C_DEPS += \
./ioLibrary_Driver/Application/multicast/multicast.d 


# Each subdirectory must supply rules for building sources it contributes
ioLibrary_Driver/Application/multicast/%.o ioLibrary_Driver/Application/multicast/%.su ioLibrary_Driver/Application/multicast/%.cyclo: ../ioLibrary_Driver/Application/multicast/%.c ioLibrary_Driver/Application/multicast/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../ioLibrary_Driver -I"../ioLibrary_Driver/Application/loopback" -I"../ioLibrary_Driver/Application/multicast" -I"../ioLibrary_Driver/Ethernet" -I../ioLibrary_Driver/Internet/httpServer -I../ioLibrary_Driver/Internet/MQTT -I"../ioLibrary_Driver/Internet" -I"D:/stm/Firmware/Drivers/wiznet" -O0 -ffunction-sections -fdata-sections -Wall -fcommon -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-ioLibrary_Driver-2f-Application-2f-multicast

clean-ioLibrary_Driver-2f-Application-2f-multicast:
	-$(RM) ./ioLibrary_Driver/Application/multicast/multicast.cyclo ./ioLibrary_Driver/Application/multicast/multicast.d ./ioLibrary_Driver/Application/multicast/multicast.o ./ioLibrary_Driver/Application/multicast/multicast.su

.PHONY: clean-ioLibrary_Driver-2f-Application-2f-multicast

