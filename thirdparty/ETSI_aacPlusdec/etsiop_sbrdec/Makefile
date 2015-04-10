#
# Makefile for SBR decoder - library
#

BASEDIR=../
include $(BASEDIR)/make.cfg

INCDIR := -I. -I../etsioplib -I../etsiop_ffrlib -I../etsiop_aacdec -I../etsiop_aacdec/src -I../etsiop_bitbuf -I../src -I./src


################## user section: insert objlist here #######
LIB = libsbrdec.$(lib)


OBJS =	$(OBJDIR)/env_calc.$(obj) \
	$(OBJDIR)/env_dec.$(obj) \
	$(OBJDIR)/env_extr.$(obj) \
	$(OBJDIR)/freq_sca.$(obj) \
	$(OBJDIR)/lpp_tran.$(obj) \
	$(OBJDIR)/sbr_ram.$(obj) \
	$(OBJDIR)/sbr_rom.$(obj) \
	$(OBJDIR)/sbr_dec.$(obj) \
	$(OBJDIR)/sbrdecoder.$(obj) \
	$(OBJDIR)/aacpluscheck.$(obj) \
	$(OBJDIR)/qmf_dec.$(obj) \
	$(OBJDIR)/sbr_crc.$(obj)

ifeq "$(MONO)" "1"
override CFLAGS += -DMONO_ONLY -DLP_SBR_ONLY
else
OBJS += $(OBJDIR)/ps_dec.$(obj) \
	$(OBJDIR)/ps_bitdec.$(obj) \
	$(OBJDIR)/hybrid.$(obj)
endif

include ../stdtargets.cfg

DATE   :=$(shell date +%Y-%m-%d)
TARGET  = sbrdeclib
