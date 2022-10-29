/**
 * @file racket.c
 * @author Matthew Doonan
 * @brief Class that controls the racket position on the screen
 * @version 0.1
 * @date 2022-10-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//Modules used
#include "system.h"
#include "racket.h"
#include "tinygl.h"

/**
 * @brief Sets up the racket on the screen 
 * 
 */
void racketInit(void) 
{
    position.leftSide = tinygl_point(4, 3);
    position.rightSide = tinygl_point(4, 4);
    showRacket();
}

/**
 * @brief Shows the racket on the screen
 * 
 */
void showRacket(void) 
{
    tinygl_draw_line(position.leftSide, position.rightSide, 1);
}

/**
 * @brief Hides the racket 
 * 
 */
void hideRacket(void) 
{
    tinygl_draw_line(position.leftSide, position.rightSide, 0);
}

/**
 * @brief Moves the racket left one point
 * 
 */
void moveLeft(void) 
{
    hideRacket();
    if (position.leftSide.y != 0) {
        position.leftSide.y -= 1;
        position.rightSide.y -= 1;
    } 
    showRacket();
}

/**
 * @brief Moves the racket right one point
 * 
 */
void moveRight(void) 
{
    hideRacket();
    if (position.rightSide.y != 6) {
        position.rightSide.y += 1;
        position.leftSide.y += 1;
    }
    showRacket();
}

/**
 * @brief Get the pointer to the left racket position 
 * 
 * @return tinygl_coord_t* the coordinate of the left racket position (pointer)
 */
tinygl_coord_t* getLeftRacketPosition(void) 
{
    return &position.leftSide.y;
}

/**
 * @brief Get the right racket position 
 * 
 * @return tinygl_coord_t* the coordinate of the reft racket position (pointer)
 */
tinygl_coord_t* getRightRacketPosition(void) 
{
    return &position.rightSide.y;
}
