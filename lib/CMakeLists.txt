add_subdirectory(assimp)
add_subdirectory(bullet3)
add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(imgui)
target_link_libraries(imgui PUBLIC glfw)

add_library(lib INTERFACE)
target_link_libraries(lib INTERFACE
    assimp::assimp
    glfw
    glm::glm
    imgui
)

target_include_directories(lib INTERFACE
    ${CMAKE_SOURCE_DIR}/stb
)