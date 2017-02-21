all: a1

main.o: src/main.c
	gcc -c $< -Wall -std=c99 -Iinclude -g

token.o: src/token.c
	gcc -c $< -Wall -std=c99 -Iinclude -g

storedList.o: src/storedList.c
	gcc -c $< -Wall -std=c99 -Iinclude -g

dynamicStringLib.o: src/dynamicStringLib.c
	gcc -c $< -Wall -std=c99 -Iinclude -g

a1: main.o storedList.o token.o dynamicStringLib.o
	gcc main.o storedList.o token.o dynamicStringLib.o -Wall -g -std=c99 -Iinclude -o a1

run:
	./a1 testCases/basicClass.cc

clean:
	rm -rf *.o
	rm -rf a1
