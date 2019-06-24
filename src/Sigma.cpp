#include "Sigma.h"
#include "/usr/include/dhdc.h"				//AMIT
#include "/usr/include/drdc.h"	

int *ID;
int  Run = 0;
Sigma::Sigma()
{

}

void* Sigma::gravity_process(void)
{
	// retrieve the device index as argument
	//int id = *((int*)arg);
	dhdEnableExpertMode ();
	// try and open requested dgevice
	for (int id=0;id<2;id++)
	{
		ID[id] = dhdOpenID (id);

		//printf ("error: cannot open device (%s)\n", dhdErrorGetLastStr());
		if (ID[id] < 0) {
			printf ("error: cannot open device (%s)\n", dhdErrorGetLastStr());
			Run = -1000;
			return NULL;
		}
		//		if(!drdIsInitialized(ID[id]))
		//		{
		//			dhdClose(ID[id]);
		//			drdOpenID(ID[id]);
		//			std::cout<<id<< " is not initialized"<<endl;
		//			drdAutoInit(ID[id]);
		//			drdClose(ID[id]);
		//			ID[id] = dhdOpenID(id);
		//		}
		dhdEnableForce (DHD_ON, ID[id]);
	}
	double oldGripForce = 0;
	// report that we are ready
	Run++;
	for (int id=0;id<2;id++)
	{
		//drdStart(ID[id]);
		//	drdRegulatePos  (lock_position,ID[id]);
		//	drdRegulateRot  (lock_orientation,ID[id]);
		//	drdRegulateGrip (lock_grasp,ID[id]);
		dhdSetForceAndTorqueAndGripperForce (0.0, 0.0, 0.0,  // force
				0.0, 0.0, 0.0,  // torque
				0.0,ID[id]);
	}
	// enable force

	// haptic loop
	while (ros::ok())
	{
		for (int id=0;id<2;id++)
		{
//			if (!update_force)
//			{
//				if (dhdSetForceAndTorqueAndGripperForce (0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, ID[id]) < DHD_NO_ERROR)
//				{
//					printf ("error: cannot set force (%s)\n", dhdErrorGetLastStr());
//					Run = 0;
//				}
//			}
//			else
//			{
				// MAKE SURE FORCES ARE NORMALIZED AND DO NOT EXCEED MAXIMUM FORCE
				double normf;
				if ((normf = force[id].length()) > MAXF) force[id] *= MAXF/normf;
//				double normt;
//				if (( normt = torque[id].length()) > MAXT) torque[id] *= MAXT/normt;

				if (grip_force[id] >  MAXG) grip_force[id] =  MAXG;
				if (grip_force[id] < -MAXG) grip_force[id] = -MAXG;

				if (dhdSetForceAndTorqueAndGripperForce (double(force[id].x()), double(force[id].y()), double(force[id].z()),double(torque[id].x()), double(torque[id].y()), double(torque[id].z()), double(grip_force[id]),ID[id])<DHD_NO_ERROR)
					ROS_INFO("error: cannot set force");
//				update_force = false;
//			}
		}
	}
	// close the connection
	for (int id=0;id<2;id++)
		dhdClose (ID[id]);
	// report that we are done
	Run--;
	return NULL;
}

