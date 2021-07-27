CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
PROJECT(piglar)
SET (CMAKE_CXX_STANDARD 20)
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -g")
SET (source_dir "${PROJECT_SOURCE_DIR}/src")
SET (vendor_dir "${source_dir}/vendor")
SET (CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

INCLUDE_DIRECTORIES(
"${vendor_dir}/glad/include"
"${vendor_dir}/stb_image"
"${vendor_dir}/inipp"
"${vendor_dir}/GLFont/"
)


FILE(GLOB source_files
"${source_dir}/main.cpp"
"${source_dir}/configParser.cpp"
"${source_dir}/GameConfig.cpp"
"${source_dir}/Game.cpp"
"${source_dir}/world/Scene.cpp"
"${source_dir}/world/entityUtil.cpp"
"${source_dir}/world/SquareEntity.cpp"
"${source_dir}/world/collisionDetection.cpp"
"${source_dir}/world/Pig.cpp"
"${source_dir}/world/Player.cpp"
"${source_dir}/TileMap.cpp"
"${source_dir}/MainTileMap.cpp"
"${source_dir}/tileMapUtil.cpp"
"${source_dir}/SceneRenderer.cpp"
"${source_dir}/Renderer.cpp"
"${source_dir}/Application.cpp"
"${source_dir}/TimeManager.cpp"
"${source_dir}/Camera.cpp"
"${source_dir}/CameraManager.cpp"
"${source_dir}/MouseManager.cpp"
"${source_dir}/TextManager.cpp"
"${source_dir}/util/timeUtil.cpp"

"${source_dir}/generator/BottomUpRectPlacer.cpp"
"${source_dir}/generator/TreeGenerator.cpp"
"${source_dir}/generator/RoadMapGen.cpp"
"${source_dir}/generator/rectUtil.cpp"


"${source_dir}/Input.cpp"
"${source_dir}/TimeManager.cpp"
"${source_dir}/util/lineUtil.cpp"
"${source_dir}/util/compassUtil.cpp"
"${source_dir}/util/Random.cpp"
"${source_dir}/util/spawnEvenly.cpp"


"${source_dir}/opengl/Display.cpp"
"${source_dir}/opengl/Buffer.cpp"
"${source_dir}/opengl/VertexArray.cpp"
"${source_dir}/opengl/Shader.cpp"
"${source_dir}/opengl/Texture.cpp"
)

FILE(GLOB vendor_files
        "${vendor_dir}/glad/src/glad.c"
        "${vendor_dir}/stb_image/stb_image/stb_image.cpp"
        "${vendor_dir}/GLFont/GLFont/GLFont.cpp"
        "${vendor_dir}/GLFont/GLFont/GLUtils.cpp"
        "${vendor_dir}/GLFont/GLFont/FTLabel.cpp"
        "${vendor_dir}/GLFont/GLFont/FontAtlas.cpp"
        )

find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Freetype REQUIRED)
find_package(Threads REQUIRED)
find_package(GLM REQUIRED)

include_directories(${GLFW3_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIR_ft2build} ${GLM_INCLUDE_DIR})

LINK_LIBRARIES( ${OPENGL_LIBRARIES} ${GLFW3_LIBRARY} Threads::Threads ${CMAKE_DL_LIBS} ${FREETYPE_LIBRARIES})

ADD_EXECUTABLE(piglar ${source_files} ${vendor_files})
