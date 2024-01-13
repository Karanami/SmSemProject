################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/main.cpp 

S_UPPER_SRCS += \
../Core/Src/tx_initialize_low_level.S 

C_SRCS += \
../Core/Src/adc.c \
../Core/Src/app_threadx.c \
../Core/Src/dma.c \
../Core/Src/gpio.c \
../Core/Src/lptim.c \
../Core/Src/memorymap.c \
../Core/Src/quadspi.c \
../Core/Src/rf.c \
../Core/Src/spi.c \
../Core/Src/stm32wbxx_hal_msp.c \
../Core/Src/stm32wbxx_hal_timebase_tim.c \
../Core/Src/stm32wbxx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32wbxx.c \
../Core/Src/tim.c \
../Core/Src/usart.c \
../Core/Src/usb.c 

C_DEPS += \
./Core/Src/adc.d \
./Core/Src/app_threadx.d \
./Core/Src/dma.d \
./Core/Src/gpio.d \
./Core/Src/lptim.d \
./Core/Src/memorymap.d \
./Core/Src/quadspi.d \
./Core/Src/rf.d \
./Core/Src/spi.d \
./Core/Src/stm32wbxx_hal_msp.d \
./Core/Src/stm32wbxx_hal_timebase_tim.d \
./Core/Src/stm32wbxx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32wbxx.d \
./Core/Src/tim.d \
./Core/Src/usart.d \
./Core/Src/usb.d 

OBJS += \
./Core/Src/adc.o \
./Core/Src/app_threadx.o \
./Core/Src/dma.o \
./Core/Src/gpio.o \
./Core/Src/lptim.o \
./Core/Src/main.o \
./Core/Src/memorymap.o \
./Core/Src/quadspi.o \
./Core/Src/rf.o \
./Core/Src/spi.o \
./Core/Src/stm32wbxx_hal_msp.o \
./Core/Src/stm32wbxx_hal_timebase_tim.o \
./Core/Src/stm32wbxx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32wbxx.o \
./Core/Src/tim.o \
./Core/Src/tx_initialize_low_level.o \
./Core/Src/usart.o \
./Core/Src/usb.o 

S_UPPER_DEPS += \
./Core/Src/tx_initialize_low_level.d 

