all: demo test

module:
	g++ -c FenwickTree.cpp

demo: module
	g++ demo.cpp FenwickTree.o -o demo

run_demo:
	./demo

test: module
	g++ test.cpp FenwickTree.o -o test

run_test:
	./test

clean:
	del *.o *.exe log.txt

rebuild: clean all