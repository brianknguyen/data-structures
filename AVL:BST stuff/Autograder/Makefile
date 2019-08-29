AVLCommands: AVLCommands.cxx AVL.o
	g++ -Wall -Werror AVLCommands.cxx AVL.o -o AVLCommands.exe

AVL.o: AVL.cpp AVL.h
	g++ -Wall -Werror -c AVL.cpp

clean:
	rm -f *.o *.exe
