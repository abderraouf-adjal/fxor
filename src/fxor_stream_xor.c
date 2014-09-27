/* fxor_stream_xor.c */
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
#include <sysexits.h>
#include <err.h>

#include "fxor_exits.h"
#include "fxor_stream_xor.h"
#include "is_empty_stream.h"


/**
 * fxor_stream_xor()
 * 
 * files/streams names are just to show them in errors messages
 * 
 * Return EX_OK (0): done Successfully
 * Return non-zero: Errors (like I/O errors), Or key_s is empty.
 */

int fxor_stream_xor(FILE *in_s, FILE *key_s, FILE *out_s,
	const char *in_n, const char *key_n, const char *out_n)
{
	static unsigned char data[XOR_BUFFSIZE], key[XOR_BUFFSIZE];
	size_t in_l = 0, key_l = 0, data_i = 0, key_i = 0;
	int is_empty_stream_r;
	
	if (!in_s || !key_s || !out_s)
	{
		if (!in_s)
		{
			warn("%s: %s", __func__, in_n);
		}
		if (!key_s)
		{
			warn("%s: %s", __func__, key_n);
		}
		if (!out_s)
		{
			warn("%s: %s", __func__, out_n);
		}
		
		return EX_IOERR;
	}
	
	
	/* Check if key stream is empty */
	if ((is_empty_stream_r = is_empty_stream(key_s, key_n)))
	{
		if (is_empty_stream_r == 1)
		{
			warnx("ERROR: '%s' is empty.", key_n);
		}
		
		return is_empty_stream_r; /* EX_NOKEY, EX_IOERR, ... */
	}
	
	
	while (1)
	{
		data_i = 0;
		
		in_l = fread(data, sizeof(unsigned char), sizeof(data), in_s);
		if (ferror(in_s))
		{
			warn("%s: %s", __func__, in_n);
			return EX_IOERR;
		}
		
		if (in_l)
		{
			while (data_i < in_l)
			{
				if (key_i >= key_l)
				{ /* Get Data From key_s */
					key_i = 0;
					
					key_l = fread(key, sizeof(unsigned char), sizeof(key), key_s);
					if (ferror(key_s))
					{
						warn("%s: %s", __func__, key_n);
						return EX_IOERR;
					}
					
					if (!key_l && feof(key_s))
					{ /* End Of key_s; Back to key_s beginning */
						rewind(key_s);
						continue;
					}
				}
				
				data[data_i] ^= key[key_i];
				
				data_i++;
				key_i++;
			}
			
			fwrite(data, sizeof(unsigned char), in_l, out_s);
			if (ferror(out_s))
			{
				warn("%s: %s", __func__, out_n);
				return EX_IOERR;
			}
		}
		else if (!in_l && feof(in_s))
		{ /* End Of in_s */
			return EX_OK;
		}
	}
}
