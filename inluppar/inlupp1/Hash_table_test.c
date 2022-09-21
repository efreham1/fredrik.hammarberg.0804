#include <CUnit/Basic.h>
#include <stdlib.h>
#include "Hash_table.h"

#define No_Buckets 17

typedef bool(*ioopm_predicate)(int key, char *value, void *extra);
typedef void(*ioopm_apply_function)(int key, char **value, void *extra);


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
  CU_ASSERT_PTR_EQUAL(*ioopm_hash_table_lookup(ht, k), v);
  ioopm_hash_table_destroy(ht);
}

void test_insert_multiple()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *v = "BRUH";
  for (int i = -40; i<40; i++)
  {
    ioopm_hash_table_insert(ht, i, v);
  }
  for (int i = -40; i<40; i++)
  {
    CU_ASSERT_PTR_EQUAL(*ioopm_hash_table_lookup(ht, i),v)
  }
  ioopm_hash_table_destroy(ht);
}

void test_insert_two_backwards()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char* v1 = "test1";
  char* v2 = "test2";
  ioopm_hash_table_insert(ht, No_Buckets*2+3, v1);
  ioopm_hash_table_insert(ht, No_Buckets*1+3, v2);
  CU_ASSERT_PTR_EQUAL(*ioopm_hash_table_lookup(ht, No_Buckets*2+3),v1);
  CU_ASSERT_PTR_EQUAL(*ioopm_hash_table_lookup(ht, No_Buckets*1+3),v2);
  ioopm_hash_table_destroy(ht);
}

void test_insert_multiple_backwards()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *v = "BRUH";
  for (int i = 40; i>-40; i--)
  {
    ioopm_hash_table_insert(ht, i, v);
  }
  for (int i = -39; i<=40; i++)
  {
    CU_ASSERT_PTR_EQUAL(*ioopm_hash_table_lookup(ht, i),v)
  }
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
  CU_ASSERT_PTR_EQUAL(*ioopm_hash_table_lookup(ht, k),v2);
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
  CU_ASSERT_PTR_EQUAL(*ioopm_hash_table_lookup(ht, k),v2);
  int k2 = 7;
  char *v3 = "hallelujah";
  ioopm_hash_table_insert(ht, k2, v3);
  CU_ASSERT_PTR_EQUAL(*ioopm_hash_table_lookup(ht, k2),v3);
  CU_ASSERT_PTR_EQUAL(*ioopm_hash_table_lookup(ht, k),v2);  
  ioopm_hash_table_destroy(ht);
}

void test_insert_multiple_values_in_same_bucket()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int keys[] = {No_Buckets*1, 
                No_Buckets*0, 
                No_Buckets*2, 
                No_Buckets*4,
                No_Buckets*3,
                No_Buckets*5
               };
  char *value = "Bertil";
  for (int i = 0; i < 5; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], value);
  }
   for (int i = 0; i < 5; i++)
  {
      CU_ASSERT_PTR_EQUAL(*ioopm_hash_table_lookup(ht, keys[i]), value);
  }
  ioopm_hash_table_destroy(ht);
}

void test_lookup_nonexisting_key()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int keys[] = {No_Buckets*1, No_Buckets*2, No_Buckets*4};
  char *value = "Bertil";
  for (int i = 0; i < 3; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], value);
  }
  CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, No_Buckets*0));
  CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, No_Buckets*3));
  CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, No_Buckets*5));
  ioopm_hash_table_destroy(ht);
}

void test_lookup_empty()
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create();
   for (int i = 0; i < No_Buckets + 1; ++i) /// 18 is a bit magical
     {
       CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, i));
     }
   CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, -1));
   ioopm_hash_table_destroy(ht);
}

void test_remove_single_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_insert(ht, 123, "hello world");
  ioopm_hash_table_remove(ht, 123);
  CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, 123));
  ioopm_hash_table_destroy(ht);
}


void test_remove_multiple_entries_in_different_buckets()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *values[] = {"test1", "test2", "test3"};
  int keys[] = {No_Buckets + No_Buckets / 2, No_Buckets - No_Buckets /5, No_Buckets + No_Buckets/9};
  for (int i = 0; i < 3; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }
  for (int i = 0; i < 3; i++)
  {
    int key = keys[i];
    ioopm_hash_table_remove(ht, key);
    CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, key));
  }
  ioopm_hash_table_destroy(ht);
}

