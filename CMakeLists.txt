cmake_minimum_required(VERSION 3.15)
project(ImageProcessingLibrary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Создание статической библиотеки
add_library(ImageProcessing STATIC
    src/Image.cpp
    src/ImageProcessor.cpp
)

# Подключение заголовочных файлов
target_include_directories(ImageProcessing PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party
)

# Установка библиотеки
install(TARGETS ImageProcessing
    EXPORT ImageProcessingTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# Установка заголовочных файлов
install(DIRECTORY include/ DESTINATION include)

# Экспорт целей
install(EXPORT ImageProcessingTargets DESTINATION cmake)