cmake_minimum_required(VERSION 3.5)

# VelodyneHDL Driver
project(lhes_external_velodyne_cpp)

# -- Check Ros system --
include("${CMAKE_CURRENT_SOURCE_DIR}/../../../../cmake/CheckRosSystem.cmake")
# ----------------------

include_directories(${CMAKE_CURRENT_SOURCE_DIR} 
                    "include"
)

add_library(PacketDriver SHARED src/PacketDriver.cpp)
target_link_libraries(PacketDriver PUBLIC
  boost_system
)

add_library(PacketDecoder SHARED src/PacketDecoder.cpp)
target_link_libraries(PacketDecoder PUBLIC
)

add_library(PacketBundler SHARED src/PacketBundler.cpp)
target_link_libraries(PacketBundler PUBLIC
)

add_library(PacketBundleDecoder SHARED src/PacketBundleDecoder.cpp)
target_link_libraries(PacketBundleDecoder PUBLIC
)

add_executable(test_PacketDriver tests/test_PacketDriver.cpp)
target_link_libraries(test_PacketDriver PUBLIC
  PacketDriver
  pcap
)

add_executable(test_PacketDecoder tests/test_PacketDecoder.cpp)
target_link_libraries(test_PacketDecoder PUBLIC
  PacketDriver
  PacketDecoder
  pcap
)

add_executable(test_PacketWriter tests/test_PacketWriter.cpp)
target_link_libraries(test_PacketWriter PUBLIC
  PacketDriver
  pcap
)

add_executable(test_PacketBundler tests/test_PacketBundler.cpp)
target_link_libraries(test_PacketBundler PUBLIC
  PacketDriver
  PacketBundler
)

add_executable(test_PacketBundleDecoder tests/test_PacketBundleDecoder.cpp)
target_link_libraries(test_PacketBundleDecoder PUBLIC
  PacketDriver
  PacketBundler
  PacketBundleDecoder
)

add_executable(PacketFileSender src/PacketFileSender.cxx)
target_link_libraries(PacketFileSender PUBLIC
  boost_system
  boost_thread
  pcap
)

set(ROS_SRC src/PacketDriver.cpp src/PacketDecoder src/PacketBundler src/PacketBundleDecoder)
set(AVIONIC_SRC src/PacketDriver.cpp src/PacketDecoder src/PacketBundler src/PacketBundleDecoder)

if(ROS_SYSTEM)
  add_library(${PROJECT_NAME} ${ROS_SRC})
else()
  add_library(${PROJECT_NAME} ${AVIONIC_SRC})
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC
  boost_system
)


# -- Install configs --
include("${CMAKE_CURRENT_SOURCE_DIR}/../../../../cmake/InstallConfigs.cmake")
# ---------------------

# -----------------------------------------------
# -----------------------------------------------
# -----------------------------------------------

if(ROS_SYSTEM)
  set(EXPORT_LIBRARIES ${PROJECT_NAME})
  set(EXPORT_NAME export_${PROJECT_NAME})  
  include("${CMAKE_CURRENT_LIST_DIR}/../../../../cmake/ExportForRos.cmake")
endif()