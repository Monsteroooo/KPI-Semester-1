cmake_minimum_required(VERSION 3.10)
project(KP9_Project C)

# Указываем стандарт, который обычно требуют в КПИ (C11 или C99)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Собираем исполняемый файл. 
# Заголовочные файлы (.h) указывать в add_executable необязательно, 
# но полезно для того, чтобы IDE (как твой VS Code) их "видела" в проекте.
add_executable(kp9_exe 
    KP9.c 
    validations.h
)