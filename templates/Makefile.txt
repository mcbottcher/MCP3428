output: MCP3428.o main.o
	g++ MCP3428.o main.o -o output

MCP3428.o: MCP3428.cpp MCP3428.h
	g++ -c MCP3428.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o output
