/* main.c */
/* fxor - A small utility to encrypt/decrypt a file using XOR cipher to do One-Time Pad */
/* 
 * Copyright (c) 2014-2015, Abderraouf Adjal
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
#include <err.h>

#include "fxor.h"	/* fxor.h include stdbool.h */
#include "fxor_exits.h"


int main(int argc, char *argv[])
{
	const char *in_n  = argc >= 3 ? argv[1] : NULL;
	const char *key_n = argc >= 3 ? argv[2] : NULL;
	const char *out_n = argc >= 4 ? argv[3] : NULL;
	
	if (argc == 2)
	{
		if (!strcmp("--help", argv[1]))
		{ /* Print usage help */
			fprintf(stdout, FXOR_USAGE);
			return FXOR_EX_OK;
		}
		else if (!strcmp("--version", argv[1]))
		{ /* Print version and copyright */
			fprintf(stdout, "fxor version %s\n%s", FXOR_VERSION, FXOR_COPYING);
			return FXOR_EX_OK;
		}
	}
	else if (argc == 3)
	{ /* Output to stdout */
		return fxor(in_n, key_n, NULL, false);
	}
	else if (argc == 4)
	{
		if (access(out_n, F_OK))
		{ /* If out_n NOT exist */
			return fxor(in_n, key_n, out_n, false);
		}
		else
		{
			warnx("WARNING: '%s' is exist", out_n);
			warnx("Abort.");
			return FXOR_EX_ABORT;
		}
	}
	else if (argc == 5)
	{
		if (!strcmp("-r", argv[4]) || (!strcmp("-s", argv[4]) && access(out_n, F_OK)))
		{ /* If Overwrite OUT_FILE option OR (Start output from OUT_FILE beginning option AND out_n NOT exist) */
			return fxor(in_n, key_n, out_n, false);
		}
		else if (!strcmp("-s", argv[4]))
		{ /* Start output from OUT_FILE beginning */
			return fxor(in_n, key_n, out_n, true);
		}
	}
	
	fprintf(stdout, INVALID_CMD_USAGE_STR);
	return FXOR_EX_USAGE;
}
