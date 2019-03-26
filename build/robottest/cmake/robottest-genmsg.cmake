# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "robottest: 2 messages, 0 services")

set(MSG_I_FLAGS "-Irobottest:/home/ge34caj/catkin_ws_test/src/robottest/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/kinetic/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(robottest_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/ge34caj/catkin_ws_test/src/robottest/msg/signal_robot.msg" NAME_WE)
add_custom_target(_robottest_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "robottest" "/home/ge34caj/catkin_ws_test/src/robottest/msg/signal_robot.msg" "geometry_msgs/Pose2D"
)

get_filename_component(_filename "/home/ge34caj/catkin_ws_test/src/robottest/msg/signal_transfer.msg" NAME_WE)
add_custom_target(_robottest_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "robottest" "/home/ge34caj/catkin_ws_test/src/robottest/msg/signal_transfer.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(robottest
  "/home/ge34caj/catkin_ws_test/src/robottest/msg/signal_robot.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose2D.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robottest
)
_generate_msg_cpp(robottest
  "/home/ge34caj/catkin_ws_test/src/robottest/msg/signal_transfer.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robottest
)

### Generating Services

### Generating Module File
_generate_module_cpp(robottest
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robottest
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(robottest_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(robottest_generate_messages robottest_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ge34caj/catkin_ws_test/src/robottest/msg/signal_robot.msg" NAME_WE)
add_dependencies(robottest_generate_messages_cpp _robottest_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ge34caj/catkin_ws_test/src/robottest/msg/signal_transfer.msg" NAME_WE)
add_dependencies(robottest_generate_messages_cpp _robottest_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(robottest_gencpp)
add_dependencies(robottest_gencpp robottest_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS robottest_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(robottest
  "/home/ge34caj/catkin_ws_test/src/robottest/msg/signal_robot.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose2D.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robottest
)
_generate_msg_eus(robottest
  "/home/ge34caj/catkin_ws_test/src/robottest/msg/signal_transfer.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robottest
)

### Generating Services

### Generating Module File
_generate_module_eus(robottest
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robottest
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(robottest_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(robottest_generate_messages robottest_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ge34caj/catkin_ws_test/src/robottest/msg/signal_robot.msg" NAME_WE)
add_dependencies(robottest_generate_messages_eus _robottest_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ge34caj/catkin_ws_test/src/robottest/msg/signal_transfer.msg" NAME_WE)
add_dependencies(robottest_generate_messages_eus _robottest_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(robottest_geneus)
add_dependencies(robottest_geneus robottest_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS robottest_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(robottest
  "/home/ge34caj/catkin_ws_test/src/robottest/msg/signal_robot.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose2D.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robottest
)
_generate_msg_lisp(robottest
  "/home/ge34caj/catkin_ws_test/src/robottest/msg/signal_transfer.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robottest
)

### Generating Services

### Generating Module File
_generate_module_lisp(robottest
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robottest
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(robottest_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(robottest_generate_messages robottest_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ge34caj/catkin_ws_test/src/robottest/msg/signal_robot.msg" NAME_WE)
add_dependencies(robottest_generate_messages_lisp _robottest_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ge34caj/catkin_ws_test/src/robottest/msg/signal_transfer.msg" NAME_WE)
add_dependencies(robottest_generate_messages_lisp _robottest_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(robottest_genlisp)
add_dependencies(robottest_genlisp robottest_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS robottest_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(robottest
  "/home/ge34caj/catkin_ws_test/src/robottest/msg/signal_robot.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose2D.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robottest
)
_generate_msg_nodejs(robottest
  "/home/ge34caj/catkin_ws_test/src/robottest/msg/signal_transfer.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robottest
)

### Generating Services

### Generating Module File
_generate_module_nodejs(robottest
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robottest
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(robottest_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(robottest_generate_messages robottest_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ge34caj/catkin_ws_test/src/robottest/msg/signal_robot.msg" NAME_WE)
add_dependencies(robottest_generate_messages_nodejs _robottest_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ge34caj/catkin_ws_test/src/robottest/msg/signal_transfer.msg" NAME_WE)
add_dependencies(robottest_generate_messages_nodejs _robottest_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(robottest_gennodejs)
add_dependencies(robottest_gennodejs robottest_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS robottest_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(robottest
  "/home/ge34caj/catkin_ws_test/src/robottest/msg/signal_robot.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose2D.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robottest
)
_generate_msg_py(robottest
  "/home/ge34caj/catkin_ws_test/src/robottest/msg/signal_transfer.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robottest
)

### Generating Services

### Generating Module File
_generate_module_py(robottest
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robottest
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(robottest_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(robottest_generate_messages robottest_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ge34caj/catkin_ws_test/src/robottest/msg/signal_robot.msg" NAME_WE)
add_dependencies(robottest_generate_messages_py _robottest_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ge34caj/catkin_ws_test/src/robottest/msg/signal_transfer.msg" NAME_WE)
add_dependencies(robottest_generate_messages_py _robottest_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(robottest_genpy)
add_dependencies(robottest_genpy robottest_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS robottest_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robottest)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robottest
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(robottest_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(robottest_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robottest)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robottest
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(robottest_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(robottest_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robottest)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robottest
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(robottest_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(robottest_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robottest)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robottest
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(robottest_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(robottest_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robottest)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robottest\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robottest
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(robottest_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(robottest_generate_messages_py geometry_msgs_generate_messages_py)
endif()
