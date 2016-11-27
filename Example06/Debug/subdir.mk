################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sensor.c \
../cr_startup_lpc17.c \
../main.c 

OBJS += \
./Sensor.o \
./cr_startup_lpc17.o \
./main.o 

C_DEPS += \
./Sensor.d \
./cr_startup_lpc17.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__REDLIB__ -I"D:\Documentos\EC\EC020\Projeto2\Lib_CMSISv1p30_LPC17xx\inc" -I"D:\Documentos\EC\EC020\Projeto2\FreeRTOS_Library\demo_code" -I"D:\Documentos\EC\EC020\Projeto2\FreeRTOS_Library\include" -I"D:\Documentos\EC\EC020\Projeto2\FreeRTOS_Library\portable" -I"D:\Documentos\EC\EC020\Projeto2\Lib_EaBaseBoard\inc" -I"D:\Documentos\EC\EC020\Projeto2\Lib_MCU\inc" -O0 -g3 -fsigned-char -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


