CC=gcc 
FLAGS=-Wall -g
OBJECTS= hash_table.o linked_list.o cart.o inventory.o undo.o ask.o general_TUI.o
%.o: %.c %.h data_structure.h iterator.h
	$(CC) $(FLAGS) $< -c

store: $(OBJECTS) store.c
	$(CC) $(FLAGS) $^ -o $@

test_store: $(OBJECTS) store_test.c
	$(CC) $(FLAGS) $^ -lcunit -o $@

test: test.c
	$(CC) $(FLAGS) $^ -o $@
	valgrind --leak-check=full ./test

memtest_store: test_store
	valgrind --leak-check=full ./test_store

memcheck_store: store
	valgrind --leak-check=full ./store

clean:
	rm -f *.o
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f *.out
	rm -f store test_store

.PHONY: clean
