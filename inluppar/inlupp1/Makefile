CC=gcc 
FLAGS=-Wall -g
OBJECTS=hash_table.o linked_list.o 
%.o: %.c %.h data_structure.h
	$(CC) $(FLAGS) $< -c

test_ht: $(OBJECTS) hash_table_test.c
	$(CC) $(FLAGS) $^ -lcunit -lm -o $@

mem_test_ht: test_ht
	valgrind ./test_ht

test_ll: linked_list.o linked_list_test.c
	$(CC) $(FLAGS) $^ -lcunit -o $@

mem_test_ll: test_ll
	valgrind ./test_ll

test_it: iterator.o linked_list.o iterator_test.c
	$(CC) $(FLAGS) $^ -lcunit -o $@

freq: $(OBJECTS) iterator.o freq-count.c
	$(CC) $(FLAGS) $^ -o $@

mem_test_freq: freq
	valgrind ./freq bee_movie.txt

mem_test_it: test_it
	valgrind ./test_it

clean:
	rm -f *.o
	rm -f test_ht test_ll test_it freq output.txt

.PHONY: clean