CPP_DEPS += \
./Core/Src/main.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu18 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -DSTM32_THREAD_SAFE_STRATEGY=2 -DUSE_FULL_LL_DRIVER -DTX_INCLUDE_USER_DEFINE_FILE -DFX_INCLUDE_USER_DEFINE_FILE -DLX_INCLUDE_USER_DEFINE_FILE -DUX_INCLUDE_USER_DEFINE_FILE -DNX_CRYPTO_STANDALONE_ENABLE -DNX_INCLUDE_USER_DEFINE_FILE -c -I../Core/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -I../Core/ThreadSafe -I../Middlewares/ST/threadx/common/inc/ -I../Middlewares/ST/threadx/ports/cortex_m4/gnu/inc/ -I../Middlewares/ST/netxduo/common/inc/ -I../Middlewares/ST/usbx/common/core/inc/ -I../Middlewares/ST/filex/common/inc/ -I../Middlewares/ST/threadx/utility/low_power/ -I../AZURE_RTOS/App -I../Middlewares/ST/filex/ports/generic/inc/ -I../Middlewares/ST/usbx/common/usbx_device_classes/inc/ -I../Middlewares/ST/usbx/ports/generic/inc/ -I../Middlewares/ST/usbx/common/usbx_network/inc/ -I../Middlewares/ST/usbx/common/usbx_stm32_device_controllers/ -I../Middlewares/ST/levelx/common/inc/ -I../FileX/App -I../LevelX/App -I../FileX/Target -I../LevelX/Target -I../USBX/App -I../USBX/Target -I../NetXDuo/App -I../NetXDuo/Target -I../Middlewares/ST/netxduo/ports/cortex_m4/gnu/inc/ -I../Middlewares/ST/netxduo/crypto_libraries/inc/ -I../Middlewares/ST/netxduo/crypto_libraries/ports/cortex_m4/gnu/inc/ -I../Components/Inc/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.cpp Core/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++20 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -DSTM32_THREAD_SAFE_STRATEGY=2 -DUSE_FULL_LL_DRIVER -DTX_INCLUDE_USER_DEFINE_FILE -DFX_INCLUDE_USER_DEFINE_FILE -DLX_INCLUDE_USER_DEFINE_FILE -DUX_INCLUDE_USER_DEFINE_FILE -DNX_CRYPTO_STANDALONE_ENABLE -DNX_INCLUDE_USER_DEFINE_FILE -c -I../Core/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -I../Core/ThreadSafe -I../Middlewares/ST/threadx/common/inc/ -I../Middlewares/ST/threadx/ports/cortex_m4/gnu/inc/ -I../Middlewares/ST/netxduo/common/inc/ -I../Middlewares/ST/usbx/common/core/inc/ -I../Middlewares/ST/filex/common/inc/ -I../Middlewares/ST/threadx/utility/low_power/ -I../AZURE_RTOS/App -I../Middlewares/ST/filex/ports/generic/inc/ -I../Middlewares/ST/usbx/common/usbx_device_classes/inc/ -I../Middlewares/ST/usbx/ports/generic/inc/ -I../Middlewares/ST/usbx/common/usbx_network/inc/ -I../Middlewares/ST/usbx/common/usbx_stm32_device_controllers/ -I../Middlewares/ST/levelx/common/inc/ -I../FileX/App -I../LevelX/App -I../FileX/Target -I../LevelX/Target -I../USBX/App -I../USBX/Target -I../NetXDuo/App -I../NetXDuo/Target -I../Middlewares/ST/netxduo/ports/cortex_m4/gnu/inc/ -I../Middlewares/ST/netxduo/crypto_libraries/inc/ -I../Middlewares/ST/netxduo/crypto_libraries/ports/cortex_m4/gnu/inc/ -I../Components/Inc/ -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/%.o: ../Core/Src/%.S Core/Src/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I../Components/Inc/ -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/adc.cyclo ./Core/Src/adc.d ./Core/Src/adc.o ./Core/Src/adc.su ./Core/Src/app_threadx.cyclo ./Core/Src/app_threadx.d ./Core/Src/app_threadx.o ./Core/Src/app_threadx.su ./Core/Src/dma.cyclo ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/lptim.cyclo ./Core/Src/lptim.d ./Core/Src/lptim.o ./Core/Src/lptim.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/memorymap.cyclo ./Core/Src/memorymap.d ./Core/Src/memorymap.o ./Core/Src/memorymap.su ./Core/Src/quadspi.cyclo ./Core/Src/quadspi.d ./Core/Src/quadspi.o ./Core/Src/quadspi.su ./Core/Src/rf.cyclo ./Core/Src/rf.d ./Core/Src/rf.o ./Core/Src/rf.su ./Core/Src/spi.cyclo ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/stm32wbxx_hal_msp.cyclo ./Core/Src/stm32wbxx_hal_msp.d ./Core/Src/stm32wbxx_hal_msp.o ./Core/Src/stm32wbxx_hal_msp.su ./Core/Src/stm32wbxx_hal_timebase_tim.cyclo ./Core/Src/stm32wbxx_hal_timebase_tim.d ./Core/Src/stm32wbxx_hal_timebase_tim.o ./Core/Src/stm32wbxx_hal_timebase_tim.su ./Core/Src/stm32wbxx_it.cyclo ./Core/Src/stm32wbxx_it.d ./Core/Src/stm32wbxx_it.o ./Core/Src/stm32wbxx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32wbxx.cyclo ./Core/Src/system_stm32wbxx.d ./Core/Src/system_stm32wbxx.o ./Core/Src/system_stm32wbxx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/tx_initialize_low_level.d ./Core/Src/tx_initialize_low_level.o ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su ./Core/Src/usb.cyclo ./Core/Src/usb.d ./Core/Src/usb.o ./Core/Src/usb.su

.PHONY: clean-Core-2f-Src

