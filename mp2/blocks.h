/*
 * tab:4
 *
 * blocks.h - header file for maze block image definitions
 *
 * "Copyright (c) 2004-2009 by Steven S. Lumetta."
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice and the following
 * two paragraphs appear in all copies of this software.
 * 
 * IN NO EVENT SHALL THE AUTHOR OR THE UNIVERSITY OF ILLINOIS BE LIABLE TO 
 * ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL 
 * DAMAGES ARISING OUT  OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, 
 * EVEN IF THE AUTHOR AND/OR THE UNIVERSITY OF ILLINOIS HAS BEEN ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * THE AUTHOR AND THE UNIVERSITY OF ILLINOIS SPECIFICALLY DISCLAIM ANY 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE 
 * PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND NEITHER THE AUTHOR NOR
 * THE UNIVERSITY OF ILLINOIS HAS ANY OBLIGATION TO PROVIDE MAINTENANCE, 
 * SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Author:        Steve Lumetta
 * Version:       2
 * Creation Date: Thu Sep  9 22:15:40 2004
 * Filename:      blocks.h
 * History:
 *    SL    1    Thu Sep  9 22:15:40 2004
 *        First written.
 *    SL    2    Sat Sep 12 12:06:20 2009
 *        Integrated original release back into main code base.
 */

#ifndef BLOCKS_H
#define BLOCKS_H

/* 
 * block image dimensions in pixels; images are defined as contiguous
 * sets of bytes in blocks.s
 */
#define BLOCK_X_DIM 12
#define BLOCK_Y_DIM 12

/* 
 * CAUTION!  The directions below are listed clockwise to allow the use
 * of modular arithmetic for turns, e.g., turning right is +1 mod 4.  The
 * directions also correspond to the order of the player blocks in the
 * enumeration below and in the blocks.s file.  The last direction of
 * motion must be used for the images--no "stopped" picture is provided.
 */
typedef enum {
    DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT, 
    NUM_DIRS,
    DIR_STOP = NUM_DIRS
} dir_t;

/*
 * CAUTION!  These colors are used as constants rather than symbols
 * in blocks.s.
 */
#define PLAYER_CENTER_COLOR 0x20
#define WALL_OUTLINE_COLOR  0x21
#define WALL_FILL_COLOR     0x22

/* 
 * CAUTION!  The order of blocks in this enumeration must match the
 * order in blocks.s.
 */
