#define ARM_PORT 0
#define ARM_DOWN 544
#define PORT_A 0
#define PORT_B 3
#define SERVO_A 3
#define SERVO_B 0
#define GREEN 0
#define RED 1
#define MAXRANGE_x 96
#define MINRANGE_x 70
#define MAXRANGE_y 120
#define MINRANGE_y 80

void arm_down()
{
	set_servo_position(ARM_PORT, ARM_DOWN);
}


void grab_trib(int color)
{
	while (1)
	{
		msleep(100); // delay for readable messages
		camera_update();
		printf("x coordinate is %d\n"),get_object_center(0,0).x; 
		printf("x coordinate is %d\n"),get_object_center(0,0).y; 
		if (get_object_center(0,0).x<MAXRANGE_x)
		{
			//printf("1\n");
			motor(PORT_A,-20);
			motor(PORT_B,20);
			
		}
		else if (get_object_center(0,0).x>MINRANGE_x)
		{
			printf("2\n");
			motor(PORT_A,20);
			motor(PORT_B,-20);
			
		}
		else if (get_object_center(0,0).y<MAXRANGE_y)
		{
			printf("3\n");
			motor(PORT_A,30);
			motor(PORT_B,30);
			
		}
		else if (get_object_center(0,0).y>MINRANGE_y)
		{
			printf("4\n");
			motor(PORT_A,-30);
			motor(PORT_B,-30);
			
		}
		else
		{
			set_servo_position(SERVO_A,544);
			msleep(1000);
			set_servo_position(SERVO_B,500);
			msleep(1000);
			set_servo_position(SERVO_A,2047);
			msleep(1000);
			printf("end :)");
			break;
		}
	}
}
