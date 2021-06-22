
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
PROJECT(piglar)
set( CMAKE_EXPORT_COMPILE_COMMANDS ON   )
SET (CMAKE_CXX_COMPILER "/usr/bin/g++")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17 -Wall")
SET (source_dir "${PROJECT_SOURCE_DIR}/src")
SET (vendor_dir "${source_dir}/vendor")

INCLUDE_DIRECTORIES(
"${vendor_dir}/glad/include"
"${vendor_dir}/stb_image"
)

FILE(GLOB source_files
"${source_dir}/main.cpp"
"${source_dir}/TimeManager.cpp"
"${source_dir}/Game.cpp"
"${source_dir}/Scene.cpp"
"${source_dir}/RoadMap.cpp"
"${source_dir}/SceneRenderer.cpp"
"${source_dir}/Renderer.cpp"
"${source_dir}/Application.cpp"
"${source_dir}/TimeManager.cpp"
"${source_dir}/Camera.cpp"
"${source_dir}/CameraManager.cpp"
"${source_dir}/MouseManager.cpp"
"${source_dir}/Input.cpp"
"${source_dir}/SquarePlayer.cpp"
"${source_dir}/SquarePlayer.h"
"${source_dir}/collisionDetection.cpp"


"${source_dir}/util/util.cpp"
"${source_dir}/util/lineFunc.cpp"
"${source_dir}/util/Random.cpp"

"${source_dir}/generator/bottomuprectplacer.cpp"
"${source_dir}/generator/TreeGenerator.cpp"
"${source_dir}/generator/RoadMapGen.cpp"
"${source_dir}/generator/rotateLine.cpp"
"${source_dir}/generator/rectUtil.cpp"

"${source_dir}/opengl/Display.cpp"
"${source_dir}/opengl/Buffer.cpp"
"${source_dir}/opengl/VertexArray.cpp"
"${source_dir}/opengl/Shader.cpp"

"${vendor_dir}/glad/src/glad.c"
"${vendor_dir}/stb_image/stb_image/stb_image.cpp"
)

FILE(GLOB test_files
    "${source_dir}/test/bottomUpTest.cpp"
    "${source_dir}/generator/rectUtil.cpp"
    "${source_dir}/generator/bottomuprectplacer.cpp"
    "${source_dir}/util/util.cpp"
    "${source_dir}/util/lineFunc.cpp"
    "${source_dir}/generator/rotateLine.cpp"

)

LINK_LIBRARIES(-lglfw -lGL -lpthread -lX11 -lXrandr -lXi -ldl)

ADD_EXECUTABLE(piglar ${source_files})
