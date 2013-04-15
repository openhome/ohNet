include make.cfg

OBJS =	$(OBJDIR)/testapp.o 

TARGET=testapp


all: $(OBJS) etsioplib
	$(CXX) $(CFLAGS) -o $(TARGET) $(OBJS) -L../ -L../$(LIBPATH) -letsiop

etsioplib:
	cd ..; $(MAKE) WMPOS=$(WMOPS) OPTIM=$(OPTIM) DEBUG=$(DEBUG)

clean:
	rm -fr $(OBJDIR)
	rm $(TARGET)

cleanall: clean
	cd ..; $(MAKE) OPTIM=$(OPTIM) DEBUG=$(DEBUG)  clean


###################
# Dependencies
.PHONY:	always
always:	
	@if (test -d $(OBJDIR)); then echo; else echo "building directory structure..."; $(MK_DIR) $(OBJDIR) 2> /dev/null; fi
-include always

TEMP = $(OBJS)
FIND = $(findstring obj,$(shell ls $(OBJDIR) 2> /dev/null))
ifeq "$(FIND)" "obj"
  SOURCE = $(subst .o,.cpp,$(TEMP))
  -include $(SOURCE:.cpp=.d)
  SOURCE = $(subst .o,.c,$(TEMP))
  -include $(SOURCE:.c=.d)
endif
