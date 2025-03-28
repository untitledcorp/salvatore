cmake_minimum_required(VERSION 3.10)
project(SalvatoreVM)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBVIRT REQUIRED libvirt)

include_directories(${LIBVIRT_INCLUDE_DIRS})
link_directories(${LIBVIRT_LIBRARY_DIRS})

add_executable(salvatore src/main.cpp src/vm_manager.cpp src/qemu_wrapper.cpp src/config.cpp src/utils.cpp)
target_link_libraries(salvatore ${LIBVIRT_LIBRARIES})
