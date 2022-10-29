/**
 * @file connection.h
 * @author Matthew Doonan
 * @brief This module header provides the ir communication functionality to game.c
 * @version 0.1
 * @date 2022-10-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// Defining the file 
#ifndef connection_h
#define connection_h

#include "system.h"

// Perminant variables
#define start 42
#define ballCode 33
#define lossCode 21

/**
 * @brief struct holds data of the y position and the y direction of the ball
 * ypos the y position of the ball
 * ydir the direction of the ball
 */
typedef struct {
    int ypos;
    int ydir;
    int loss;
} data;

/*
    Sets up the ir connection functions 
*/
void connectionInit(void);

/*
    The function that sends that start key
*/
void startConnection(void);

/*
    The function that checks for possible opponent
*/
bool possibleConnection(void);

/* 
    The function that checks if the opponent has sent info for starting with a ball
*/
bool recivedBallConnection(void);

/*
    Sends ball code ot the opponent 
*/
void sendBallConnection(void);

/*
    Sends the balls current y position and y direction
*/
void sendBallCoords(int8_t y, int8_t dir);

/*
    Gets y position and y direction and if loss from oponent if sent
*/
data recievedOpponentInfo(void);

/*
    Sends loss code to opponent
*/
void sendLoss(void);

#endif
