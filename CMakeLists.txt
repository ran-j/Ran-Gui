
cmake_minimum_required(VERSION 3.15)

project(RanGUI)

option(RanGUI_BUILD_EXAMPLE "Build the example" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_definitions(-DUNICODE -D_UNICODE)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

include(FetchContent)

if(RanGUI_BUILD_EXAMPLE)
  add_executable(RanGUISimpleExample example/simple/simple.cpp)
  target_link_libraries(RanGUISimpleExample PRIVATE RanGUI d2d1 dwrite windowscodecs)

  add_custom_command(TARGET RanGUISimpleExample POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/example/r.png
    $<TARGET_FILE_DIR:RanGUISimpleExample>)

  add_executable(RanGUIDXAppExample example/dx_app/dx_app.cpp example/dx_app/Renderer.cpp example/dx_app/Renderer.h example/dx_app/dx_window.cpp example/dx_app/dx_window.h)
  target_link_libraries(RanGUIDXAppExample PRIVATE RanGUI d2d1 dwrite windowscodecs dxgi d3d11 d3dcompiler)
  target_include_directories(RanGUIDXAppExample PUBLIC example/dx_app)
  include_directories(example/dx_app)
endif()

include_directories(src/include)

file(GLOB_RECURSE SOURCES "src/source/*.cpp")
file(GLOB_RECURSE HEADERS "src/include/*.h")

add_library(RanGUI STATIC ${SOURCES} ${HEADERS})

target_include_directories(RanGUI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(RanGUI PUBLIC d2d1 dwrite windowscodecs)

if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()