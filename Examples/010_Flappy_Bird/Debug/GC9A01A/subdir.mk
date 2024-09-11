################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GC9A01A/GC9A01A.c \
../GC9A01A/font.c 

OBJS += \
./GC9A01A/GC9A01A.o \
./GC9A01A/font.o 

C_DEPS += \
./GC9A01A/GC9A01A.d \
./GC9A01A/font.d 


# Each subdirectory must supply rules for building sources it contributes
GC9A01A/%.o GC9A01A/%.su GC9A01A/%.cyclo: ../GC9A01A/%.c GC9A01A/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/shrey/STM32CubeIDE/nano-board-lcd-sw/Examples/010_Flappy_Bird/Core/Inc" -I"C:/Users/shrey/STM32CubeIDE/nano-board-lcd-sw/Examples/010_Flappy_Bird/GC9A01A" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-GC9A01A

clean-GC9A01A:
	-$(RM) ./GC9A01A/GC9A01A.cyclo ./GC9A01A/GC9A01A.d ./GC9A01A/GC9A01A.o ./GC9A01A/GC9A01A.su ./GC9A01A/font.cyclo ./GC9A01A/font.d ./GC9A01A/font.o ./GC9A01A/font.su

.PHONY: clean-GC9A01A

