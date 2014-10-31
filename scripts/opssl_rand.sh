#! /bin/sh

# for fxor (a tool to encrypt/decrypt a file using XOR operation to do one-time pad)

# Usage: opssl_rand.sh IN_FILE_NAME OUT_FILE_NAME

# This script take IN_FILE_NAME size and run openssl command to make
# a random file (OUT_FILE_NAME), So OUT_FILE_NAME_SIZE = IN_FILE_NAME_SIZE


if ! [ "$#" -eq 2 ]; then
	printf 'Usage: %s IN_FILE_NAME OUT_FILE_NAME\n\n' "$0"
	printf 'This script take IN_FILE_NAME size and run openssl command to make\n'
	printf 'a random file (OUT_FILE_NAME), So OUT_FILE_NAME_SIZE = IN_FILE_NAME_SIZE\n'
	
	exit 64;
fi

openssl_rand_cmd="`stat \"$1\" --format=\"openssl rand %s -out \"$2\"\"`"

eval $openssl_rand_cmd
