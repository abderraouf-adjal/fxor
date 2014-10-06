/* main.c */
/* fxor - A small utility to encrypt/decrypt a file using XOR cipher to do One-Time Pad */
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
#include <sysexits.h>
#include <err.h>

#include "fxor_exits.h"
#include "fxor.h"	/* fxor.h include stdbool.h too */
#include "y_or_n.h"


int main(int argc, char *argv[])
{
	char *in_n = NULL, *key_n = NULL, *out_n = NULL;
	
	
	if (argc >= 2)
	{
		in_n = argv[1];
		
		if (argc >= 3)
		{
			key_n = argv[2];
			
			if (argc >= 4)
			{
				out_n = argv[3];
			}
		}
	}
	
	
	if (argc == 2)
	{
		if (!strcmp("--help", argv[1]))
		{
			usage();
			return EX_OK;
		}
		else if (!strcmp("--version", argv[1]))
		{ /* Print version and copyright */
			version();
			copyright();
			return EX_OK;
		}
	}
	else if (argc == 3)
	{ /* Output to stdout */
		return fxor(in_n, key_n, NULL, false);
	}
	else if (argc == 4)
	{
		if (access(out_n, F_OK))
		{ /* NOT exist */
			return fxor(in_n, key_n, out_n, false);
		}
		else
		{
			warnx(FILE_EXIST_WARN, out_n);
			warnx(FXOR_ABORT_STR);
			return FXOR_EX_ABORT;
		}
	}
	else if (argc == 5)
	{
		if (!strcmp("--overwrite", argv[4]) || !strcmp("-r", argv[4]))
		{ /* Overwrite (destroy contents) OUT_FILE */
			return fxor(in_n, key_n, out_n, false);
		}
		else if (!strcmp("--output-to-beginning", argv[4]) || !strcmp("-s", argv[4]))
		{ /* Start output from OUT_FILE beginning */
			if (!access(out_n, F_OK))
			{ /* exist */
				return fxor(in_n, key_n, out_n, true);
			}
			else
			{
				return fxor(in_n, key_n, out_n, false);
			}
		}
		else if (!strcmp("--ask", argv[4]) || !strcmp("-i", argv[4]))
		{
			if (access(out_n, F_OK))
			{ /* NOT exist */
				return fxor(in_n, key_n, out_n, false);
			}
			else
			{
				warnx(FILE_EXIST_WARN, out_n);
				
				if (fxor_y_or_n("Overwrite OUT_FILE then output?"))
				{
					return fxor(in_n, key_n, out_n, false);
				}
				else if (fxor_y_or_n("Start output from OUT_FILE beginning?"))
				{
					return fxor(in_n, key_n, out_n, true);
				}
				else
				{
					warnx(FXOR_ABORT_STR);
					return FXOR_EX_ABORT;
				}
			}
		}
	}
	else if (argc == 6 && (!strcmp("--ask", argv[4]) || !strcmp("-i", argv[4])))
	{
		if (!strcmp("--overwrite", argv[5]) || !strcmp("-r", argv[5]))
		{ /* Overwrite (destroy contents) OUT_FILE */
			if (access(out_n, F_OK))
			{ /* NOT exist */
				return fxor(in_n, key_n, out_n, false);
			}
			else
			{
				warnx(FILE_EXIST_WARN, out_n);
				
				if (fxor_y_or_n("Overwrite OUT_FILE then output?"))
				{
					return fxor(in_n, key_n, out_n, false);
				}
				else
				{
					warnx(FXOR_ABORT_STR);
					return FXOR_EX_ABORT;
				}
			}
		}
		else if (!strcmp("--output-to-beginning", argv[5]) || !strcmp("-s", argv[5]))
		{ /* Start output from OUT_FILE beginning */
			if (access(out_n, F_OK))
			{ /* NOT exist */
				return fxor(in_n, key_n, out_n, false);
			}
			else
			{
				warnx(FILE_EXIST_WARN, out_n);
				
				if (fxor_y_or_n("Start output from OUT_FILE beginning?"))
				{
					return fxor(in_n, key_n, out_n, true);
				}
				else
				{
					warnx(FXOR_ABORT_STR);
					return FXOR_EX_ABORT;
				}
			}
		}
	}
	
	invalid_cmd_usage();
	
	return EX_USAGE;
}
