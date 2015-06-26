all: kal clean
kal: main.o
	g++ `pkg-config --libs --cflags glib-2.0`  -std=c++11 main.o  -o kal -lGL -lSOIL -lGLU -lglfw3 -lX11 -lXrandr -lpthread -lXi -lXcursor -lXrandr -lm  -lXinerama -lrt -lfreetype  

 
main.o: main.cpp
	 g++ -c main.cpp -std=c++11 `pkg-config --libs --cflags glib-2.0` `pkg-config --libs --cflags  cairo` 
	


clean:
	rm -rf *.o
