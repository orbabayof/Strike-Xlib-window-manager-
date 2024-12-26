flags = -lX11

all: strikeWm

strikeWm: main.o window.o display.o
	g++ $(flags) main.o window.o display.o -o strikeWm

main.o: main.cpp
	g++ -c $(flags) main.cpp

window.o: window/window.cpp
	g++ -c $(flags) window/window.cpp

display.o: display/display.cpp
	g++ -c $(flags) display/display.cpp

clean:
	rm *.o 
