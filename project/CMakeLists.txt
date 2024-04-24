cmake_minimum_required(VERSION 3.25)

# import the pico-sdk
set(ENV{PICO_SDK_FETCH_FROM_GIT} 1)
include(pico_sdk_import.cmake)

include(FetchContent)

FetchContent_Declare(freertos
    GIT_REPOSITORY https://github.com/freertos/freertos-kernel.git
    GIT_TAG V11.0.1)

add_library(freertos_config INTERFACE)
set(FREERTOS_PORT GCC_RP2040)
FetchContent_Populate(freertos)
set(FREERTOS_KERNEL_PATH ${freertos_SOURCE_DIR})
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

FetchContent_Declare(nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3)
fetchcontent_makeavailable(nlohmann_json)
#find_package(nlohmann_json 3.2.0 REQUIRED)

message(VERSION_REVISION="${PICO_SDK_VERSION_REVISION}")

project(direct C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_definitions(-DPICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS=5000)

add_executable(${PROJECT_NAME}
    main.cpp
    )

    # if the PIO is used, this is how to do it.
pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/uart_rx.pio)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR} 
    ${lsm6ds3tr_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    FreeRTOS-Kernel
    FreeRTOS-Kernel-Heap4
    hardware_pio
    hardware_rtc
    hardware_uart
    hardware_gpio
    hardware_i2c
    hardware_spi
    hardware_adc
    nlohmann_json::nlohmann_json
)

pico_add_extra_outputs(${PROJECT_NAME} 1)
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)