void test_remove_multiple_entries_in_same_bucket()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *value = "Bertil";
  int keys[] = {No_Buckets*1, No_Buckets*6, No_Buckets*0, No_Buckets*2, No_Buckets*4};
  for (int i = 0; i < 4; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], value);
  }
  for (int i = 0; i < 3; i++)
  {
    int key = keys[i];
    ioopm_hash_table_remove(ht, key);
    CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, key));
  }
  ioopm_hash_table_destroy(ht);
}


void test_size_empty_ht()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  CU_ASSERT(ioopm_hash_table_size(ht) == 0);
  ioopm_hash_table_destroy(ht);
}

void test_size_different_buckets()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int keys[] = {No_Buckets, No_Buckets-1, No_Buckets+1};
  char *values[] = {"test1", "test2", "test3"};
  for ( int i = 0; i < 3; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 3);
  ioopm_hash_table_destroy(ht);
}

void test_size_same_bucket()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int keys [] = {No_Buckets*0, No_Buckets*2, No_Buckets*8, No_Buckets*3};
  char *value = "test";
  for (int i = 0; i<4; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], value);
  }
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 4);
  ioopm_hash_table_destroy(ht);
}

void test_size_one_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int key = 42;
  char *value = "test";
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 1);
  ioopm_hash_table_destroy(ht);
}

void test_empty_empty_ht()
{
 ioopm_hash_table_t *ht = ioopm_hash_table_create();
 CU_ASSERT(ioopm_hash_table_is_empty(ht));
 ioopm_hash_table_destroy(ht); 
}

void test_empty_different_buckets()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int keys[] = {No_Buckets, No_Buckets-1, No_Buckets+1};
  char *values[] = {"test1", "test2", "test3"};
  for ( int i = 0; i < 3; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }

  CU_ASSERT(!ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);
}

void test_empty_one_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int key = 42;
  char *value = "test";
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);
}

void test_clear_empty_ht()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_clear(ht);
  CU_ASSERT(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);
}

void test_clear_different_buckets()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int keys[] = {No_Buckets, No_Buckets-1, No_Buckets+1};
  char *values[] = {"test1", "test2", "test3"};
  for ( int i = 0; i < 3; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }
  ioopm_hash_table_clear(ht);
  CU_ASSERT(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);
}

void test_clear_same_bucket()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int keys [] = {No_Buckets*0, No_Buckets*2, No_Buckets*8, No_Buckets*3};
  char *value = "test";
  for (int i = 0; i<4; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], value);
  }
  ioopm_hash_table_clear(ht);
  CU_ASSERT(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);
}

void test_clear_one_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int key = 42;
  char *value = "test";
  ioopm_hash_table_insert(ht, key, value);
  ioopm_hash_table_clear(ht);
  CU_ASSERT(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);
}

void test_keys_empty_ht()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int *keys = ioopm_hash_table_keys(ht);
  CU_ASSERT_PTR_NULL(keys);
  ioopm_hash_table_destroy(ht);
  free(keys);
}


void test_keys_different_buckets()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int keys[3] = {No_Buckets, No_Buckets-1, No_Buckets+1};
  bool found[3] = {false, false, false}; 
  char *values[] = {"test1", "test2", "test3"};
  for ( int i = 0; i < 3; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }
  int *result_keys = ioopm_hash_table_keys(ht);

  for (int i = 0; i < 3; i++)
  {
    int key = result_keys[i];
    int j = 0;
    while (key != keys[j])
    {
      j += 1;
      if (j == 3)
      {
        CU_FAIL("Found a key that was never inserted!");
      }
    }
    found[j] = true;
  }
  for (int i = 0; i < 3; i++)
  {
    CU_ASSERT(found[i]);
  }
  ioopm_hash_table_destroy(ht);
  free(result_keys);
}

void test_keys_same_bucket()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int keys [] = {No_Buckets*0, No_Buckets*2, No_Buckets*8, No_Buckets*3};
  bool found[4] = {false};
  char *value = "test";
  for (int i = 0; i<4; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], value);
  }
  int *result_keys = ioopm_hash_table_keys(ht);
  for (int i = 0; i<4; i++)
  {
    for (int j = 0; j<4; j++)
    {
      if (keys[j] == result_keys[i])
      {
        found[j] = true;
        break;
      }
      if (j==3)
      {
        CU_FAIL("Found a key that was never inserted!");
      }
    }
  }
  for (int i = 0; i<4; i++)
  {
    CU_ASSERT(found[i]);
  }
  ioopm_hash_table_destroy(ht);
  free(result_keys);
}

