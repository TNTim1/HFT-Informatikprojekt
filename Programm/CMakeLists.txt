cmake_minimum_required(VERSION 3.10)
project(Programm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------------
# Windows MSYS2 fix for large template files
# -------------------------------
add_compile_options(-Wa,-mbig-obj)

# -------------------------------
# Boost include path
# -------------------------------
set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/boost_1_70_0")

# -------------------------------
# OpenSSL paths (MSYS2 MinGW64)
# -------------------------------
set(OPENSSL_ROOT_DIR "C:/msys64/mingw64")
set(OPENSSL_INCLUDE_DIR "C:/msys64/mingw64/include")
set(OPENSSL_CRYPTO_LIBRARY "C:/msys64/mingw64/lib/libcrypto.a")
set(OPENSSL_SSL_LIBRARY "C:/msys64/mingw64/lib/libssl.a")

find_package(OpenSSL REQUIRED)

# -------------------------------
# binapi library
# -------------------------------
file(GLOB BINAPI_SRC "binapi/src/*.cpp")
add_library(binapi STATIC ${BINAPI_SRC})

target_include_directories(binapi PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/binapi/include
        ${BOOST_ROOT}
        ${OPENSSL_INCLUDE_DIR}
)

target_link_libraries(binapi PUBLIC
        OpenSSL::SSL
        OpenSSL::Crypto
        ws2_32
        mswsock
)

# -------------------------------
# main executable
# -------------------------------
add_executable(Programm main.cpp)

# Link binapi (which already links OpenSSL + sockets)
target_link_libraries(Programm PRIVATE binapi)
