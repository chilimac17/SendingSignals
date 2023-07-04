/**
 * @file SendingSignals.h
 * @author your name (you@domain.com)
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
#include<sys/types.h>
#include<signal.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

/**
 * @brief Variables
 * 
 */
static int float_zero_divisor_flag = 0;
static int float_overflow_flag = 0;
static int int_zero_divisor_flag = 0;
static int int_overflow_flag = 0;

/**
 * @brief 
 * 
 * @param sig 
 */
void integerOverflow(int sig);

/**
 * @brief 
 * 
 * @param sig 
 */
void floatNonZeroDivisor(int sig);

/**
 * @brief 
 * 
 * @param sig 
 */
void intNonZeroDivisor(int sig);

/**
 * @brief 
 * 
 * @param sig 
 */
void floatOverflow(int sig);

/**
 * @brief 
 * 
 * @param userInput1 
 * @param userInput2 
 */
void testingUserFLoatInput(float userInput1, float userInput2);

/**
 * @brief 
 * 
 * @param userInput1 
 * @param userInput2 
 */
void testingUserIntInput(int userInput1, int userInput2);