void test_keys_one_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int key = 42;
  char *value = "test";
  ioopm_hash_table_insert(ht, key, value);
  int *keys = ioopm_hash_table_keys(ht);
  CU_ASSERT_EQUAL(*keys, key);
  ioopm_hash_table_destroy(ht);
  free(keys);
}


void test_keys_and_values_different_buckets()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int keys[3] = {No_Buckets, No_Buckets-1, No_Buckets+1};
  char *values[3] = {"test1", "test2", "test3"};
  bool found[3] = {false, false, false}; 
  for ( int i = 0; i < 3; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }
  int *result_keys = ioopm_hash_table_keys(ht);
  char **result_values = ioopm_hash_table_values(ht);

  for (int i = 0; i < 3; i++)
  {
    int key = result_keys[i];
    char *value = result_values[i];
    int j = 0;
    while (key != keys[j] && value != values[j])
    {
      j += 1;
      if (j == 3)
      {
        CU_FAIL("Found an entry that was never inserted or wrong order in keys and value arrays!");
      }
    }
    found[j] = true;
  }
  for (int i = 0; i < 3; i++)
  {
    CU_ASSERT(found[i]);
  }
  ioopm_hash_table_destroy(ht);
  free(result_values);
  free(result_keys);
}


void test_keys_and_values_same_bucket()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int keys[3] = {No_Buckets, No_Buckets*2, No_Buckets*3};
  char *values[3] = {"test1", "test2", "test3"};
  bool found[3] = {false, false, false}; 
  for ( int i = 0; i < 3; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }
  int *result_keys = ioopm_hash_table_keys(ht);
  char **result_values = ioopm_hash_table_values(ht);

  for (int i = 0; i < 3; i++)
  {
    int key = result_keys[i];
    char *value = result_values[i];
    int j = 0;
    while (key != keys[j] && value != values[j])
    {
      j += 1;
      if (j == 3)
      {
        CU_FAIL("Found an entry that was never inserted or wrong order in keys and value arrays!");
      }
    }
    found[j] = true;
  }
  for (int i = 0; i < 3; i++)
  {
    CU_ASSERT(found[i]);
  }
  free(result_keys);
  free(result_values);
  ioopm_hash_table_destroy(ht);
}


void test_values_empty_ht()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char **values = ioopm_hash_table_values(ht);
  CU_ASSERT_PTR_NULL(values);
  ioopm_hash_table_destroy(ht);
  free(values);
}


void test_values_different_buckets()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int keys[3] = {No_Buckets, No_Buckets-1, No_Buckets+1};
  bool found[3] = {false, false, false}; 
  char *values[] = {"test1", "test2", "test3"};
  for ( int i = 0; i < 3; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }
  char **result_values = ioopm_hash_table_values(ht);

  for (int i = 0; i < 3; i++)
  {
    char *value = result_values[i];
    int j = 0;
    while (value != values[j])
    {
      j += 1;
      if (j == 3)
      {
        CU_FAIL("Found a value that was never inserted!");
      }
    }
    found[j] = true;
  }
  for (int i = 0; i < 3; i++)
  {
    CU_ASSERT(found[i]);
  }
  ioopm_hash_table_destroy(ht);
  free(result_values);
}

void test_values_same_bucket()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int keys[] = {No_Buckets*0, No_Buckets*2, No_Buckets*8, No_Buckets*3};
  bool found[4] = {false};
  char *values[] = {"test1", "test2", "test3", "test4"};
  for (int i = 0; i<4; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }
  char **result_values = ioopm_hash_table_values(ht);
  for (int i = 0; i<4; i++)
  {
    for (int j = 0; j<4; j++)
    {
      if (values[j] == result_values[i])
      {
        found[j] = true;
        break;
      }
      if (j==4)
      {
        CU_FAIL("Found a value that was never inserted!");
      }
    }
  }
  for (int i = 0; i<4; i++)
  {
    CU_ASSERT(found[i]);
  }
  ioopm_hash_table_destroy(ht);
  free(result_values);
}

void test_values_one_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int key = 42;
  char *value = "test";
  ioopm_hash_table_insert(ht, key, value);
  char **values = ioopm_hash_table_values(ht);
  CU_ASSERT_PTR_EQUAL(*values, value);
  ioopm_hash_table_destroy(ht);
  free(values);
}

