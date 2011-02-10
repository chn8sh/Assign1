# @file Makefile
# compiles program files when modified
#
# @author Christopher Nostrand (chn8sh)
# @date 06 February 2011	(created)
#		06 February 2011	(last updated)		Modified by: Christopher Nostrand

# macros
CC = gcc
CFLAGS = -ggdb -Wall
OFILES = Driver.o
OUTPUT = run
.SUFFIXES: .o .c


# target rules
compile: List.h $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(OUTPUT)

clean: 
	rm *.o *.stackdump run