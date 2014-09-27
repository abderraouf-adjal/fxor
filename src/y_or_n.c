/* y_or_n.c */
/* 
 * Copyright (c) 2014, Abderraouf Adjal
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


#include <stdio.h>
#include <err.h>	/* warnx() */


/**
 * y_or_n()
 * 
 * Returns:
 *  1 if 1st char is: y Or Y
 *  0 if 1st char is: n Or N
 *  else return -1
 */

int y_or_n(void)
{
	int c, answer;
	
	/* Read the first character of the line. */
	c = fgetc(stdin);
	
	answer = c;
	
	/* Discard rest of input line. */
	while (c != '\n' && c != EOF)
	{
		c = fgetc(stdin);
	}
	
	if (answer == 'Y' || answer == 'y')
	{
		return 1;
	}
	else if (answer == 'N' || answer == 'n')
	{
		return 0;
	}
	else
	{ /* Invalid Answer */
		return -1;
	}
}


/**
 * fxor_y_or_n()
 * 
 * Return:
 *  1 if 1st char is: y Or Y
 *  0 if 1st char is: n Or N
 */

int fxor_y_or_n(const char *q)
{
	int a;
	
	while (1)
	{
		fprintf(stderr, "%s [y/n] ", q);
		
		a = y_or_n();
		
		if (a == 0 || a == 1)
		{
			return a;
		}
		else
		{
			warnx("Invalid Answer.");
		}
	}
}
