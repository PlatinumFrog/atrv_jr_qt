cmake_minimum_required(VERSION 3.8)
project(atrv_jr_qt)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(ros_image_to_qimage REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS
Core
Quick
Widgets
Multimedia
MultimediaWidgets
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

add_executable(atrv_jr_qt
  src/Main.cpp
  include/CameraNode.hpp
  include/Gui.hpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PUBLIC $<INSTALL_INTERFACE:include>)

ament_target_dependencies(atrv_jr_qt rclcpp std_msgs sensor_msgs ros_image_to_qimage)

target_link_libraries(atrv_jr_qt
  Qt5::Core
  Qt5::Quick
  Qt5::Widgets
  Qt5::Multimedia
  Qt5::MultimediaWidgets
)

install(TARGETS
  atrv_jr_qt
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
