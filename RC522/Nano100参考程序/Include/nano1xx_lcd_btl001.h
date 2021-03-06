/******************************************************************************
 * @file     nano1xx_btl001.h
 * @brief    NANO1xx LCD panel header file
 * @version  1.0.1
 * @date     04, September, 2012
 *
 * @note
 * Copyright (C) 2012-2014 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifdef __LCDDISPLAY_BTL001_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

#define LCD_ALPHABET_NUM		7
//#define LCD_DIGIT_NUM			11
#define LCD_DIGIT_NUM			4

#define LCD_ALPHABET_SEGNUM		14
#define LCD_DIGIT_SEGNUM				8

/**************************************************************************//**
 * 
 * Defines each text's segment (alphabet+numeric) in terms of COM and BIT numbers,
 * Using this way that text segment can be consisted of each bit in the
 * following bit pattern:
 * @illustration
 *               A
 *         ----------
 *         |\   |J  /|
 *        F| H  |  K |B
 *         |  \ | /  |
 *         --G-- --M--
 *         |   /| \  |
 *       E |  Q |  N |C
 *         | /  |P  \|   
 *         -----------     
 *             D         
 *
 *         -------0------
 *	    
 *        |   \7  |8  /9 |
 *        |5   \  |  /   |1
 *
 *         --6---  ---10--
 *
 *        |    /  |  \11 |
 *        |4  /13 |12 \  |2
 *							 
 *         -------3------	 
 *
 * 
 * 
 *****************************************************************************/
typedef struct
{
	uint32_t com[LCD_ALPHABET_SEGNUM]; /* LCD COM line (for multiplexing) */
	uint32_t bit[LCD_ALPHABET_SEGNUM]; /* LCD SEG bit number */
} CHAR_TypeDef;


/**************************************************************************//**
 * Defines segment COM and BIT fields for numeric display
 *****************************************************************************/
typedef struct
{
	uint32_t com[LCD_DIGIT_SEGNUM];
	uint32_t bit[LCD_DIGIT_SEGNUM];
} NUMBER_TypeDef;



/**************************************************************************//**
 * Defines all types of display for all segments
 *****************************************************************************/
typedef struct
{
	CHAR_TypeDef    Text[LCD_ALPHABET_NUM];
  	NUMBER_TypeDef  Number[LCD_DIGIT_NUM];

} NANO1XX_DISPLAY;

/**************************************************************************//**
 * Defines the COM/SEG for each alphabet and numeric 
 *****************************************************************************/
