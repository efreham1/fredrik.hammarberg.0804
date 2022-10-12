CC=gcc 
FLAGS=-Wall -g
FRONTEND= ask.o TUI_inventory.o TUI_cart.o general_TUI.o
BACKEND= hash_table.o linked_list.o merch.o cart.o inventory.o undo.o iterator.o
%.o: %.c %.h data_structure.h
	$(CC) $(FLAGS) $< -c

store: $(FRONTEND) $(BACKEND) store.c
	$(CC) $(FLAGS) $^ -o $@

test_store: $(FRONTEND) $(BACKEND) store_test.c
	$(CC) $(FLAGS) $^ -lcunit -o $@

memtest_store: test_store
	valgrind --leak-check=full ./test_store

clean:
	rm -f *.o
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f *.out
	rm -f store

.PHONY: clean
