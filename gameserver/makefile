SHELL=/bin/bash
TARGET = ../bin/gameserver
OBJPATH = obj

CXX = x86_64-linux-gnu-g++

CFLAGS = -g -O2 -Wall -I.. -I../share -I../libanswer/include -I../mysql/include -DLIBANSWER_LINUX
CCOMLINE = $(CXX) -c $(CFLAGS) $< -o $@

LFLAGS = -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lz -lssl -lcrypto -lzstd
LLIB = -L../libanswer/obj -lanswer

OBJS = $(patsubst %.cpp, $(OBJPATH)/%.o, $(notdir $(wildcard *.cpp)))
OBJS += $(OBJPATH)/CKunExt.o 	$(OBJPATH)/CXinMo.o \
	$(OBJPATH)/CDaTingReward.o \
	$(OBJPATH)/CKiaFuRecharge.o \
	$(OBJPATH)/CSuperTeHui.o \
	$(OBJPATH)/CMonthlyChouJiang.o \
	$(OBJPATH)/CXingMai.o \
	$(OBJPATH)/CWan360.o \
	$(OBJPATH)/CWuHunShop.o \
	$(OBJPATH)/CTestServerReward.o \
	$(OBJPATH)/CVipClub.o \
	$(OBJPATH)/CCardGroupBox.o \
	$(OBJPATH)/CHttpRequest.o
DS = $(OBJS:.o=.d)

$(OBJPATH)/%.d : %.cpp
	echo -n $(OBJPATH)/ > $@
	$(CXX) -MM $(CFLAGS) $< >> $@
	echo -e \\t$(CCOMLINE:.d=.o) >> $@

all : $(TARGET)

$(TARGET) : $(DS) $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LLIB) $(LFLAGS)

-include $(DS)

clean:
	@rm -f $(OBJPATH)/*
	@rm -f $(TARGET)

