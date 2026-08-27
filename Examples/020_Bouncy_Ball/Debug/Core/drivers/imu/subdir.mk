################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/drivers/imu/mpu6050.c 

OBJS += \
./Core/drivers/imu/mpu6050.o 

C_DEPS += \
./Core/drivers/imu/mpu6050.d 


# Each subdirectory must supply rules for building sources it contributes
Core/drivers/imu/%.o Core/drivers/imu/%.su Core/drivers/imu/%.cyclo: ../Core/drivers/imu/%.c Core/drivers/imu/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/bhara/STM32CubeIDE/fastbit-stm32-nano-board/Examples/020_Bouncy_Ball/Core/drivers/display" -I"C:/Users/bhara/STM32CubeIDE/fastbit-stm32-nano-board/Examples/020_Bouncy_Ball/Core/drivers/game" -I"C:/Users/bhara/STM32CubeIDE/fastbit-stm32-nano-board/Examples/020_Bouncy_Ball/Core/drivers/gfx" -I"C:/Users/bhara/STM32CubeIDE/fastbit-stm32-nano-board/Examples/020_Bouncy_Ball/Core/drivers/imu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-drivers-2f-imu

clean-Core-2f-drivers-2f-imu:
	-$(RM) ./Core/drivers/imu/mpu6050.cyclo ./Core/drivers/imu/mpu6050.d ./Core/drivers/imu/mpu6050.o ./Core/drivers/imu/mpu6050.su

.PHONY: clean-Core-2f-drivers-2f-imu

