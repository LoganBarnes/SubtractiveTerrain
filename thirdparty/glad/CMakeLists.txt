cmake_minimum_required ( VERSION 3.0.0 )
project ( Glad )

add_library(
            glad SHARED
            ${PROJECT_SOURCE_DIR}/src/glad.c
            )

target_include_directories(
                           glad PUBLIC
                           ${PROJECT_SOURCE_DIR}/include
                           )

install(
        TARGETS glad
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )

install(
        DIRECTORY ${PROJECT_SOURCE_DIR}/include/glad
        DESTINATION include
        )

install(
        DIRECTORY ${PROJECT_SOURCE_DIR}/include/KHR
        DESTINATION include
        )
