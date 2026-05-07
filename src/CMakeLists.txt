add_executable(${PROJECT_NAME}
    main.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE lib)

add_compile_definitions(PROJECT_ROOT="${CMAKE_SOURCE_DIR}/")