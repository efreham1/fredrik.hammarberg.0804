CC=gcc 
FLAGS=-Wall -g
OBJECTS=hash_table.o linked_list.o 
%.o: %.c %.h data_structure.h
	$(CC) $(FLAGS) $< -c -pg

clean:
	rm -f *.o
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f *.out
	rm -f test_ht test_ll test_it freq output.txt

.PHONY: clean