void test_not_has_key_empty()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  CU_ASSERT(!ioopm_hash_table_has_key(ht, No_Buckets));
  ioopm_hash_table_destroy(ht);
}

void test_has_key_single()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_insert(ht, No_Buckets, "test");
  CU_ASSERT(ioopm_hash_table_has_key(ht, No_Buckets));
  ioopm_hash_table_destroy(ht);
}
void test_not_has_key_single()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_insert(ht, No_Buckets, "test");
  CU_ASSERT(!ioopm_hash_table_has_key(ht, No_Buckets+1));
  ioopm_hash_table_destroy(ht);
}

void test_has_key_multiple()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_insert(ht, No_Buckets, "test");
  ioopm_hash_table_insert(ht, No_Buckets+1, "test");
  ioopm_hash_table_insert(ht, No_Buckets+2, "test");
  CU_ASSERT(ioopm_hash_table_has_key(ht, No_Buckets));
  CU_ASSERT(ioopm_hash_table_has_key(ht, No_Buckets+1));
  CU_ASSERT(ioopm_hash_table_has_key(ht, No_Buckets+2));
  ioopm_hash_table_destroy(ht);
}

void test_not_has_key_multiple()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_insert(ht, No_Buckets, "test");
  ioopm_hash_table_insert(ht, No_Buckets+1, "test");
  ioopm_hash_table_insert(ht, No_Buckets+2, "test");
  CU_ASSERT(!ioopm_hash_table_has_key(ht, No_Buckets-1));
  CU_ASSERT(!ioopm_hash_table_has_key(ht, No_Buckets-2));
  CU_ASSERT(!ioopm_hash_table_has_key(ht, No_Buckets-3));
  ioopm_hash_table_destroy(ht);
}
void test_not_has_value_empty()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *value = "test";
  CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, value));
  ioopm_hash_table_destroy(ht);
}

void test_not_has_value_single_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *value = "test";
  char *fake_value = "test2";
  ioopm_hash_table_insert(ht, No_Buckets/2, value);
  CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, fake_value));
  ioopm_hash_table_destroy(ht);
}

void test_not_has_value_different_buckets()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int keys[3] = {No_Buckets, No_Buckets-1, No_Buckets+1};
  char *values[] = {"test1", "test2", "test3"};
  char *fake_values[] = {"test4", "test5", "test6"};
  for (int i = 0; i<3; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }
  for (int i = 0; i<3; i++)
  {
    CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, fake_values[i]));
  }
  ioopm_hash_table_destroy(ht);
}

void test_not_has_value_same_bucket()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int keys[] = {No_Buckets*0, No_Buckets*2, No_Buckets*8, No_Buckets*3};
  char *values[] = {"test1", "test2", "test3", "test4"};
  char *fake_values[] = {"test5", "test6", "test7", "test8"};
  for (int i = 0; i<4; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }
  for (int i = 0; i<4; i++)
  {
    CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, fake_values[i]));
  }
  ioopm_hash_table_destroy(ht);
}

void test_has_value_single_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *value = "test";
  ioopm_hash_table_insert(ht, No_Buckets/2, value);
  CU_ASSERT(ioopm_hash_table_has_value(ht, value));
  ioopm_hash_table_destroy(ht);
}

void test_has_value_different_buckets()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int keys[3] = {No_Buckets, No_Buckets-1, No_Buckets+1};
  char *values[] = {"test1", "test2", "test3"};
  for (int i = 0; i<3; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }
  for (int i = 0; i<3; i++)
  {
    CU_ASSERT(ioopm_hash_table_has_value(ht, values[i]));
  }
  ioopm_hash_table_destroy(ht);
}

void test_has_value_same_bucket()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int keys[] = {No_Buckets*0, No_Buckets*2, No_Buckets*8, No_Buckets*3};
  char *values[] = {"test1", "test2", "test3", "test4"};
  for (int i = 0; i<4; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }
  for (int i = 0; i<4; i++)
  {
    CU_ASSERT(ioopm_hash_table_has_value(ht, values[i]));
  }
  ioopm_hash_table_destroy(ht);
}

bool predicate_not_true_all(int key, char *value, void *extra)
{
  int *got_int = extra;
  bool got_extra = *got_int == 8;
  return got_extra || strchr(value, 'c') != NULL;
}