const NANO1XX_DISPLAY NANO1XXDISPLAY = {
  .Text        = {
    { /* 1 */						
		/* A            B               C              D    */
      .com[0] = 3, .com[1] = 2, .com[2] = 1, .com[3] = 0,
      .bit[0] = 0, .bit[1] = 0, .bit[2] = 0, .bit[3] = 0,
		/* E            F               G              H    */
      .com[4] = 1, .com[5] = 2, .com[6] = 2, .com[7] = 3,
      .bit[4] = 38, .bit[5] = 38, .bit[6] = 39, .bit[7] = 39,
		/* J            K               M              N    */
      .com[8] = 3, .com[9] = 2, .com[10] = 1, .com[11] = 0,
      .bit[8] = 1, .bit[9] = 1, .bit[10] = 1, .bit[11] = 1,
		/* P            Q      */
      .com[12] = 0, .com[13] = 1,
      .bit[12] = 39, .bit[13] = 39
    },
    { /* 2 */

      .com[0] = 3, .com[1] = 2, .com[2] = 1, .com[3] = 0,
      .bit[0] = 4, .bit[1] = 4, .bit[2] = 4, .bit[3] = 4,

      .com[4] = 1, .com[5] = 2, .com[6] = 2, .com[7] = 3,
      .bit[4] = 2, .bit[5] = 2, .bit[6] = 3, .bit[7] = 3,

      .com[8] = 3, .com[9] = 2, .com[10] = 1, .com[11] = 0,
      .bit[8] = 5, .bit[9] = 5, .bit[10] = 5, .bit[11] = 5,

      .com[12] = 0, .com[13] = 1,
      .bit[12] = 3, .bit[13] = 3
    },
    { /* 3 */

      .com[0] = 3, .com[1] = 2, .com[2] = 1, .com[3] = 0,
      .bit[0] = 8, .bit[1] = 8, .bit[2] = 8, .bit[3] = 8,

      .com[4] = 1, .com[5] = 2, .com[6] = 2, .com[7] = 3,
      .bit[4] = 6, .bit[5] = 6, .bit[6] = 7, .bit[7] = 7,

      .com[8] = 3, .com[9] = 2, .com[10] = 1, .com[11] = 0,
      .bit[8] = 9, .bit[9] = 9, .bit[10] = 9, .bit[11] = 9,

      .com[12] = 0, .com[13] = 1,
      .bit[12] = 7, .bit[13] = 7
    },
    { /* 4 */

      .com[0] = 3, .com[1] = 2, .com[2] = 1, .com[3] = 0,
      .bit[0] = 12, .bit[1] = 12, .bit[2] = 12, .bit[3] = 12,

      .com[4] = 1, .com[5] = 2, .com[6] = 2, .com[7] = 3,
      .bit[4] = 10, .bit[5] = 10, .bit[6] = 11, .bit[7] = 11,

      .com[8] = 3, .com[9] = 2, .com[10] = 1, .com[11] = 0,
      .bit[8] = 13, .bit[9] = 13, .bit[10] = 13, .bit[11] = 13,

      .com[12] = 0, .com[13] = 1,
      .bit[12] = 11, .bit[13] = 11
    },
    { /* 5 */

      .com[0] = 3, .com[1] = 2, .com[2] = 1, .com[3] = 0,
      .bit[0] = 16, .bit[1] = 16, .bit[2] = 16, .bit[3] = 16,

      .com[4] = 1, .com[5] = 2, .com[6] = 2, .com[7] = 3,
      .bit[4] = 14, .bit[5] = 14, .bit[6] = 15, .bit[7] = 15,

      .com[8] = 3, .com[9] = 2, .com[10] = 1, .com[11] = 0,
      .bit[8] = 17, .bit[9] = 17, .bit[10] = 17, .bit[11] = 17,

      .com[12] = 0, .com[13] = 1,
      .bit[12] = 15, .bit[13] = 15
    },
    { /* 6 */

      .com[0] = 3, .com[1] = 2, .com[2] = 1, .com[3] = 0,
      .bit[0] = 20, .bit[1] = 20, .bit[2] = 20, .bit[3] = 20,

      .com[4] = 1, .com[5] = 2, .com[6] = 2, .com[7] = 3,
      .bit[4] = 18, .bit[5] = 18, .bit[6] = 19, .bit[7] = 19,

      .com[8] = 3, .com[9] = 2, .com[10] = 1, .com[11] = 0,
      .bit[8] = 21, .bit[9] = 21, .bit[10] = 21, .bit[11] = 21,

      .com[12] = 0, .com[13] = 1,
      .bit[12] = 19, .bit[13] = 19
    },
    { /* 7 */

      .com[0] = 3, .com[1] = 2, .com[2] = 1, .com[3] = 0,
      .bit[0] = 24, .bit[1] = 24, .bit[2] = 24, .bit[3] = 24,

      .com[4] = 1, .com[5] = 2, .com[6] = 2, .com[7] = 3,
      .bit[4] = 22, .bit[5] = 22, .bit[6] = 23, .bit[7] = 23,

      .com[8] = 3, .com[9] = 2, .com[10] = 1, .com[11] = 0,
      .bit[8] = 25, .bit[9] = 25, .bit[10] = 25, .bit[11] = 25,

      .com[12] = 0, .com[13] = 1,
      .bit[12] = 23, .bit[13] = 23
    }
  },
  .Number      = {
#if 0  
    {	/* 1 */
		/* A            B               C              D    */
      .com[0] = 3, .com[1] = 2, .com[2] = 1, .com[3] = 0,
      .bit[0] = 0, .bit[1] = 0, .bit[2] = 0, .bit[3] = 0,
		/* E            F               G              M    */
      .com[4] = 1, .com[5] = 2, .com[6] = 2, .com[7] = 1,
      .bit[4] = 38, .bit[5] = 38, .bit[6] = 39, .bit[7] = 1
    },
    {	/* 2 */
      .com[0] = 3, .com[1] = 2, .com[2] = 1, .com[3] = 0,
      .bit[0] = 4, .bit[1] = 4, .bit[2] = 4, .bit[3] = 4,

      .com[4] = 1, .com[5] = 2, .com[6] = 2, .com[7] = 1,
      .bit[4] = 2, .bit[5] = 2, .bit[6] = 3, .bit[7] = 5
    },
    {	/* 3 */
      .com[0] = 3, .com[1] = 2, .com[2] = 1, .com[3] = 0,
      .bit[0] = 8, .bit[1] = 8, .bit[2] = 8, .bit[3] = 8,

      .com[4] = 1, .com[5] = 2, .com[6] = 2, .com[7] = 1,
      .bit[4] = 6, .bit[5] = 6, .bit[6] = 7, .bit[7] = 9
    },
    {	/* 4 */
      .com[0] = 3, .com[1] = 2, .com[2] = 1, .com[3] = 0,
      .bit[0] = 12, .bit[1] = 12, .bit[2] = 12, .bit[3] = 12,

      .com[4] = 1, .com[5] = 2, .com[6] = 2, .com[7] = 1,
      .bit[4] = 10, .bit[5] = 10, .bit[6] = 11, .bit[7] = 13
    }, 
	{	/* 5 */
      .com[0] = 3, .com[1] = 2, .com[2] = 1, .com[3] = 0,
      .bit[0] = 16, .bit[1] = 16, .bit[2] = 16, .bit[3] = 16,

      .com[4] = 1, .com[5] = 2, .com[6] = 2, .com[7] = 1,
      .bit[4] = 14, .bit[5] = 14, .bit[6] = 15, .bit[7] = 17
    },
	{	/* 6 */
      .com[0] = 3, .com[1] = 2, .com[2] = 1, .com[3] = 0,
      .bit[0] = 20, .bit[1] = 20, .bit[2] = 20, .bit[3] = 20,

      .com[4] = 1, .com[5] = 2, .com[6] = 2, .com[7] = 1,
      .bit[4] = 18, .bit[5] = 18, .bit[6] = 19, .bit[7] = 21
    },
	{	/* 7 */
      .com[0] = 3, .com[1] = 2, .com[2] = 1, .com[3] = 0,
      .bit[0] = 24, .bit[1] = 24, .bit[2] = 24, .bit[3] = 24,

      .com[4] = 1, .com[5] = 2, .com[6] = 2, .com[7] = 1,
      .bit[4] = 22, .bit[5] = 22, .bit[6] = 23, .bit[7] = 25
    },
#endif    
	{	/* 8 */
      .com[0] = 0, .com[1] = 1, .com[2] = 2, .com[3] = 3,
      .bit[0] = 32, .bit[1] = 32, .bit[2] = 32, .bit[3] = 33,

      .com[4] = 2, .com[5] = 0, .com[6] = 1, .com[7] = 1,
      .bit[4] = 33, .bit[5] = 33, .bit[6] = 33, .bit[7] = 33
    },
    {	/* 9 */
      .com[0] = 0, .com[1] = 1, .com[2] = 2, .com[3] = 3,
      .bit[0] = 30, .bit[1] = 30, .bit[2] = 30, .bit[3] = 31,

      .com[4] = 2, .com[5] = 0, .com[6] = 1, .com[7] = 1,
      .bit[4] = 31, .bit[5] = 31, .bit[6] = 31, .bit[7] = 31
    },
    {	/* 10 */
      .com[0] = 0, .com[1] = 0, .com[2] = 2, .com[3] = 3,
      .bit[0] = 29, .bit[1] = 28, .bit[2] = 28, .bit[3] = 28,

      .com[4] = 2, .com[5] = 1, .com[6] = 1, .com[7] = 1,
      .bit[4] = 29, .bit[5] = 29, .bit[6] = 28, .bit[7] = 28
    },
    {	/* 11 */
      .com[0] = 0, .com[1] = 0, .com[2] = 2, .com[3] = 3,
      .bit[0] = 27, .bit[1] = 26, .bit[2] = 26, .bit[3] = 26,

      .com[4] = 2, .com[5] = 1, .com[6] = 1, .com[7] = 1,
      .bit[4] = 27, .bit[5] = 27, .bit[6] = 26, .bit[7] = 26
    }
  }
};

