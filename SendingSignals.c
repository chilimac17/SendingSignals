/**
 * @file SendingSignals.h
 * @author Michael Chillemi
 * @brief 
 * @version 0.1
 * @date 2023-04-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/**
 * Includes
 */
//#include<sys/types.h>
//#include<signal.h>
//#include<stdio.h>
//#include<unistd.h>
//#include<stdlib.h>
#include<limits.h>
#include"SendingSignals.h"

/**
 * @brief Variables
 * 
 */

static int float_zero_divisor_flag = 0;
static int float_overflow_flag = 0;
static int int_zero_divisor_flag = 0;
static int int_overflow_flag = 0;

//---------------------------------------------------------------------------//
void floatOverflow(int sig) 
{
    printf("Floating-Point Overflow \n");
    float_overflow_flag = 1;   //set a flag to indicate the signal was received
}

//---------------------------------------------------------------------------//
void floatNonZeroDivisor(int sig)
{
    printf("Float: Second input can not be equal to 0!\n");
    float_zero_divisor_flag = 1;   //set a flag to indicate the signal was received
}

//---------------------------------------------------------------------------//
void intNonZeroDivisor(int sig)
{
    printf("Second input can not be equal to 0!\n");
    int_zero_divisor_flag = 1;   //set a flag to indicate the signal was received
}

//---------------------------------------------------------------------------//
void integerOverflow(int sig)
{
    printf("Integer Overflow\n");
    int_overflow_flag = 1;   //set a flag to indicate the signal was received
}


//---------------------------------------------------------------------------//
void testingUserFLoatInput(float userInput1, float userInput2)
{
    printf("Please Provide a Floating Point Value: \n");
        scanf("%f",&userInput1);
        printf("Please Provide one more Floating Point Value: \n");
        scanf("%f",&userInput2);
        
        if(userInput2 == 0)
        {
            kill(getppid(), SIGFPE);  //sends a SIGINT to the parent

        }
        else
        {
            float divide_inputs =  userInput1 / userInput2;
            printf("%f / %f = %f", userInput1, userInput2, divide_inputs);

            float product_of_user_input = userInput1 * userInput2;
            float total = 0;
            product_of_user_input *=  10000000000;
            
            if(product_of_user_input > INT_MAX / 10000000000)
            {
                total = -1;
            }
            
    

            if(total == -1)
            {
                kill(getppid(), SIGINT);  //sends a SIGINT to the parent
            
            }
        }
        // sleep(5);   //child sleeps for 5 seconds
        // kill(getppid(), SIGINT);  //sends a SIGINT to the parent
}

//---------------------------------------------------------------------------//
void testingUserIntInput(int userInput_1, int userInput_2)
{
    printf("Please Provide a Integer: \n");
    scanf("%d",&userInput_1);
    printf("Please Provide one more Integer: \n");
    scanf("%d",&userInput_2);
    
    if(userInput_2 == 0)
    {
        kill(getppid(), SIGILL);  //sends a SIGINT to the parent
    }
    else
    {
        int divide_inputs_2 =  userInput_1 / userInput_2;
        printf("%d / %d = %d\n", userInput_1, userInput_2, divide_inputs_2);
        int product_of_user_input_2 = userInput_1 * userInput_2;
        int total_2 = 0;
        
        if(product_of_user_input_2 > 0 && INT_MAX / 10000000000)
        {
            total_2 = -1;
        }
        else if(product_of_user_input_2 < 0 && 10000000000 < 0 && total_2 > 0)
        {
            total_2 = -1;
        }

        if(total_2 == -1)
        {
            kill(getppid(), SIGABRT);  //sends a SIGINT to the parent
        }
    }
    // sleep(5);   //child sleeps for 5 seconds
    // kill(getppid(), SIGINT);  //sends a SIGINT to the parent
}



//---------------------------------------------------------------------------//
int main()
{
   pid_t pid;
   float first_user_input = 0;
   float second_user_input = 0;
   int first_user_input_2 = 0;
   int second_user_input_2 = 0;

   printf("Signal Starting\n");

   pid = fork();        //new process started

   switch(pid) 
   {
        case -1: 
            perror("Fork Failed");
            exit(1);
        case 0: 
            testingUserFLoatInput(first_user_input,second_user_input);
            testingUserIntInput(first_user_input_2,second_user_input_2);
            exit(0);
        default:
            printf("Y");
   }

   //in the parent process
   printf("Waiting For The Interrupt\n");
   signal(SIGFPE, floatNonZeroDivisor);  
   signal(SIGINT, floatOverflow);  
   signal(SIGILL, intNonZeroDivisor);  
   signal(SIGABRT, integerOverflow);  
                            //which sets a flag.
//HAVE PARENT FUNCTION CALL TESTING METHOD except check second line in directions 
   pause();
   if(float_zero_divisor_flag)
    {  
      printf("Interrupt received!\n");
    }
    else if(float_overflow_flag)
    {
        printf("Interrupt 2received!\n");
    }
    else if(int_zero_divisor_flag)
    {
        printf("Interrupt 3received!\n");
    }
    else if(int_overflow_flag)
    {
        printf("Interrupt 4received!\n");
    }

   printf("done\n");
   exit(0);
}
