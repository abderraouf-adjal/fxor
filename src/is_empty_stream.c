/* is_empty_stream.c */
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
#include <err.h>


/**
 * is_empty_stream()
 * 
 * Need stream name to show error messages
 * 
 * Return:  0: Not empty; 1: Empty; -1: I/O Error
 */

int is_empty_stream(FILE *s, const char *s_name)
{
	if (fgetc(s) == EOF && !ferror(s))
	{
		rewind(s);
		
		if (fgetc(s) == EOF && !ferror(s))
		{
			return 1; /* Empty */
		}
		else if (!ferror(s))
		{
			if (fseek(s, 0, SEEK_END))
			{
				warn("%s: %s", __func__, s_name);
				return -1;
			}
		}
	}
	else if (!ferror(s))
	{
		if (fseek(s, -1, SEEK_CUR))
		{
			warn("%s: %s", __func__, s_name);
			return -1;
		}
	}
	else if (ferror(s))
	{
		warn("%s: %s", __func__, s_name);
		return -1;
	}
	
	return 0; /* Not empty */
}
