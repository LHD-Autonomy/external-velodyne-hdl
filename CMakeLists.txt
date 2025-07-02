cmake_minimum_required(VERSION 3.5)

# VelodyneHDL Driver
project(lhes_external_velodyne_cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} 
                    "include"
)

add_library(PacketDriver SHARED src/PacketDriver.cpp)
target_link_libraries(PacketDriver
  boost_system
)

add_library(PacketDecoder SHARED src/PacketDecoder.cpp)
target_link_libraries(PacketDecoder
)

add_library(PacketBundler SHARED src/PacketBundler.cpp)
target_link_libraries(PacketBundler
)

add_library(PacketBundleDecoder SHARED src/PacketBundleDecoder.cpp)
target_link_libraries(PacketBundleDecoder
)

add_executable(test_PacketDriver tests/test_PacketDriver.cpp)
target_link_libraries(test_PacketDriver
  PacketDriver
  pcap
)

add_executable(test_PacketDecoder tests/test_PacketDecoder.cpp)
target_link_libraries(test_PacketDecoder
  PacketDriver
  PacketDecoder
  pcap
)

add_executable(test_PacketWriter tests/test_PacketWriter.cpp)
target_link_libraries(test_PacketWriter
  PacketDriver
  pcap
)

add_executable(test_PacketBundler tests/test_PacketBundler.cpp)
target_link_libraries(test_PacketBundler
  PacketDriver
  PacketBundler
)

add_executable(test_PacketBundleDecoder tests/test_PacketBundleDecoder.cpp)
target_link_libraries(test_PacketBundleDecoder
  PacketDriver
  PacketBundler
  PacketBundleDecoder
)

add_executable(PacketFileSender src/PacketFileSender.cxx)
target_link_libraries(PacketFileSender
  boost_system
  boost_thread
  pcap
)
