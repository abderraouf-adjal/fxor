#! /bin/sh

# for fxor (a tool to encrypt/decrypt a file using XOR operation to do one-time pad)

# Usage: opssl_rand.sh IN_FILE_NAME OUT_FILE_NAME

# This script take IN_FILE_NAME size and run openssl command to make a random file (OUT_FILE_NAME)
# OUT_FILE_NAME_SIZE = IN_FILE_NAME_SIZE


openssl_rand_cmd="`stat $1 --format=\"openssl rand %s -out $2\"`"

eval $openssl_rand_cmd
