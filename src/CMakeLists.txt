cmake_minimum_required(VERSION 3.10)
project(neuro_log)

set(SOURCE
    device_connector.cpp
    le_brainbit.cpp
    main.cpp
)

set(HEADER
    device_connector.h
    le_brainbit.h
    log.h
)


########
include(FetchContent)
FetchContent_Declare(
    neurosdk2-cpp
    GIT_REPOSITORY https://github.com/BrainbitLLC/neurosdk2-cpp
    GIT_TAG        1.0.6.39
)
FetchContent_MakeAvailable(neurosdk2-cpp)
########


add_executable(${PROJECT_NAME} ${SOURCE} ${HEADER})
target_include_directories(${PROJECT_NAME} PRIVATE ${neurosdk2-cpp_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${neurosdk2-cpp_SOURCE_DIR}/neurosdk2-x64.lib)


########
if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${neurosdk2-cpp_SOURCE_DIR}/neurosdk2-x64.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        COMMENT "Copying 3rdparty DLLs to executable directory..."
    )
endif()
########

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
