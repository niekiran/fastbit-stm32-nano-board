################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/drivers/game/app.c \
../Core/drivers/game/ball_img.c \
../Core/drivers/game/game.c \
../Core/drivers/game/player.c \
../Core/drivers/game/world.c 

OBJS += \
./Core/drivers/game/app.o \
./Core/drivers/game/ball_img.o \
./Core/drivers/game/game.o \
./Core/drivers/game/player.o \
./Core/drivers/game/world.o 

C_DEPS += \
./Core/drivers/game/app.d \
./Core/drivers/game/ball_img.d \
./Core/drivers/game/game.d \
./Core/drivers/game/player.d \
./Core/drivers/game/world.d 


# Each subdirectory must supply rules for building sources it contributes
Core/drivers/game/%.o Core/drivers/game/%.su Core/drivers/game/%.cyclo: ../Core/drivers/game/%.c Core/drivers/game/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/bhara/STM32CubeIDE/fastbit-stm32-nano-board/Examples/020_Bouncy_Ball/Core/drivers/display" -I"C:/Users/bhara/STM32CubeIDE/fastbit-stm32-nano-board/Examples/020_Bouncy_Ball/Core/drivers/game" -I"C:/Users/bhara/STM32CubeIDE/fastbit-stm32-nano-board/Examples/020_Bouncy_Ball/Core/drivers/gfx" -I"C:/Users/bhara/STM32CubeIDE/fastbit-stm32-nano-board/Examples/020_Bouncy_Ball/Core/drivers/imu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-drivers-2f-game

clean-Core-2f-drivers-2f-game:
	-$(RM) ./Core/drivers/game/app.cyclo ./Core/drivers/game/app.d ./Core/drivers/game/app.o ./Core/drivers/game/app.su ./Core/drivers/game/ball_img.cyclo ./Core/drivers/game/ball_img.d ./Core/drivers/game/ball_img.o ./Core/drivers/game/ball_img.su ./Core/drivers/game/game.cyclo ./Core/drivers/game/game.d ./Core/drivers/game/game.o ./Core/drivers/game/game.su ./Core/drivers/game/player.cyclo ./Core/drivers/game/player.d ./Core/drivers/game/player.o ./Core/drivers/game/player.su ./Core/drivers/game/world.cyclo ./Core/drivers/game/world.d ./Core/drivers/game/world.o ./Core/drivers/game/world.su

.PHONY: clean-Core-2f-drivers-2f-game

