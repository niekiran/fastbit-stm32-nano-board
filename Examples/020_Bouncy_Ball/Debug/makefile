################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F3xx_HAL_Driver/Src/subdir.mk
-include Core/drivers/imu/subdir.mk
-include Core/drivers/gfx/subdir.mk
-include Core/drivers/game/subdir.mk
-include Core/drivers/display/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := 020_Bouncy_Ball
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
020_Bouncy_Ball.elf \

MAP_FILES += \
020_Bouncy_Ball.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
020_Bouncy_Ball.list \

OBJCOPY_HEX += \
020_Bouncy_Ball.hex \

OBJCOPY_BIN += \
020_Bouncy_Ball.bin \


# All Target
all: main-build

# Main-build Target
main-build: 020_Bouncy_Ball.elf secondary-outputs

# Tool invocations
020_Bouncy_Ball.elf 020_Bouncy_Ball.map: $(OBJS) $(USER_OBJS) C:\Users\bhara\STM32CubeIDE\fastbit-stm32-nano-board\Examples\020_Bouncy_Ball\STM32F303CCTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "020_Bouncy_Ball.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\bhara\STM32CubeIDE\fastbit-stm32-nano-board\Examples\020_Bouncy_Ball\STM32F303CCTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="020_Bouncy_Ball.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

020_Bouncy_Ball.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "020_Bouncy_Ball.list"
	@echo 'Finished building: $@'
	@echo ' '

020_Bouncy_Ball.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "020_Bouncy_Ball.hex"
	@echo 'Finished building: $@'
	@echo ' '

020_Bouncy_Ball.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "020_Bouncy_Ball.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) 020_Bouncy_Ball.bin 020_Bouncy_Ball.elf 020_Bouncy_Ball.hex 020_Bouncy_Ball.list 020_Bouncy_Ball.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
