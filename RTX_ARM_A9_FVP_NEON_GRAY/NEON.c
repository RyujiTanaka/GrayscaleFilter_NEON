/*----------------------------------------------------------------------------
 *      CMSIS-RTOS  -  RTX
 *----------------------------------------------------------------------------
 *      Name:    NEON.C
 *      Purpose: RTX example program
 *----------------------------------------------------------------------------
 *
 * Copyright (c) 1999-2009 KEIL, 2009-2015 ARM Germany GmbH
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  - Neither the name of ARM  nor the names of its contributors may be used 
 *    to endorse or promote products derived from this software without 
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/

#include <stdio.h>                    /* standard I/O .h-file                */
#include "rt_TypeDef.h"
#include "rt_Time.h"
#include "cmsis_os.h"

#define SRC_BUFFER 0x80600000
#define DST_BUFFER 0x80700000
#define BMP_WIDTH 640
#define BMP_HEIGHT 480
#define BMP_BYTE 3
#define BMP_DATA_MAX 0x000E1000	// 640 x 480 x 3(RGB_24_888) = (0x000E1000)


static void fill_screen(unsigned char r, unsigned char g, unsigned char b)
{
	unsigned int i;

	for (i = 0; i < BMP_DATA_MAX; i++)
	{
		// RGB 32bit 888
		((volatile unsigned char *)DST_BUFFER)[i]     = b;	// blue
		((volatile unsigned char *)DST_BUFFER)[i + 1] = g;	// green
		((volatile unsigned char *)DST_BUFFER)[i + 2] = r;	// red
	}
}

static void set_bmp()
{
	unsigned int x, y, xmax, ymax;

	xmax = BMP_WIDTH * BMP_BYTE;
	ymax = BMP_HEIGHT - 1;

	for (y = 0; y <= ymax; y++)
	{
		for (x = 0; x <= xmax; x++)
		{
			((unsigned char *)DST_BUFFER)[(y * xmax) + x] = ((unsigned char *)SRC_BUFFER)[(ymax - y) * xmax + x];
		}
	}
}

void convert(unsigned char * dst, unsigned char * src)
{
	int i;
	int blue, green, red, gray;

	for (i = 0; i < (BMP_WIDTH * BMP_HEIGHT); i++)
	{
		// RGB 32bit 888
		blue  = *src++;	// blue
		green = *src++;	// green
		red   = *src++;	// red

		// gray scaling
		gray = (red * 77 + green * 150 + blue * 29) >> 8;

        *dst++ = gray;	// blue
        *dst++ = gray;	// green
        *dst++ = gray;	// red
	}
}

/*----------------------------------------------------------------------------
 *   Main Thread
 *---------------------------------------------------------------------------*/
int main (void) {                     /* program execution starts here       */
	unsigned int starttime;
	unsigned int endtime;

	fill_screen(0xFF, 0xFF, 0xFF);

	starttime = rt_time_get();
	convert((unsigned char *)DST_BUFFER, (unsigned char *)SRC_BUFFER);
	endtime = rt_time_get();
	printf("%d ms\n", endtime - starttime);

	return 0;
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/

