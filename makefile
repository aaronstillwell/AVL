all: ; gcc -Wall -pedantic src/AVL_Tree.c src/util.c src/a4.c -Iinclude -o bin/a4

clean: ; rm -rf bin/*
