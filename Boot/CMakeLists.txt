# bootloader/CMakeLists.txt
cmake_minimum_required(VERSION 3.22)

project(BootModule)

enable_language(C ASM)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/bootloader.c
)

set(INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GENERATED_INCLUDE_DIR}
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})

target_link_libraries(${PROJECT_NAME} PUBLIC
    stm32cubemx
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -O2
    -Wall
    -Wextra
    -mcpu=cortex-m7
    -mthumb
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    USE_HAL_DRIVER
    STM32H743xx
    $<$<CONFIG:Debug>:DEBUG>
)