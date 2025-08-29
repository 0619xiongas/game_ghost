cmake_minimum_required(VERSION 3.10.0)
project(Ghoost VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(OTHER_LIB ${CMAKE_SOURCE_DIR}/third_party)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin)
set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})

set(SDL3_INCLUDE ${OTHER_LIB}/SDL3/include)
set(SDL3_LIB ${OTHER_LIB}/SDL3/lib/x64)
set(GLM_INCLUDE ${OTHER_LIB}/glm/include)
set(GLM_LIB ${OTHER_LIB}/glm/lib)
set(VLD_INCLUDE ${OTHER_LIB}/vld/include)
set(VLD_LIB ${OTHER_LIB}/vld/lib/x64)



# 包含头文件目录
include_directories(
    ${SDL3_INCLUDE}
    ${GLM_INCLUDE}
    ${VLD_INCLUDE}
    ${CMAKE_SOURCE_DIR}/include
)

# 链接库目录
link_directories(
    ${SDL3_LIB}
    ${GLM_LIB}
    ${VLD_LIB}
)
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# 添加可执行文件
add_executable(${TARGET} 
    ${SRC_FILES}
)

# 链接库
target_link_libraries(${TARGET}
    SDL3
    SDL3_image
    SDL3_mixer
    SDL3_ttf
    vld
    glm
)

if(WIN32)
    file(COPY ${SDL3_LIB}/SDL3.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})
    file(COPY ${SDL3_LIB}/SDL3_image.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})
    file(COPY ${SDL3_LIB}/SDL3_mixer.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})
    file(COPY ${SDL3_LIB}/SDL3_ttf.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})
    # 隐藏控制台
    if(MSVC)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    else()
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
    endif()

endif(WIN32)