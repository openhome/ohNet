#
# Makefile for fractional arithmetic library
#

BASEDIR=../
include $(BASEDIR)/make.cfg

INCDIR := -I. -I.. -I../etsioplib

################## user section: insert objlist here #######
LIB = libffr.$(lib)



OBJS =	$(OBJDIR)/transcendent.$(obj) \
	$(OBJDIR)/vector.$(obj) \
	$(OBJDIR)/dsp_fft32x32s.$(obj) \
	$(OBJDIR)/intrinsics-$(INTRINSICS).$(obj) \
	$(OBJDIR)/transcendent_enc.$(obj)

ifeq "$(INTRINSICS)" ""
INTRINSICS = dpf
endif

include ../stdtargets.cfg

DATE   :=$(shell date +%Y-%m-%d)
TARGET  = ffrlib