/**************************************************************************//**
 * 
 * Defines segments for the alphabet
 * Bit pattern below defined for alphabet (text segments)
 * 
 *****************************************************************************/
const uint16_t Nuvo_alphabet[] = {
  0x0000, /* space */
  0x1100, /* ! */
  0x0280, /* " */
  0x0000, /* # */
  0x0000, /* $ */
  0x0000, /* % */
  0x0000, /* & */
  0x0000, /* ?  */
  0x0039, /* ( */
  0x000f, /* ) */
  0x3fc0, /* * */
  0x1540, /* + */
  0x0000, /* , */
  0x0440, /* - */
  0x8000, /* . */
  0x2200, /* / */

  0x003f, /* 0 */
  0x0006, /* 1 */
  0x045b, /* 2 */
  0x044f, /* 3 */
  0x0466, /* 4 */
  0x046d, /* 5 */
  0x047d, /* 6 */
  0x0007, /* 7 */
  0x047f, /* 8 */
  0x046f, /* 9 */

  0x0000, /* : */
  0x0000, /* ; */
  0x0a00, /* < */
  0x0000, /* = */
  0x2080, /* > */
  0x0000, /* ? */
  0xffff, /* @ */

  0x0477, /* A */
  0x0a79, /* B */
  0x0039, /* C */
  0x20b0, /* D */
  0x0079, /* E */
  0x0071, /* F */
  0x047d, /* G */
  0x0476, /* H */
  0x0006, /* I */
  0x000e, /* J */
  0x0a70, /* K */
  0x0038, /* L */
  0x02b6, /* M */
  0x08b6, /* N */
  0x003f, /* O */
  0x0473, /* P */
  0x203f, /* Q */
  0x0c73, /* R */
  0x046d, /* S */
  0x1101, /* T */
  0x003e, /* U */
  0x2230, /* V */
  0x2836, /* W */
  0x2a80, /* X */
  0x046e, /* Y */
  0x2209, /* Z */

  0x0039, /* [ */
  0x0880, /* backslash */
  0x000f, /* ] */
  0x0001, /* ^ */
  0x0008, /* _ */
  0x0000, /* ` */

  0x1058, /* a */
  0x047c, /* b */
  0x0058, /* c */
  0x045e, /* d */
  0x2058, /* e */
  0x0471, /* f */
  0x0c0c, /* g */
  0x0474, /* h */
  0x0004, /* i */
  0x000e, /* j */
  0x0c70, /* k */
  0x0038, /* l */
  0x1454, /* m */
  0x0454, /* n */
  0x045c, /* o */
  0x0473, /* p */
  0x0467, /* q */
  0x0450, /* r */
  0x0c08, /* s */
  0x0078, /* t */
  0x001c, /* u */
  0x2010, /* v */
  0x2814, /* w */
  0x2a80, /* x */
  0x080c, /* y */
  0x2048, /* z */

  0x0000,
};

