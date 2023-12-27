cmake_minimum_required(VERSION 3.25.0)
project(glfwext
        VERSION 0.2.2 
        LANGUAGES C CXX)

find_package(glfw3 REQUIRED)

set(SOURCES
    include/glfwext/glfwext.hpp
    src/glfwext.cpp
    include/glfwext/Events.hpp
    include/glfwext/Window.hpp
    src/Window.cpp
    include/glfwext/exception.hpp
    src/exception.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 23 CXX_STANDARD_REQUIRED On)

target_link_libraries(${PROJECT_NAME} 
    glfw
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
    
export(TARGETS ${PROJECT_NAME} FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.cmake)