cmake_minimum_required(VERSION 3.5.0)
project(glfwextlib 
        VERSION 0.1.0 
        LANGUAGES C CXX)

find_package(glfw3 REQUIRED)

set(SOURCES
    src/glfwextlib.cpp
    src/Window.cpp
)
    
add_library(${PROJECT_NAME} STATIC ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 23 CXX_STANDARD_REQUIRED On)

target_link_libraries(${PROJECT_NAME} 
    glfw
    OpenGL
)


target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
    
export(TARGETS ${PROJECT_NAME} FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.cmake)