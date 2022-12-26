cmake_minimum_required(VERSION 3.5)
project(happymimi_bringup2)

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
find_package(tf REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

#include_directories(launch/include)

# Megarover pub_odom.cpp node
set(dependencies
  "rclcpp"
  "tf"
  "nav_msgs"
  "geometry_msgs"
)

find_package(rmw_implementation REQUIRED)
find_package(std_msgs REQUIRED)
find_package(tf2 REQUIRED)

include_directories(${rclcpp_INCLUDE_DIRS}
                    ${rmw_implementation_INCLUDE_DIRS}
                    ${std_msgs_INCLUDE_DIRS}
		    ${tf_IMCLUDE_DIRS})

add_executable(mega_pub_odom src/pub_odom.cpp)
target_link_libraries(mega_pub_odom
                      ${rclcpp_LIBRARIES}
                      ${rmw_implementation_LIBRARIES}
                      ${std_msgs_LIBRARIES})
install(TARGETS mega_pub_odom DESTINATION lib/${PROJECT_NAME})

# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
>>>>>>> eeded87ded977b91f6eade8db80834b363d2546b
)
set(exec_name "pub_odom2")
add_executable(${exec_name} src/pub_odom2.cpp)
ament_target_dependencies(${exec_name} ${dependencies})
install(TARGETS ${exec_name}
  DESTINATION lib/${PROJECT_NAME})

# Directories
install(DIRECTORY config launch src
  DESTINATION share/${PROJECT_NAME}/)

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
