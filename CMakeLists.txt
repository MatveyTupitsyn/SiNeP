cmake_minimum_required(VERSION 3.14)
project(messenger_tui CXX)

# Скачивание FTXUI через FetchContent
include(FetchContent)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
  GIT_TAG v7.0.3
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(ftxui)

add_executable(messenger_tui main.cpp)

# Таргет ftxui::component сам пропишет нужные пути к заголовочным файлам
target_link_libraries(messenger_tui PRIVATE ftxui::component ftxui::dom ftxui::screen)
