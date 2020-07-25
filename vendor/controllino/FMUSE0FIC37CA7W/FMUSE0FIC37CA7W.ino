/*This document should end up as a short introduction to one particular method of sidestepping Accelstepper's somewhat low step-rate limit using default stepper.run() protocol. It is not the only and certainly not the best method. But it works.*/
//Extra note about the purpose: This lets you use the nice accelstepper acceleration algorithm for the initial acceleration and then a much cruder linear ramp thereafter. 
#include <AccelStepper.h> 

/* Accelstepper SetMotorIdentifier(TYPE, STEP, DIRECTION)  We are using type 1 because it's a classic stepper Driver. 
Different types might ask for things other than step&direction [see Accelsteppr documentation]*/

const int stepPin=23; 
const int directionPin=14;
AccelStepper stepper(1,stepPin,directionPin); 

long actuatorDistance = 158400;     //This varies depending on your purpose. I wanted to go 158,400 steps. That equated to 99 rotations of my 1.8 deg stepper motor with 1/8th microstepping.  
int actuatorSpeed=3900; //This corresponded to 487.5 steps/second, or 2.47 revs/second, which for me corresponding to about 40 seconds for my actuator. 

unsigned long actuatorTimeout =19000;  //This might not be used in the tutorial, but it's good to have a timeout threshold if you think your actuator might stall out and you want some backup timeout. 

int actuatorAcceleration=8500;  //This acceleration value was chosen by experimentation, and only corresponds to the initial actuatorSpeed trigger point - after that your linear acceleration takes over.

const byte programOverhead=26; //measured in mS. During the fast-stepping function you may want to check a few sensors (in my case, for an end-stop). The thing is you want your initial linear step-delay to be pretty close to whatever step rate the accelstepper actuatorSpeed was. For this to work, you need to know roughly how much time your control loop takes excluding the step delay. If your sketch is similar to mine in what it's checking, you can start with my numbers. 

const byte minPulseWidth=3; //different drivers require different mininum step pulses to register a line change...The basic reprap drivers are 1-2mS, this is sort of an unnecessary variable I used for extra fluff, you can probably do without it. 
 
//FINAL STEP RATE VALUE
byte stepDelayTarget=90-minPulseWidth-programOverhead; //Uhoh! This should never add up to <0. Check manually. 
//This number, here shown as 90, relates to your target final step max speed. 90 is in uS, so I went up to 1000,000/90 = 11,111.1.. steps/second.  That's an improvement over the default max of 3900 steps/seconds and as rate limited in my application by the physical system. I don't know how high you can expect an arduino to go. 


const int systemEndstop=24;       
   
const int enablePin=53;   //This is another extra variable I kept in the example code. You can ignore it, but it refers to a pin that is controlling the enable pin of my DRV8825 driver. Because it's 53 you can see I wrote this probably for an arduino mega. 

//Global variables as part of the program functions.
unsigned long timeStart; 
//We want to be able to reset Timestart in different parts of the program. It's a global variable redeclared by a number of functions. Be aware. Another 'extra variable' I kept in the example code. 

void setup(){ //Void setup runs once during initial boot of microprocessor, but not after. 
  
    stepper.setPinsInverted(false,false,true);   // setPinsInverted(bool Dir,bool Step,bool Enable) Bool enable is == true because my enable pin is OFF when HIGH and ON when LOW. This is opposite of the default, so we enable the invert function. I believe the default is set for an A4988 driver, and this use case is for the Pololu DRV8825 breakout. 
 
 
	//these should be familiar if you've used the accelstepper program before. 
    stepper.setMaxSpeed(actuatorSpeed);
    stepper.setAcceleration(actuatorAcceleration);
    stepper.setEnablePin(enablePin); 
    stepper.setMinPulseWidth(3); //Remember the minPulseWidth variable from before? This is the accelstepper version. 

// declare pinmodes
  pinMode(systemEndstop,INPUT);
  digitalWrite(systemEndstop,HIGH); //This sets internal 20k pull-up resistor. It is usually necessary for a hall sensor to have a pull-up resistor, and in this case I was using a hall-sensor endstop. 
}

