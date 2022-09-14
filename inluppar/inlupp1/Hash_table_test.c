#include <CUnit/Basic.h>
#include "Hash_table.h"
#include <stdlib.h>

int init_suite(void) {
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

int clean_suite(void) {
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

// These are example test functions. You should replace them with
// functions of your own.
void test_create_destroy()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  CU_ASSERT_PTR_NOT_NULL(ht);
  ioopm_hash_table_destroy(ht);
}

void test_insert_once()
{
  int k = 5;
  char *v = "BRUH";
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, k));
  ioopm_hash_table_insert(ht, k, v);
  CU_ASSERT(*ioopm_hash_table_lookup(ht, k)==v);
  ioopm_hash_table_destroy(ht);
}

void test_insert_existing_key()
{
  int k = 5;
  char *v = "BRUH";
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_insert(ht, k, v);
  char *v2 = "OOPS";
  ioopm_hash_table_insert(ht, k, v2);
  CU_ASSERT(*ioopm_hash_table_lookup(ht, k)==v2);
  ioopm_hash_table_destroy(ht);
}

void test_insert_existing_and_new_key()
{
  int k = 5;
  char *v = "BRUH";
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_insert(ht, k, v);
  char *v2 = "OOPS";
  ioopm_hash_table_insert(ht, k, v2);
  CU_ASSERT(*ioopm_hash_table_lookup(ht, k)==v2);
  int k2 = 7;
  char *v3 = "hallelujah";
  ioopm_hash_table_insert(ht, k2, v3);
  CU_ASSERT(*ioopm_hash_table_lookup(ht, k2)==v3);
  CU_ASSERT(*ioopm_hash_table_lookup(ht, k)==v2);  
  ioopm_hash_table_destroy(ht);
}

void test_lookup_empty()
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create();
   for (int i = 0; i < 18; ++i) /// 18 is a bit magical
     {
       CU_ASSERT_PTR_NULL(*ioopm_hash_table_lookup(ht, i));
     }
   CU_ASSERT_PTR_NULL(*ioopm_hash_table_lookup(ht, -1));
   ioopm_hash_table_destroy(ht);
}

/*
void test_insert_invalid_key()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();  
  int k = 18;
  char *v = "test";
  ioopm_hash_table_insert(ht, k, v);
  ioopm_hash_table_destroy(ht);
}
*/

int main() {
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("Test for Hash_table.c", init_suite, clean_suite);
  if (my_test_suite == NULL) {
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
    (CU_add_test(my_test_suite, "Test for create and destroy", test_create_destroy) == NULL) ||
    (CU_add_test(my_test_suite, "Test for one insertion", test_insert_once) == NULL) ||
    (CU_add_test(my_test_suite, "Test for insertion to an existing key", test_insert_existing_key) == NULL) ||
    (CU_add_test(my_test_suite, "Test for inserting a new key then an existing key and then a new key", test_insert_existing_and_new_key) == NULL) ||
    (CU_add_test(my_test_suite, "Test for looking in an empty hash-table", test_lookup_empty) == NULL) ||
    0
  )
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