CC=gcc 
FLAGS=-Wall 

%.o: %.c %.h
	$(CC) $(FLAGS) $< -c

test_ht: hash_table.o hash_table_test.c
	$(CC) $(FLAGS) $^ -lcunit -o $@

mem_test_ht: test_ht
	valgrind ./test_htmem

test_ll: linked_list.o iterator.o linked_list_test.c
	$(CC) $(FLAGS) $^ -lcunit -o $@

mem_test_ll: test_ll
	valgrind ./test_ll

test_it: iterator.o linked_list.o iterator_test.c
	$(CC) $(FLAGS) $^ -lcunit -o $@

mem_test_it: test_it
	valgrind ./test_it

clean:
	rm -f *.o
	rm -f test_ht test_ll test_it

.PHONY: clean
