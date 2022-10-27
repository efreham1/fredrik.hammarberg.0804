CC=gcc 
FLAGS=-Wall -g
OBJECTS= hash_table.o linked_list.o cart.o inventory.o ask.o general_TUI.o
%.o: %.c %.h data_structure.h iterator.h hash_table_internal.h linked_list_internal.h
	$(CC) $(FLAGS) $< -c

store: $(OBJECTS) store.c
	$(CC) $(FLAGS) $^ -o $@

test_store: $(OBJECTS) store_test.c
	$(CC) $(FLAGS) $^ -lcunit -o $@

memtest_store: test_store
	valgrind --leak-check=full --show-leak-kinds=all ./test_store

memcheck_store: store
	valgrind --leak-check=full --show-leak-kinds=all ./store

stock: store
	rm -f inventory.bin
	touch inventory.bin
	gcc make_stock.c -o make_stock
	./make_stock
	./store < Stock.txt

clean:
	rm -f *.o
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f *.out
	rm -f store test_store make_stock

.PHONY: clean stock
