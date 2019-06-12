#include <assert.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>

#include <ros/ros.h>
#include <tf/transform_datatypes.h>
#include <tf2/LinearMath/Transform.h>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <visualization_msgs/Marker.h>

#include "fiducial_msgs/Fiducial.h"
#include "fiducial_msgs/FiducialArray.h"
#include "fiducial_msgs/FiducialTransform.h"
#include "fiducial_msgs/FiducialTransformArray.h"

#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>


#include <list>
#include <string>

using namespace std;
using namespace cv;

ros::Publisher pub;
tf::Transform transf;

// Convert "/fiducial_transforms" of type "FiducialTransformArray" to "/tf's"
void transformCallback(const fiducial_msgs::FiducialTransformArray::ConstPtr& msg)
{
	
    for (int i=0; i<msg->transforms.size(); i++) {
        const fiducial_msgs::FiducialTransform &ft = msg->transforms[i];

	    static tf2_ros::TransformBroadcaster br;
	    geometry_msgs::TransformStamped transformStamped;

	    transformStamped.header.stamp = ros::Time::now();
	    transformStamped.header.frame_id = "global_camera";
	    transformStamped.child_frame_id = "fid_" + to_string(ft.fiducial_id);
	    transformStamped.transform.translation.x = ft.transform.translation.x;
	    transformStamped.transform.translation.y = ft.transform.translation.y;
	    transformStamped.transform.translation.z = ft.transform.translation.z;

	    transformStamped.transform.rotation.x = ft.transform.rotation.x;
	    transformStamped.transform.rotation.y = ft.transform.rotation.y;
	    transformStamped.transform.rotation.z = ft.transform.rotation.z;
	    transformStamped.transform.rotation.w = ft.transform.rotation.w;

	    br.sendTransform(transformStamped);
    }
}

int main(int argc, char ** argv) {

  /* This node is responsible for converting all 'FiducialTransform' contained
   * in '/fiducial_transforms' of type 'FiducialTransformArray' and converts than 
   * to 'tf's.
   */
  ros::init(argc, argv, "fiducial_tf");
  ROS_INFO("Fiducial TF running!");
  ros::NodeHandle node;
  ros::Subscriber sub = node.subscribe("/fiducial_transforms", 1, &transformCallback);

  ros::spin();
    return 0;
}
