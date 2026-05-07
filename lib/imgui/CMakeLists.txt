file(GLOB src "imgui/*.cpp")

add_library(imgui STATIC ${src})
target_include_directories(imgui PUBLIC ".")