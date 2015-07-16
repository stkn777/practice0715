all: p clean

p: cpoint.o points.o
	g++ *.o -o p

cpoint.o:
	g++ -c cpoint.cpp

points.o:
	g++ -c points.cpp
	
f_clean:
	rm -rf *.o

clean:
	rm -rf *.o p
