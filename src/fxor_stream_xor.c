/* fxor_stream_xor.c */
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
#include <err.h>

#include "fxor_exits.h"
#include "fxor_stream_xor.h"


/**
 * fxor_stream_xor()
 * 
 * files/fp names are just to show them in errors messages
 * 
 * Return FXOR_EX_OK (0): Done Successfully
 * Return non-zero:  Errors (e.g., I/O errors), OR key_fp is empty.
 */

int fxor_stream_xor(FILE *in_fp, FILE *key_fp, FILE *out_fp,
	const char *in_n, const char *key_n, const char *out_n)
{
	static unsigned char data[FXOR_XOR_BUFFSIZE], key[FXOR_XOR_BUFFSIZE];
	size_t in_l, key_l = 0, key_i = 0, data_i;
	int is_empty_key_fp_r;
	
	if (!in_fp || !key_fp || !out_fp) {
		if (!in_fp) {
			warn("%s: %s", __func__, in_n);
		}
		if (!key_fp) {
			warn("%s: %s", __func__, key_n);
		}
		if (!out_fp) {
			warn("%s: %s", __func__, out_n);
		}
		
		return FXOR_EX_IOERR;
	}
	
	/* Check if key_fp is empty */
	if ((is_empty_key_fp_r = is_empty_fp(key_fp, key_n))) {
		if (is_empty_key_fp_r == 1) {
			warnx("Key file '%s' is empty.", key_n);
			return FXOR_EX_NOKEY;
		}
		
		return FXOR_EX_IOERR;
	}
	
	
	while (1)
	{
		data_i = 0;
		
		in_l = fread(data, sizeof(unsigned char), sizeof(data), in_fp);
		if (ferror(in_fp)) {
			warn("%s: %s", __func__, in_n);
			return FXOR_EX_IOERR;
		}
		
		if (in_l) {
			while (data_i < in_l)
			{
				if (key_i >= key_l) {
					/* Get Data From key_fp */
					
					key_i = 0;
					
					key_l = fread(key, sizeof(unsigned char), sizeof(key), key_fp);
					if (ferror(key_fp)) {
						warn("%s: %s", __func__, key_n);
						return FXOR_EX_IOERR;
					}
					
					if (!key_l && feof(key_fp)) {
						/* End Of key_fp; Back to key_fp beginning */
						if (fseek(key_fp, 0L, SEEK_SET)) {
							return FXOR_EX_IOERR;
						}
						continue;
					}
				}
				
				data[data_i] ^= key[key_i];
				
				data_i++;
				key_i++;
			}
			
			fwrite(data, sizeof(unsigned char), in_l, out_fp);
			if (ferror(out_fp)) {
				warn("%s: %s", __func__, out_n);
				return FXOR_EX_IOERR;
			}
		}
		else if (!in_l && feof(in_fp)) {
			/* End Of in_fp */
			return FXOR_EX_OK;
		}
	}
}


/**
 * is_empty_fp()
 * 
 * Need fp name to show error messages
 * Return:  (0): NOT empty;  (1): Empty;  (-1): I/O Error
 */

int is_empty_fp(FILE *fp, const char *fp_name)
{
	if (fgetc(fp) == EOF && !ferror(fp)) {
		if (fseek(fp, 0L, SEEK_SET)) {
			goto err;
		}
		
		if (fgetc(fp) == EOF && !ferror(fp)) {
			return 1; /* Empty */
		}
		else if (!ferror(fp)) {
			if (fseek(fp, 0L, SEEK_END)) {
				goto err;
			}
		}
	}
	else if (!ferror(fp)) {
		if (fseek(fp, -1L, SEEK_CUR)) {
			goto err;
		}
	}
	
	if (!ferror(fp)) {
		return 0; /* NOT empty */
	}
	
	err:
	warn("%s", fp_name);
	return -1;
}
