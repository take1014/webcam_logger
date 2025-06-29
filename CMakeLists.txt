cmake_minimum_required(VERSION 3.11)

project(CameraThreadMain)

include(./find_dependencies.cmake)

find_package(OpenCV REQUIRED)

add_library(CameraThreadLib
  camera.h
  camera.cc
)

# インクルードディレクトリの指定
target_include_directories(CameraThreadLib
  PRIVATE ${OpenCV_INCLUDE_DIRS}
)

# 依存ライブラリの指定
target_link_libraries(CameraThreadLib
  PRIVATE ${OpenCV_LIBS}
  PRIVATE jsoncpp
  PRIVATE pthread
)

# main.cppを使って実行可能なプログラムをビルド
add_executable(${PROJECT_NAME}
  main.cc
)

# インクルードディレクトリの指定
target_include_directories(${PROJECT_NAME}
  PRIVATE ${OpenCV_INCLUDE_DIRS}
)

# 依存ライブラリの指定
target_link_libraries(${PROJECT_NAME}
  PRIVATE CameraThreadLib
)
