cmake_minimum_required(VERSION 3.14)
project(fastcdc-rs-project)

include(ExternalProject)

if (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
    set(FASTCDC_ARCH "x86_64-unknown-linux-gnu")
    set(FASTCDC_TARGET_ARG "--target=${FASTCDC_ARCH}")
elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
    set(FASTCDC_ARCH "aarch64-unknown-linux-gnu")
    set(FASTCDC_TARGET_ARG "--target=${FASTCDC_ARCH}")
else()
    set(FASTCDC_ARCH "")
    set(FASTCDC_TARGET_ARG "")
endif()
set(FASTCDC_STATIC_LIB ${CMAKE_CURRENT_SOURCE_DIR}/target/${FASTCDC_ARCH}/release/libfastcdc.a)
set(FASTCDC_SHARED_LIB ${CMAKE_CURRENT_SOURCE_DIR}/target/${FASTCDC_ARCH}/release/libfastcdc.so)
message(STATUS "Build fastcdc for ${FASTCDC_ARCH}")

ExternalProject_Add(
    fastcdc-rs
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
    BUILD_COMMAND cargo build --release --manifest-path=${CMAKE_CURRENT_SOURCE_DIR}/Cargo.toml --config=${CMAKE_CURRENT_SOURCE_DIR}/.cargo/config.toml ${FASTCDC_TARGET_ARG}
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy ${FASTCDC_STATIC_LIB} ${CMAKE_CURRENT_BINARY_DIR}
            COMMAND ${CMAKE_COMMAND} -E copy ${FASTCDC_SHARED_LIB} ${CMAKE_CURRENT_BINARY_DIR}
    BUILD_BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/libfastcdc.a ${CMAKE_CURRENT_BINARY_DIR}/libfastcdc.so
)

if (BUILD_SHARED_LIBS)
    add_library(fastcdc SHARED IMPORTED GLOBAL)
    set_target_properties(fastcdc PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/libfastcdc.so
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
else()
    add_library(fastcdc STATIC IMPORTED GLOBAL)
    set_target_properties(fastcdc PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/libfastcdc.a
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
endif()

add_dependencies(fastcdc fastcdc-rs)