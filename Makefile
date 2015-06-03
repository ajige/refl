SOURCE:=$(wildcard *.cpp) \
		 $(wildcard src/*.cpp)

OBJS:=$(patsubst %.cpp, %.o, $(SOURCE))

INCLUDE=-Isrc/  \
		-I/usr/include/boost

#LIBRARY=libreflect.a
TARGET=main

all:$(TARGET)

$(LIBRARY):$(OBJS)
#	echo $(SOURCE)
#	echo $(OBJS)
	rm -f $@
	ar -rs $@ $(OBJS)

$(TARGET): src/main.o
	g++ -g src/main.o -o $@

depend:
	g++ -MM $(SOURCE) > .depend

-include .depend

.c.o:
	gcc -g -c $< -o $@

.cpp.o:
	g++ -g -c $< -o $@ $(INCLUDE)

clean:
	rm -f $(OBJS) $(LIBRARY) 
