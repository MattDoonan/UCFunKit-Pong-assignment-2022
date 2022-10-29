/**
 * @file movement.c
 * @author Matthew Doonan
 * @brief Class controls the interactions between the ball, the racket and the screen
 * @version 0.1
 * @date 2022-10-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//Modules used
#include "system.h"
#include "ball.h"
#include "racket.h"
#include "movement.h"

/**
 * @brief Set the Ball On Screen object
 * 
 * @param bOS boolean for true of false depending if the ball is on the screen first
 */
void setBallOnScreen(bool bOS) 
{
    ballOnScreen = bOS;
}

/**
 * @brief Spawns the racket and the ball on the screen depending who controls the ball
 * 
 */
void spawnObjects(void) 
{
    if (ballOnScreen) {
        ballInit(0, 3, 0);
    }
    racketInit();
}

/**
 * @brief Calls the racket.c moveRight function
 * 
 */
void racketMoveRight(void) 
{
    moveRight();
}

/**
 * @brief Calls the racket.c moveLeft function
 * 
 */
void racketMoveLeft(void) 
{
    moveLeft();
}

/**
 * @brief Returns boolean of if the ball is on the screen
 * 
 * @return true if the ball is on the screen
 * @return false if the ball is not
 */
bool* getBallOnScreen(void) 
{
    return &ballOnScreen;
}

/**
 * @brief Checks if the racket is behind the ball on the next movement 
 * 
 * @return true if the racket is behind the ball
 * @return false if the racket isn't behind the ball
 */
bool checkRacketBehindBall(void) 
{
    if (*getBallPositionY() == 0 || *getBallPositionY() == 6) {
        if (*getLeftRacketPosition() == (*getBallPositionY())
        || *getRightRacketPosition() == (*getBallPositionY())) { 
            return true;
        }
    } else {
        if (*getLeftRacketPosition() == (*getBallPositionY() + *ballYMovement())
        || *getRightRacketPosition() == (*getBallPositionY() + *ballYMovement())) {
            return true;
        }
    }
    
    return false;
}

/**
 * @brief Moves the ball and returns boolean for if the game is over 
 * 
 * @return true if the game isn't over 
 * @return false if the game is over
 */
bool moveBall(void) 
{
    hideBall();
    if (*getBallPositionX() + *ballXMovement() == 4) {
        if (checkRacketBehindBall()) {
            changeBallMovement();
            randomYDirrection();
        } else {
            return false;
        }
    }
    moveBallY();
    moveBallX();
    showBall();
    return true;
}

/**
 * @brief Checks if the ball is going to hit the end of the screen to go to the other one
 * 
 * @return true if the ball needs to move to the other screen
 * @return false if the ball stays on the screen
 */
bool needConnection(void) 
{
    if ((*getBallPositionX() + *ballXMovement()) < 0) {
        hideBall();
        moveBallY();
        hideBall();
        return true; 
    } 
    return false;
}

/**
 * @brief Get the dirrection of the y pointer of the movement
 * 
 * @return int the direction in (-1,0,1)
 */
int8_t* getDirrectionOfY (void) 
{
    return ballYMovement();
}

/**
 * @brief Gets the Y coordinate of the pointer of the ball
 * 
 * @return int the y cooridinate 
 */
int8_t* getYBallCoord(void) 
{
    return getBallPositionY();
}

/**
 * @brief Gets Y direction and Y position and sends the values to the ball.c class
 * 
 * @param dir The Y direction of the ball
 * @param y The y position of the ball
 */
void sendToSetBallCoords(int dir, int y) 
{
    ballInit(0, ((y*(-1))+6), (dir*(-1)));
    showBall();
}
