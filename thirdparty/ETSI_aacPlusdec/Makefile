#
# Makefile for enhAacPlusDec
#

DATE        := $(shell date +%Y-%m-%d)
MAKE         = gmake

BASEDIR=./
include $(BASEDIR)/make.cfg 

INCDIR := -Ietsioplib -Ietsiop_ffrlib -Ietsiop_bitbuf -Ietsiop_sbrdec -Ietsiop_aacdec -Ietsiop_aacdec/src -I3g_lib -I3g_lib/linux

LIBS      = -L$(LIBPATH) -L3g_lib/linux -lenhAacPlusdec -lisomediafile -laudio

MAINOBJS     = 	$(OBJDIR)/main.$(obj)
OBJS         = 	$(OBJDIR)/fileifc.$(obj) \
		$(OBJDIR)/spline_resampler.$(obj)

SRC          = ./src
OBJ          = ./src

sources      =  $(SRC)/main.c \
		$(SRC)/fileifc.c \
		$(SRC)/spline_resampler.c \
		Test/TestIntrinsics.c

ifeq "$(MONO)" "1"
override CFLAGS += -DMONO_ONLY -DLP_SBR_ONLY
TARGET = enhAacPlusDec.mono
else
TARGET = enhAacPlusDec
endif # MONO

all: enhAacPlusDec

enhAacPlusDec: .depend $(MAINOBJS) $(OBJS) DECLIB 
	$(CXX) -o $(TARGET) $(MAINOBJS) $(OBJS) $(LIBS) $(LDFLAGS)

TestIntrinsics: .depend DECLIB
	$(CC) -pp -v -o TestIntrinsics Test/TestIntrinsics.c  -L./lib/Linux -Ietsioplib -Ietsiop_ffrlib -lenhAacPlusdec

.depend:
	@echo "Creating dependencies..."
	for i in $(sources); do \
	($(CC_DEP) -MM $(CPPFLAGS) $(INCDIR) $$i >> tmp_depend); done
	mv tmp_depend .depend

ETSIOPLIB:
	cd etsioplib; make WMOPS=$(WMOPS)

FFRLIB:
	make -C etsiop_ffrlib

BITBUF:
	make -C etsiop_bitbuf

AUDIO:
	cd audiolib ; make

UTILLIB:
	cd util ; make

AACDECLIB:
	make -C etsiop_aacdec MONO=$(MONO)

SBRDECLIB:
	make -C etsiop_sbrdec MONO=$(MONO)

DECLIB: ETSIOPLIB FFRLIB BITBUF AACDECLIB SBRDECLIB
	mkdir -p tmp-obj
	rm -f tmp-obj/*.$(obj)
	cd tmp-obj ; $(AR) x ../etsioplib/$(LIBPATH)/libetsiop.$(lib)
	cd tmp-obj ; $(AR) x ../etsiop_aacdec/$(LIBPATH)/libaacdec.$(lib)
	cd tmp-obj ; $(AR) x ../etsiop_sbrdec/$(LIBPATH)/libsbrdec.$(lib)
	cd tmp-obj ; $(AR) x ../etsiop_bitbuf/$(LIBPATH)/libbitbuf.$(lib)
	cd tmp-obj ; $(AR) x ../etsiop_ffrlib/$(LIBPATH)/libffr.$(lib)
	cd tmp-obj ; $(RM) ../$(LIBPATH)/libenhAacPlusdec.$(lib)
	cd tmp-obj ; $(AR) rcu ../$(LIBPATH)/libenhAacPlusdec.$(lib) *.$(obj)
	$(RM) -r tmp-obj

.PHONY: clean
clean:
	rm -f .depend
	rm -f $(OBJS) $(TARGET)
	make -C etsioplib     DEBUG=$(DEBUG) OPTIM=$(OPTIM) clean
	make -C etsiop_ffrlib DEBUG=$(DEBUG) OPTIM=$(OPTIM) clean
	make -C etsiop_bitbuf DEBUG=$(DEBUG) OPTIM=$(OPTIM) clean  
	make -C etsiop_aacdec DEBUG=$(DEBUG) OPTIM=$(OPTIM) clean
	make -C etsiop_sbrdec DEBUG=$(DEBUG) OPTIM=$(OPTIM) clean

.PHONY: distclean
distclean:
	rm -f .depend
	rm -f $(OBJS) $(TARGET)
	make -C etsiop_ffrlib distclean $(INTRINSICS)
	make -C etsiop_bitbuf distclean
	make -C etsiop_aacdec distclean
	make -C etsiop_sbrdec distclean

.PHONY: tags
tags:
	etags *.c *.cpp *.h


.PHONY:	always
always:	
	@if (test -d $(LIBPATH)); then echo; else echo "building directory structure..."; $(MK_DIR) $(LIBPATH) 2> /dev/null; $(MK_DIR) $(OBJDIR) 2> /dev/null; fi



-include always


-include .depend

