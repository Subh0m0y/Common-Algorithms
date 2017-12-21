DIRECTORIES := obj bin util 

.PHONY: all clean make_directories util_gcd test_gcd
all: make_directories util_gcd test_gcd

# This one makes the gcd utility: ./util/gcd or .\util\gcd.exe
util_gcd: util/gcd

util/gcd: obj/gcd.o obj/gcd_util.o
	gcc obj/gcd.o obj/gcd_util.o -o util/gcd

obj/gcd_util.o: src/gcd_util.c
	gcc -c src/gcd_util.c -o obj/gcd_util.o

# This one tests the code for GCD
test_gcd: bin/gcd_tests

bin/gcd_tests: obj/gcd.o obj/gcd_tests.o obj/test.o
	gcc obj/gcd.o obj/test.o obj/gcd_tests.o -o bin/gcd_tests

make_directories:
	-mkdir ${DIRECTORIES}

obj/gcd_tests.o: src/gcd_tests.c src/test.h
	gcc -c src/gcd_tests.c -o obj/gcd_tests.o

# This is for all the <name>.c and <name>.h pairs
# This rule creates an object file for each source
# which is ready for independent linking
obj/%.o: src/%.c src/%.h
	gcc -c src/$*.c -o obj/$*.o

clean:
	rm -r ./obj
	rm -r ./bin
