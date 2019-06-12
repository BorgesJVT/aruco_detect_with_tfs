
cmake_minimum_required(VERSION 2.8.3)
project(aruco_detect_with_tfs)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  tf2_geometry_msgs
  tf2_ros
  tf2
  visualization_msgs
  image_transport
  cv_bridge
  sensor_msgs
  std_msgs
  fiducial_msgs
  dynamic_reconfigure
)

find_package(OpenCV REQUIRED)

generate_dynamic_reconfigure_options(cfg/DetectorParams.cfg)

catkin_package(INCLUDE_DIRS DEPENDS OpenCV)

###########
## Build ##
###########

add_definitions(-std=c++11)

include_directories(${catkin_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(aruco_detect_with_tfs src/aruco_detect_with_tfs.cpp)
add_executable(fiducial_tf src/fiducial_tf.cpp)

add_dependencies(aruco_detect_with_tfs ${${PROJECT_NAME}_EXPORTED_TARGETS}
                 ${catkin_EXPORTED_TARGETS})
add_dependencies(fiducial_tf ${${PROJECT_NAME}_EXPORTED_TARGETS}
                 ${catkin_EXPORTED_TARGETS})

target_link_libraries(aruco_detect_with_tfs ${catkin_LIBRARIES} ${OpenCV_LIBS})
target_link_libraries(fiducial_tf ${catkin_LIBRARIES} ${OpenCV_LIBS})


