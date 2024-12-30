
flags= -lX11 -std=c++23

all: wm

wm: main.o util.o event_dispatcher.o window_manager.o frame_manager.o
	g++ $(flags) main.o util.o event_dispatcher.o window_manager.o frame_manager.o -o wm

main.o: main.cpp 
	g++ -c $(flags) main.cpp

util.o: util/util.cpp
	g++ -c $(flags) util/util.cpp

event_dispatcher.o: event_dispatcher/event_dispatcher.cpp
	g++ -c $(flags) event_dispatcher/event_dispatcher.cpp

frame_manager.o: frame_manager/frame_manager.cpp
	g++ -c $(flags) frame_manager/frame_manager.cpp

window_manager.o: window_manager/window_manager.cpp
	g++ -c $(flags) window_manager/window_manager.cpp


clean:
	rm *.o