bool predicate_not_true_any(int key, char *value, void *extra)
{
  int *got_int = extra;
  bool got_extra = *got_int == 3;
  return got_extra || strlen(value)>4;
}

bool predicate_true_all(int key, char *value, void *extra)
{
  int *got_int = extra;
  bool got_extra = *got_int == 2;
  return got_extra && strchr(value, 'a') != NULL;
}

bool predicate_true_any(int key, char *value, void *extra)
{
  int *got_int = extra;
  bool got_extra = *got_int == 2;
  return got_extra && strlen(value)<3;
}

char *values[4] = {"a", "ab", "abc", "abcd"};
ioopm_predicate predicates[4] = {predicate_not_true_all, predicate_not_true_any, predicate_true_all, predicate_true_any};

void test_predicates_empty_ht()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int digit = 2;
  CU_ASSERT_FALSE(ioopm_hash_table_all(ht, predicates[0], &digit));
  CU_ASSERT_FALSE(ioopm_hash_table_any(ht, predicates[1], &digit));
  CU_ASSERT_FALSE(ioopm_hash_table_all(ht, predicates[2], &digit));
  CU_ASSERT_FALSE(ioopm_hash_table_any(ht, predicates[3], &digit));
  ioopm_hash_table_destroy(ht);
}

void test_predicates_single_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int digit = 2;
  ioopm_hash_table_insert(ht, No_Buckets/2, values[0]);
  CU_ASSERT_FALSE(ioopm_hash_table_all(ht, predicates[0], &digit));
  CU_ASSERT_FALSE(ioopm_hash_table_any(ht, predicates[1], &digit));
  CU_ASSERT(ioopm_hash_table_all(ht, predicates[2], &digit));
  CU_ASSERT(ioopm_hash_table_any(ht, predicates[3], &digit));
  ioopm_hash_table_destroy(ht);
}

void test_predicates_multiple_entries_same_bucket()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int digit = 2;
  int keys[4] = {No_Buckets*3+No_Buckets/2, No_Buckets*1+No_Buckets/2, No_Buckets*5+No_Buckets/2, No_Buckets*7+No_Buckets/2};
  for (int i = 0; i < 4; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }
  CU_ASSERT_FALSE(ioopm_hash_table_all(ht, predicates[0], &digit));
  CU_ASSERT_FALSE(ioopm_hash_table_any(ht, predicates[1], &digit));
  CU_ASSERT(ioopm_hash_table_all(ht, predicates[2], &digit));
  CU_ASSERT(ioopm_hash_table_any(ht, predicates[3], &digit));
  ioopm_hash_table_destroy(ht);
}

void test_predicates_multiple_entries_different_buckets()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int digit = 2;
  int keys[4] = {No_Buckets+2, No_Buckets+4, No_Buckets, No_Buckets+1};
  for (int i = 0; i < 4; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }
  CU_ASSERT_FALSE(ioopm_hash_table_all(ht, predicates[0], &digit));
  CU_ASSERT_FALSE(ioopm_hash_table_any(ht, predicates[1], &digit));
  CU_ASSERT(ioopm_hash_table_all(ht, predicates[2], &digit));
  CU_ASSERT(ioopm_hash_table_any(ht, predicates[3], &digit));
  ioopm_hash_table_destroy(ht);
}

char *values1[5] = {"H", "HE", "HEJ", "HEJS", "HEJSA"};
char *values2[5] = {"a", "ab", "abc", "abcd", "abcde"};

void apply_function(int key, char **value, void *extra)
{
  char **values_local = extra;
  if (key%No_Buckets==0 && key != 0)
  {
    int idx = key/No_Buckets-1;
    idx++;
    *value = values_local[idx];
  }
  else
  {
    int idx = key;
    idx++;
    *value = values_local[idx];
  }
}

bool predicate_for_function(int key, char *value, void *extra)
{
  if (key%No_Buckets==0 && key != 0)
  {
    int idx = key/No_Buckets-1;
    idx++;
    return strcmp(values2[idx], value) == 0;
  }
  else
  {
    int idx = key;
    idx++;
    return strcmp(values2[idx], value) == 0;
  }
}

void test_apply_all_empty_ht()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_apply_to_all(ht, apply_function, &values2);
  CU_ASSERT(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);
}

