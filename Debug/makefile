################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
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


BUILD_ARTIFACT_NAME := LEDpixel_ws2812b_for_STM32_whit_DMA_and_SPI
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
LEDpixel_ws2812b_for_STM32_whit_DMA_and_SPI.elf \

MAP_FILES += \
LEDpixel_ws2812b_for_STM32_whit_DMA_and_SPI.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
LEDpixel_ws2812b_for_STM32_whit_DMA_and_SPI.list \

OBJCOPY_BIN += \
LEDpixel_ws2812b_for_STM32_whit_DMA_and_SPI.bin \


# All Target
all: main-build

# Main-build Target
main-build: LEDpixel_ws2812b_for_STM32_whit_DMA_and_SPI.elf secondary-outputs

# Tool invocations
LEDpixel_ws2812b_for_STM32_whit_DMA_and_SPI.elf LEDpixel_ws2812b_for_STM32_whit_DMA_and_SPI.map: $(OBJS) $(USER_OBJS) R:\Documentos\ RAID\LEDpixel_ws2812b_for_STM32_whit_DMA_and_SPI\LEDpixel_ws2812b_for_STM32_whit_DMA_and_SPI\STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "LEDpixel_ws2812b_for_STM32_whit_DMA_and_SPI.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"R:\Documentos RAID\LEDpixel_ws2812b_for_STM32_whit_DMA_and_SPI\LEDpixel_ws2812b_for_STM32_whit_DMA_and_SPI\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="LEDpixel_ws2812b_for_STM32_whit_DMA_and_SPI.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

LEDpixel_ws2812b_for_STM32_whit_DMA_and_SPI.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "LEDpixel_ws2812b_for_STM32_whit_DMA_and_SPI.list"
	@echo 'Finished building: $@'
	@echo ' '

LEDpixel_ws2812b_for_STM32_whit_DMA_and_SPI.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "LEDpixel_ws2812b_for_STM32_whit_DMA_and_SPI.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) LEDpixel_ws2812b_for_STM32_whit_DMA_and_SPI.bin LEDpixel_ws2812b_for_STM32_whit_DMA_and_SPI.elf LEDpixel_ws2812b_for_STM32_whit_DMA_and_SPI.list LEDpixel_ws2812b_for_STM32_whit_DMA_and_SPI.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
