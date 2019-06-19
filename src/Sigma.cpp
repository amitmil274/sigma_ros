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
		drdStart(ID[id]);
		drdRegulatePos  (lock_position,ID[id]);
		drdRegulateRot  (lock_orientation,ID[id]);
		drdRegulateGrip (lock_grasp,ID[id]);
		dhdSetForceAndTorqueAndGripperForce (0.0, 0.0, 0.0,  // force
				0.0, 0.0, 0.0,  // torque
				0.0,ID[id]);
	}
	// enable force

	// haptic loop
	while (ros::ok()) {
		//	if(!msg_new)
		if (!force_feedback)
		{
			for (int id=0;id<2;id++)
				if (dhdSetForceAndTorqueAndGripperForce (0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, ID[id]) < DHD_NO_ERROR)
				{
					printf ("error: cannot set force (%s)\n", dhdErrorGetLastStr());
					Run = 0;
				}
		}
		else
		{
			msg_new = false;
			//	msg_proc = true;
			for (int id=0;id<2;id++)
				if (dhdSetForceAndTorqueAndGripperForce (0.0, 0.0, 0.0, 0.0, 0.0, 0.0, gripForce[id]*2, ID[id]) < DHD_NO_ERROR);
			//		{
			//		printf ("error: cannot set force (%s)\n", dhdErrorGetLastStr());
			//		Run = 0;
			//		}
			//	msg_proc = false;
			//	oldGripForce = gripForce;
		}

		// retrieve wrist joints

		for (int id=0;id++;id<2)
		{
			force[id].setZero();
			torque[id].setZero();
			fGripper[id] = 0;
		}
		// compute joint torques as appropriate
		//		    for (int i=1; i<7; i++) {
		//		      if (lock[i])
		//		    	  jointTorque[i] = -Kj[i] * (jointAngle[i] - jointAngleTarget[i]) - Kv[i] * jointVelocity[i];
		//		      else
		//		    	  jointTorque[i] = 0.0;
		//		    }
		//
		//		    // apply as appropriate
		//		    int res = dhdSetForceAndWristJointTorquesAndGripperForce (jointTorque[0], jointTorque[1], jointTorque[2],
		//		                                                              jointTorque[3], jointTorque[4], jointTorque[5],
		//																	  jointTorque[6]);
		if (lock_position)
			for (int id=0;id++;id<2)
			{
				force[id] - KP * position[id];
				double normf;
				if ((normf = force[id].length()) > MAXF) force[id] *= MAXF/normf;
				force[id]  -= KVP * velposition[id];

				//	fX[id] = - KP * px[id];
				//fY[id] = - KP * py[id];
				//fZ[id] = - KP * pz[id];
			}

		if (lock_orientation)
			for (int id=0;id++;id<2)
			{
				tf::Quaternion qTemp;
				curr_ori[id].transpose().getRotation(qTemp);
				torque[id] = curr_ori[id] * (KR * qTemp.getAngle() * qTemp.getAxis());
				double normt;
				if (( normt = torque[id].length()) > MAXT) torque[id] *= MAXT/normt;
				torque[id] -= KWR * velorientation[id];
			}
		if (lock_grasp)
			for (int id=0;id++;id<2)
			{
				fGripper[id]  = - KG * (gripper[id] - 0.015);
				if (fGripper[id] >  MAXG) fGripper[id] =  MAXG;
				if (fGripper[id] < -MAXG) fGripper[id] = -MAXG;
				fGripper[id]   -= KVG * velgripper[id];

			}
		// compute wrist centering torque
		// AngleAxisd deltaRotation (rotation.transpose() * center);
		//  torque = rotation * (KR * deltaRotation.angle() * deltaRotation.axis());

		// compute gripper centering force


		// scale force to a pre-defined ceiling
		//if ((double normf = transForce[id].norm()) > MAXF) force *= MAXF/normf;

		// scale torque to a pre-defined ceiling
		//if ((normt = torque.norm()) > MAXT) torque *= MAXT/normt;

		// scale gripper force to a pre-defined ceiling
		//    if (f[6] >  MAXG) f[6] =  MAXG;
		//   if (f[6] < -MAXG) f[6] = -MAXG;

		// add damping
		// force  -= KVP * velposition[id];
		//  torque -= KWR * velrotation[id];
		//   fGripper[id]   -= KVG * v[6];

		// apply centering force with damping
		for (int id=0;id++;id<2)
			dhdSetForceAndTorqueAndGripperForce (force[id].x(), force[id].y(), force[id].z(),  // force
					torque[id].x(), torque[id].y(), torque[id].z(),  // torque
					fGripper[id],ID[id]);             // gripper force
		//		printf ("[%d] %s:  grip (%+0.03f) m  |  freq [%0.02f kHz]\r", id, dhdGetSystemName(ID[0]), gripForce, dhdGetComFreq (ID[id]));
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
			if(id == 1)
			{
				px[id]=-px[id];
				py[id]=-py[id];
			}
			pz[id]=-pz[id];
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
		publish_haptic_msg(pz,px,py,gripper,orimat0,orimat1);
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
	lock_orientation = msg.lock_orientation;
	if (lock_orientation)
	{
		lock[3] = lock[4] = lock[5] = true;
		for (int i=3; i<6; i++)
			jointAngleTarget[i] = jointAngle[i];
	}
	else
		lock[3] = lock[4] = lock[5] = false;

	lock_position = msg.lock_position;
	if (lock_position)
	{
		lock[0] = lock[1] = lock[2] = true;
		for (int i=0; i<3; i++)
			jointAngleTarget[i] = jointAngle[i];
	}
	else
		lock[0] = lock[1] = lock[2] = false;
	lock_grasp = msg.lock_grasp;
	if (lock_grasp)
	{
		lock[6] = true;
		jointAngleTarget[6] = jointAngle[6];
	}
	else
		lock[6] = false;

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
	int i = 0;
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

