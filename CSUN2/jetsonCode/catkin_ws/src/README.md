# -Definitely-Not-CSUN-Vex-Robotics-Global-Offensive

2015-2016 CSUN Vex Robotics Repository: https://github.com/kpjoyce1/Definitely-Not-Csun-Matabots-Robotcs-2015

This repository will be the primary location for the code development for the CSUN Vex Robotics Team Matabots.

Sensors
-------
encoders
Yost
kinect
potentiometers

Things that are done
--------------------
Yost-Sensor working
Encoder reading
analog read potentiometer
way of serial motor powers from arduino to cortex
drivers working for kinect and cuda

Things that need to happen
--------------------------
Get good
rewrite object detection make sure it runs at 30Hz
ROS wrappers for programs (its a server, and umm we  are just gonna use it
                           ... and it will be amazing)
state machine
integration


Magical Things That We Would Love
---------------------------------
Localization



ROS Services
------------
#Object Detection Service
-identify object objects using kinect and opencv
-Publish object locations to roscore

#Position Service
-Take data from cereal for lift, drive, and orientation
-Publish object locations to roscore

#Cognition Service
-Take the published data from position service and add logic for when power is applied
-Send powers to cortex


