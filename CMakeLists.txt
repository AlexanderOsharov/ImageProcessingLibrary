cmake_minimum_required(VERSION 3.10)

project(ImageProcessingLibrary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(ImageProcessing STATIC
    src/Image.cpp
    src/ImageProcessor.cpp
)

target_include_directories(ImageProcessingLibrary PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party
)

target_include_directories(ImageProcessingLibrary 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(ImageProcessingLibrary 
    PRIVATE src/Image.cpp
)

install(TARGETS ImageProcessingLibrary 
    EXPORT ImageProcessingLibraryExport
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)

export(EXPORT ImageProcessingLibraryExport FILE ${CMAKE_CURRENT_BINARY_DIR}/ImageProcessingLibraryConfig.cmake)
install(EXPORT ImageProcessingLibraryExport DESTINATION cmake)