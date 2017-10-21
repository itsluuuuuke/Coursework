/*
This example program sounds the bell when driver is on seat 
AND haven't closed the doors. Use the general framework and the function 
shells, replace the code inside  the control_action() function with your 
own code.

Note: This code is designed to run in an infinite loop to mimic a real control system. 
If you prefer to read the inputs from a file, modify the code appropriately to terminate the
loop when all the inputs have been processed.

run this file as : gcc filename.c -o executableName

*/


#include <stdio.h> //This is useful to do i/o to test the code 

unsigned int driver_on_seat;
unsigned int driver_seat_belt_fasten;
unsigned int engine_running;
unsigned int doors_closed;
unsigned int key_in_car;
unsigned int door_lock_lever;
unsigned int brake_pedal;
unsigned int car_moving;

unsigned int bell;
unsigned int door_lock;
unsigned int brake;


void read_inputs_from_ip_if(){

	//place your input code here
	//to read the current state of the available sensors

	printf("Driver on seat? 0/1: ");
	scanf("%u",&driver_on_seat);
	printf("Driver seat belt fasten? 0/1: ");
	scanf("%u",&driver_seat_belt_fasten);
	printf("Car engine running? 0/1: ");
	scanf("%u",&engine_running);
	printf("Car doors closed? 0/1: ");
	scanf("%u",&doors_closed);
	printf("Key inside the car? 0/1: ");
	scanf("%u",&key_in_car);
	printf("Door lever closed? 0/1: ");
	scanf("%u",&door_lock_lever);
	printf("Brake pedal is pressed? 0/1: ");
	scanf("%u",&brake_pedal);
	printf("Car moving? 0/1: ");
	scanf("%u",&car_moving);

}

void write_output_to_op_if(){

	//place your output code here
    //to display/print the state of the 3 actuators (DLA/BELL/BA)
	if(bell)
		printf("\n#BELL ALARMS!#");
	else
		printf("\n#bell is silent#");

	if(door_lock)
		printf("\n#Doors are LOCKED by the door lock lever!#");
	else
		printf("\n#doors are NOT locked by the door lock lever＃");

	if(brake)
		printf("\n#The car BRAKE is ACTIVATED!#");
	else
		printf("\n#The car BRAKE is NOT activated#");
	printf("\n\n");
		
}


//The code segment which implements the decision logic
void control_action(){

	/*
	The code given here sounds the bell when driver is on seat 
	AND hasn't closed the doors. (Requirement-2)
 	Replace this code segment with your own code.
	*/

	if (driver_on_seat && !doors_closed)
		bell = 1;
	else bell = 0;

	if(engine_running && (!doors_closed || !driver_seat_belt_fasten))
		bell = 1;
	else
		bell = 0;
	

	if(!driver_on_seat && key_in_car)
		door_lock = 0;
	else
	{
		if(door_lock_lever)
			door_lock = 1;
		else
			door_lock = 0;
	}

	if(car_moving)
		if(brake_pedal)
			brake = 1;
		else 
			brake = 0;
	else
		brake = 0;
	
}

/* ---     You should not have to modify anything below this line ---------*/

int main(int argc, char *argv[])
{
	
	/*The main control loop which keeps the system alive and responsive for ever, 
	until the system is powered off */
	for (; ; )
	{
		read_inputs_from_ip_if();
		control_action();
		write_output_to_op_if();

	}
	
	return 0;
}
