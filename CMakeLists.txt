cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_COMPILER "Z:/Qt/Tools/mingw810_64/bin/g++.exe")
set(CMAKE_C_COMPILER "Z:/Qt/Tools/mingw810_64/bin/gcc.exe")

project ("razer-da-editor" LANGUAGES C CXX)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Add source to this project's executable.
add_executable (razer-da-editor src/main.cpp src/gui.cpp src/razer.c src/usb.c)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET razer-da-editor PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(razer-da-editor PRIVATE "include")

target_link_libraries(razer-da-editor Qt5::Core)
target_link_libraries(razer-da-editor Qt5::Gui)
target_link_libraries(razer-da-editor Qt5::Widgets)

target_link_libraries(razer-da-editor "${CMAKE_CURRENT_SOURCE_DIR}/lib/libusb-1.0.dll.a")
