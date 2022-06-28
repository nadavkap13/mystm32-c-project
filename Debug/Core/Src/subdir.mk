################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/LED.c \
../Core/Src/RGBLED.c \
../Core/Src/clock.c \
../Core/Src/lightsens.c \
../Core/Src/main.c \
../Core/Src/mybuzzer.c \
../Core/Src/mymain.c \
../Core/Src/new_button.c \
../Core/Src/stm32l4xx_hal_msp.c \
../Core/Src/stm32l4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l4xx.c 

OBJS += \
./Core/Src/LED.o \
./Core/Src/RGBLED.o \
./Core/Src/clock.o \
./Core/Src/lightsens.o \
./Core/Src/main.o \
./Core/Src/mybuzzer.o \
./Core/Src/mymain.o \
./Core/Src/new_button.o \
./Core/Src/stm32l4xx_hal_msp.o \
./Core/Src/stm32l4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l4xx.o 

C_DEPS += \
./Core/Src/LED.d \
./Core/Src/RGBLED.d \
./Core/Src/clock.d \
./Core/Src/lightsens.d \
./Core/Src/main.d \
./Core/Src/mybuzzer.d \
./Core/Src/mymain.d \
./Core/Src/new_button.d \
./Core/Src/stm32l4xx_hal_msp.d \
./Core/Src/stm32l4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/LED.d ./Core/Src/LED.o ./Core/Src/LED.su ./Core/Src/RGBLED.d ./Core/Src/RGBLED.o ./Core/Src/RGBLED.su ./Core/Src/clock.d ./Core/Src/clock.o ./Core/Src/clock.su ./Core/Src/lightsens.d ./Core/Src/lightsens.o ./Core/Src/lightsens.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/mybuzzer.d ./Core/Src/mybuzzer.o ./Core/Src/mybuzzer.su ./Core/Src/mymain.d ./Core/Src/mymain.o ./Core/Src/mymain.su ./Core/Src/new_button.d ./Core/Src/new_button.o ./Core/Src/new_button.su ./Core/Src/stm32l4xx_hal_msp.d ./Core/Src/stm32l4xx_hal_msp.o ./Core/Src/stm32l4xx_hal_msp.su ./Core/Src/stm32l4xx_it.d ./Core/Src/stm32l4xx_it.o ./Core/Src/stm32l4xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32l4xx.d ./Core/Src/system_stm32l4xx.o ./Core/Src/system_stm32l4xx.su

.PHONY: clean-Core-2f-Src

