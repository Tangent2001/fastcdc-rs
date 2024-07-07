cmake_minimum_required(VERSION 3.14)
project(fastcdc-rs-project)

include(ExternalProject)

if (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
    set(FASTCDC_LIB_BINARY ${CMAKE_CURRENT_SOURCE_DIR}/target/x86_64-unknown-linux-gnu/release/libfastcdc.a)
    set(FASTCDC_BUILD_TARGET --target=x86_64-unknown-linux-gnu)
    message(STATUS "Build fastcdc for x86_64")
elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
    set(FASTCDC_LIB_BINARY ${CMAKE_CURRENT_SOURCE_DIR}/target/aarch64-unknown-linux-gnu/release/libfastcdc.a)
    set(FASTCDC_BUILD_TARGET --target=aarch64-unknown-linux-gnu)
    message(STATUS "Build fastcdc for aarch64")
else()
    set(FASTCDC_LIB_BINARY ${CMAKE_CURRENT_SOURCE_DIR}/target/release/libfastcdc.a) # 默认不指定架构
    set(FASTCDC_BUILD_TARGET "")
    message(STATUS "Build fastcdc for native arch")
endif()

ExternalProject_Add(
    fastcdc-rs
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
    BUILD_COMMAND cargo build --release --manifest-path=${CMAKE_CURRENT_SOURCE_DIR}/Cargo.toml --config=${CMAKE_CURRENT_SOURCE_DIR}/.cargo/config.toml ${FASTCDC_BUILD_TARGET}
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy ${FASTCDC_LIB_BINARY} ${CMAKE_CURRENT_BINARY_DIR}
    BUILD_BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/libfastcdc.a
)

add_library(fastcdc STATIC IMPORTED GLOBAL)
set_target_properties(fastcdc PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/libfastcdc.a
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include
)
add_dependencies(fastcdc fastcdc-rs)