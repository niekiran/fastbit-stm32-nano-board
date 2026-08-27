################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/drivers/ui/ui_watch.c 

OBJS += \
./Core/drivers/ui/ui_watch.o 

C_DEPS += \
./Core/drivers/ui/ui_watch.d 


# Each subdirectory must supply rules for building sources it contributes
Core/drivers/ui/%.o Core/drivers/ui/%.su Core/drivers/ui/%.cyclo: ../Core/drivers/ui/%.c Core/drivers/ui/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/bhara/STM32CubeIDE/fastbit-stm32-nano-board/Examples/020_Bouncy_Ball/Core/drivers/display" -I"C:/Users/bhara/STM32CubeIDE/fastbit-stm32-nano-board/Examples/020_Bouncy_Ball/Core/drivers/imu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-drivers-2f-ui

clean-Core-2f-drivers-2f-ui:
	-$(RM) ./Core/drivers/ui/ui_watch.cyclo ./Core/drivers/ui/ui_watch.d ./Core/drivers/ui/ui_watch.o ./Core/drivers/ui/ui_watch.su

.PHONY: clean-Core-2f-drivers-2f-ui

