#       MAKEFILE
CFLAGS = -g -Wall -Wshadow -o
GCC = g++ $(CFLAGS)

all: scanner

scanner:     main.cpp scanner.cpp testScanner.cpp utility.cpp
	$(GCC) $(CFLAGS) scanner main.cpp scanner.cpp testScanner.cpp utility.cpp -std=c++11

clean:
	rm -f *.o a.out scanner
