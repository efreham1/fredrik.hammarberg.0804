#include <CUnit/Basic.h>
#include <stdlib.h>
#include "cart.h"
#include "merch.h"

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
  merch_t merch = {.name = "test", .description="A test", .price=1010};
  ioopm_cart_add(cart, merch);
  ioopm_list_t *merches = ioopm_hash_table_keys(ioopm_cart_get_merch(cart));
  CU_ASSERT_EQUAL(((merch_t *)ioopm_linked_list_get(merches, 0).ptr_v)->name, merch.name);
  CU_ASSERT_EQUAL(((merch_t *)ioopm_linked_list_get(merches, 0).ptr_v)->description, merch.description);
  CU_ASSERT_EQUAL(((merch_t *)ioopm_linked_list_get(merches, 0).ptr_v)->price, merch.price);
  ioopm_cart_destroy(cart);
  ioopm_linked_list_destroy(merches);
}
// end of cart tests ================================================================
int main()
{
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite suite_cart = CU_add_suite("Test for cart.c", init_suite_cart, clean_suite_cart);
  if (suite_cart == NULL)
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
