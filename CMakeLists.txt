cmake_minimum_required(VERSION 3.10)
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
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party
)

# Установка библиотеки
install(TARGETS ImageProcessing
    EXPORT ImageProcessingTargets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# Установка заголовочных файлов
install(DIRECTORY include/ DESTINATION include)

# Экспорт целей
export(EXPORT ImageProcessingTargets FILE ${CMAKE_CURRENT_BINARY_DIR}/ImageProcessingConfig.cmake)
install(EXPORT ImageProcessingTargets DESTINATION cmake)