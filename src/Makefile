CC=cc
PCRE2_DIR=/home/diego/Projects/pcre2-10.21
CFLAGS=-I. -I$(PCRE2_DIR)/src -Wall -pedantic -std=gnu99
BIN_DIR=../bin/
EXECUTABLE=$(BIN_DIR)/tokenize
BINARIES=$(EXECUTABLE)

all: $(BINARIES)

$(EXECUTABLE): read_stdin.o treebank_tokenize.o regex_replace.o \
	treebank_tokens.o main.c
	$(CC) $(CFLAGS) treebank_tokenize.o read_stdin.o \
	regex_replace.o treebank_tokens.o \
	$(PCRE2_DIR)/.libs/libpcre2-8.a main.c -o $(EXECUTABLE)

read_stdin.o: read_stdin.c
	$(CC) $(CFLAGS) -c read_stdin.c

treebank_tokenize.o: treebank_tokens.o regex_replace.o treebank_tokenize.c
	$(CC) $(CFLAGS) treebank_tokens.o regex_replace.o -c treebank_tokenize.c

treebank_tokens.o: treebank_tokens.c
	$(CC) $(CFLAGS) -c treebank_tokens.c

regex_replace.o: regex_replace.c
	$(CC) $(CFLAGS) -c regex_replace.c

clean:
	rm -rf *.o $(BINARIES)
