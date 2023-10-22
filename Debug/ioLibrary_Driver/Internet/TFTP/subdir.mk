################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ioLibrary_Driver/Internet/TFTP/netutil.c \
../ioLibrary_Driver/Internet/TFTP/tftp.c 

OBJS += \
./ioLibrary_Driver/Internet/TFTP/netutil.o \
./ioLibrary_Driver/Internet/TFTP/tftp.o 

C_DEPS += \
./ioLibrary_Driver/Internet/TFTP/netutil.d \
./ioLibrary_Driver/Internet/TFTP/tftp.d 


# Each subdirectory must supply rules for building sources it contributes
ioLibrary_Driver/Internet/TFTP/%.o ioLibrary_Driver/Internet/TFTP/%.su ioLibrary_Driver/Internet/TFTP/%.cyclo: ../ioLibrary_Driver/Internet/TFTP/%.c ioLibrary_Driver/Internet/TFTP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../ioLibrary_Driver -I"../ioLibrary_Driver/Application/loopback" -I"../ioLibrary_Driver/Application/multicast" -I"../ioLibrary_Driver/Ethernet" -I../ioLibrary_Driver/Internet/httpServer -I../ioLibrary_Driver/Internet/MQTT -I"../ioLibrary_Driver/Internet" -I"D:/stm/Firmware/Drivers/wiznet" -O0 -ffunction-sections -fdata-sections -Wall -fcommon -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-ioLibrary_Driver-2f-Internet-2f-TFTP

clean-ioLibrary_Driver-2f-Internet-2f-TFTP:
	-$(RM) ./ioLibrary_Driver/Internet/TFTP/netutil.cyclo ./ioLibrary_Driver/Internet/TFTP/netutil.d ./ioLibrary_Driver/Internet/TFTP/netutil.o ./ioLibrary_Driver/Internet/TFTP/netutil.su ./ioLibrary_Driver/Internet/TFTP/tftp.cyclo ./ioLibrary_Driver/Internet/TFTP/tftp.d ./ioLibrary_Driver/Internet/TFTP/tftp.o ./ioLibrary_Driver/Internet/TFTP/tftp.su

.PHONY: clean-ioLibrary_Driver-2f-Internet-2f-TFTP

