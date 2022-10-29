/**
 * @file racket.h
 * @author Matthew Doonan
 * @brief This module header controls the racket on the screen
 * @version 0.1
 * @date 2022-10-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// Defining the file 
#ifndef racket_h
#define racket_h

#include "system.h"
#include "tinygl.h"

/**
 * @brief struct holds the left and right side tinygl_point_t of the racket
 * 
 */
typedef struct {
    tinygl_point_t leftSide;
    tinygl_point_t rightSide;
} racketPosition_t;

// The struct that holds the postion 
racketPosition_t position; 

/*
    Sets up the racket
*/
void racketInit(void);

/*
    Shows the racket
*/
void showRacket(void);

/*
    Hides the racket
*/
void hideRacket(void);

/*
    Moves the racket left
*/
void moveLeft(void);

/*
    Moves thr racket right
*/
void moveRight(void);

/*
    Gets the coordinate of the left racket position
*/
tinygl_coord_t* getLeftRacketPosition(void); 

/*
    Gets the coordinate of the right racket position
*/
tinygl_coord_t* getRightRacketPosition(void); 


#endif
