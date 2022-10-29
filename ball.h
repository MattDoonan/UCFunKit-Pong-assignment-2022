/**
 * @file ball.h
 * @author Matthew Doonan
 * @brief This module header controls the ball on the screen
 * @version 0.1
 * @date 2022-10-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// Defining the file 
#ifndef ball_h
#define ball_h

#include "system.h"
#include "tinygl.h"

// The ball position on the screen
tinygl_point_t ballPosition;

// The ball direction its moving in
int8_t ballMovementX;
int8_t ballMovementY;

/*
    Sets up the ball
*/
void ballInit(int, int, int);

/*
    Gets the x position of the ball
*/
int8_t* getBallPositionX(void);

/*
    Gets the y position of the ball
*/
int8_t* getBallPositionY(void);

/*
    Gets the x movement / direction of the ball
*/
int8_t* ballXMovement(void); 

/*
    Gets the y movement / direction of the ball
*/
int8_t* ballYMovement(void);

/*
    Shows the ball on the screen 
*/
void showBall(void);

/*
    Hides the ball on the screen
*/
void hideBall(void);

/*
    Changes the ball movement 
*/
void changeBallMovement(void);

/*
    Sets a random y direction
*/
void randomYDirrection(void);

/*
    Moves the ball in the Y direction 
*/
void moveBallY(void);

/*
    Moves the ball in the X direction
*/
void moveBallX(void);

#endif
