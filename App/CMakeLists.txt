# App/CMakeLists.txt
cmake_minimum_required(VERSION 3.22)

project(AppModule)

enable_language(C)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/app.c
    ${CMAKE_CURRENT_SOURCE_DIR}/utils.c
    ${CMAKE_CURRENT_SOURCE_DIR}/app_update.c
    ${CMAKE_CURRENT_SOURCE_DIR}/app_config.c
)

set(INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc
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