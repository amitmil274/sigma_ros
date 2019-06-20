#ifndef SIGMA_H_
#define SIGMA_H_

#include "/usr/include/dhdc.h"				//AMIT
#include "/usr/include/drdc.h"				//AMIT
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include <tf/transform_datatypes.h>
#include <stdio.h>
#include <iomanip>
#include <ros/ros.h>
#include <ros/ros.h>
#include <ros/transport_hints.h>
#include <sstream>
#include <pthread.h>
#include <termios.h>
#include <queue>
#include "std_msgs/Float32.h"
#include "sigma_ros/haptic_device.h"
#include "sigma_ros/haptic_commands.h"
#include <math.h>

# define M_PI           3.14159265358979323846  /* pi */
using namespace sigma_ros;
using namespace std;

#define KP    100.0
#define KVP    10.0
#define MAXF    4.0
#define KR      0.3
#define KWR     0.02
#define MAXT    0.1
#define KG    100.0
#define KVG     5.0
#define MAXG    1.0

class Sigma
{
	private:
		int PUB_COUNT;
		int SUB_COUNT;
		bool SHOW_STATUS;
		bool RECEIVED_FIRST;
		bool PAUSE;
		bool force_feedback = false;
		pthread_t console_thread;
		pthread_t ros_thread;
		pthread_t gravity_thread;
		pthread_t haptic_thread;
		std_msgs::Float32 force_sensor_data;
		ros::Publisher sigma_publisher;
		ros::Subscriber sigma_subscriber;
		ros::Subscriber haptic_subscriber;

		bool msg_new = false;
		bool msg_proc = false;

		bool lock_position = false;
		bool lock_orientation  = false;
		bool lock_grasp  = false;

		  const double Kj[DHD_MAX_DOF] = { 3.0, 3.0, 3.0,
		                                   4.0, 3.0, 1.0,    // locked wrist joint stiffness (in Nm/rad)
		                                   1.0,
		                                   0.0 };

		  // regulation viscosity
		  const double Kv[DHD_MAX_DOF] = { 2.0, 2.0, 2.0,
		                                   0.04, 0.03, 0.01, // locked wrist joint viscosity (in Nm/(rad/s))
		                                   2.0,
		                                   0.0 };

		  double jointAngle[DHD_MAX_DOF];
		  double jointVelocity[DHD_MAX_DOF];
		  double jointAngleTarget[DHD_MAX_DOF];
		  double jointTorque[DHD_MAX_DOF];
		  bool   lock[DHD_MAX_DOF];

		  double px[2]={0,0};
		  	double py[2]={0,0};
		  	double pz[2]={0,0};
			  double fX[2]={0,0};
			  	double fY[2]={0,0};
			  	double fZ[2]={0,0};
			  	double prevx[2]={0,0};
			  	double prevy[2]={0,0};
			  	double prevz[2]={0,0};

		  	double gripper[2]={0,0};
		  	double prevgripper[2]={0,0};
		  	double fGripper[2]={0,0};

		  	double orimat0[3][3];
		  	double orimat1[3][3];
		  	tf::Matrix3x3 curr_ori[2];
			tf::Matrix3x3 prev_ori[2];
			tf::Vector3 force[2];
			tf::Vector3 torque[2];
			tf::Vector3 position[2];
			tf::Vector3 velposition[2];
			tf::Vector3 velorientation[2];
			tfScalar velgripper[2];

		//  double transForce[6];
		double gripForce[2];
	public:
		Sigma();		// constructor
		void initial(int, char**);	// initialization and console display
		void init_sys();
		bool init_ros(int, char**);
		void init_words();
		bool menu_words(bool);
		void final_words();

		void start_thread();		// thread management
		void join_thread();
		void *console_process(void);
		void *ros_process(void);
		static void *static_console_process(void*);
		static void *static_ros_process(void*);

		void publish_sigma();			 // ROS publish
		void callback_sigma(std_msgs::Float32 msg); // ROS subscribe
		void callback_haptic(haptic_commands); // ROS subscribe

		void output_STATUS();		// show ROS and raven state
		void output_PUBinfo();
		void output_SUBinfo();

		int getKey();

		void init_haptic();			//AMIT
		void *gravity_process(void); 	//AMIT
		void *haptic_process(void); 	//AMIT
		static void *static_haptic_process(void*);
		static void *static_gravity_process(void*);
		void publish_haptic_msg(double px[2], double py[2], double pz[2], double gripper[2], double orientation0[3][3], double orientation1[3][3]);

}; //end of class definition

#endif
