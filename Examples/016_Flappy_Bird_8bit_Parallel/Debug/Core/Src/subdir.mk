################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/CST816S.c \
../Core/Src/GC9A01A.c \
../Core/Src/background.c \
../Core/Src/font.c \
../Core/Src/main.c \
../Core/Src/mpu6050.c \
../Core/Src/obstacle.c \
../Core/Src/player.c \
../Core/Src/stm32f3xx_hal_msp.c \
../Core/Src/stm32f3xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f3xx.c \
../Core/Src/text_mssg.c 

OBJS += \
./Core/Src/CST816S.o \
./Core/Src/GC9A01A.o \
./Core/Src/background.o \
./Core/Src/font.o \
./Core/Src/main.o \
./Core/Src/mpu6050.o \
./Core/Src/obstacle.o \
./Core/Src/player.o \
./Core/Src/stm32f3xx_hal_msp.o \
./Core/Src/stm32f3xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f3xx.o \
./Core/Src/text_mssg.o 

C_DEPS += \
./Core/Src/CST816S.d \
./Core/Src/GC9A01A.d \
./Core/Src/background.d \
./Core/Src/font.d \
./Core/Src/main.d \
./Core/Src/mpu6050.d \
./Core/Src/obstacle.d \
./Core/Src/player.d \
./Core/Src/stm32f3xx_hal_msp.d \
./Core/Src/stm32f3xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f3xx.d \
./Core/Src/text_mssg.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/CST816S.cyclo ./Core/Src/CST816S.d ./Core/Src/CST816S.o ./Core/Src/CST816S.su ./Core/Src/GC9A01A.cyclo ./Core/Src/GC9A01A.d ./Core/Src/GC9A01A.o ./Core/Src/GC9A01A.su ./Core/Src/background.cyclo ./Core/Src/background.d ./Core/Src/background.o ./Core/Src/background.su ./Core/Src/font.cyclo ./Core/Src/font.d ./Core/Src/font.o ./Core/Src/font.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/mpu6050.cyclo ./Core/Src/mpu6050.d ./Core/Src/mpu6050.o ./Core/Src/mpu6050.su ./Core/Src/obstacle.cyclo ./Core/Src/obstacle.d ./Core/Src/obstacle.o ./Core/Src/obstacle.su ./Core/Src/player.cyclo ./Core/Src/player.d ./Core/Src/player.o ./Core/Src/player.su ./Core/Src/stm32f3xx_hal_msp.cyclo ./Core/Src/stm32f3xx_hal_msp.d ./Core/Src/stm32f3xx_hal_msp.o ./Core/Src/stm32f3xx_hal_msp.su ./Core/Src/stm32f3xx_it.cyclo ./Core/Src/stm32f3xx_it.d ./Core/Src/stm32f3xx_it.o ./Core/Src/stm32f3xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f3xx.cyclo ./Core/Src/system_stm32f3xx.d ./Core/Src/system_stm32f3xx.o ./Core/Src/system_stm32f3xx.su ./Core/Src/text_mssg.cyclo ./Core/Src/text_mssg.d ./Core/Src/text_mssg.o ./Core/Src/text_mssg.su

.PHONY: clean-Core-2f-Src

