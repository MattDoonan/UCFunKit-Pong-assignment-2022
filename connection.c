/**
 * @file connection.c
 * @author Matthew Doonan
 * @brief Class controlls the infra red connection signal. Sends and checks for recieved infomation. 
 * @version 0.1
 * @date 2022-10-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//Modules used
#include "system.h"
#include "ir_uart.h"
#include "connection.h"

/**
 * @brief Sets up the ir_uart class 
 * 
 */
void connectionInit(void) 
{
    ir_uart_init();
}

/**
 * @brief sends the start key to the other controller
 * 
 */
void startConnection(void) 
{
    ir_uart_putc(start); 
}

/**
 * @brief Checks if another controller has the start code
 * 
 * @return true if the start code has been recieved
 * @return false if the start code hasn't been recived
 */
bool possibleConnection(void) 
{
    if (ir_uart_read_ready_p()) {
        if (ir_uart_getc() == start) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Sends the ball code to the other player
 * 
 */
void sendBallConnection(void) {
    ir_uart_putc(ballCode);
}

/**
 * @brief Checks if the player has recieved a ball code
 * 
 * @return true if the player has recived the ball code
 * @return false if not
 */
bool recivedBallConnection(void) {
    if (ir_uart_read_ready_p()) {
        if (ir_uart_getc() == ballCode) {
            return true;
        }
    }
    return false;
} 

/**
 * @brief Sends the balls y coordinate and the direction its moving
 * 
 * @param y the y position on the board
 * @param dir the direction its moving 
 */
void sendBallCoords(int8_t y, int8_t dir)
{
    ir_uart_putc(y); 
    ir_uart_putc(dir);
}

/**
 * @brief Checks for any data recieved by the other player
 * 
 * @return data Struct of the y and direction and if the game is a loss
 */
data recievedOpponentInfo(void) 
{
    data get = {-2,-2,0};
    if (ir_uart_read_ready_p()) {
        int findings = ir_uart_getc();
        if (findings != lossCode) {
            get.ypos = findings;
            get.ydir = ir_uart_getc();
        } else {
            get.loss = 1;
        }
    }
    return get;

}

/**
 * @brief Sends the loss code to the opponent
 * 
 */
void sendLoss(void) 
{
    ir_uart_putc(lossCode); 
}
