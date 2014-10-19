/* fxor.c */
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
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <err.h>

#include "fxor_exits.h"
#include "fxor.h"
#include "fxor_stream_xor.h"


/**
 * fxor()
 * 
 * If out_n is NULL, output to stdout
 * 
 * Return EX_OK (0): done Successfully
 * Return non-zero if:
 * 	I/O errors
 * 	key_file is empty
 * 	(in_file Or key_file) not exist Or not readable
 * 	out_file exist And not writable
 */

int fxor(const char *in_n, const char *key_n, const char *out_n, bool write_from_beginning)
{
	FILE *in_f = NULL, *key_f = NULL, *out_f = NULL;
	
	
	if (access(in_n, R_OK) || access(key_n, R_OK)
	       || (out_n != NULL && (!access(out_n, F_OK) && access(out_n, W_OK)))
	   )
	{
		if (access(in_n, R_OK))
		{ /* If the file NOT exist OR NOT readable */
			warn("%s", in_n);
		}
		if (access(key_n, R_OK))
		{ /* If the file NOT exist OR NOT readable */
			warn("%s", key_n);
		}
		if (out_n != NULL && (!access(out_n, F_OK) && access(out_n, W_OK)))
		{ /* If the file exist And NOT writable */
			warn("%s", out_n);
		}
		
		return EX_NOINPUT;
	}
	
	
	in_f = fopen(in_n, "rb");
	key_f = fopen(key_n, "rb");
	
	if (!in_f || !key_f)
	{
		if (!in_f)
		{
			warn("%s", in_n);
		}
		if (!key_f)
		{
			warn("%s", key_n);
		}
		
		return EX_IOERR;
	}
	
	
	if (out_n != NULL)
	{ /* output to a file */
		out_f = write_from_beginning == true ? fopen(out_n, "rb+") : fopen(out_n, "wb");
	}
	else
	{ /* output to stdout */
		out_f = stdout;
		out_n = "(stdout)";
	}
	
	if (!out_f)
	{
		warn("%s", out_n);
		return EX_IOERR;
	}
	
	
	return fxor_stream_xor(in_f, key_f, out_f, in_n, key_n, out_n);
}


void invalid_cmd_usage(void)
{
	fprintf(stdout, INVALID_CMD_USAGE_STR);
}


void usage(void)
{
	fprintf(stdout, FXOR_USAGE);
}


void version(void)
{
	fprintf(stdout, "fxor version %s\n", FXOR_VERSION);
}


void copyright(void)
{
	fprintf(stdout, "%s", FXOR_COPYING);
}
