#
# Makefile for AAC decoder library
#

BASEDIR=../
include $(BASEDIR)/make.cfg


INCDIR := -I. -I../etsioplib -I../etsiop_ffrlib -I../etsiop_bitbuf -I../etsiop_sbrdec -I../etsiop_sbrdec/src

LIB = libaacdec.$(lib)

OBJS =  $(OBJDIR)/aacdecoder.$(obj) \
        $(OBJDIR)/block.$(obj) \
        $(OBJDIR)/channel.$(obj) \
        $(OBJDIR)/channelinfo.$(obj) \
        $(OBJDIR)/imdct.$(obj) \
        $(OBJDIR)/longblock.$(obj) \
        $(OBJDIR)/shortblock.$(obj) \
        $(OBJDIR)/stereo.$(obj) \
        $(OBJDIR)/aac_ram.$(obj) \
        $(OBJDIR)/aac_rom.$(obj) \
        $(OBJDIR)/tns.$(obj) \
        $(OBJDIR)/streaminfo.$(obj) \
	$(OBJDIR)/conceal.$(obj) \
	$(OBJDIR)/pns.$(obj) \


OBJS += $(OBJDIR)/datastream.$(obj) \
        $(OBJDIR)/bitstream.$(obj) \
        $(OBJDIR)/pulsedata.$(obj)

ifeq "$(MONO)" "1"
override CFLAGS += -DMONO_ONLY -DLP_SBR_ONLY
endif

include ../stdtargets.cfg

DATE   :=$(shell date +%Y-%m-%d)
TARGET  = aacdeclib
