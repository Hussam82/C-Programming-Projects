//-------------Vehicle Control System Mini Project-----------//
//Name: Hussam ali
//Diploma number: 60

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ON 1
#define OFF 0

//using all of the car options in a struct to make things easier and organized
typedef struct{
	char light;
	int engine_state;
	int ac_state;
	float room_temp;
	int engine_temp_controller_state;
	float engine_temp;
	int vehicle_speed;
}vehicles;


//Prototypes of the used functions
//function to display the first menu
void input_func(char *input);
//function to display the second menu
void engine_input(char *engine_on_input);
//function to set the sensors
void engine_on(char *input, vehicles *v);
void set_traffic_light(vehicles *v);
void set_room_temp(vehicles *v);
void set_engine_temp(vehicles *v);
void display_current_state(vehicles *v);

int changed_room = 0;
int changed_engine = 0;


int main()
{
	vehicles v;
	v.vehicle_speed = 80;
	v.engine_temp = 110;
	v.room_temp = 31;
	char input;
	// take the input from the user if it is (b) it will go to the menu again if (c) the program will end
	input_func(&input);
	while(1)
	{
		switch(input)
			{
				case 'a':
				{
					// takes us to the sensors menu
					printf("Engine ON\n");
					engine_on(&input, &v);
					break;
				}
				case 'b':
				{
					// get the first menu again
					printf("Engine OFF\n");
					input_func(&input);
					break;
				}
				case 'c':
				{
					printf("Terminating the program......\n");
					return 0;
				}
			}
	}
}


void input_func(char *input)
{
	printf("---------- Vehicle Control System ------------\n");
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n");
	// do while to make sure that the user entered a,b,c or d otherwise it will prompt to enter the valid option
	do
	{
		printf("Enter an option\n");
		fflush(stdout);
		scanf(" %c", input);
	} while(*input != 'a' && *input != 'b' && *input != 'c'); //if anything other than a, b or c is entered it will ask you again to enter a,b,c
}


void engine_on(char *input, vehicles *v)
{
	v->engine_state = ON;
	char engine_on_input;
	// takes an input to the second menu
	engine_input(&engine_on_input);
	while(1)
	{

		switch(engine_on_input)
				{
					case 'a':
					{
						// make the input character go to (b) case, to display the first menu again
						display_current_state(v);
						*input = 'b';
						return;
					}
					case 'b':
					{
						set_traffic_light(v);
						//when the function is done return to the first menu again
						display_current_state(v);
						engine_input(&engine_on_input);

						break;
					}
					case 'c':
					{
						set_room_temp(v);
						//when the function is done return to the first menu again
						display_current_state(v);
						engine_input(&engine_on_input);
						break;
					}
					case 'd':
					{
						set_engine_temp(v);
						//when the function is done return to the first menu again
						display_current_state(v);
						engine_input(&engine_on_input);
						break;
					}
				}
		//display_current_state(v);
	}
}


void engine_input(char *engine_on_input)
{
	printf("---------- Sensors set menu ------------\n");
	printf("a. Turn off the engine\n");
	printf("b. Set the traffic light color\n");
	printf("c. Set the room temperature\n");
	printf("d. Set the engine temperature\n");
	// do while to make sure that the user entered a,b,c or d otherwise it will prompt to enter the valid option
	do
	{
		printf("Enter an option\n");
		fflush(stdout);
		scanf(" %c", engine_on_input);
	} while(*engine_on_input != 'a' && *engine_on_input != 'b' && *engine_on_input != 'c' && *engine_on_input != 'd');
}

void set_traffic_light(vehicles *v)
{
	printf("Enter the traffic light\n");
	printf("'G' for green\n");
	printf("'O' for orange\n");
	printf("'R' for red\n");
	// to make sure that the sure entered G,O or R and nothing else
	do
	{
		printf("input\n");
		fflush(stdout);
		scanf(" %c", &v->light);
	}while(v->light != 'G' && v->light != 'O' && v->light != 'R');
	//sets the vehicle speed according to the traffic light color
	switch(v->light)
	{
		case 'G':
		{
			v->vehicle_speed = 100;
			break;
		}
		case 'O':
		{
			v->vehicle_speed = 30;
			break;
		}
		case 'R':
		{
			v->vehicle_speed = 0;
			break;
		}
	}

}

void set_room_temp(vehicles *v)
{
	//do while to make sure that the user didnt enter negative temp or above 100 temp
	do
	{
		printf("Enter room temperature:\n");
		fflush(stdout);
		scanf("%f", &v->room_temp);
	}while(v->room_temp < 0 || v->room_temp > 100);
	changed_room = 1;
	if(v->room_temp < 10 || v->room_temp > 30)
	{
		v->ac_state = ON;
		v->room_temp = 20;
	}
	else
	{
		v->ac_state = OFF;
	}
}

void set_engine_temp(vehicles *v)
{
	printf("Enter the engine temperature:\n");
	fflush(stdout);
	scanf("%f", &v->engine_temp);
	changed_engine = 1;
	if(v->engine_temp < 100 || v->engine_temp > 150)
	{
		v->engine_temp_controller_state = ON;
		v->engine_temp = 125;
	}
	else
	{
		v->engine_temp_controller_state = OFF;
	}
	//--------------------REMOVED--------------------------
	//if(v->vehicle_speed == 30)
	//{
	//	v->ac_state = ON;
	//	v->room_temp = (float)v->room_temp * 5.0/4 + 1;
	//	v->engine_temp_controller_state = ON;
	//	v->engine_temp = (float)v->engine_temp * 5.0/4 + 1;
	//}
	//// displays the current state after finishing entering all of the required inputs
	//display_current_state(v);
	//----------------------------------------------------
}

void display_current_state(vehicles *v)
{
	if (30 == v->vehicle_speed)
	{
		v->ac_state = ON;
		if(changed_room-- == 1)
		{
			v->room_temp = (float)v->room_temp * 5.0/4 + 1;
		}
		if(changed_engine-- == 1)
		{
			v->engine_temp_controller_state = ON;
		}
		v->engine_temp = (float)v->engine_temp * 5.0/4 + 1;
	}
	printf("---------- Current vehicle state ------------\n");
	if(v->engine_state == 1)
	{
		printf("i. Engine state: ON\n");
	}
	else
	{
		printf("i. Engine state: OFF\n");
	}
	if(v->ac_state == 1)
	{
		printf("ii. AC: ON\n");
	}
	else
	{
		printf("ii. AC: OFF\n");
	}
	printf("iii. Vehicle speed: %d km/h\n", v->vehicle_speed);
	printf("iv. Room temperature: %.1f degrees\n", v->room_temp);
	if(v->engine_temp_controller_state == 1)
	{
		printf("v. Engine temperature controller state: ON\n");
	}
	else
	{
		printf("v. Engine temperature controller state: OFF\n");
	}
	printf("vi. Engine temperature: %.1f degrees\n", v->engine_temp);


}





