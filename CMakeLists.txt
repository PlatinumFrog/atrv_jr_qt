cmake_minimum_required(VERSION 3.8)
project(atrv_jr_qt)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Widgets REQUIRED)

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

add_executable(atrv_jr_qt src/qtInterface.cpp)
ament_target_dependencies(atrv_jr_qt rclcpp)

target_link_libraries(atrv_jr_qt
  Qt5::Core
  Qt5::Quick
  Qt5::Widgets
)

install(TARGETS
  atrv_jr_qt
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY src
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