void* Sigma::haptic_process(void){


	for (int id=0;id<2;id++)
	{
		dhdGetPosition (&px[id], &py[id], &pz[id], ID[id]);
		dhdGetGripperAngleRad(&gripper[id],ID[id]);
		if(id==0)
			dhdGetOrientationFrame(orimat0,ID[id]);
		else
			dhdGetOrientationFrame(orimat1,ID[id]);
	}
	while (ros::ok()) {
		for (int id=0;id<2;id++)
		{
			prevx[id]=px[id];
			prevy[id]=py[id];
			prevz[id]=pz[id];
			prevgripper[id]=gripper[id];
			// display some info on the currently selected device
			dhdGetPosition (&px[id], &py[id], &pz[id], ID[id]);
			position[id].setValue(px[id],py[id],pz[id]);
//			if(id == 1)
//			{
//				px[id]=-px[id];
//				py[id]=-py[id];
//			}
			//pz[id]=-pz[id];
			dhdGetGripperAngleRad(&gripper[id],ID[id]);
			if(id==0)
				dhdGetOrientationFrame(orimat0,ID[id]);
			else
				dhdGetOrientationFrame(orimat1,ID[id]);

			prev_ori[0]=curr_ori[0];
			prev_ori[1]=curr_ori[1];
			curr_ori[0].setValue(orimat0[0][0],orimat0[0][1],orimat0[0][2],orimat0[1][0],orimat0[1][1],orimat0[1][2],orimat0[2][0],orimat0[2][1],orimat0[2][2]);
			curr_ori[1].setValue(orimat1[0][0],orimat1[0][1],orimat1[0][2],orimat1[1][0],orimat1[1][1],orimat1[1][2],orimat1[2][0],orimat1[2][1],orimat1[2][2]);

			// printf ("[%d] %s:  p (%+0.03f %+0.03f %+0.03f) m  |  freq [%0.02f kHz]\r", id, dhdGetSystemName(ID[0]), px, py, pz, dhdGetComFreq (ID[id]));
			dhdGetJointAngles     (jointAngle);
			dhdGetJointVelocities (jointVelocity);
			double vx,vy,vz;
			double wx,wy,wz;
			dhdGetLinearVelocity (&vx,&vy,&vz,ID[id]);
			dhdGetAngularVelocityRad (&wx,&wy,&wz,ID[id]);
			dhdGetGripperLinearVelocity(&velgripper[id],ID[id]);

			velposition[id].setValue(vx,vy,vz);
			velorientation[id].setValue(wx,wy,wz);

		}
		//publish_haptic_msg(pz,px,py,gripper,orimat0,orimat1);
		publish_haptic_msg(px,py,pz,gripper,orimat0,orimat1);

	}

	// happily exit
	printf("\ndone HAPtiC\n");
	return 0;
	for (int id=0;id<2;id++)
		dhdClose (ID[id]);
}

void Sigma::callback_sigma(std_msgs::Float32 msg)
{
	// (1) save the updated raven_state
	force_feedback = true;
	if(!msg_proc)
	{
		msg_new = true;
		gripForce[0] = msg.data;
		gripForce[1] = msg.data;
	}
	//	dhdSetForceAndGripperForce(0,0,0,msg.data,0);
	//	std::cout<<msg.data<<"\r";
	// (2) update recieved data count
	SUB_COUNT ++;
}
void Sigma::callback_haptic(haptic_commands msg)
{
	// (1) save the updated raven_state
	//ROS_INFO("haptic callback");
	lock_orientation = msg.lock_orientation;
	lock_grasp = msg.lock_grasp;
	lock_position = msg.lock_position;
	force[0].setValue(msg.force[0],msg.force[1],msg.force[2]);
	force[1].setValue(msg.force[3],msg.force[4],msg.force[5]);
	torque[0].setValue(msg.torque[0],msg.torque[1],msg.torque[2]);
	torque[1].setValue(msg.torque[3],msg.torque[4],msg.torque[5]);
	grip_force[0] = msg.grip_force[0];
	grip_force[1] = msg.grip_force[1];
	update_force = true;

}
void Sigma::initial(int argc, char** argv)
{
	init_sys();
	if(!init_ros(argc,argv))
	{
		ROS_ERROR("Fail to initialize ROS. Exiting!");
		exit(1);
	}
	init_haptic();
}
void Sigma::init_sys()
{
	this->PUB_COUNT = 0;
	this->SUB_COUNT = 0;
	this->force_feedback = false;
}
void Sigma::init_haptic()
{
	// globals




	int    count;


	// message
	int major, minor, release, revision;
	dhdGetSDKVersion (&major, &minor, &release, &revision);
	printf ("\n");
	printf ("Force Dimension - Multi-threaded Gravity Compensation Example %d.%d.%d.%d\n", major, minor, release, revision);
	printf ("(C) 2001-2018 Force Dimension\n");
	printf ("All Rights Reserved.\n\n");

	// check for devices (limit to 10 devices)
	//count = MIN(10, dhdGetDeviceCount ());
	count = dhdGetDeviceCount();
	if (count < 1) {
		printf ("error: no device detected\n");
		dhdSleep (2.0);
		return;
	}

	// allocate resources and start threads
	printf ("starting %d threads\n\n", count);
	ID = new int[count];
	for (int i=0; i<count; i++ ) {
		ID[i] = i;
		// dhdStartThread (GravityThread, &(ID[i]), DHD_THREAD_PRIORITY_HIGH);
	}

	// wait for all threads to start (each thread increments the 'Run' variable by 1 when ready)
	//while (Run >= 0 && Run < count) dhdSleep (0.1);
	if (Run < 0) {
		printf ("error: thread launch failed\n");
		return;
	}

	// identify each device
	for (int i=0;i <count; i++) printf ("[%d] %s device detected\n", i, dhdGetSystemName(ID[i]));
	printf ("\n");

	// display instructions
	printf ("press 'q' to quit\n");
	printf ("      [0..9] to select display device\n\n");

	// UI thread (default priority)

}

