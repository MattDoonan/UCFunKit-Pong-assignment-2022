/**
 * @file movement.h
 * @author Matthew Doonan
 * @brief This module header provides the movement functionality to the game.c class
 * @version 0.1
 * @date 2022-10-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// Defining the file 
#ifndef movement_h
#define movement_h

#include "system.h"

// boolean for if the ball is on the screen 
bool ballOnScreen;

/*
    Sets the ballOnScreen value to true or false
*/
void setBallOnScreen(bool bOS);

/*
    Calls the racket.c and the ball.c to spawn the objects in
*/
void spawnObjects(void);

/*
    Calls rackerRight from racket.c
*/
void racketMoveRight(void);

/*
    Calls racketLeft from racket.c
*/
void racketMoveLeft(void);

/*
    Returns ballOnScreen value
*/
bool* getBallOnScreen(void); 

/*
    Checks if the racket is behind the ball
*/
bool checkRacketBehindBall(void);

/* 
    Actions from move ball
*/
bool moveBall(void);

/*
    Checks if the ball is going to go to the next screen
*/
bool needConnection(void);

/*
    Gets the y direction of the ball
*/
int8_t* getDirrectionOfY (void);

/*
    Gets the y coordinate of the ball
*/
int8_t* getYBallCoord(void); 

/*
    Sends tha ball coordinate to the ball.c class
*/
void sendToSetBallCoords(int, int);

#endif
