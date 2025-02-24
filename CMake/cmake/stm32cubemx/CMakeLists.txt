cmake_minimum_required(VERSION 3.22)

project(stm32cubemx)
add_library(stm32cubemx INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

target_compile_definitions(stm32cubemx INTERFACE 
	USE_PWR_LDO_SUPPLY 
	USE_HAL_DRIVER 
	STM32H743xx
    $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories(stm32cubemx INTERFACE
    ../../../FATFS/Target
    ../../../FATFS/App
    ../../../USB_HOST/App
    ../../../USB_HOST/Target
    ../../../Core/Inc
    ../../../Drivers/STM32H7xx_HAL_Driver/Inc
    ../../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy
    ../../../Middlewares/Third_Party/FatFs/src
    ../../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc
    ../../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc
    ../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include
    ../../../Drivers/CMSIS/Include
)

target_sources(stm32cubemx INTERFACE
    ../../../Core/Src/main.c
    ../../../Core/Src/stm32h7xx_it.c
    ../../../Core/Src/stm32h7xx_hal_msp.c
    ../../../FATFS/Target/usbh_diskio.c
    ../../../FATFS/App/fatfs.c
    ../../../USB_HOST/App/usb_host.c
    ../../../USB_HOST/Target/usbh_conf.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_hcd.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_usb.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash_ex.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_hsem.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma_ex.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mdma.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c_ex.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_exti.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_crc.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_crc_ex.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_fmc.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_nor.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sram.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_nand.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sdram.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_iwdg.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_qspi.c
    ../../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_delayblock.c
    ../../../Core/Src/system_stm32h7xx.c
    ../../../Middlewares/Third_Party/FatFs/src/diskio.c
    ../../../Middlewares/Third_Party/FatFs/src/ff.c
    ../../../Middlewares/Third_Party/FatFs/src/ff_gen_drv.c
    ../../../Middlewares/Third_Party/FatFs/src/option/syscall.c
    ../../../Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.c
    ../../../Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.c
    ../../../Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.c
    ../../../Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.c
    ../../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc.c
    ../../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc_bot.c
    ../../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc_scsi.c
    ../../../Core/Src/sysmem.c
    ../../../Core/Src/syscalls.c
    ../../startup_stm32h743xx.s
)

target_link_directories(stm32cubemx INTERFACE
)

target_link_libraries(stm32cubemx INTERFACE
)

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()