enum {
    BLOCK_,               /* 16 blocks for walls with up, right, down,    */
    BLOCK_U,              /*   and left connections to adjacent walls     */
    BLOCK_R,
    BLOCK_UR,
    BLOCK_D,
    BLOCK_UD,
    BLOCK_RD,
    BLOCK_URD,
    BLOCK_L,
    BLOCK_UL,
    BLOCK_RL,
    BLOCK_URL,
    BLOCK_DL,
    BLOCK_UDL,
    BLOCK_RDL,
    BLOCK_URDL,
    BLOCK_EMPTY,          /* empty (non-wall) maze space                  */
    BLOCK_SHADOW,         /* obscured maze space                          */
    BLOCK_PLAYER_UP,  //UP_M    /* four pictures of the player, in dir_t order  */
    BLOCK_PLAYER_UP_U,
    BLOCK_PLAYER_UP_M_2,
    BLOCK_PLAYER_UP_H,
    BLOCK_PLAYER_UP_A,
    BLOCK_PLAYER_UP_P,
    BLOCK_PLAYER_UP_P_2,
    BLOCK_PLAYER_UP_Y,
    BLOCK_PLAYER_UP_B,
    BLOCK_PLAYER_UP_I,
    BLOCK_PLAYER_UP_R,
    BLOCK_PLAYER_UP_T,
    BLOCK_PLAYER_UP_H_2,
    BLOCK_PLAYER_UP_D,
    BLOCK_PLAYER_UP_A_2,
    BLOCK_PLAYER_UP_Y_2,
    BLOCK_PLAYER_RIGHT,  //RIGHT_M    /* four pictures of the player, in dir_t order  */
    BLOCK_PLAYER_RIGHT_U,
    BLOCK_PLAYER_RIGHT_M_2,
    BLOCK_PLAYER_RIGHT_H,
    BLOCK_PLAYER_RIGHT_A,
    BLOCK_PLAYER_RIGHT_P,
    BLOCK_PLAYER_RIGHT_P_2,
    BLOCK_PLAYER_RIGHT_Y,
    BLOCK_PLAYER_RIGHT_B,
    BLOCK_PLAYER_RIGHT_I,
    BLOCK_PLAYER_RIGHT_R,
    BLOCK_PLAYER_RIGHT_T,
    BLOCK_PLAYER_RIGHT_H_2,
    BLOCK_PLAYER_RIGHT_D,
    BLOCK_PLAYER_RIGHT_A_2,
    BLOCK_PLAYER_RIGHT_Y_2,
    BLOCK_PLAYER_DOWN,  //DOWN_M    /* four pictures of the player, in dir_t order  */
    BLOCK_PLAYER_DOWN_U,
    BLOCK_PLAYER_DOWN_M_2,
    BLOCK_PLAYER_DOWN_H,
    BLOCK_PLAYER_DOWN_A,
    BLOCK_PLAYER_DOWN_P,
    BLOCK_PLAYER_DOWN_P_2,
    BLOCK_PLAYER_DOWN_Y,
    BLOCK_PLAYER_DOWN_B,
    BLOCK_PLAYER_DOWN_I,
    BLOCK_PLAYER_DOWN_R,
    BLOCK_PLAYER_DOWN_T,
    BLOCK_PLAYER_DOWN_H_2,
    BLOCK_PLAYER_DOWN_D,
    BLOCK_PLAYER_DOWN_A_2,
    BLOCK_PLAYER_DOWN_Y_2,
    BLOCK_PLAYER_LEFT,  //LEFT_M    /* four pictures of the player, in dir_t order  */
    BLOCK_PLAYER_LEFT_U,
    BLOCK_PLAYER_LEFT_M_2,
    BLOCK_PLAYER_LEFT_H,
    BLOCK_PLAYER_LEFT_A,
    BLOCK_PLAYER_LEFT_P,
    BLOCK_PLAYER_LEFT_P_2,
    BLOCK_PLAYER_LEFT_Y,
    BLOCK_PLAYER_LEFT_B,
    BLOCK_PLAYER_LEFT_I,
    BLOCK_PLAYER_LEFT_R,
    BLOCK_PLAYER_LEFT_T,
    BLOCK_PLAYER_LEFT_H_2,
    BLOCK_PLAYER_LEFT_D,
    BLOCK_PLAYER_LEFT_A_2,
    BLOCK_PLAYER_LEFT_Y_2,
    BLOCK_PLAYER_MASK_UP, /* four masks for player images, in dir_t order */
    BLOCK_PLAYER_MASK_RIGHT,
    BLOCK_PLAYER_MASK_DOWN,
    BLOCK_PLAYER_MASK_LEFT,
    BLOCK_FRUIT_1,        /* fruit pictures                               */
    BLOCK_FRUIT_2,
    BLOCK_FRUIT_3,
    BLOCK_FRUIT_4,
    BLOCK_FRUIT_5,
    BLOCK_FRUIT_6,
    BLOCK_FRUIT_7,  LAST_FRUIT = BLOCK_FRUIT_7,
    BLOCK_FRUIT_SHADOW,   /* obscured fruit                               */
    BLOCK_EXIT,           /* the exit from the maze                       */
    NUM_BLOCKS
};

/*
 * CAUTION: Fruits are encoded using several bits in the maze_bit_t
 * bit vector.  Make sure that enough bits are used to cover the
 * number of fruits defined here.
 */
#define NUM_FRUIT_TYPES (LAST_FRUIT - BLOCK_FRUIT_1 + 1)

/* the array of block pictures defined in blocks.s */
extern unsigned char blocks[NUM_BLOCKS][BLOCK_Y_DIM][BLOCK_X_DIM];

#endif /* BLOCKS_H */