void fastSteppingFunction(){ 
   
  //Ok! StepDelay needs to be set so that it creates a stepping speed approximately equal to the stepping speed that accelstepper leaves off at. Much different, and you will have caused an instantaneous acceleration that the stepper motor will fail to keep up with. 
  
  byte stepDelay=((1000000/actuatorSpeed)-minPulseWidth-programOverhead); 
  //In my original code, I actually hard coded the stepDelay start at 250 instead of (100000/actuatorSpeed). The math for my values would put 1,000,000/actuatorSpeed at 256 steps/second, and for some reason I chose 250. But this math step allows for you to change your actuatorSpeed without needing to change the value here. 
   
  byte counter = 0;   //counter is used as a way to make a very quick conditional statement that overflows every 256 digits. There are other ways to implement the linear ramp. This is the way I chose.  I thought it would be fast although it's no longer clear to me why I chose exactly this method. 
  
  while(digitalRead(systemEndstop)==HIGH){ //remember this is our ending condition. In my code we are not relying on our steps to be counted until our endstop. You can do this too, by setting your condition to be be when a bigger counter reaches a certain number. Then you need to implement a counter that increments during each step. 
  
  digitalWrite(stepPin,HIGH);
  delayMicroseconds(minPulseWidth);
  digitalWrite(stepPin,LOW);
  delayMicroseconds(stepDelay);
    
      if (actuatorTimeout<(millis()-timeStart)){
		  //Did you notice we said "timeStart=millis()" at the start of actuation? This is because I recommend your system has a timeout in case your motor stalls out and you never reach your endstop. 
		
		//make an error function and call it here. 
		//make a function to get back up to speed, assuming you want to do that after you resolve the error. Optional not included. 
		//recursively return to the fastSteppingFunction();
      }
      
	  //Next increment the counter, this will run each time you repeat the loop. At the point I'm writing this instructable, I suggest using a different method to make a linear ramp. This method is not very adjustable to changing the ramp, more in next comments.
	  
      counter=counter+2; //always manipulate this counter so that you understand when your counter will reach the condition in the if statement below.  In my case, it will reach the condition every 256/2 steps, i.e, every 128 steps, or, about every fifth of a revolution. If I chose a number like "3" instead of "2" I would have a problem because the counter would not reach 0 until a third overflow of the byte number, so I would be decreasing the slope of my linear ramp six times. Meanwhile I can also decrease the slope by half by changing the number to 1, or I can double the slope by saying 4. This lack of flexibility in changing the linear ramp slope is why I suggest considering other methods to make a linear ramp.  Try to implement your method with minimum math. Ideally do not include multiplication in the loop, and especially not division. Division is not native on the arduino, and requires more software overhead. 
	  
      if (stepDelay>stepDelayTarget && counter==0){
		  //So this condition is looking to see if you're reached your max speed target, and if you haven't yet and the counter has reached its trigger point [0], then it decreases the delay. 
        stepDelay--;  //Stepdelay-- is a fast way of saying "stepdelay=stepdelay-1", i.e, your decreasing the step delay. By decreasing the step delay, you are increasing the frequency of steps/ the speed of your motor.
      }
  }
}

void moveActuatorForward(){
 
 //Hey! You're about to start moving a motor. In a lot of cases that means you should make some safety check. The following commented if statement is a filler for that.  
  /*if ([insert errorCondition]){  
    //stepper.disableOutputs();
    //error();
  }*/
  
  stepper.enableOutputs(); //This is redundant, in fact. It's already been called. 
  stepper.move(actuatorDistance); //You need to tell accelstepper how far you're going! 
  
  timeStart = millis(); //I used a global variable in other parts of the code, maybe you want to use a local variable. 
  
  //Hey we're finally starting!!
  while(1){ //Title: "Basic Moving While Loop"
	
	if (digitalRead(systemEndstop)==LOW){
		//we finished before acceleration got past the library limit! This never happened for my application, but maybe does for yours. 
		break; //break removes you from the while loop called "Basic Moving While loop"
	}
	
    stepper.run(); //this makes your initial acceleration completely abstract. 
    
	if(stepper.speed()<actuatorSpeed){
		 fastSteppingFunction();
		 break;
	}
	
	}
  
  stepper.disableOutputs(); 
  //Hey, we're done. 
  return;  
}  

void loop(){
  //do stuff other than moving your motors, if you have other stuff to do. 
	
  stepper.disableOutputs();
  //I tend to add extra disableOutputs in case I made mistakes in the code, because my stepper motors were set to a high current that would eventually make those little motors overheat. For simple programs this isn't a big deal, but once you start running around with more program states you want to be sure you don't let your motor overheat while you're doing something else. 
  
  if (1){ //Here I'm just suggesting that you probably want to run the actuator based on some condition. 
 
  //Now this is a stripped version of the code. Let's just look at it as a goal to "actuate" a linear actuator. There are two endstops for this device but we're only looking at moving the actuator from "home" to "endstop"
  
	  stepper.enableOutputs();
	  stepper.setCurrentPosition(0); //My physical system had a lot of friction, so I never decelerated my load.  This meant that when I start the motor, accelstepper sometimes wants to "slow down" before it accelerates again. This is even if it was in fact not running. SetCurrentPosition(0) acts as a reset to the accelstepper code. 
	
      moveActuatorForward();
	  
      stepper.disableOutputs();
      }  
}



