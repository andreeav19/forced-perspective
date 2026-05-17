add_executable(${PROJECT_NAME}
    main.cpp
        Window.cpp
        ../headers/Window.h
        Application.cpp
        ../headers/Application.h
        InputManager.cpp
        ../headers/InputManager.h
        Shader.cpp
        ../headers/Shader.h
        TextureManager.cpp
        ../headers/TextureManager.h
        Camera.cpp
        ../headers/Camera.h
        ../headers/Constants.h
        ../headers/InputAction.h
        ActionController.cpp
        ../headers/ActionController.h
        Light.cpp
        ../headers/Light.h
        LightManager.cpp
        ../headers/LightManager.h
        Material.cpp
        ../headers/Material.h
        Mesh.cpp
        ../headers/Mesh.h
)
target_link_libraries(${PROJECT_NAME} PRIVATE lib)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        COMMAND_EXPAND_LISTS
)

add_compile_definitions(PROJECT_ROOT="${CMAKE_SOURCE_DIR}/")