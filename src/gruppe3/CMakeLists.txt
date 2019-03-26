cmake_minimum_required(VERSION 2.8.3)
project(gruppe3)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  genmsg
  geometry_msgs
  nav_msgs
  cv_bridge
  image_transport
  sensor_msgs
  message_generation
)
find_package(OpenCV REQUIRED COMPONENTS
  core
  highgui
  imgproc
)
find_package(Boost COMPONENTS system filesystem REQUIRED)
add_message_files(
   FILES
   signal_transfer.msg
   signal_robot.msg)

generate_messages(
 
 DEPENDENCIES
 std_msgs
 geometry_msgs
)

catkin_package(

  CATKIN_DEPENDS  roscpp  std_msgs message_runtime
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend tag for "message_generation"
##   * add a build_depend and a exec_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependency has been pulled in
##     but can be declared for certainty nonetheless:
##     * add a exec_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   std_msgs
# )

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a exec_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES my_turtle
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_LIBRARIES}
)

## Declare a C++ library
# add_library(${PROJECT_NAME}
#   src/${PROJECT_NAME}/my_turtle.cpp
# )

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
# add_executable(${PROJECT_NAME}_node src/my_turtle_node.cpp)

## Rename C++ executable without prefix
## The above recommended prefix causes long target names, the following renames the
## target back to the shorter version for ease of user use
## e.g. "rosrun someones_pkg node" instead of "rosrun someones_pkg someones_pkg_node"
# set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
 #target_link_libraries(${PROJECT_NAME}_node
  # ${catkin_LIBRARIES}
  #${OpenCV_LIBRARIES}
 #)

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_my_turtle.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
#generate_messages(
#   DEPENDENCIES
#   std_msgs
# )

include_directories(/usr/include/eigen3/)
include_directories(~/catkin_ws_test/src/gruppe3/include/)
include_directories(${Boost_INCLUDE_DIRS})

#add_library(run_game2_lib member/run_game2_member.cpp)
#target_link_libraries(run_game2_lib ${catkin_LIBRARIES} ${roscpp_LIBRARIES} ${OpenCV_LIBRARIES})
#set_target_properties(run_game2_lib PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

#add_executable(run_game2_test src/run_game2.cpp src/lidar_main.cpp src/clear_angle.cpp
#        src/clear_area.cpp src/clear_average.cpp src/find_tangent.cpp
#        src/find_colinear.cpp src/sort_lines.cpp src/find_ortho.cpp src/create_map.cpp
#        src/PredictPoints.cpp src/cal_coordinate.cpp src/find_b.cpp src/file_descriptor.cpp
#        src/predict2.cpp src/find_poles.cpp src/trans_coordinate.cpp src/find_path.cpp 
#	src/move_para.cpp src/find_ball.cpp src/line_fitting.cpp src/trans_x_y.cpp
#        src/trans_c_o.cpp src/trans_o_c.cpp)
#target_link_libraries(run_game2_test ${catkin_LIBRARIES})
#target_link_libraries(run_game2_test run_game2_lib)

#add_executable(run_game1 src/run_game1.cpp src/lidar_main.cpp src/clear_angle.cpp
#        src/clear_area.cpp src/clear_average.cpp src/find_tangent.cpp
#        src/find_colinear.cpp src/sort_lines.cpp src/find_ortho.cpp src/create_map.cpp
#        src/PredictPoints.cpp src/cal_coordinate.cpp src/find_b.cpp src/file_descriptor.cpp
#        src/predict2.cpp src/find_poles.cpp src/trans_coordinate.cpp src/find_path.cpp 
#	src/move_para.cpp src/find_ball.cpp src/line_fitting.cpp src/trans_x_y.cpp
#        src/trans_c_o.cpp src/trans_o_c.cpp)
#target_link_libraries(run_game1 ${catkin_LIBRARIES})
#target_link_libraries(run_game1 run_game2_lib)

#add_executable(anti_bump src/anti_bump.cpp)
#target_link_libraries(anti_bump ${catkin_LIBRARIES})



add_executable(test_odom src/test_odom.cpp)
target_link_libraries(test_odom ${catkin_LIBRARIES})

#add_executable(move_odometry src/move_odometry.cpp)
#target_link_libraries(move_odometry ${catkin_LIBRARIES})
#add_dependencies(move_odometry my_turtle_cpp)

#add_executable(test_move src/test_move.cpp)
#target_link_libraries(test_move ${catkin_LIBRARIES})
#add_dependencies(test_move my_turtle_cpp)

#add_executable(test_odom src/test_odom.cpp)
#target_link_libraries(test_odom ${catkin_LIBRARIES})
#add_dependencies(test_odom my_turtle_cpp)

#add_executable(move_odom src/move_odom.cpp)
#target_link_libraries(move_odom ${catkin_LIBRARIES})
#add_dependencies(move_odom my_turtle_cpp)

#add_executable(synthesis src/synthesis.cpp src/lidar_main.cpp
#        src/clear_angle.cpp src/clear_average.cpp src/find_tangent.cpp
#        src/find_colinear.cpp src/sort_lines.cpp src/find_ortho.cpp src/create_map.cpp
#        src/PredictPoints.cpp src/cal_coordinate.cpp src/find_b.cpp src/file_descriptor.cpp
#        src/predict2.cpp src/find_poles.cpp src/trans_coordinate.cpp src/find_path.cpp )
#target_link_libraries(synthesis ${catkin_LIBRARIES})
#target_link_libraries(synthesis ${OpenCV_LIBRARIES})
#target_link_libraries(synthesis ${Boost_LIBRARIES})
#add_dependencies(synthesis my_turtle_cpp)

# add_executable(laser laser_main.cpp
#         clear_angle.cpp load_data.cpp clear_average.cpp find_tangent.cpp find_colinear.cpp sort_lines.cpp find_ortho.cpp create_map.cpp PredictPoints.cpp)
# target_link_libraries(laser ${catkin_LIBRARIES})
# add_dependencies(laser my_turtle_cpp)

