all: kal clean
kal: main.o
	g++ -std=c++11 main.o -o kal -lGL -lSOIL -lGLU -lglfw3 -lX11 -lXrandr -lpthread -lXi -lXcursor -lXrandr -lm  -lXinerama -lrt -lfreetype 'pkg-config --cflags glib-2.0'    

 
main.o: main.cpp
	 g++ -c main.cpp -std=c++11
	


clean:
	rm -rf *.o
