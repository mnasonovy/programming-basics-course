cmake_minimum_required(VERSION 3.16)  # 4.0 не существует
project(programming_basics_course LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# --- Практические задания ---
add_executable(linear
        practices/25.09.25_practic/linear.c
)

add_executable(quadratic_equation
        practices/02.10.25_practic/quadratic_equation.c
)

add_executable(vector_operations
        practices/09.10.25_practic/vector_operations.c
)

add_executable(polynomial_derivative
        practices/16.10.25_practic/polynomial_derivative.c
)

add_executable(middle_normal
        practices/23.10.25_practic/middle_normal.c
)

# --- Подключаем тестовую систему ---
add_subdirectory(C/base/tests/test_runner)

# --- Универсальная цель Rebuild ---
add_custom_target(rebuild
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
        COMMENT "🔄 Полная пересборка проекта"
)
