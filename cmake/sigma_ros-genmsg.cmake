# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "sigma_ros: 2 messages, 0 services")

set(MSG_I_FLAGS "-Isigma_ros:/home/bgusigma/amit_raven/src/sigma_ros/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/kinetic/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(sigma_ros_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/bgusigma/amit_raven/src/sigma_ros/msg/haptic_device.msg" NAME_WE)
add_custom_target(_sigma_ros_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "sigma_ros" "/home/bgusigma/amit_raven/src/sigma_ros/msg/haptic_device.msg" ""
)

get_filename_component(_filename "/home/bgusigma/amit_raven/src/sigma_ros/msg/haptic_commands.msg" NAME_WE)
add_custom_target(_sigma_ros_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "sigma_ros" "/home/bgusigma/amit_raven/src/sigma_ros/msg/haptic_commands.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(sigma_ros
  "/home/bgusigma/amit_raven/src/sigma_ros/msg/haptic_device.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/sigma_ros
)
_generate_msg_cpp(sigma_ros
  "/home/bgusigma/amit_raven/src/sigma_ros/msg/haptic_commands.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/sigma_ros
)

### Generating Services

### Generating Module File
_generate_module_cpp(sigma_ros
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/sigma_ros
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(sigma_ros_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(sigma_ros_generate_messages sigma_ros_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/bgusigma/amit_raven/src/sigma_ros/msg/haptic_device.msg" NAME_WE)
add_dependencies(sigma_ros_generate_messages_cpp _sigma_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bgusigma/amit_raven/src/sigma_ros/msg/haptic_commands.msg" NAME_WE)
add_dependencies(sigma_ros_generate_messages_cpp _sigma_ros_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(sigma_ros_gencpp)
add_dependencies(sigma_ros_gencpp sigma_ros_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS sigma_ros_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(sigma_ros
  "/home/bgusigma/amit_raven/src/sigma_ros/msg/haptic_device.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/sigma_ros
)
_generate_msg_eus(sigma_ros
  "/home/bgusigma/amit_raven/src/sigma_ros/msg/haptic_commands.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/sigma_ros
)

### Generating Services

### Generating Module File
_generate_module_eus(sigma_ros
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/sigma_ros
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(sigma_ros_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(sigma_ros_generate_messages sigma_ros_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/bgusigma/amit_raven/src/sigma_ros/msg/haptic_device.msg" NAME_WE)
add_dependencies(sigma_ros_generate_messages_eus _sigma_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bgusigma/amit_raven/src/sigma_ros/msg/haptic_commands.msg" NAME_WE)
add_dependencies(sigma_ros_generate_messages_eus _sigma_ros_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(sigma_ros_geneus)
add_dependencies(sigma_ros_geneus sigma_ros_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS sigma_ros_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(sigma_ros
  "/home/bgusigma/amit_raven/src/sigma_ros/msg/haptic_device.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/sigma_ros
)
_generate_msg_lisp(sigma_ros
  "/home/bgusigma/amit_raven/src/sigma_ros/msg/haptic_commands.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/sigma_ros
)

### Generating Services

### Generating Module File
_generate_module_lisp(sigma_ros
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/sigma_ros
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(sigma_ros_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(sigma_ros_generate_messages sigma_ros_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/bgusigma/amit_raven/src/sigma_ros/msg/haptic_device.msg" NAME_WE)
add_dependencies(sigma_ros_generate_messages_lisp _sigma_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bgusigma/amit_raven/src/sigma_ros/msg/haptic_commands.msg" NAME_WE)
add_dependencies(sigma_ros_generate_messages_lisp _sigma_ros_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(sigma_ros_genlisp)
add_dependencies(sigma_ros_genlisp sigma_ros_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS sigma_ros_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(sigma_ros
  "/home/bgusigma/amit_raven/src/sigma_ros/msg/haptic_device.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/sigma_ros
)
_generate_msg_nodejs(sigma_ros
  "/home/bgusigma/amit_raven/src/sigma_ros/msg/haptic_commands.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/sigma_ros
)

### Generating Services

### Generating Module File
_generate_module_nodejs(sigma_ros
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/sigma_ros
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(sigma_ros_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(sigma_ros_generate_messages sigma_ros_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/bgusigma/amit_raven/src/sigma_ros/msg/haptic_device.msg" NAME_WE)
add_dependencies(sigma_ros_generate_messages_nodejs _sigma_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bgusigma/amit_raven/src/sigma_ros/msg/haptic_commands.msg" NAME_WE)
add_dependencies(sigma_ros_generate_messages_nodejs _sigma_ros_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(sigma_ros_gennodejs)
add_dependencies(sigma_ros_gennodejs sigma_ros_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS sigma_ros_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(sigma_ros
  "/home/bgusigma/amit_raven/src/sigma_ros/msg/haptic_device.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/sigma_ros
)
_generate_msg_py(sigma_ros
  "/home/bgusigma/amit_raven/src/sigma_ros/msg/haptic_commands.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/sigma_ros
)

### Generating Services

### Generating Module File
_generate_module_py(sigma_ros
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/sigma_ros
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(sigma_ros_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(sigma_ros_generate_messages sigma_ros_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/bgusigma/amit_raven/src/sigma_ros/msg/haptic_device.msg" NAME_WE)
add_dependencies(sigma_ros_generate_messages_py _sigma_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bgusigma/amit_raven/src/sigma_ros/msg/haptic_commands.msg" NAME_WE)
add_dependencies(sigma_ros_generate_messages_py _sigma_ros_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(sigma_ros_genpy)
add_dependencies(sigma_ros_genpy sigma_ros_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS sigma_ros_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/sigma_ros)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/sigma_ros
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(sigma_ros_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(sigma_ros_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/sigma_ros)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/sigma_ros
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(sigma_ros_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(sigma_ros_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/sigma_ros)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/sigma_ros
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(sigma_ros_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(sigma_ros_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/sigma_ros)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/sigma_ros
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(sigma_ros_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(sigma_ros_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/sigma_ros)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/sigma_ros\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/sigma_ros
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(sigma_ros_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(sigma_ros_generate_messages_py geometry_msgs_generate_messages_py)
endif()
