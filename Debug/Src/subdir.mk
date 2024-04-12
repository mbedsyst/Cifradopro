################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/AES.c \
../Src/GPIO.c \
../Src/HASH.c \
../Src/HSM_Lib.c \
../Src/LED.c \
../Src/RNG.c \
../Src/UART.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/AES.o \
./Src/GPIO.o \
./Src/HASH.o \
./Src/HSM_Lib.o \
./Src/LED.o \
./Src/RNG.o \
./Src/UART.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/AES.d \
./Src/GPIO.d \
./Src/HASH.d \
./Src/HSM_Lib.d \
./Src/LED.d \
./Src/RNG.d \
./Src/UART.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L4R5xx -c -I../Inc -I"C:/Users/zalma/OneDrive/Documents/STM32L4+/GCC_STM32CubeIDE/HSM_Application/ChipHeaders/CMSIS/Include" -I"C:/Users/zalma/OneDrive/Documents/STM32L4+/GCC_STM32CubeIDE/01_ LED/ChipHeaders/CMSIS/Device/ST/STM32L4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/AES.cyclo ./Src/AES.d ./Src/AES.o ./Src/AES.su ./Src/GPIO.cyclo ./Src/GPIO.d ./Src/GPIO.o ./Src/GPIO.su ./Src/HASH.cyclo ./Src/HASH.d ./Src/HASH.o ./Src/HASH.su ./Src/HSM_Lib.cyclo ./Src/HSM_Lib.d ./Src/HSM_Lib.o ./Src/HSM_Lib.su ./Src/LED.cyclo ./Src/LED.d ./Src/LED.o ./Src/LED.su ./Src/RNG.cyclo ./Src/RNG.d ./Src/RNG.o ./Src/RNG.su ./Src/UART.cyclo ./Src/UART.d ./Src/UART.o ./Src/UART.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

