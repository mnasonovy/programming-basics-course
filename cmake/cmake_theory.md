# Полный конспект по **CMake** 

---

## 1. Что такое CMake

**CMake** — это кроссплатформенная система автоматизации сборки. Она не компилирует код напрямую, а **генерирует файлы сборки** для конкретной системы:

- **Makefiles** (Linux/macOS)
- **Ninja build files** (современная альтернатива Make)
- **Visual Studio solution (.sln)** (Windows)

### Принцип работы:
```
CMakeLists.txt  →  cmake configure  →  build system  →  compile/link
```

Этапы:
1. **Configure** — анализ исходников и зависимостей.
2. **Generate** — создание файлов для выбранного билдера.
3. **Build** — фактическая компиляция и линковка.

---

## 2. Основные понятия

| Термин | Значение |
|:--|:--|
| **Проект (project)** | Совокупность исходников, библиотек, исполняемых файлов. |
| **Цель (target)** | Результат сборки — исполняемый файл или библиотека. |
| **Static library (.a/.lib)** | Статическая библиотека — вшивается в бинарник при линковке. |
| **Shared library (.so/.dll)** | Динамическая библиотека — подключается при выполнении. |
| **Build directory** | Отдельная папка, где хранятся все сгенерированные файлы. |

Совет: никогда не собирай в исходной папке. Используй out-of-source build:
```
cmake -S . -B build
```

---

## 3. Основные команды CMake

```cmake
cmake_minimum_required(VERSION 3.16)  # минимальная версия
project(MyApp LANGUAGES C CXX)         # объявление проекта
```

### 🔹 Создание исполняемого файла
```cmake
add_executable(main src/main.cpp)
```

### 🔹 Создание библиотеки
```cmake
add_library(math STATIC src/math.cpp src/math.h)
add_library(utils SHARED src/utils.cpp)
```

### 🔹 Линковка
```cmake
target_link_libraries(main PRIVATE math utils)
```

Модификаторы видимости:
- **PRIVATE** — флаги/зависимости применяются только к этой цели.
- **PUBLIC** — применяются и к целевой библиотеке, и к зависящим от неё.
- **INTERFACE** — только к зависящим.

### 🔹 Пути к заголовкам
```cmake
target_include_directories(main PUBLIC include)
```

### 🔹 Переменные и вывод сообщений
```cmake
set(MY_PATH src)
message(STATUS "Building from ${MY_PATH}")
```

### 🔹 Условия
```cmake
if(WIN32)
  message(STATUS "Building on Windows")
elseif(UNIX)
  message(STATUS "Building on Linux")
endif()
```

---

## 4. Конфигурация сборки

Тип сборки задаётся переменной `CMAKE_BUILD_TYPE`:

```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
```

Доступные режимы:
- **Debug** — отладочная сборка.
- **Release** — оптимизированная.
- **RelWithDebInfo** — компромисс: оптимизация + символы отладки.
- **MinSizeRel** — минимальный размер бинарников.

### 🔹 Компиляторы
| ОС | Команда | Пример |
|----|----------|--------|
| Linux | gcc / g++ | `cmake -DCMAKE_CXX_COMPILER=g++` |
| macOS | clang | `cmake -G "Unix Makefiles"` |
| Windows | MSVC | `cmake -G "Visual Studio 17 2022"` |

### 🔹 Флаги компиляции
```cmake
target_compile_features(main PRIVATE cxx_std_17)

if(MSVC)
  target_compile_options(main PRIVATE /W4)
else()
  target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic)
endif()
```

---

## 5. Работа с библиотеками

### 🔹 Подключение локальной библиотеки
```cmake
add_subdirectory(libs/math)
target_link_libraries(main PRIVATE mathlib)
```

### 🔹 find_package
```cmake
find_package(OpenSSL REQUIRED)
target_link_libraries(main PRIVATE OpenSSL::SSL OpenSSL::Crypto)
```

### 🔹 FetchContent (скачивает внешние библиотеки при сборке)
```cmake
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.11.0
)
FetchContent_MakeAvailable(googletest)
```

---

## 6. Переменные и пути

| Переменная | Значение |
|:--|:--|
| `CMAKE_SOURCE_DIR` | Корень исходников |
| `CMAKE_BINARY_DIR` | Корень сборки |
| `PROJECT_SOURCE_DIR` | Путь проекта |
| `PROJECT_BINARY_DIR` | Путь сборки проекта |

Работа с файлами:
```cmake
file(GLOB SRC_FILES src/*.cpp)
add_executable(main ${SRC_FILES})
```

---

## 7. Генерация и сборка

### 🔹 Windows
```powershell
cmake -S . -B build -G "Visual Studio 17 2022"
cmake --build build --config Release
```

### 🔹 Linux / macOS
```
cmake -S . -B build -G "Unix Makefiles"
cmake --build build -- -j$(nproc)
```

### 🔹 Ninja (быстрая альтернатива)
```
cmake -S . -B build -G Ninja
cmake --build build
```

---

## 8. Установка и экспорт

```cmake
install(TARGETS main
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib/static)

install(FILES include/math.h DESTINATION include)
install(DIRECTORY assets/ DESTINATION share/assets)
```

Экспорт библиотек:
```cmake
install(EXPORT MyTargets
  FILE MyTargets.cmake
  NAMESPACE MyProject::
  DESTINATION lib/cmake/MyProject)
```

---

## 9. Пример мини-проекта

**Структура:**
```
CMakeLists.txt
src/
 ├─ main.cpp
 └─ math.cpp
include/
 └─ math.h
```

**CMakeLists.txt:**
```cmake
cmake_minimum_required(VERSION 3.16)
project(SimpleMath LANGUAGES CXX)

add_library(math STATIC src/math.cpp)
target_include_directories(math PUBLIC include)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE math)
```

**Сборка:**
```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/main
```

---

## 10. Частые ошибки и советы

| Ошибка | Причина | Решение |
|:--|:--|:--|
| `target_link_libraries: not found` | Библиотека не объявлена | Проверь порядок `add_library` → `target_link_libraries` |
| `Cannot find package` | Отсутствует пакет | Установи dev-пакет (например, `libssl-dev`) |
| `LINK : fatal error LNK1104` | Конфликт Debug/Release | Собери в чистой папке `build/` |
| `CMake Error: The source directory does not appear...` | Запуск из неправильной директории | Используй `-S` и `-B` явно |

---

## 11. Полезные ссылки

- 📘 [Официальная документация CMake](https://cmake.org/cmake/help/latest/)
- 📗 [CMake Tutorial (официальный гайд)](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
- 📙 [Modern CMake examples](https://github.com/ttroy50/cmake-examples)

---

## Итог

CMake — это стандарт для кроссплатформенной сборки C/C++ проектов. Он позволяет:
- централизовать настройку компиляции и линковки;
- гибко подключать зависимости (через find_package или FetchContent);
- работать одинаково на Windows, Linux и macOS;
- создавать читаемые, воспроизводимые и масштабируемые сборки.

Используй отдельные директории `src`, `include`, `libs`, а сборку всегда веди в `build/`. Так проект останется чистым и управляемым.
