cmake_minimum_required(VERSION 3.0.0)
project(OpenGlSandboxC VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(OpenGlSandboxC
    src/main.c
    src/Model.c
    src/Mesh.c
    src/Util.c
    src/Texture.c
    src/Sprite.c
    src/stb_image.c
    thirdparty/glad/src/glad.c
    )

#add_subdirectory("thirdparty/assimp")
add_subdirectory("thirdparty/freeGLUT/freeglut/freeglut")

target_link_libraries(OpenGlSandboxC freeglut_static)
#target_link_libraries(OpenGlSandboxC assimp)

if (UNIX)
    target_link_libraries(OpenGlSandboxC dl)
endif (UNIX)

target_include_directories(OpenGlSandboxC PUBLIC
    "thirdparty/cglm/include"
    "thirdparty/freeGLUT/freeglut/freeglut/include"
    "thirdparty/glad/include"
    "thirdparty/stb"
    #"thirdparty/assimp/include"
    )
