#
# Copyright (C) 2011 Richard Cochran <richardcochran@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

KBUILD_OUTPUT ?= /lib/modules/$(shell uname -r)/build

#CROSS_COMPILE = /export/crosstools/yocto-1.0/sysroots/x86_64-spirentsdk-linux/usr/bin/x86_64-spirent-linux/x86_64-spirent-linux-

DEBUG	=
CC	= $(CROSS_COMPILE)gcc
#INC	= -I$(KBUILD_OUTPUT)/usr/include
CFLAGS	= -Wall $(INC) $(DEBUG) $(EXTRA_CFLAGS)
LDLIBS	= -lm -lrt $(EXTRA_LDFLAGS)
PRG	= commd
OBJ	= config.o  commd.o

OBJECTS	= $(OBJ)
SRC	= $(OBJECTS:.o=.c)
DEPEND	= $(OBJECTS:.o=.d)
srcdir	:= $(dir $(lastword $(MAKEFILE_LIST)))
VPATH	= $(srcdir)

all: $(PRG)

#ptp4l: $(OBJ)
commd: $(OBJ)


clean:
	rm -f $(OBJECTS) $(DEPEND)

distclean: clean
	rm -f $(PRG)

# Implicit rule to generate a C source file's dependencies.
%.d: %.c
	@echo DEPEND $<; \
	rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

ifneq ($(MAKECMDGOALS), clean)
ifneq ($(MAKECMDGOALS), distclean)
-include $(DEPEND)
endif
endif
