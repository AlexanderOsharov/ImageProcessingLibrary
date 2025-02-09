# ImageProcessingLibrary

## Описание
Библиотека для работы с изображениями. Поддерживает загрузку, обработку и сохранение изображений в различных форматах.

## Установка
1. Клонируйте репозиторий:
   ```bash
   git clone https://github.com/AlexanderOsharov/ImageProcessingLibrary.git
   ```
2. Скомпилируйте библиотеку
   ```bash
   cmake .
   make
   ```
## Использование
Пример кода
```C++
#include "Image.h"
#include "GrayscaleProcessor.h"

int main() {
    Image image;
    if (!image.load("input.png")) {
        std::cerr << "Failed to load image" << std::endl;
        return 1;
    }

    GrayscaleProcessor processor;
    processor.process(image);

    if (!image.save("output.png")) {
        std::cerr << "Failed to save image" << std::endl;
        return 1;
    }

    return 0;
}
```

## Форматы
1. Загрузка: BMP, PNG, JPEG, SVG (базовый парсер).
2. Сохранение: PNG, JPEG.
