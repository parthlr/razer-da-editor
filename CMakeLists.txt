cmake_minimum_required (VERSION 3.8)

project ("razer-da-editor")

# Add source to this project's executable.
add_executable (razer-da-editor "src/main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET razer-da-editor PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(razer-da-editor PRIVATE "include")

target_link_libraries(razer-da-editor PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/lib/libusb-1.0.dll.a")
