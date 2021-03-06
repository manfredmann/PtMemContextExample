TARGET = PtMemContextExample
SRCDIR = ./src/
SRCS =	memcontext.cpp \
		yalabel.cpp \
		timer.cpp \
		main.cpp

BINDIR = ./bin/
OBJDIR = ./obj/
OBJS = $(SRCS:.cpp=.o)
CC = cc
INCLUDEDIRS += ./inc

LIBS = photon_s
LIBS += /qnx4/phtk/lib/phrender_s.lib /qnx4/phtk/lib/phexlib3r.lib

CFLAGS = -Oentx -ms -s -w1 -5r, -WC,-xss \
							$(addprefix -I, $(INCLUDEDIRS))
LDFLAGS = -M -N 64k \
							$(addprefix -l, $(LIBS))

.PHONY:				all clean

all:					$(BINDIR)$(TARGET)

clean:
							-rm -f $(OBJDIR)*.o $(BINDIR)$(TARGET) $(BINDIR)*.map *.err 

$(OBJDIR)%.o : $(SRCDIR)%.cpp
							$(CC) $(CFLAGS) -c -o $@ $<

$(BINDIR)$(TARGET): 	$(addprefix $(OBJDIR), 	$(OBJS))
							$(CC) $(LDFLAGS) -o $@ $^
