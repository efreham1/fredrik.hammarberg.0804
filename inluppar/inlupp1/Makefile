CC=gcc 
FLAGS=-Wall 

test_ll: linked_list_test.c 
	gcc -g -Wall linked_list_test.c -lcunit linked_list.c
	valgrind ./a.out

hash_table.o: hash_table.c hash_table.h
	$(CC) $(FLAGS) $< -c


test_ht: hash_table.o hash_table_test.c
	$(CC) $(FLAGS) $^ -lcunit -o $@

%_mem_test: %test_ht
	valgrind ./$^
