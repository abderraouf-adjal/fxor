## Welcome to fxor home page.

> **fxor** is a tool to encrypt/decrypt a file using [XOR operation](http://en.wikipedia.org/wiki/XOR_cipher) to do [one-time pad](http://en.wikipedia.org/wiki/One-time_pad). **fxor** follows the [Unix philosophy](http://en.wikipedia.org/wiki/Unix_philosophy).


***

## Syntax

	fxor IN_FILE KEY_FILE
	fxor IN_FILE KEY_FILE OUT_FILE [OPTION]

Display usage information:

	fxor --help

Display version and copyright information:

	fxor --version


***

## Description

fxor is a tool that you can use to encrypt/decrypt **IN_FILE** content
with **KEY_FILE** content using XOR operation, and output to:

*  The file **OUT_FILE**.
*  *STDOUT* if **OUT_FILE** not defined.

fxor can be used as [OTP (One-Time Pad)](http://en.wikipedia.org/wiki/One-time_pad) tool.

**IN_FILE**: Input file name, Witch will processed.

**KEY_FILE**: Key file name, Usually random bytes file.

**OUT_FILE**: Output file name.


***

## Options

`-r`:
Overwrite (destroy contents) **OUT_FILE** then output

`-s`:
Start output from **OUT_FILE** beginning and replace bytes,
Perfect to encrypt/decrypt **IN_FILE** and output to **IN_FILE**!


***

## Examples

Output to **OUT_FILE** (overwrite if exist):

	fxor IN_FILE KEY_FILE OUT_FILE -r

Output to **OUT_FILE** and replace byte by byte from beginning:

	fxor IN_FILE KEY_FILE OUT_FILE -s

Output to *STDOUT*:

	fxor IN_FILE KEY_FILE


***

## fxor releases

* [fxor releases](https://github.com/abderraouf-adjal/fxor/releases)


***

## fxor FAQ

See the file '[FAQ](https://github.com/abderraouf-adjal/fxor/blob/master/FAQ)' for details.


***

## Requirements

C99 GCC-compatible compiler, e.g.: gcc, clang.

unix-like OS, e.g.: GNU/Linux, *BSD.


***

## Installation

After you unpack the distribution tarball and change into the source directory:

#### Compile:

	% make


#### Install:

	% make install

You can install/copy files in a different destination:

	% make PREFIX="/directory/directory" install


#### Uninstall:

	% make uninstall

Or:

	% make PREFIX="/directory/directory" uninstall


***

## Reporting bugs

Report fxor bugs to: <abderraouf.adjal@gmail.com>

Or [create an issue on GitHub](https://github.com/abderraouf-adjal/fxor/issues).


***

## Copyright

Copyright (c) 2014-2015 [Abderraouf Adjal](https://github.com/abderraouf-adjal).  All rights reserved.

License: [BSD 2-Clause License (Simplified BSD License)](http://opensource.org/licenses/BSD-2-Clause). There is NO WARRANTY.

See the file '[COPYING](https://github.com/abderraouf-adjal/fxor/blob/master/COPYING)' for details.
