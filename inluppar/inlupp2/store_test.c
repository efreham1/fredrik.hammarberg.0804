#include <CUnit/Basic.h>
#include <stdlib.h>
#include "cart.h"
#include "inventory.h"

bool eq_int(elem_t a, elem_t b)
{
  return a.int_v == b.int_v;
}


int init_suite_cart(void)
{
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

int clean_suite_cart(void)
{
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

int init_suite_inventory(void)
{
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

int clean_suite_inventory(void)
{
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

// start of cart tests ==============================================================

void cart_test_create_destroy(void)
{
  ioopm_cart_t *cart = ioopm_cart_create();
  CU_ASSERT_PTR_NOT_NULL(cart);
  ioopm_cart_destroy(cart);
}

void cart_test_add(void)
{
  ioopm_cart_t *cart = ioopm_cart_create();
  ioopm_cart_add(cart, strdup("test"), 123, 4);
  cart_merch_t *merch = ioopm_linked_list_get(cart->contents, 0).ptr_v;
  CU_ASSERT_STRING_EQUAL(merch->name, "test");
  CU_ASSERT_EQUAL(merch->pcs, 4);
  CU_ASSERT_EQUAL(merch->price, 123);
  CU_ASSERT_EQUAL(cart->cost, 123*4);
  CU_ASSERT_STRING_EQUAL((char *) ioopm_linked_list_get(cart->names, 0).ptr_v, "test");
  ioopm_cart_destroy(cart);
}

void cart_test_add_multiple(void)
{
  ioopm_cart_t *cart = ioopm_cart_create();
  char *names[6] = {"test1", "test2", "test3", "test4", "test5", "test6"};
  int cost = 0;
  for (int i = 0; i < 6; i++)
  {
    ioopm_cart_add(cart, strdup(names[i]), i, i+3);
    cost += i*(i+3);
  }
  for (int i = 0; i < 6; i++)
  {
    cart_merch_t *merch = ioopm_linked_list_get(cart->contents, i).ptr_v;
    CU_ASSERT_STRING_EQUAL(merch->name, names[i]);
    CU_ASSERT_EQUAL(merch->pcs, i+3);
    CU_ASSERT_EQUAL(merch->price, i);
  }
  CU_ASSERT_EQUAL(cart->cost, cost);
  ioopm_cart_destroy(cart);
  
}

void cart_test_remove(void)
{
  ioopm_cart_t *cart = ioopm_cart_create();
  char *names[6] = {"test1", "test2", "test3", "test4", "test5", "test6"};
  for (int i = 0; i < 6; i++)
  {
    ioopm_cart_add(cart, strdup(names[i]), i, i+3);
  }

  ioopm_cart_remove(cart, "test2");
  cart_merch_t *merch = ioopm_linked_list_get(cart->contents, 1).ptr_v;
  CU_ASSERT_STRING_EQUAL(merch->name, "test3");
  CU_ASSERT_FALSE(ioopm_linked_list_contains(cart->names, (elem_t) {.ptr_v = "test2"}));
  ioopm_cart_destroy(cart);
}

void cart_test_clear(void)
{
  ioopm_cart_t *cart = ioopm_cart_create();
  char *names[6] = {"test1", "test2", "test3", "test4", "test5", "test6"};
  for (int i = 0; i < 6; i++)
  {
    ioopm_cart_add(cart, strdup(names[i]), i, i+3);
  }
  ioopm_cart_clear(cart);
  CU_ASSERT(ioopm_linked_list_is_empty(cart->contents));
  CU_ASSERT(ioopm_linked_list_is_empty(cart->names));
  CU_ASSERT_EQUAL(cart->cost, 0);
  int cost = 0;
  for (int i = 5; i > -1; i--)
  {
    ioopm_cart_add(cart, strdup(names[i]), i, i+3);
    cost += i*(i+3);
  }
  for (int i = 5; i > -1; i--)
  {
    cart_merch_t *merch = ioopm_linked_list_get(cart->contents, 5-i).ptr_v;
    CU_ASSERT_STRING_EQUAL(merch->name, names[i]);
    CU_ASSERT_EQUAL(merch->pcs, i+3);
    CU_ASSERT_EQUAL(merch->price, i);
  }
  CU_ASSERT_EQUAL(cart->cost, cost);
  ioopm_cart_clear(cart);
  ioopm_cart_destroy(cart);
}

// end of cart tests ================================================================

// start of inventory tests =========================================================
void inventory_test_create_destroy(void) {
  ioopm_inventory_t *inventory = ioopm_inventory_create();
  CU_ASSERT_PTR_NOT_NULL(inventory);
  ioopm_inventory_destroy(inventory);
}

void inventory_test_add_remove(void) {
  ioopm_inventory_t *inventory = ioopm_inventory_create();
  ioopm_inventory_add_merchandise(inventory, strdup("Car"), strdup("Vehicle"), 99999);
  inventory_merch_t *merch = ioopm_hash_table_lookup(inventory->warehouse, (elem_t) {.ptr_v = "Car"})->ptr_v;

  CU_ASSERT_STRING_EQUAL(merch->name, "Car");
  CU_ASSERT_STRING_EQUAL(merch->desc, "Vehicle");
  CU_ASSERT_EQUAL(merch->price, 99999);

  ioopm_inventory_remove_merchandise(inventory, "Car");
  void *gone = ioopm_hash_table_lookup(inventory->warehouse, (elem_t) {.ptr_v = "Car"});

  CU_ASSERT_PTR_NULL(gone);

  ioopm_inventory_destroy(inventory);
}

void inventory_test_edit(void) {
  ioopm_inventory_t *inventory = ioopm_inventory_create();
  ioopm_inventory_add_merchandise(inventory, strdup("Car"), strdup("Vehicle"), 99999);
  inventory_merch_t *merch = ioopm_hash_table_lookup(inventory->warehouse, (elem_t) {.ptr_v = "Car"})->ptr_v;

  ioopm_inventory_edit_merchandise(inventory, "Car", strdup("Boat"), strdup("Water vehicle"), 1000000);

  merch = ioopm_hash_table_lookup(inventory->warehouse, (elem_t) {.ptr_v = "Boat"})->ptr_v;

  CU_ASSERT_STRING_EQUAL(merch->name, "Boat");
  CU_ASSERT_STRING_EQUAL(merch->desc, "Water vehicle");
  CU_ASSERT_EQUAL(merch->price, 1000000);

  ioopm_inventory_destroy(inventory);
}

void inventory_test_replenish(void) {
  ioopm_inventory_t *inventory = ioopm_inventory_create();
  ioopm_inventory_add_merchandise(inventory, strdup("Car"), strdup("Vehicle"), 99999);
  inventory_merch_t *merch = ioopm_hash_table_lookup(inventory->warehouse, (elem_t) {.ptr_v = "Car"})->ptr_v;

  ioopm_inventory_replenish_new_shelf_stock(inventory, "Car", 12, strdup("A08"));
  storage_location_t *storage_location = ((storage_location_t *)ioopm_linked_list_get(merch->storage_locations, 0).ptr_v);

  CU_ASSERT_STRING_EQUAL(storage_location->shelf, "A08");
  CU_ASSERT_EQUAL(storage_location->stock, 12);

  ioopm_inventory_replenish_existing_shelf_stock(inventory, "Car", 12, "A08");

  CU_ASSERT_EQUAL(storage_location->stock, 24);

  ioopm_inventory_destroy(inventory);
}

void inventory_test_load_save()
{
  ioopm_inventory_t *inventory = ioopm_inventory_create();
  ioopm_inventory_add_merchandise(inventory, strdup("Car"), strdup("Vehicle"), 99999);

  ioopm_inventory_save(inventory, "inventory_test.bin");
  inventory = ioopm_inventory_load("inventory_test.bin");

  ioopm_inventory_replenish_new_shelf_stock(inventory, "Car", 12, strdup("A08"));

  ioopm_inventory_save(inventory, "inventory_test.bin");
  inventory = ioopm_inventory_load("inventory_test.bin");

  inventory_merch_t *merch = ioopm_hash_table_lookup(inventory->warehouse, (elem_t) {.ptr_v = "Car"})->ptr_v;
  storage_location_t *storage_location = ((storage_location_t *)ioopm_linked_list_get(merch->storage_locations, 0).ptr_v);
  CU_ASSERT_STRING_EQUAL(storage_location->shelf, "A08");
  CU_ASSERT_EQUAL(storage_location->stock, 12);

  ioopm_inventory_save(inventory, "inventory_test.bin");
  inventory = ioopm_inventory_load("inventory_test.bin");

  ioopm_inventory_replenish_existing_shelf_stock(inventory, "Car", 12, "A08");

  ioopm_inventory_save(inventory, "inventory_test.bin");
  inventory = ioopm_inventory_load("inventory_test.bin");

  merch = ioopm_hash_table_lookup(inventory->warehouse, (elem_t) {.ptr_v = "Car"})->ptr_v;
  storage_location = ((storage_location_t *)ioopm_linked_list_get(merch->storage_locations, 0).ptr_v);
  CU_ASSERT_EQUAL(storage_location->stock, 24);

  ioopm_inventory_destroy(inventory);
}

// end of inventory tests ===========================================================

int main()
{
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite suite_cart = CU_add_suite("Test for cart.c", init_suite_cart, clean_suite_cart);
  CU_pSuite suite_inventory = CU_add_suite("Test for inventory.c", init_suite_inventory, clean_suite_inventory);

  if (suite_cart == NULL || suite_inventory == NULL)
  {
    // If the test suite could not be added, tear down CUnit and exit
    CU_cleanup_registry();
    return CU_get_error();
  }

  // This is where we add the test functions to our test suite.
  // For each call to CU_add_test we specify the test suite, the
  // name or description of the test, and the function that runs
  // the test in question. If you want to add another test, just
  // copy a line below and change the information

  if (
    // cart tests=======================================================================================
      (CU_add_test(suite_cart, "Test for create and destroy", cart_test_create_destroy) == NULL) ||

      (CU_add_test(suite_cart, "Test for adding a single element to an empty cart", cart_test_add) == NULL) ||
      (CU_add_test(suite_cart, "Test for adding multiple elements to an empty cart", cart_test_add_multiple) == NULL) ||

      (CU_add_test(suite_cart, "Test for removing a element in a cart", cart_test_remove) == NULL) ||

      (CU_add_test(suite_cart, "Test for clearing a cart", cart_test_clear) == NULL) ||

    // inventory tests==================================================================================
      (CU_add_test(suite_inventory, "Test for create and destroy", inventory_test_create_destroy) == NULL) ||

      (CU_add_test(suite_inventory, "Test for adding and removing merch", inventory_test_add_remove) == NULL) ||

      (CU_add_test(suite_inventory, "Test for editing merch", inventory_test_edit) == NULL) ||

      (CU_add_test(suite_inventory, "Test for replenishing merch", inventory_test_replenish) == NULL) ||

      (CU_add_test(suite_inventory, "Test for loading and saving merch", inventory_test_load_save) == NULL) ||

      0)
  {
    // If adding any of the tests fails, we tear down CUnit and exit
    CU_cleanup_registry();
    return CU_get_error();
  }

  // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
  // Use CU_BRM_NORMAL to only print errors and a summary
  CU_basic_set_mode(CU_BRM_VERBOSE);

  // This is where the tests are actually run!
  CU_basic_run_tests();

  // Tear down CUnit before exiting
  CU_cleanup_registry();
  return CU_get_error();
}
