# Make file for POSIX compatible OSs with C99 GCC-compatible compiler

CC = cc
OPTIMIZATION = -O2
STD = -std=c99
CWARNS = -W -Wall -Wextra -Wformat=2 -Wstrict-prototypes -Wimplicit-function-declaration -Wredundant-decls -Wdeclaration-after-statement -Wconversion -Wsign-conversion -Wfloat-equal -Winit-self -Wundef -Wshadow -Wpointer-arith -Wmultichar -pedantic -Wunused-macros -Wcast-qual
CFLAGS = $(CWARNS) $(STD) $(OPTIMIZATION)

RM = rm -f
CP = cp -f
CD = cd
INSTALL = install -C
CHMOD = chmod

NFP = 644

PREFIX = /usr
BIN_DIR = $(PREFIX)/bin/
MAN_DIR = $(PREFIX)/share/man/man1/
DOC_DIR = $(PREFIX)/share/doc/fxor

SRC_DIR = src/
TGT = bin/
MAN_SRC_DIR = man/
DOC_SRC_DIR = doc/fxor


# Files
FXOR_EXEC_NAME = fxor
OPSSL_RAND_SCRIPT = scripts/opssl_rand

MAIN_SRC = main.c
MAIN_OBJ = main.o

FXOR_SRC = fxor.c
FXOR_OBJ = fxor.o

FXOR_STREAM_XOR_SRC = fxor_stream_xor.c
FXOR_STREAM_XOR_OBJ = fxor_stream_xor.o

FXOR_OBJS = $(SRC_DIR)$(MAIN_OBJ) $(SRC_DIR)$(FXOR_OBJ) $(SRC_DIR)$(FXOR_STREAM_XOR_OBJ)

FXOR_MAN = fxor.1

FXOR_DOCS = AUTHORS ChangeLog COPYING FAQ NEWS README


# Main target
$(TGT)$(FXOR_EXEC_NAME): $(FXOR_OBJS)
	$(CC) $(CFLAGS) $(FXOR_OBJS) -o $(TGT)$(FXOR_EXEC_NAME)
	$(CP) $(FXOR_DOCS) $(DOC_SRC_DIR)

$(SRC_DIR)$(MAIN_OBJ): $(SRC_DIR)$(MAIN_SRC)
	$(CD) $(SRC_DIR) && $(CC) -c $(CFLAGS) $(MAIN_SRC) -o $(MAIN_OBJ)

$(SRC_DIR)$(FXOR_OBJ): $(SRC_DIR)$(FXOR_SRC)
	$(CD) $(SRC_DIR) && $(CC) -c $(CFLAGS) $(FXOR_SRC) -o $(FXOR_OBJ)

$(SRC_DIR)$(FXOR_STREAM_XOR_OBJ): $(SRC_DIR)$(FXOR_STREAM_XOR_SRC)
	$(CD) $(SRC_DIR) && $(CC) -c $(CFLAGS) $(FXOR_STREAM_XOR_SRC) -o $(FXOR_STREAM_XOR_OBJ)


install:
	$(INSTALL) -D $(TGT)$(FXOR_EXEC_NAME) $(BIN_DIR)
	
	$(INSTALL) -D $(OPSSL_RAND_SCRIPT) $(BIN_DIR)
	
	$(INSTALL) -m $(NFP) -D $(MAN_SRC_DIR)$(FXOR_MAN) $(MAN_DIR)
	
	$(INSTALL) -d -D $(DOC_SRC_DIR) $(DOC_DIR)
	$(INSTALL) -m $(NFP) -D $(DOC_SRC_DIR)/* $(DOC_DIR)


.PHONY: clean

clean:
	$(RM) $(TGT)$(FXOR_EXEC_NAME)
	$(RM) $(FXOR_OBJS)
	$(CD) $(DOC_SRC_DIR) && $(RM) $(FXOR_DOCS)


uninstall:
	$(RM) $(BIN_DIR)$(FXOR_EXEC_NAME)
	$(RM) $(BIN_DIR)$(OPSSL_RAND_SCRIPT)
	$(RM) $(MAN_DIR)$(FXOR_MAN)
	$(RM) -r $(DOC_DIR)
