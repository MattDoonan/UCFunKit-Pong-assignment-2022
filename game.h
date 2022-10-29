/**
 * @file game.h
 * @author Matthew Doonan, Alex Holton
 * @brief This module header provides that main game functionality
 * @version 0.1
 * @date 2022-10-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// Defining the file 
#ifndef game_h
#define game_h

#include "system.h"

#define startSpeed 500
#define increaseSpeed 1.1
#define resetTick 0

// The shared values across the game.c file
bool ballStart;
int randomSeed;
bool gameWon;
uint32_t speed;
uint32_t tick;

/*
    Sets up the tinygl functions
*/
void tinyglSetup(void);

/*
    Controls the while loop for the game phase of the app
*/
void gamePhase(void);

/*
    Controls the while loop for the loading phase of the app
*/
void loadingPhase(void);

/*
    Contols the while loop for the setup phase of the app 
*/
void setupPhase(void);

/*
    Controls the while loop for the endPhase of the app
*/
void endPhase(void);

/*
    Controls the while loop for the full functionality of the app
*/
int main (void);

#endif
