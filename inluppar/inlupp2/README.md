# Instructions for building program, tests and test coverage report

To build the program: make store
To run the program: ./store
To build and run tests for inventory and cart: make memtest_store
Test coverage obtained through use of gcov.

File 'store_test.c'

- Lines executed:95.65% of 161
- Taken at least once:65.79% of 38
- Calls executed:95.80% of 119

File 'inventory.c'

- Lines executed:82.23% of 242
- Taken at least once:54.00% of 50
- Calls executed:80.68% of 88
  (Branches not taken are for the trivial cases when
  i.e. if edit function edits nothing, return input merchandise).

File 'cart.c'

- Lines executed:81.13% of 53
- No branches
- Calls executed:100.00% of 15

# Non-trivial documentation details

See module interface documentation in each respective header file.

- Since we implemented persistance on file we added:
  - make stock: to build a store with 45 pieces of merchandise that are in stock
  - make inv_clear: to clear the binary file that the warehouse is stored on
- All error handling (bad inputs) when communicating with the terminal are handled in ask.c
- Undo functionality is not implemented.
