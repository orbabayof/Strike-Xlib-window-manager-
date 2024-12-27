flags = -lX11

all: strikeWm

strikeWm: main.o window.o display.o handler.o
	g++ $(flags) main.o window.o display.o handler.o -o strikeWm

main.o: main.cpp
	g++ -c $(flags) main.cpp

window.o: window/window.cpp
	g++ -c $(flags) window/window.cpp

display.o: display/display.cpp
	g++ -c $(flags) display/display.cpp

handler.o: handler/handler.cpp
	g++ -c $(flags) handler/handler.cpp

clean:
	rm *.o 
