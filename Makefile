# Make file for POSIX compatible OSs with C99 GCC-compatible compiler

CC = cc
CFLAGS = -std=c99 -O2 -funroll-loops
CWARNINGS = -Wall -Wextra -Wformat=2 -Wstrict-prototypes -Wdeclaration-after-statement -Wconversion -Wsign-conversion -Winit-self -pedantic
#LIBS = 

RM = rm -f
CP = cp -f
INSTALL = install -C
CD = cd
CHMOD = chmod

NFP = 644

SRC_DIR = src/
TGT = bin/
MAN_SRC_DIR = man/
DOC_SRC_DIR = doc/fxor

INSTALL_ROOT = /usr
BIN_DIR = $(INSTALL_ROOT)/bin/
MAN_DIR = $(INSTALL_ROOT)/share/man/man1/
DOC_DIR = $(INSTALL_ROOT)/share/doc/fxor


# Files
FXOR_EXEC_NAME = fxor

MAIN_SRC = main.c
MAIN_OBJ = main.o

FXOR_SRC = fxor.c
FXOR_OBJ = fxor.o

IS_EMPTY_STREAM_SRC = is_empty_stream.c
IS_EMPTY_STREAM_OBJ = is_empty_stream.o

FXOR_STREAM_XOR_SRC = fxor_stream_xor.c
FXOR_STREAM_XOR_OBJ = fxor_stream_xor.o

Y_OR_N_SRC = y_or_n.c
Y_OR_N_OBJ = y_or_n.o

FXOR_OBJS = $(SRC_DIR)$(MAIN_OBJ) $(SRC_DIR)$(FXOR_OBJ) $(SRC_DIR)$(IS_EMPTY_STREAM_OBJ) $(SRC_DIR)$(FXOR_STREAM_XOR_OBJ) $(SRC_DIR)$(Y_OR_N_OBJ)

FXOR_MAN = fxor.1

FXOR_DOCS = AUTHORS ChangeLog COPYING FAQ NEWS README


# Main target
$(TGT)$(FXOR_EXEC_NAME): $(FXOR_OBJS)
	$(CC) $(CWARNINGS) $(CFLAGS) $(FXOR_OBJS) -o $(TGT)$(FXOR_EXEC_NAME)
	$(CP) $(FXOR_DOCS) $(DOC_SRC_DIR)

$(SRC_DIR)$(MAIN_OBJ): $(SRC_DIR)$(MAIN_SRC)
	$(CD) $(SRC_DIR) && $(CC) -c $(CWARNINGS) $(CFLAGS) $(MAIN_SRC) -o $(MAIN_OBJ)

$(SRC_DIR)$(FXOR_OBJ): $(SRC_DIR)$(FXOR_SRC)
	$(CD) $(SRC_DIR) && $(CC) -c $(CWARNINGS) $(CFLAGS) $(FXOR_SRC) -o $(FXOR_OBJ)

$(SRC_DIR)$(IS_EMPTY_STREAM_OBJ): $(SRC_DIR)$(IS_EMPTY_STREAM_SRC)
	$(CD) $(SRC_DIR) && $(CC) -c $(CWARNINGS) $(CFLAGS) $(IS_EMPTY_STREAM_SRC) -o $(IS_EMPTY_STREAM_OBJ)

$(SRC_DIR)$(FXOR_STREAM_XOR_OBJ): $(SRC_DIR)$(FXOR_STREAM_XOR_SRC)
	$(CD) $(SRC_DIR) && $(CC) -c $(CWARNINGS) $(CFLAGS) $(FXOR_STREAM_XOR_SRC) -o $(FXOR_STREAM_XOR_OBJ)

$(SRC_DIR)$(Y_OR_N_OBJ): $(SRC_DIR)$(Y_OR_N_SRC)
	$(CD) $(SRC_DIR) && $(CC) -c $(CWARNINGS) $(CFLAGS) $(Y_OR_N_SRC) -o $(Y_OR_N_OBJ)


install:
	$(INSTALL) -D $(TGT)$(FXOR_EXEC_NAME) $(BIN_DIR)
	
	$(INSTALL) -m $(NFP) -D $(MAN_SRC_DIR)$(FXOR_MAN) $(MAN_DIR)
	
	$(INSTALL) -d -D $(DOC_SRC_DIR) $(DOC_DIR)
	$(INSTALL) -m $(NFP) -D $(DOC_SRC_DIR)/* $(DOC_DIR)


# Phony means not a "real" target, it doesn't build anything
# The phony target "clean" is used to remove all compiled object files.

.PHONY: clean

clean:
	$(RM) $(TGT)$(FXOR_EXEC_NAME)
	$(RM) $(FXOR_OBJS)
	$(CD) $(DOC_SRC_DIR) && $(RM) $(FXOR_DOCS)


uninstall:
	$(RM) $(BIN_DIR)$(FXOR_EXEC_NAME)
	$(RM) $(MAN_DIR)$(FXOR_MAN)
	$(RM) -r $(DOC_DIR)
