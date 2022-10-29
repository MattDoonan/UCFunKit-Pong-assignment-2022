/**
 * @file game.c
 * @author Matthew Doonan, Alex Holton
 * @brief The main controller of the game. Controls all the phases. 
 * @version 0.1
 * @date 2022-10-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//Modules used
#include "system.h"
#include "connection.h"
#include "movement.h"
#include "game.h"
#include "pacer.h"
#include "pio.h"
#include "tinygl.h"
#include "navswitch.h"
#include "../fonts/font5x7_1.h"
#include <stdlib.h>

/**
 * @brief The funtion that sets up the aspects of the tinygl 
 * 
 */

void tinyglSetup(void)
{
    tinygl_init(500);
    tinygl_font_set (&font5x7_1);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_speed_set (10);
}

/**
 * @brief the function that controls the gamephase of the application it ends when a player losses
 * 
 */
void gamePhase(void)
{
    tinyglSetup();
    // Sets the ballOnScreen variable to the ballStart variable 
    setBallOnScreen(ballStart);
    // spawns in the racket and ball depending on who has it 
    spawnObjects();
    // True if the game hasn't been lost
    gameWon = true;
    // Sets the seed
    srand(randomSeed);
    // Sets the timer for the speed of the ball 
    tick = resetTick;
    // Sets the speed of the ball
    speed = startSpeed;
    // False if the game isn't over
    bool gameOver = false;

    while (!gameOver) {

        pacer_wait();
        tinygl_update ();
        navswitch_update();

        // moved the paddle left on navswitch north
        if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
            racketMoveLeft();
        // moved the paddle right on navswitch south
        } else if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
            racketMoveRight();
        }
        // Checks if the ball can move
        if (speed <= tick) {
            tick = resetTick;
            // Checks if the ball is on the users screen
            if (*getBallOnScreen()) {
                // Checks if the movement will cause the user to swap screen 
                if (needConnection()) {
                    // sends the info to the other player
                    setBallOnScreen(false);
                    sendBallCoords(*getYBallCoord(), *getDirrectionOfY());
                    speed /= increaseSpeed;
                } else {
                    // Checks if the game is still on
                    gameWon = moveBall();
                    gameOver = !gameWon;
                }   
            }
        }
        // Checks for a connection for end game or swap screens 
        data get = recievedOpponentInfo();
        // checks if the result is valid
        if (get.ydir != -2) {
        // Sets the balls coordinates
            tick = resetTick;
            sendToSetBallCoords(get.ydir, get.ypos);
            setBallOnScreen(true);
        } else if (get.loss == 1) {
            gameOver = true;
        }
        tick++;

    }
    tinygl_clear();
    if (!gameWon) {
        sendLoss();
    }
}

/**
 * @brief This function controls the loading phase of the game.
 * This is were the user creates a connection with another board
 * 
 */
void loadingPhase(void)
{

    tinyglSetup();
    // Sets the button to an input
    pio_config_set(PD7_PIO, PIO_INPUT);
    // Sets the text
    tinygl_text("Pong\0");

    // Is fals if there is no connection
    bool nextPhase = false;

    // false if the user hasn't clicked for a connection
    bool createConnection = false;

    // Sets the seed to 0 to help randomises ball movements
    randomSeed = 0;

    bool pressed = false;

    while (!nextPhase) {
        //Increases the seed
        randomSeed += 1;
        pacer_wait();
        tinygl_update (); 
        // On button click then sets create connection to true
        if (pio_input_get(PD7_PIO) && nextPhase == false) {
            createConnection = true;
            pressed = false;
        }
        // if the user wants a connection will send and check for connection
        if (createConnection == true) {
            if (!pressed) {
                startConnection();
                pressed = true;
            }
            if (possibleConnection()) {
                nextPhase = true;
            }
        }
        tick ++;
    }
    // Clears the screen
    tinygl_clear();

}

/**
 * @brief This function controls the setup phase of the board
 * This is where the player chooses who they want to start with the ball
 * 
 */
void setupPhase(void)
{
    tinyglSetup();
    // False if no user has spawned in the ball
    bool ballSpawned = false;
    // inits the ballStart variable to false
    ballStart = false;
    // Sets the text
    tinygl_text("Click to spawn ball\0");

    while (!ballSpawned) {

        pacer_wait();
        tinygl_update ();
        navswitch_update();
        // Checks if the other user has requested to start with the ball
        ballSpawned = recivedBallConnection();
        // If no user has requested and the user clicks the navswitch they start with the ball 
        if (ballSpawned == false && navswitch_down_p(NAVSWITCH_PUSH)) {
            sendBallConnection();
            ballSpawned = true;
            ballStart = true;
        }
    }
    // clears the screen
    tinygl_clear();

}

/**
 * @brief This function controls the end phase of the game
 * This is where the board tells who wins ans who loses
 * 
 */
void endPhase(void)
{
    tinyglSetup();
    bool restartGame = false;
    if (gameWon) {
        tinygl_text("You Win\0");
    } else {
        tinygl_text("You Lose\0");
    }

    while (!restartGame) {
        pacer_wait();
        navswitch_update();
        tinygl_update();
        if (navswitch_down_p(NAVSWITCH_PUSH)) {
            restartGame = true;
        }
    }
    tinygl_clear();
}
/**
 * @brief The function controls the structure of the game 
 * Calling other functions depending on whats happening
 * 
 * @return int 0 when the game is terminated
 */
int main (void)
{
    system_init ();
    connectionInit();
    pacer_init (500);

    while (1)
    {
        //Different phases of the game
        loadingPhase();
        setupPhase();
        gamePhase();
        endPhase();
    }
    return 0;
}