/**************************************************************************//**
 * Defines segments for the numeric display
 *****************************************************************************/
const uint16_t Nuvo_Numbers[] =
{
  0x3f, /* 0 */
  0x06, /* 1 */
  0xdb, /* 2 */
  0xcf, /* 3 */
  0xe6, /* 4 */
  0xed, /* 5 */
  0xfd, /* 6 */
  0x07, /* 7 */
  0xff, /* 8 */
  0xef, /* 9 */
  0xc0, /* - */
};


/** @defgroup S_LCDSYMBOL
  * @{
  */

typedef struct
{
	uint32_t com; /* Symbol COM line */
	uint32_t seg; /* Symbol SEG bit number */
} SYMBOL_TypeDef;

const SYMBOL_TypeDef S_LCDSYMBOL[] = 
{
	{3, 38},					/* 0 */
	{0, 38},					/* 1 */
	{0, 2},						/* 2 */
	{0, 6},						/* 3 */
	{0, 10},					/* 4 */
	{0, 14},					/* 5 */
	{0, 18},					/* 6 */
	{0, 22},					/* 7 */
	{3, 32},					/* 8 */
	{3, 30},					/* 9 */
	{3, 27},					/* 10 */
	{3, 2},						/* 11 */
	{3, 6},						/* 12 */
	{3, 10},					/* 13 */
	{3, 14},					/* 14 */
	{3, 18},					/* 15 */
	{3, 29},					/* 16 */
	{3, 37},					/* 17 */
	{2, 37},					/* 18 */
	{1, 37},					/* 19 */
	{0, 37},					/* 20 */
	{0, 36},					/* 21 */
	{1, 36},					/* 22 */
	{2, 36},					/* 23 */
	{3, 36},					/* 24 */
	{3, 35},					/* 25 */
	{2, 35},					/* 26 */
	{1, 35},					/* 27 */
	{0, 35},					/* 28 */
	{0, 34},					/* 29 */
	{3, 34},					/* 30 */
	{2, 34},					/* 31 */
	{1, 34},					/* 32 */	
	{3, 22},					/* 33 */
};
/**
  * @}
  */ 


#ifdef __cplusplus
}
#endif

#endif		/* __LCDDISPLAY_BTL001_H */

/*** (C) COPYRIGHT 2012 Nuvoton Technology Corp. ***/





