cmake_minimum_required(VERSION 3.22)

project(BspModule)

enable_language(C)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/bsp_qspi_w25qxx.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/bsp_fmc_sdram.c
    ${CMAKE_CURRENT_SOURCE_DIR}/bsp.c
)

set(INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GENERATED_INCLUDE_DIR}
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})

target_link_libraries(${PROJECT_NAME} PUBLIC
    stm32cubemx
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    USE_HAL_DRIVER
    STM32H743xx
    $<$<CONFIG:Debug>:DEBUG>
)