bool Sigma::init_ros(int argc, char** argv)
{
	//initialize ROS
	ros::init(argc, argv, "autocircle_generator");

	static ros::NodeHandle n;

	sigma_subscriber = n.subscribe("chatter",1,&Sigma::callback_sigma,this);
	haptic_subscriber = n.subscribe("haptic_commands",1,&Sigma::callback_haptic,this);

	sigma_publisher = n.advertise<haptic_device>("haptic_msg", 1);
	return true;
}
void Sigma::start_thread()
{
	pthread_create(&gravity_thread,NULL,Sigma::static_gravity_process,this);
	pthread_create(&haptic_thread,NULL,Sigma::static_haptic_process,this);

}
void Sigma::join_thread()
{
	pthread_join(gravity_thread,NULL);
	pthread_join(haptic_thread,NULL);
}

void * Sigma::static_gravity_process(void* classRef)
{
	return ((Sigma *)classRef)->gravity_process();
}
void * Sigma::static_haptic_process(void* classRef)
{
	return ((Sigma *)classRef)->haptic_process();
}
void Sigma::publish_haptic_msg(double px[2], double py[2], double pz[2], double gripper[2], double orientation0[3][3], double orientation1[3][3])
{
	static ros::Rate loop_rate(1000);
	static haptic_device msg_haptic_msg;
	// (1) wrap up the new command
	//TODO add the second haptic device as well
	msg_haptic_msg.position[0] = px[0];
	msg_haptic_msg.position[1] = py[0];
	msg_haptic_msg.position[2] = pz[0];
	msg_haptic_msg.position[3] = px[1];
	msg_haptic_msg.position[4] = py[1];
	msg_haptic_msg.position[5] = pz[1];
	msg_haptic_msg.gripper[0] = gripper[0];
	msg_haptic_msg.gripper[1] = gripper[1];
//	msg_haptic_msg.vel_position[0]=velposition[0][0];
//	msg_haptic_msg.vel_position[1]=velposition[0][1];
//	msg_haptic_msg.vel_position[2]=velposition[0][2];
//	msg_haptic_msg.vel_position[3]=velposition[1][0];
//	msg_haptic_msg.vel_position[4]=velposition[1][1];
//	msg_haptic_msg.vel_position[5]=velposition[1][2];
//	msg_haptic_msg.vel_orientation[0]=velorientation[0][0];
//	msg_haptic_msg.vel_orientation[1]=velorientation[0][1];
//	msg_haptic_msg.vel_orientation[2]=velorientation[0][2];
//	msg_haptic_msg.vel_orientation[3]=velorientation[1][0];
//	msg_haptic_msg.vel_orientation[4]=velorientation[1][1];
//	msg_haptic_msg.vel_orientation[5]=velorientation[1][2];
//	msg_haptic_msg.vel_gripper[0]=velgripper[0];
//	msg_haptic_msg.vel_gripper[1]=velgripper[1];



	int i = 0;
	for (int m=0;m<2;m++)
	{
		msg_haptic_msg.vel_gripper[m]=velgripper[m];
		for (int n=0;n<3;n++)
		{
			msg_haptic_msg.vel_position[i]=velposition[m][n];
			msg_haptic_msg.vel_orientation[i]=velorientation[m][n];
			i++;
		}
	}

	i = 0;
	for(int m=0;m<3;m++)
		for(int n=0;n<3;n++)
		{
			msg_haptic_msg.orientation[i] = orientation0[m][n];

			i++;
		}
	for(int m=0;m<3;m++)
		for(int n=0;n<3;n++)
		{
			msg_haptic_msg.orientation[i] = orientation1[m][n];

			i++;
		}

	// (2) send new command
	sigma_publisher.publish(msg_haptic_msg);
	ros::spinOnce();

	//(3) prepare for next publish
	loop_rate.sleep();
	//PUB_COUNT ++;
}

