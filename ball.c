/**
 * @file ball.c
 * @author Matthew Doonan
 * @brief Class that controls the ball position on the screen
 * @version 0.1
 * @date 2022-10-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//Modules used
#include "system.h"
#include "ball.h"
#include "tinygl.h"
#include <stdlib.h>

/**
 * @brief Sets up the ball on the screen to a certian position
 * 
 * @param x The x position of the ball to be set
 * @param y The y positon of the ball to be set
 * @param dir the y direction of the ball
 */
void ballInit(int x, int y, int dir) 
{
    ballPosition = tinygl_point(x,y);
    ballMovementX = 1;
    ballMovementY = dir;
    showBall();
}

/**
 * @brief Get the pointer for the x position of the ball
 * 
 * @return int8_t* the coordinate of the ball (pointer)
 */
int8_t* getBallPositionX(void) 
{
    return &ballPosition.x;
}

/**
 * @brief Get the pointer for the y position of the ball
 * 
 * @return int8_t* the coordinate of the ball (pointer)
 */
int8_t* getBallPositionY(void) 
{
    return &ballPosition.y;
}

/**
 * @brief Gets the pointer for the x direction of the ball
 * 
 * @return int8_t* the x direction of the ball (pointer)
 */
int8_t* ballXMovement(void) 
{
    return &ballMovementX;
}

/**
 * @brief Gets the poiinter for the y direction of the ball
 * 
 * @return int8_t* the y direction of the ball (pointer)
 */
int8_t* ballYMovement(void) 
{
    return &ballMovementY;
}

/**
 * @brief Shows the ball on the screen 
 * 
 */
void showBall(void) 
{
    tinygl_draw_point(ballPosition, 1);
}

/**
 * @brief Hides the ball
 * 
 */
void hideBall(void) 
{
    tinygl_draw_point(ballPosition, 0);
}

/**
 * @brief Changes the direction of the ball
 * 
 */
void changeBallMovement(void) 
{
    ballMovementX *= -1;
}

/**
 * @brief Gerentates a random y direction and sets ballMovementY to it 
 * 
 */
void randomYDirrection(void) 
{
    int number = rand() % 3; 

    if (number == 0) {
        ballMovementY = 0;
    } else if (number == 1) {
        ballMovementY = 1;
    } else {
        ballMovementY = -1;
    }
}

/**
 * @brief Moves the y position of the ball
 * 
 */
void moveBallY(void) 
{
    if (ballPosition.y + ballMovementY < 0 
        || ballPosition.y + ballMovementY > 6) {
        ballMovementY *= -1;
        ballPosition.y += ballMovementY; 
    } else {
        ballPosition.y += ballMovementY;
    }    
}

/**
 * @brief Moves the x position of the ball
 * 
 */
void moveBallX(void) 
{
    ballPosition.x = (ballPosition.x + ballMovementX); 
}
