SHELL=/bin/bash
TARGET = libanswer.a

OBJPATH = ../obj

LIBPATH = /usr/lib64

CFLAGS = -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX
CCOMLINE = $(CXX) -c $(CFLAGS) $< -o $@

OBJS = $(patsubst %.cpp, $(OBJPATH)/%.o, $(notdir $(wildcard *.cpp)))
DS = $(OBJS:.o=.d)

$(OBJPATH)/%.d : %.cpp
	echo -n $(OBJPATH)/ > $@
	$(CXX) -MM $(CFLAGS) $< >> $@
	echo -e \\t$(CCOMLINE:.d=.o) >> $@

all : $(OBJPATH)/$(TARGET)

$(OBJPATH)/$(TARGET) : $(DS) $(OBJS)
	$(AR) -rcs $(OBJPATH)/$(TARGET) $(OBJS) 

install:
	@cp $(OBJPATH)/$(TARGET) $(LIBPATH)

-include $(DS)

clean:
	@rm -f $(OBJPATH)/*
	@rm -f $(LIBPATH)/$(TARGET)

