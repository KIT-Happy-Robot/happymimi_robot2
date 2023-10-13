cmake_minimum_required(VERSION 3.5)
project(happymimi_bringup_ros2)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(xacro REQUIRED)
find_package(rmw_implementation REQUIRED)

include_directories(launch/include)
#include_directories(${rclcpp_INCLUDE_DIRS}
#                    ${rmw_implementation_INCLUDE_DIRS}
#                    ${std_msgs_INCLUDE_DIRS}
#		                ${tf_IMCLUDE_DIRS})

# Megarover pub_odom.cpp node
set(dependencies
  rclcpp
  tf2
  tf2_ros
  tf2_geometry_msgs
  nav_msgs
  geometry_msgs
)

#include_directories(${rclcpp_INCLUDE_DIRS}
#                    ${rmw_implementation_INCLUDE_DIRS}
#                    ${std_msgs_INCLUDE_DIRS}
#		                ${tf_IMCLUDE_DIRS}
#)

add_executable(pub_odom src/pub_odom.cpp)
ament_target_dependencies(pub_odom ${dependencies})
install(TARGETS pub_odom
  DESTINATION lib/${PROJECT_NAME})

#install(TARGETS launch rviz config 
#  DESTINATION share/${PROJECT_NAME})

# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
install(DIRECTORY
  src launch config rviz
  DESTINATION share/${PROJECT_NAME}/
)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
