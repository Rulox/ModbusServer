cmake_minimum_required(VERSION 2.8.4)
project(Modbus_Server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES ModbusServer.cpp prueba1.cpp)
add_executable(Modbus_Server ${SOURCE_FILES})