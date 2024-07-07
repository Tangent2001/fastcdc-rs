cmake_minimum_required(VERSION 3.14)
project(fastcdc-rs-project)

include(ExternalProject)

ExternalProject_Add(
    fastcdc-rs
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
    BUILD_COMMAND cargo build --release --manifest-path=${CMAKE_CURRENT_SOURCE_DIR}/Cargo.toml
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/target/release/libfastcdc.a ${CMAKE_CURRENT_BINARY_DIR}
    BUILD_BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/libfastcdc.a
)

add_library(fastcdc STATIC IMPORTED GLOBAL)
set_target_properties(fastcdc PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/libfastcdc.a
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include
)
add_dependencies(fastcdc fastcdc-rs)