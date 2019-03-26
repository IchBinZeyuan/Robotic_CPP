# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "gruppe3: 2 messages, 0 services")

set(MSG_I_FLAGS "-Igruppe3:/home/ge34caj/catkin_ws_test/src/gruppe3/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/kinetic/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(gruppe3_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/ge34caj/catkin_ws_test/src/gruppe3/msg/signal_robot.msg" NAME_WE)
add_custom_target(_gruppe3_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "gruppe3" "/home/ge34caj/catkin_ws_test/src/gruppe3/msg/signal_robot.msg" "geometry_msgs/Pose2D"
)

get_filename_component(_filename "/home/ge34caj/catkin_ws_test/src/gruppe3/msg/signal_transfer.msg" NAME_WE)
add_custom_target(_gruppe3_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "gruppe3" "/home/ge34caj/catkin_ws_test/src/gruppe3/msg/signal_transfer.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(gruppe3
  "/home/ge34caj/catkin_ws_test/src/gruppe3/msg/signal_robot.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose2D.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/gruppe3
)
_generate_msg_cpp(gruppe3
  "/home/ge34caj/catkin_ws_test/src/gruppe3/msg/signal_transfer.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/gruppe3
)

### Generating Services

### Generating Module File
_generate_module_cpp(gruppe3
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/gruppe3
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(gruppe3_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(gruppe3_generate_messages gruppe3_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ge34caj/catkin_ws_test/src/gruppe3/msg/signal_robot.msg" NAME_WE)
add_dependencies(gruppe3_generate_messages_cpp _gruppe3_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ge34caj/catkin_ws_test/src/gruppe3/msg/signal_transfer.msg" NAME_WE)
add_dependencies(gruppe3_generate_messages_cpp _gruppe3_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(gruppe3_gencpp)
add_dependencies(gruppe3_gencpp gruppe3_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS gruppe3_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(gruppe3
  "/home/ge34caj/catkin_ws_test/src/gruppe3/msg/signal_robot.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose2D.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/gruppe3
)
_generate_msg_eus(gruppe3
  "/home/ge34caj/catkin_ws_test/src/gruppe3/msg/signal_transfer.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/gruppe3
)

### Generating Services

### Generating Module File
_generate_module_eus(gruppe3
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/gruppe3
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(gruppe3_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(gruppe3_generate_messages gruppe3_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ge34caj/catkin_ws_test/src/gruppe3/msg/signal_robot.msg" NAME_WE)
add_dependencies(gruppe3_generate_messages_eus _gruppe3_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ge34caj/catkin_ws_test/src/gruppe3/msg/signal_transfer.msg" NAME_WE)
add_dependencies(gruppe3_generate_messages_eus _gruppe3_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(gruppe3_geneus)
add_dependencies(gruppe3_geneus gruppe3_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS gruppe3_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(gruppe3
  "/home/ge34caj/catkin_ws_test/src/gruppe3/msg/signal_robot.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose2D.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/gruppe3
)
_generate_msg_lisp(gruppe3
  "/home/ge34caj/catkin_ws_test/src/gruppe3/msg/signal_transfer.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/gruppe3
)

### Generating Services

### Generating Module File
_generate_module_lisp(gruppe3
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/gruppe3
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(gruppe3_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(gruppe3_generate_messages gruppe3_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ge34caj/catkin_ws_test/src/gruppe3/msg/signal_robot.msg" NAME_WE)
add_dependencies(gruppe3_generate_messages_lisp _gruppe3_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ge34caj/catkin_ws_test/src/gruppe3/msg/signal_transfer.msg" NAME_WE)
add_dependencies(gruppe3_generate_messages_lisp _gruppe3_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(gruppe3_genlisp)
add_dependencies(gruppe3_genlisp gruppe3_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS gruppe3_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(gruppe3
  "/home/ge34caj/catkin_ws_test/src/gruppe3/msg/signal_robot.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose2D.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/gruppe3
)
_generate_msg_nodejs(gruppe3
  "/home/ge34caj/catkin_ws_test/src/gruppe3/msg/signal_transfer.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/gruppe3
)

### Generating Services

### Generating Module File
_generate_module_nodejs(gruppe3
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/gruppe3
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(gruppe3_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(gruppe3_generate_messages gruppe3_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ge34caj/catkin_ws_test/src/gruppe3/msg/signal_robot.msg" NAME_WE)
add_dependencies(gruppe3_generate_messages_nodejs _gruppe3_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ge34caj/catkin_ws_test/src/gruppe3/msg/signal_transfer.msg" NAME_WE)
add_dependencies(gruppe3_generate_messages_nodejs _gruppe3_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(gruppe3_gennodejs)
add_dependencies(gruppe3_gennodejs gruppe3_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS gruppe3_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(gruppe3
  "/home/ge34caj/catkin_ws_test/src/gruppe3/msg/signal_robot.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Pose2D.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/gruppe3
)
_generate_msg_py(gruppe3
  "/home/ge34caj/catkin_ws_test/src/gruppe3/msg/signal_transfer.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/gruppe3
)

### Generating Services

### Generating Module File
_generate_module_py(gruppe3
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/gruppe3
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(gruppe3_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(gruppe3_generate_messages gruppe3_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ge34caj/catkin_ws_test/src/gruppe3/msg/signal_robot.msg" NAME_WE)
add_dependencies(gruppe3_generate_messages_py _gruppe3_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ge34caj/catkin_ws_test/src/gruppe3/msg/signal_transfer.msg" NAME_WE)
add_dependencies(gruppe3_generate_messages_py _gruppe3_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(gruppe3_genpy)
add_dependencies(gruppe3_genpy gruppe3_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS gruppe3_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/gruppe3)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/gruppe3
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(gruppe3_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(gruppe3_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/gruppe3)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/gruppe3
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(gruppe3_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(gruppe3_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/gruppe3)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/gruppe3
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(gruppe3_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(gruppe3_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/gruppe3)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/gruppe3
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(gruppe3_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(gruppe3_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/gruppe3)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/gruppe3\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/gruppe3
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(gruppe3_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(gruppe3_generate_messages_py geometry_msgs_generate_messages_py)
endif()
