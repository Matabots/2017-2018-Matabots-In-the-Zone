/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Locomotion.h
 * Author: nathan
 *
 * Created on March 28, 2017, 8:26 PM
 */

#ifndef LOCOMOTION_H
#define LOCOMOTION_H


namespace robot
{
    //properties of the encoders.
    typedef struct
    {
            int currTick;
            int prevTick;
            float gearRatio;
    }Encoder;

    //different states in FSM state machine
    typedef enum 
    {
            Start,
            IdleRobot,
            FindObj,
            GoToObj,
            GrabObj,
            UpdateMap,
            GoToFence,
            Score
    }States;
    
    //Subcommands that happen in the main state machine. Pertain to smaller functions like moving the claw.
    enum SubStates
    {
            IdleClaw,
            OpenClaw,
            CloseClaw,
            LiftClaw,
            ScoreClaw
    };
    
    //the phase of the robot. 
    enum Phase
    {
            Instruction, //go to predefined points
            Find //search for objects
    };
    
    //motors and their corresponding ports
    enum  motors
    {
         claw = 0,
        leftFront = 1,
        leftTop = 2,
        leftBack = 3,
       liftBottom = 4,
        liftTop = 5,
         rightTop = 6,
        rightFront = 7,
         rightBack= 8,
        claw2 = 9
    };

}

#endif /* LOCOMOTION_H */

