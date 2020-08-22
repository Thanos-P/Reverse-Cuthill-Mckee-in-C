# ####################################################################
#
#			   C/C++ Makefile
#
#	Modified by: Thanos Paraskevas
#							 athanasps <athanasps@ece.auth.gr>
# Original:
# Author: Dimitris Floros <fcdimitr@auth.gr>
#
# Adapted from
#  http://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
#
# ####################################################################
#
# 'make'        build executable file 'main'
# 'make lib'	build the libraries .a
# 'make clean'  removes all .o and executable files
#

# define the shell to bash
SHELL := /bin/bash

# define the C/C++ compiler to use,default here is clang
CC = gcc-7

# define compile-time flags
CFLAGS = -O3 -Wall -fcilkplus

# define any directories containing header files
INCLUDES = -Iinc

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib specify
#   their path using -Lpath, something like:
LDFLAGS =

# define any libraries to link into executable:
#   To ling libusb-1.0 :
#   LIBS = -lusb-1.0
LIBS =
# define the source file for the library
SRC = RCM

#define auxiliary file names
AUX = queue myQuickSort mmio

# define the different possible executables
TYPES = sequential

# define the executable file name
MAIN = main

# define paths to .a files
LIBDIR = ./lib
# and .c files
SRCDIR = ./src

# call everytime
.PRECIOUS: %.a

all: $(addprefix $(MAIN)_, $(TYPES))

lib: $(addprefix $(LIBDIR)/, $(addsuffix .a, $(addprefix $(SRC)_, $(TYPES)))) $(addprefix $(LIBDIR)/, $(addsuffix .a, $(AUX)))

$(MAIN)_%: $(SRCDIR)/$(MAIN).c $(LIBDIR)/$(SRC)_%.a $(addprefix $(LIBDIR)/, $(addsuffix .a, $(AUX)))
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .cpp file) and $@: the name of the target of the rule (a .o file)

$(LIBDIR)/%.a: $(LIBDIR)/%.o
	ar rcs $@ $<

$(LIBDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	$(RM) $(LIBDIR)/*.o $(LIBDIR)/*.a *~ $(addprefix $(MAIN)_, $(TYPES))
