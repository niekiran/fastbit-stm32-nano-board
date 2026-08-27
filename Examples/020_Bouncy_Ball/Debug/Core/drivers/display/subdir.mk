################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/drivers/display/gc9a01a.c 

OBJS += \
./Core/drivers/display/gc9a01a.o 

C_DEPS += \
./Core/drivers/display/gc9a01a.d 


# Each subdirectory must supply rules for building sources it contributes
Core/drivers/display/%.o Core/drivers/display/%.su Core/drivers/display/%.cyclo: ../Core/drivers/display/%.c Core/drivers/display/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/bhara/STM32CubeIDE/fastbit-stm32-nano-board/Examples/020_Bouncy_Ball/Core/drivers/display" -I"C:/Users/bhara/STM32CubeIDE/fastbit-stm32-nano-board/Examples/020_Bouncy_Ball/Core/drivers/game" -I"C:/Users/bhara/STM32CubeIDE/fastbit-stm32-nano-board/Examples/020_Bouncy_Ball/Core/drivers/gfx" -I"C:/Users/bhara/STM32CubeIDE/fastbit-stm32-nano-board/Examples/020_Bouncy_Ball/Core/drivers/imu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-drivers-2f-display

clean-Core-2f-drivers-2f-display:
	-$(RM) ./Core/drivers/display/gc9a01a.cyclo ./Core/drivers/display/gc9a01a.d ./Core/drivers/display/gc9a01a.o ./Core/drivers/display/gc9a01a.su

.PHONY: clean-Core-2f-drivers-2f-display