void test_apply_all_single_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int key = 3;
  ioopm_hash_table_insert(ht, key, values1[key]);
  CU_ASSERT_FALSE(ioopm_hash_table_any(ht, predicate_for_function, NULL));
  ioopm_hash_table_apply_to_all(ht, apply_function, values2);
  CU_ASSERT(ioopm_hash_table_all(ht, predicate_for_function, NULL));
  ioopm_hash_table_destroy(ht);
}

void test_apply_all_multiple_in_different_buckets()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int keys[4] = {0, 1, 2, 3};
  for (int i = 0; i < 4; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], values1[i]);
  }
  CU_ASSERT_FALSE(ioopm_hash_table_any(ht, predicate_for_function, NULL));
  ioopm_hash_table_apply_to_all(ht, apply_function, &values2);
  CU_ASSERT(ioopm_hash_table_all(ht, predicate_for_function, NULL));
  ioopm_hash_table_destroy(ht);
}

void test_apply_all_multiple_in_same_bucket()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int keys[4] = {No_Buckets*1, No_Buckets*2, No_Buckets*3, No_Buckets*4};
  for (int i = 0; i < 4; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], values1[i]);
  }
  CU_ASSERT_FALSE(ioopm_hash_table_any(ht, predicate_for_function, NULL));
  ioopm_hash_table_apply_to_all(ht, apply_function, &values2);
  CU_ASSERT(ioopm_hash_table_all(ht, predicate_for_function, NULL));
  ioopm_hash_table_destroy(ht);
}

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
    (CU_add_test(my_test_suite, "Test for two insertions backwards", test_insert_two_backwards) == NULL) ||
    (CU_add_test(my_test_suite, "Test for multiple insertions", test_insert_multiple) == NULL) ||
    (CU_add_test(my_test_suite, "Test for multiple insertions opposite order", test_insert_multiple_backwards) == NULL) ||
    (CU_add_test(my_test_suite, "Test for insertion to an existing key", test_insert_existing_key) == NULL) ||
    (CU_add_test(my_test_suite, "Test for inserting a new key then an existing key and then a new key", test_insert_existing_and_new_key) == NULL) ||
    (CU_add_test(my_test_suite, "Test for inserting multiple entries in the same bucket", test_insert_multiple_values_in_same_bucket) == NULL) ||
    
    (CU_add_test(my_test_suite, "Test for looking up multiple non_exsisting entries in the same bucket", test_lookup_nonexisting_key) == NULL) ||
    (CU_add_test(my_test_suite, "Test for looking in an empty hash-table", test_lookup_empty) == NULL) ||

    (CU_add_test(my_test_suite, "Test for removing a single entry", test_remove_single_entry) == NULL) ||
    (CU_add_test(my_test_suite, "Test for removing multiple entries in different buckets", test_remove_multiple_entries_in_different_buckets) == NULL) ||
    (CU_add_test(my_test_suite, "Test for removing multiple entries in the same bucket", test_remove_multiple_entries_in_same_bucket) == NULL) ||
    
    (CU_add_test(my_test_suite, "Test for size of empty hash table", test_size_empty_ht) == NULL) ||
    (CU_add_test(my_test_suite, "Test for size of hash table with single entry", test_size_one_entry) == NULL) ||
    (CU_add_test(my_test_suite, "Test for size of hash table with multiple entries in same bucket", test_size_same_bucket) == NULL) ||
    (CU_add_test(my_test_suite, "Test for size of hash table with multiple entries in different buckets", test_size_different_buckets) == NULL) ||
    
    (CU_add_test(my_test_suite, "Test that hash table with no entries is empty", test_empty_empty_ht) == NULL) ||
    (CU_add_test(my_test_suite, "Test that hash table with a single entry isn't empty", test_empty_one_entry) == NULL) ||
    (CU_add_test(my_test_suite, "Test that hash table with multiple entries isn't empty", test_empty_different_buckets ) == NULL) ||
    
    (CU_add_test(my_test_suite, "Test that clear-function clears an empty hash table", test_clear_empty_ht) == NULL) ||
    (CU_add_test(my_test_suite, "Test that clear-function clears hash table with single entry", test_clear_one_entry) == NULL) ||
    (CU_add_test(my_test_suite, "Test that clear-function clears hash table with multiple entries in same bucket", test_clear_same_bucket) == NULL) ||
    (CU_add_test(my_test_suite, "Test that clear-function clears hash table with multiple entries in different buckets", test_clear_different_buckets) == NULL) ||
    
    (CU_add_test(my_test_suite, "Test finding keys in an empty hash table", test_keys_empty_ht) == NULL) ||
    (CU_add_test(my_test_suite, "Test finding keys in a hash table with single entry", test_keys_one_entry) == NULL) ||
    (CU_add_test(my_test_suite, "Test finding keys in a hash table with multiple entries in same bucket", test_keys_same_bucket) == NULL) ||
    (CU_add_test(my_test_suite, "Test finding keys in a hash table with multiple entries in different buckets", test_keys_different_buckets) == NULL) ||

    (CU_add_test(my_test_suite, "Test finding values in an empty hash table", test_values_empty_ht) == NULL) ||
    (CU_add_test(my_test_suite, "Test finding values in a hash table with single entry", test_values_one_entry) == NULL) ||
    (CU_add_test(my_test_suite, "Test finding values in a hash table with multiple entries in same bucket", test_values_same_bucket) == NULL) ||
    (CU_add_test(my_test_suite, "Test finding values in a hash table with multiple entries in different buckets", test_values_different_buckets) == NULL) ||

    (CU_add_test(my_test_suite, "Test finding keys and values in a hash table with multiple entries in same bucket", test_keys_and_values_same_bucket) == NULL) ||
    (CU_add_test(my_test_suite, "Test finding keys and values in a hash table with multiple entries in different buckets", test_keys_and_values_different_buckets) == NULL) ||

    (CU_add_test(my_test_suite, "Test if empty hash table has non-existing key", test_not_has_key_empty) == NULL) ||
    (CU_add_test(my_test_suite, "Test if hash table with single entry has existing key", test_has_key_single) == NULL) ||
    (CU_add_test(my_test_suite, "Test if hash table with multiple entries has existing key", test_has_key_multiple) == NULL) ||
    (CU_add_test(my_test_suite, "Test if hash table with single entry has non-existing key", test_not_has_key_single) == NULL) ||
    (CU_add_test(my_test_suite, "Test if hash table with multiple entries has non-existing key", test_not_has_key_multiple) == NULL) ||
    
    (CU_add_test(my_test_suite, "Test checking that value doesn't exist in an empty hash table", test_not_has_value_empty) == NULL) ||
    (CU_add_test(my_test_suite, "Test checking that value doesn't exist in a hash table with single entry", test_not_has_value_single_entry) == NULL) ||
    (CU_add_test(my_test_suite, "Test checking that value doesn't exist in a hash table with multiple entries in same bucket", test_not_has_value_same_bucket) == NULL) ||
    (CU_add_test(my_test_suite, "Test checking that value doesn't exist in a hash table with multiple entries in different buckets", test_not_has_value_different_buckets) == NULL) ||

    (CU_add_test(my_test_suite, "Test checking that value exists in a hash table with single entry", test_has_value_single_entry) == NULL) ||
    (CU_add_test(my_test_suite, "Test checking that value exists in a hash table with multiple entries in same bucket", test_has_value_same_bucket) == NULL) ||
    (CU_add_test(my_test_suite, "Test checking that value exists in a hash table with multiple entries in different buckets", test_has_value_different_buckets) == NULL) ||

    (CU_add_test(my_test_suite, "Applying predicates to an empty hash table", test_predicates_empty_ht) == NULL) ||
    (CU_add_test(my_test_suite, "Applying predicates to an hash table with a single entry", test_predicates_single_entry) == NULL) ||
    (CU_add_test(my_test_suite, "Applying predicates to an hash table with multiple entries in same bucket", test_predicates_multiple_entries_same_bucket) == NULL) ||
    (CU_add_test(my_test_suite, "Applying predicates to an hash table with a single entries in different buckets", test_predicates_multiple_entries_different_buckets) == NULL) ||
    
    (CU_add_test(my_test_suite, "Applying function to all elements in an empty hash table", test_apply_all_empty_ht) == NULL) ||
    (CU_add_test(my_test_suite, "Applying function to all elements in hash table with single entry", test_apply_all_single_entry) == NULL) ||
    (CU_add_test(my_test_suite, "Applying function to all elements in hash table with multiple entries in different buckets", test_apply_all_multiple_in_different_buckets) == NULL) ||
    (CU_add_test(my_test_suite, "Applying function to all elements in hash table with multiple entries in same bucket", test_apply_all_multiple_in_same_bucket) == NULL) ||
    
    
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