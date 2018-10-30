#       MAKEFILE
CFLAGS = -g -Wall -Wshadow -o
GCC = g++ $(CFLAGS)

all: scanner

scanner:     main.cpp node.cpp scanner.cpp testScanner.cpp
	$(GCC) $(CFLAGS) scanner main.cpp node.cpp scanner.cpp testScanner.cpp -std=c++11

clean:
	rm -f *.o a.out scanner
