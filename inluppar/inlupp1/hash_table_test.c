#include <CUnit/Basic.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include <math.h>

typedef bool (*ioopm_predicate)(elem_t key, elem_t value, void *extra);
typedef void (*ioopm_apply_function)(elem_t key, elem_t *value, void *extra);

int init_suite(void)
{
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

int clean_suite(void)
{
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

// hash functions start
int simple_hash_int(elem_t key, int buckets)
{
  return abs(key.int_v % buckets);
}

int hash_unsigned_int(elem_t key, int buckets)
{
  return key.u_int_v % buckets;
}

int hash_float(elem_t key, int buckets)
{
  int rounded_float = round(key.float_v);
  return abs(rounded_float % buckets);
}

int hash_char(elem_t key, int buckets)
{
  int char_to_int = (int)key.char_v;
  return char_to_int % buckets;
}
int hash_string(elem_t key, int buckets)
{
  char *str = (char *)key.ptr_v;
  int str_len = strlen(str);
  int total_product = 1;
  for (int i = 0; i < str_len; i++)
  {
    total_product = str[i] * total_product;
  }
  return total_product % buckets;
}

// hash functions end

// equals function start
bool compare_eq_string(elem_t a, elem_t b)
{
  return strcmp(a.ptr_v, b.ptr_v) == 0;
}

bool compare_eq_int(elem_t a, elem_t b)
{
  return a.int_v == b.int_v;
}

bool compare_eq_unsigned_int(elem_t a, elem_t b)
{
  return a.u_int_v == b.u_int_v;
}

bool compare_eq_bool(elem_t a, elem_t b)
{
  return a.bool_v == b.bool_v;
}

bool compare_eq_float(elem_t a, elem_t b)
{
  return a.float_v == b.float_v;
}

bool compare_eq_char(elem_t a, elem_t b)
{
  return a.char_v == b.char_v;
}

// equals functions end

// less than functions start
bool compare_lt_int(elem_t a, elem_t b)
{
  return a.int_v < b.int_v;
}

bool compare_lt_unsigned_int(elem_t a, elem_t b)
{
  return a.u_int_v < b.u_int_v;
}

bool compare_lt_bool(elem_t a, elem_t b)
{
  return a.bool_v < b.bool_v;
}

bool compare_lt_float(elem_t a, elem_t b)
{
  return a.float_v < b.float_v;
}

bool compare_lt_char(elem_t a, elem_t b)
{
  return a.char_v < b.char_v;
}

bool compare_lt_string(elem_t a, elem_t b)
{
  char *str1 = (char *)a.ptr_v;
  char *str2 = (char *)b.ptr_v;
  return strcmp(str1, str2) < 0;
}

// less than function ends
//  These are example test functions. You should replace them with
//  functions of your own.
void test_create_destroy()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  CU_ASSERT_PTR_NOT_NULL(ht);
  ioopm_hash_table_destroy(ht);
}

void test_insert_once()
{
  elem_t k = {.int_v = 5};
  elem_t v = {.ptr_v = "BRUH"};
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, k));
  ioopm_hash_table_insert(ht, k, v);
  CU_ASSERT_PTR_EQUAL(ioopm_hash_table_lookup(ht, k)->ptr_v, v.ptr_v);
  ioopm_hash_table_destroy(ht);
}

void test_insert_multiple()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  elem_t v = {.ptr_v = "BRUH"};
  for (int i = -40; i < 40; i++)
  {
    elem_t k = {.int_v = i};
    ioopm_hash_table_insert(ht, k, v);
  }
  for (int i = -40; i < 40; i++)
  {
    elem_t k = {.int_v = i};
    CU_ASSERT_PTR_EQUAL(ioopm_hash_table_lookup(ht, k)->ptr_v, v.ptr_v)
  }
  ioopm_hash_table_destroy(ht);
}

void test_insert_two_backwards()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  elem_t v1 = {.ptr_v = "test1"};
  elem_t v2 = {.ptr_v = "test2"};
  ioopm_hash_table_insert(ht, (elem_t){.int_v = ioopm_hash_table_number_of_buckets(ht) * 2 + 3}, v1);
  ioopm_hash_table_insert(ht, (elem_t){.int_v = ioopm_hash_table_number_of_buckets(ht) * 1 + 3}, v2);
  CU_ASSERT_PTR_EQUAL(ioopm_hash_table_lookup(ht, (elem_t){.int_v = ioopm_hash_table_number_of_buckets(ht) * 2 + 3})->ptr_v, v1.ptr_v);
  CU_ASSERT_PTR_EQUAL(ioopm_hash_table_lookup(ht, (elem_t){.int_v = ioopm_hash_table_number_of_buckets(ht) * 1 + 3})->ptr_v, v2.ptr_v);
  ioopm_hash_table_destroy(ht);
}

void test_insert_multiple_backwards()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  elem_t v = {.ptr_v = "test"};
  for (int i = 40; i > -40; i--)
  {
    elem_t k = {.int_v = i};
    ioopm_hash_table_insert(ht, k, v);
  }
  for (int i = -39; i <= 40; i++)
  {
    elem_t k = {.int_v = i};
    CU_ASSERT_PTR_EQUAL(ioopm_hash_table_lookup(ht, k)->ptr_v, v.ptr_v)
  }
  ioopm_hash_table_destroy(ht);
}

void test_insert_existing_key()
{
  elem_t k = {.int_v = 5};
  elem_t v = {.ptr_v = "BRUH"};
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  ioopm_hash_table_insert(ht, k, v);
  elem_t v2 = {.ptr_v = "oops"};
  ioopm_hash_table_insert(ht, k, v2);
  CU_ASSERT_PTR_EQUAL(ioopm_hash_table_lookup(ht, k)->ptr_v, v2.ptr_v);
  ioopm_hash_table_destroy(ht);
}

void test_insert_existing_and_new_key()
{
  elem_t k = {.int_v = 5};
  elem_t v = {.ptr_v = "BRUH"};
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  ioopm_hash_table_insert(ht, k, v);
  elem_t v2 = {.ptr_v = "oops"};
  ioopm_hash_table_insert(ht, k, v2);
  CU_ASSERT_PTR_EQUAL(ioopm_hash_table_lookup(ht, k)->ptr_v, v2.ptr_v);
  elem_t k2 = {.int_v = 7};
  elem_t v3 = {.ptr_v = "hallelujah"};
  ioopm_hash_table_insert(ht, k2, v3);
  CU_ASSERT_PTR_EQUAL(ioopm_hash_table_lookup(ht, k2)->ptr_v, v3.ptr_v);
  CU_ASSERT_PTR_EQUAL(ioopm_hash_table_lookup(ht, k)->ptr_v, v2.ptr_v);
  ioopm_hash_table_destroy(ht);
}

void test_insert_multiple_values_in_same_bucket()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int keys[] = {ioopm_hash_table_number_of_buckets(ht) * 1,
                ioopm_hash_table_number_of_buckets(ht) * 0,
                ioopm_hash_table_number_of_buckets(ht) * 2,
                ioopm_hash_table_number_of_buckets(ht) * 4,
                ioopm_hash_table_number_of_buckets(ht) * 3,
                ioopm_hash_table_number_of_buckets(ht) * 5};
  char *value = "test";
  for (int i = 0; i < 5; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t){.int_v = keys[i]}, (elem_t){.ptr_v = value});
  }
  for (int i = 0; i < 5; i++)
  {
    CU_ASSERT_PTR_EQUAL(ioopm_hash_table_lookup(ht, (elem_t){.int_v = keys[i]})->ptr_v, (elem_t){.ptr_v = value}.ptr_v);
  }
  ioopm_hash_table_destroy(ht);
}

void test_lookup_nonexisting_key()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int keys[] = {ioopm_hash_table_number_of_buckets(ht) * 1, ioopm_hash_table_number_of_buckets(ht) * 2, ioopm_hash_table_number_of_buckets(ht) * 4};
  int badkeys[] = {ioopm_hash_table_number_of_buckets(ht) * 0, ioopm_hash_table_number_of_buckets(ht) * 3, ioopm_hash_table_number_of_buckets(ht) * 5};
  char *value = "test";
  for (int i = 0; i < 3; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t){.int_v = keys[i]}, (elem_t){.ptr_v = value});
  }
  for (int i = 0; i < 3; i++)
  {
    CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, (elem_t){.int_v = badkeys[i]}));
  }

  ioopm_hash_table_destroy(ht);
}

void test_lookup_empty()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  for (int i = 0; i < ioopm_hash_table_number_of_buckets(ht) + 1; ++i)
  {
    CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, (elem_t){.int_v = i}));
  }
  CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, (elem_t){.int_v = -1}));
  ioopm_hash_table_destroy(ht);
}

void test_remove_non_existing_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  char *values[] = {"test1", "test2", "test3"};
  int keys[] = {ioopm_hash_table_number_of_buckets(ht) + ioopm_hash_table_number_of_buckets(ht) / 2, ioopm_hash_table_number_of_buckets(ht) - ioopm_hash_table_number_of_buckets(ht) / 5, ioopm_hash_table_number_of_buckets(ht) + ioopm_hash_table_number_of_buckets(ht) / 9};
  for (int i = 0; i < 3; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t){.int_v = keys[i]}, (elem_t){.ptr_v = values[i]});
  }
  //CU_ASSERT_PTR_NULL(ioopm_hash_table_remove(ht, (elem_t){ioopm_hash_table_number_of_buckets(ht) * 52 - 6}));
  ioopm_hash_table_destroy(ht);
}

void test_remove_single_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  ioopm_hash_table_insert(ht, (elem_t){.int_v = 123}, (elem_t){.ptr_v = "hello world"});
  ioopm_hash_table_remove(ht, (elem_t){.int_v = 123});
  CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, (elem_t){.int_v = 123}));
  ioopm_hash_table_destroy(ht);
}

void test_remove_multiple_entries_in_different_buckets()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  char *values[] = {"test1", "test2", "test3"};
  int keys[] = {ioopm_hash_table_number_of_buckets(ht) + ioopm_hash_table_number_of_buckets(ht) / 2, ioopm_hash_table_number_of_buckets(ht) - ioopm_hash_table_number_of_buckets(ht) / 5, ioopm_hash_table_number_of_buckets(ht) + ioopm_hash_table_number_of_buckets(ht) / 9};
  for (int i = 0; i < 3; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t){.int_v = keys[i]}, (elem_t){.ptr_v = values[i]});
  }
  for (int i = 0; i < 3; i++)
  {
    int key = keys[i];
    ioopm_hash_table_remove(ht, (elem_t){.int_v = key});
    CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, (elem_t){.int_v = key}));
  }
  ioopm_hash_table_destroy(ht);
}

void test_remove_multiple_entries_in_same_bucket()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  char *value = "Bertil";
  int keys[] = {ioopm_hash_table_number_of_buckets(ht) * 1, ioopm_hash_table_number_of_buckets(ht) * 6, ioopm_hash_table_number_of_buckets(ht) * 0, ioopm_hash_table_number_of_buckets(ht) * 2, ioopm_hash_table_number_of_buckets(ht) * 4};
  for (int i = 0; i < 4; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t){.int_v = keys[i]}, (elem_t){.ptr_v = value});
  }
  for (int i = 0; i < 3; i++)
  {
    int key = keys[i];
    ioopm_hash_table_remove(ht, (elem_t){.int_v = key});
    CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, (elem_t){.int_v = key}));
  }
  ioopm_hash_table_destroy(ht);
}

void test_size_empty_ht()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  CU_ASSERT(ioopm_hash_table_size(ht) == 0);
  ioopm_hash_table_destroy(ht);
}

void test_size_different_buckets()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int keys[] = {ioopm_hash_table_number_of_buckets(ht), ioopm_hash_table_number_of_buckets(ht) - 1, ioopm_hash_table_number_of_buckets(ht) + 1};
  char *values[] = {"test1", "test2", "test3"};
  for (int i = 0; i < 3; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t){.int_v = keys[i]}, (elem_t){.ptr_v = values[i]});
  }
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 3);
  ioopm_hash_table_destroy(ht);
}

void test_size_same_bucket()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int keys[] = {ioopm_hash_table_number_of_buckets(ht) * 0, ioopm_hash_table_number_of_buckets(ht) * 2, ioopm_hash_table_number_of_buckets(ht) * 8, ioopm_hash_table_number_of_buckets(ht) * 3};
  char *value = "test";
  for (int i = 0; i < 4; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t){.int_v = keys[i]}, (elem_t){.ptr_v = value});
  }
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 4);
  ioopm_hash_table_destroy(ht);
}

void test_size_one_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int key = 42;
  char *value = "test";
  ioopm_hash_table_insert(ht, (elem_t){.int_v = key}, (elem_t){.ptr_v = value});
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 1);
  ioopm_hash_table_destroy(ht);
}

void test_empty_empty_ht()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  CU_ASSERT(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);
}

void test_empty_different_buckets()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int keys[] = {ioopm_hash_table_number_of_buckets(ht), ioopm_hash_table_number_of_buckets(ht) - 1, ioopm_hash_table_number_of_buckets(ht) + 1};
  char *values[] = {"test1", "test2", "test3"};
  for (int i = 0; i < 3; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t){.int_v = keys[i]}, (elem_t){.ptr_v = values[i]});
  }

  CU_ASSERT(!ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);
}

void test_empty_one_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int key = 42;
  char *value = "test";
  ioopm_hash_table_insert(ht, (elem_t){.int_v = key}, (elem_t){.ptr_v = value});
  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);
}

void test_clear_empty_ht()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  ioopm_hash_table_clear(ht);
  CU_ASSERT(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);
}

void test_clear_different_buckets()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int keys[] = {ioopm_hash_table_number_of_buckets(ht), ioopm_hash_table_number_of_buckets(ht) - 1, ioopm_hash_table_number_of_buckets(ht) + 1};
  char *values[] = {"test1", "test2", "test3"};
  for (int i = 0; i < 3; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t){.int_v = keys[i]}, (elem_t){.ptr_v = values[i]});
  }
  ioopm_hash_table_clear(ht);
  CU_ASSERT(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);
}

void test_clear_same_bucket()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int keys[] = {ioopm_hash_table_number_of_buckets(ht) * 0, ioopm_hash_table_number_of_buckets(ht) * 2, ioopm_hash_table_number_of_buckets(ht) * 8, ioopm_hash_table_number_of_buckets(ht) * 3};
  char *value = "test";
  for (int i = 0; i < 4; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t){.int_v = keys[i]}, (elem_t){.ptr_v = value});
  }
  ioopm_hash_table_clear(ht);
  CU_ASSERT(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);
}

void test_clear_one_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int key = 42;
  char *value = "test";
  ioopm_hash_table_insert(ht, (elem_t){.int_v = key}, (elem_t){.ptr_v = value});
  ioopm_hash_table_clear(ht);
  CU_ASSERT(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);
}

void test_keys_empty_ht()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  ioopm_list_t *keys_list = ioopm_hash_table_keys(ht);
  CU_ASSERT(ioopm_linked_list_is_empty(keys_list));
  ioopm_hash_table_destroy(ht);
  ioopm_linked_list_destroy(keys_list);
}

void test_keys_different_buckets()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int keys[3] = {ioopm_hash_table_number_of_buckets(ht), ioopm_hash_table_number_of_buckets(ht) - 1, ioopm_hash_table_number_of_buckets(ht) + 1};
  bool found[3] = {false, false, false};
  char *values[] = {"test1", "test2", "test3"};
  for (int i = 0; i < 3; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t){.int_v = keys[i]}, (elem_t){.ptr_v = values[i]});
  }
  ioopm_list_t *keys_list = ioopm_hash_table_keys(ht);

  for (int i = 0; i < 3; i++)
  {
    elem_t key = ioopm_linked_list_get(keys_list, i);
    int j = 0;
    while (compare_eq_int(key, (elem_t){.int_v = keys[j]}) == false)
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
  ioopm_linked_list_destroy(keys_list);
}

void test_keys_same_bucket()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int keys[] = {ioopm_hash_table_number_of_buckets(ht) * 0, ioopm_hash_table_number_of_buckets(ht) * 2, ioopm_hash_table_number_of_buckets(ht) * 8, ioopm_hash_table_number_of_buckets(ht) * 3};
  bool found[4] = {false};
  char *value = "test";
  for (int i = 0; i < 4; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t){.int_v = keys[i]}, (elem_t){.ptr_v = value});
  }
  ioopm_list_t *keys_list = ioopm_hash_table_keys(ht);
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      if (compare_eq_int((elem_t){.int_v = keys[j]}, ioopm_linked_list_get(keys_list, i)))
      {
        found[j] = true;
        break;
      }
      if (j == 3)
      {
        CU_FAIL("Found a key that was never inserted!");
      }
    }
  }
  for (int i = 0; i < 4; i++)
  {
    CU_ASSERT(found[i]);
  }
  ioopm_hash_table_destroy(ht);
  ioopm_linked_list_destroy(keys_list);
}

void test_keys_one_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int key = 42;
  char *value = "test";
  ioopm_hash_table_insert(ht, (elem_t){.int_v = key}, (elem_t){.ptr_v = value});
  ioopm_list_t *keys_list = ioopm_hash_table_keys(ht);
  CU_ASSERT_EQUAL(ioopm_linked_list_get(keys_list, 0).int_v, key);
  ioopm_hash_table_destroy(ht);
  ioopm_linked_list_destroy(keys_list);
}

void test_keys_and_values_different_buckets()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int keys[3] = {ioopm_hash_table_number_of_buckets(ht), ioopm_hash_table_number_of_buckets(ht) - 1, ioopm_hash_table_number_of_buckets(ht) + 1};
  char *values[3] = {"test1", "test2", "test3"};
  bool found[3] = {false, false, false};
  for (int i = 0; i < 3; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t){.int_v = keys[i]}, (elem_t){.ptr_v = values[i]});
  }
  ioopm_list_t *keys_list = ioopm_hash_table_keys(ht);
  ioopm_list_t *result_values = ioopm_hash_table_values(ht);

  for (int i = 0; i < 3; i++)
  {
    int key = ioopm_linked_list_get(keys_list, i).int_v;
    char *value = ioopm_linked_list_get(keys_list, i).ptr_v;
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
  ioopm_linked_list_destroy(keys_list);
  ioopm_linked_list_destroy(result_values);
}

void test_keys_and_values_same_bucket()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int keys[3] = {ioopm_hash_table_number_of_buckets(ht), ioopm_hash_table_number_of_buckets(ht) * 2, ioopm_hash_table_number_of_buckets(ht) * 3};
  char *values[3] = {"test1", "test2", "test3"};
  bool found[3] = {false, false, false};
  for (int i = 0; i < 3; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t){.int_v = keys[i]}, (elem_t){.ptr_v = values[i]});
  }
  ioopm_list_t *keys_list = ioopm_hash_table_keys(ht);
  ioopm_list_t *result_values = ioopm_hash_table_values(ht);

  for (int i = 0; i < 3; i++)
  {
    int key = ioopm_linked_list_get(keys_list, i).int_v;
    char *value = ioopm_linked_list_get(keys_list, i).ptr_v;
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
  ioopm_linked_list_destroy(keys_list);
  ioopm_linked_list_destroy(result_values);
  ioopm_hash_table_destroy(ht);
}

void test_values_empty_ht()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  ioopm_list_t *values = ioopm_hash_table_values(ht);
  CU_ASSERT(ioopm_linked_list_is_empty(values));
  ioopm_hash_table_destroy(ht);
  ioopm_linked_list_destroy(values);
}

void test_values_different_buckets()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int keys[3] = {ioopm_hash_table_number_of_buckets(ht), ioopm_hash_table_number_of_buckets(ht) - 1, ioopm_hash_table_number_of_buckets(ht) + 1};
  bool found[3] = {false, false, false};
  char *values[] = {"test1", "test2", "test3"};
  for (int i = 0; i < 3; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t){.int_v = keys[i]}, (elem_t){.ptr_v = values[i]});
  }
  ioopm_list_t *result_values = ioopm_hash_table_values(ht);

  for (int i = 0; i < 3; i++)
  {
    char *value = ioopm_linked_list_get(result_values, i).ptr_v;
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
  ioopm_linked_list_destroy(result_values);
}

void test_values_same_bucket()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int keys[] = {ioopm_hash_table_number_of_buckets(ht) * 0, ioopm_hash_table_number_of_buckets(ht) * 2, ioopm_hash_table_number_of_buckets(ht) * 8, ioopm_hash_table_number_of_buckets(ht) * 3};
  bool found[4] = {false};
  char *values[] = {"test1", "test2", "test3", "test4"};
  for (int i = 0; i < 4; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t){.int_v = keys[i]}, (elem_t){.ptr_v = values[i]});
  }
  ioopm_list_t *result_values = ioopm_hash_table_values(ht);
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      if (values[j] == ioopm_linked_list_get(result_values, i).ptr_v)
      {
        found[j] = true;
        break;
      }
      if (j == 4)
      {
        CU_FAIL("Found a value that was never inserted!");
      }
    }
  }
  for (int i = 0; i < 4; i++)
  {
    CU_ASSERT(found[i]);
  }
  ioopm_hash_table_destroy(ht);
  ioopm_linked_list_destroy(result_values);
}

void test_values_one_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int key = 42;
  char *value = "test";
  ioopm_hash_table_insert(ht, (elem_t){.int_v = key}, (elem_t){.ptr_v = value});
  ioopm_list_t *values = ioopm_hash_table_values(ht);
  CU_ASSERT_PTR_EQUAL(ioopm_linked_list_get(values, 0).ptr_v, value);
  ioopm_hash_table_destroy(ht);
  ioopm_linked_list_destroy(values);
}

void test_not_has_key_empty()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, (elem_t){.int_v = ioopm_hash_table_number_of_buckets(ht)}));
  ioopm_hash_table_destroy(ht);
}

void test_has_key_single()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  ioopm_hash_table_insert(ht, (elem_t){.int_v = ioopm_hash_table_number_of_buckets(ht)}, (elem_t){.ptr_v = "test"});
  CU_ASSERT(ioopm_hash_table_has_key(ht, (elem_t){.int_v = ioopm_hash_table_number_of_buckets(ht)}));
  ioopm_hash_table_destroy(ht);
}
void test_not_has_key_single()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  ioopm_hash_table_insert(ht, (elem_t){.int_v = ioopm_hash_table_number_of_buckets(ht)}, (elem_t){.ptr_v = "test"});
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, (elem_t){.int_v = ioopm_hash_table_number_of_buckets(ht) + 1}));
  ioopm_hash_table_destroy(ht);
}

void test_has_key_multiple()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  ioopm_hash_table_insert(ht, (elem_t){.int_v = ioopm_hash_table_number_of_buckets(ht)}, (elem_t){.ptr_v = "test"});
  ioopm_hash_table_insert(ht, (elem_t){.int_v = ioopm_hash_table_number_of_buckets(ht) + 1}, (elem_t){.ptr_v = "test"});
  ioopm_hash_table_insert(ht, (elem_t){.int_v = ioopm_hash_table_number_of_buckets(ht) + 2}, (elem_t){.ptr_v = "test"});
  CU_ASSERT(ioopm_hash_table_has_key(ht, (elem_t){.int_v = ioopm_hash_table_number_of_buckets(ht)}));
  CU_ASSERT(ioopm_hash_table_has_key(ht, (elem_t){.int_v = ioopm_hash_table_number_of_buckets(ht) + 1}));
  CU_ASSERT(ioopm_hash_table_has_key(ht, (elem_t){.int_v = ioopm_hash_table_number_of_buckets(ht) + 2}));
  ioopm_hash_table_destroy(ht);
}

void test_not_has_key_multiple()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  ioopm_hash_table_insert(ht, (elem_t){.int_v = ioopm_hash_table_number_of_buckets(ht)}, (elem_t){.ptr_v = "test"});
  ioopm_hash_table_insert(ht, (elem_t){.int_v = ioopm_hash_table_number_of_buckets(ht) + 1}, (elem_t){.ptr_v = "test"});
  ioopm_hash_table_insert(ht, (elem_t){.int_v = ioopm_hash_table_number_of_buckets(ht) + 2}, (elem_t){.ptr_v = "test"});
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, (elem_t){.int_v = ioopm_hash_table_number_of_buckets(ht) - 1}));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, (elem_t){.int_v = ioopm_hash_table_number_of_buckets(ht) - 2}));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, (elem_t){.int_v = ioopm_hash_table_number_of_buckets(ht) - 3}));
  ioopm_hash_table_destroy(ht);
}
void test_not_has_value_empty()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  char *value = "test";
  CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, (elem_t){.ptr_v = value}));
  ioopm_hash_table_destroy(ht);
}

void test_not_has_value_single_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  char *value = "test";
  char *fake_value = "test2";
  ioopm_hash_table_insert(ht, (elem_t){.int_v = ioopm_hash_table_number_of_buckets(ht) / 2}, (elem_t){.ptr_v = value});
  CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, (elem_t){.ptr_v = fake_value}));
  ioopm_hash_table_destroy(ht);
}

void test_not_has_value_different_buckets()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int keys[3] = {ioopm_hash_table_number_of_buckets(ht), ioopm_hash_table_number_of_buckets(ht) - 1, ioopm_hash_table_number_of_buckets(ht) + 1};
  char *values[] = {"test1", "test2", "test3"};
  char *fake_values[] = {"test4", "test5", "test6"};
  for (int i = 0; i < 3; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t){.int_v = keys[i]}, (elem_t){.ptr_v = values[i]});
  }
  for (int i = 0; i < 3; i++)
  {
    CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, (elem_t){.ptr_v = fake_values[i]}));
  }
  ioopm_hash_table_destroy(ht);
}

void test_not_has_value_same_bucket()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int keys[] = {ioopm_hash_table_number_of_buckets(ht) * 0, ioopm_hash_table_number_of_buckets(ht) * 2, ioopm_hash_table_number_of_buckets(ht) * 8, ioopm_hash_table_number_of_buckets(ht) * 3};
  char *values[] = {"test1", "test2", "test3", "test4"};
  char *fake_values[] = {"test5", "test6", "test7", "test8"};
  for (int i = 0; i < 4; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t){.int_v = keys[i]}, (elem_t){.ptr_v = values[i]});
  }
  for (int i = 0; i < 4; i++)
  {
    CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, (elem_t){.ptr_v = fake_values[i]}));
  }
  ioopm_hash_table_destroy(ht);
}

void test_has_value_single_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  char *value = "test";
  ioopm_hash_table_insert(ht, (elem_t){.int_v = ioopm_hash_table_number_of_buckets(ht) / 2}, (elem_t){.ptr_v = value});
  CU_ASSERT(ioopm_hash_table_has_value(ht, (elem_t){.ptr_v = value}));
  ioopm_hash_table_destroy(ht);
}

void test_has_value_different_buckets()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int keys[3] = {ioopm_hash_table_number_of_buckets(ht), ioopm_hash_table_number_of_buckets(ht) - 1, ioopm_hash_table_number_of_buckets(ht) + 1};
  char *values[] = {"test1", "test2", "test3"};
  for (int i = 0; i < 3; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t){.int_v = keys[i]}, (elem_t){.ptr_v = values[i]});
  }
  for (int i = 0; i < 3; i++)
  {
    CU_ASSERT(ioopm_hash_table_has_value(ht, (elem_t){.ptr_v = values[i]}));
  }
  ioopm_hash_table_destroy(ht);
}

void test_has_value_same_bucket()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int keys[] = {ioopm_hash_table_number_of_buckets(ht) * 0, ioopm_hash_table_number_of_buckets(ht) * 2, ioopm_hash_table_number_of_buckets(ht) * 8, ioopm_hash_table_number_of_buckets(ht) * 3};
  char *values[] = {"test1", "test2", "test3", "test4"};
  for (int i = 0; i < 4; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t){.int_v = keys[i]}, (elem_t){.ptr_v = values[i]});
  }
  for (int i = 0; i < 4; i++)
  {
    CU_ASSERT(ioopm_hash_table_has_value(ht, (elem_t){.ptr_v = values[i]}));
  }
  ioopm_hash_table_destroy(ht);
}

bool predicate_not_true_all(elem_t key, elem_t value, void *extra)
{
  int *got_int = extra;
  bool got_extra = *got_int == 8;
  return got_extra || strchr(value.ptr_v, 'c') != NULL;
}

bool predicate_not_true_any(elem_t key, elem_t value, void *extra)
{
  int *got_int = extra;
  bool got_extra = *got_int == 3;
  return got_extra || strlen(value.ptr_v) > 4;
}

bool predicate_true_all(elem_t key, elem_t value, void *extra)
{
  int *got_int = extra;
  bool got_extra = *got_int == 2;
  return got_extra && strchr(value.ptr_v, 'a') != NULL;
}

bool predicate_true_any(elem_t key, elem_t value, void *extra)
{
  int *got_int = extra;
  bool got_extra = *got_int == 2;
  return got_extra && strlen(value.ptr_v) < 3;
}

char *values[4] = {"a", "ab", "abc", "abcd"};
ioopm_predicate predicates[4] = {predicate_not_true_all, predicate_not_true_any, predicate_true_all, predicate_true_any};

void test_predicates_empty_ht()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int digit = 2;
  CU_ASSERT_FALSE(ioopm_hash_table_all(ht, predicates[0], &digit));
  CU_ASSERT_FALSE(ioopm_hash_table_any(ht, predicates[1], &digit));
  CU_ASSERT_FALSE(ioopm_hash_table_all(ht, predicates[2], &digit));
  CU_ASSERT_FALSE(ioopm_hash_table_any(ht, predicates[3], &digit));
  ioopm_hash_table_destroy(ht);
}

void test_predicates_single_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int digit = 2;
  ioopm_hash_table_insert(ht, (elem_t){.int_v = ioopm_hash_table_number_of_buckets(ht) / 2}, (elem_t){.ptr_v = values[0]});
  CU_ASSERT_FALSE(ioopm_hash_table_all(ht, predicates[0], &digit));
  CU_ASSERT_FALSE(ioopm_hash_table_any(ht, predicates[1], &digit));
  CU_ASSERT(ioopm_hash_table_all(ht, predicates[2], &digit));
  CU_ASSERT(ioopm_hash_table_any(ht, predicates[3], &digit));
  ioopm_hash_table_destroy(ht);
}

void test_predicates_multiple_entries_same_bucket()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int digit = 2;
  int keys[4] = {ioopm_hash_table_number_of_buckets(ht) * 3 + ioopm_hash_table_number_of_buckets(ht) / 2, ioopm_hash_table_number_of_buckets(ht) * 1 + ioopm_hash_table_number_of_buckets(ht) / 2, ioopm_hash_table_number_of_buckets(ht) * 5 + ioopm_hash_table_number_of_buckets(ht) / 2, ioopm_hash_table_number_of_buckets(ht) * 7 + ioopm_hash_table_number_of_buckets(ht) / 2};
  for (int i = 0; i < 4; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t){.int_v = keys[i]}, (elem_t){.ptr_v = values[i]});
  }
  CU_ASSERT_FALSE(ioopm_hash_table_all(ht, predicates[0], &digit));
  CU_ASSERT_FALSE(ioopm_hash_table_any(ht, predicates[1], &digit));
  CU_ASSERT(ioopm_hash_table_all(ht, predicates[2], &digit));
  CU_ASSERT(ioopm_hash_table_any(ht, predicates[3], &digit));
  ioopm_hash_table_destroy(ht);
}

void test_predicates_multiple_entries_different_buckets()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int digit = 2;
  int keys[4] = {ioopm_hash_table_number_of_buckets(ht) + 2, ioopm_hash_table_number_of_buckets(ht) + 4, ioopm_hash_table_number_of_buckets(ht), ioopm_hash_table_number_of_buckets(ht) + 1};
  for (int i = 0; i < 4; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t){.int_v = keys[i]}, (elem_t){.ptr_v = values[i]});
  }
  CU_ASSERT_FALSE(ioopm_hash_table_all(ht, predicates[0], &digit));
  CU_ASSERT_FALSE(ioopm_hash_table_any(ht, predicates[1], &digit));
  CU_ASSERT(ioopm_hash_table_all(ht, predicates[2], &digit));
  CU_ASSERT(ioopm_hash_table_any(ht, predicates[3], &digit));
  ioopm_hash_table_destroy(ht);
}

char *values1[5] = {"H", "HE", "HEJ", "HEJS", "HEJSA"};
char *values2[5] = {"a", "ab", "abc", "abcd", "abcde"};

void apply_function(elem_t key, elem_t *value, void *extra)
{
  char **values_local = extra;
  if (key.int_v % 266 == 0 && key.int_v != 0)
  {
    int idx = key.int_v / 266 - 1;
    idx++;
    value->ptr_v = values_local[idx];
  }
  else
  {
    int idx = key.int_v;
    idx++;
    value->ptr_v = values_local[idx];
  }
}

bool predicate_for_function(elem_t key, elem_t value, void *extra)
{
  if (key.int_v % 266 == 0 && key.int_v != 0)
  {
    int idx = key.int_v / 266 - 1;
    idx++;
    return strcmp(values2[idx], value.ptr_v) == 0;
  }
  else
  {
    int idx = key.int_v;
    idx++;
    return strcmp(values2[idx], value.ptr_v) == 0;
  }
}

void test_apply_all_empty_ht()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  ioopm_hash_table_apply_to_all(ht, apply_function, &values2);
  CU_ASSERT(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);
}

void test_apply_all_single_entry()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int key = 3;
  ioopm_hash_table_insert(ht, (elem_t){.int_v = key}, (elem_t){.ptr_v = values1[key]});
  CU_ASSERT_FALSE(ioopm_hash_table_any(ht, predicate_for_function, NULL));
  ioopm_hash_table_apply_to_all(ht, apply_function, values2);
  CU_ASSERT(ioopm_hash_table_all(ht, predicate_for_function, NULL));
  ioopm_hash_table_destroy(ht);
}

void test_apply_all_multiple_in_different_buckets()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int keys[4] = {0, 1, 2, 3};
  for (int i = 0; i < 4; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t){.int_v = keys[i]}, (elem_t){.ptr_v = values1[i]});
  }
  CU_ASSERT_FALSE(ioopm_hash_table_any(ht, predicate_for_function, NULL));
  ioopm_hash_table_apply_to_all(ht, apply_function, &values2);
  CU_ASSERT(ioopm_hash_table_all(ht, predicate_for_function, NULL));
  ioopm_hash_table_destroy(ht);
}

void test_apply_all_multiple_in_same_bucket()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int keys[4] = {ioopm_hash_table_number_of_buckets(ht) * 1, ioopm_hash_table_number_of_buckets(ht) * 2, ioopm_hash_table_number_of_buckets(ht) * 3, ioopm_hash_table_number_of_buckets(ht) * 4};
  for (int i = 0; i < 4; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t){.int_v = keys[i]}, (elem_t){.ptr_v = values1[i]});
  }
  CU_ASSERT_FALSE(ioopm_hash_table_any(ht, predicate_for_function, NULL));
  ioopm_hash_table_apply_to_all(ht, apply_function, &values2);
  CU_ASSERT(ioopm_hash_table_all(ht, predicate_for_function, NULL));
  ioopm_hash_table_destroy(ht);
}

void test_all_possible_elem_combinations()
{
  int int_array[3] = {1, 2, 3};
  elem_t keys[] = {(elem_t){.int_v = 1}, (elem_t){.u_int_v = 42}, (elem_t){.bool_v = true}, (elem_t){.float_v = 6.9}, (elem_t){.char_v = 'd'}, (elem_t){.ptr_v = int_array}};
  elem_t *values = keys;
  ioopm_eq_function eq_functions[] = {compare_eq_int, compare_eq_unsigned_int, compare_eq_bool, compare_eq_float, compare_eq_char, compare_eq_string};
  ioopm_lt_function lt_functions[] = {compare_lt_int, compare_lt_unsigned_int, compare_lt_bool, compare_lt_float, compare_lt_char, compare_lt_string};
  ioopm_hash_function hash_functions[] = {simple_hash_int, hash_unsigned_int, NULL, hash_float, hash_char, hash_string};
  int ARRAY_LENGTHS = 6;
  // Testing keys
  for (int i = 0; i < ARRAY_LENGTHS; i++)
  {
    if (hash_functions[i] == NULL)
    {
      break;
    }
    ioopm_eq_function current_eq_function = eq_functions[i];
    ioopm_lt_function current_lt_function = lt_functions[i];
    ioopm_hash_function current_hash_function = hash_functions[i];

    // Testing values
    for (int j = 0; j < ARRAY_LENGTHS; j++)
    {
      ioopm_hash_table_t *ht = ioopm_hash_table_create(current_hash_function, current_eq_function, eq_functions[j], current_lt_function);
      elem_t key = keys[i];
      elem_t value = values[j];
      ioopm_hash_table_insert(ht, key, value);
      CU_ASSERT(eq_functions[j](*ioopm_hash_table_lookup(ht, key), value));
      ioopm_hash_table_destroy(ht);
    }
  }
}

void test_dynamic_No_buckets()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create_spec(0.5, 50, simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  for (int i = 0; i < 50; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t) {.int_v = i}, (elem_t) {.int_v = i});
  }
  CU_ASSERT_EQUAL(ioopm_hash_table_number_of_buckets(ht), 100);

  for (int i = 50; i < 60; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t) {.int_v = i}, (elem_t) {.int_v = i});
  }
  CU_ASSERT_EQUAL(ioopm_hash_table_number_of_buckets(ht), 150);

  for (int i = 60; i < 75; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t) {.int_v = i}, (elem_t) {.int_v = i});
  }
  CU_ASSERT_EQUAL(ioopm_hash_table_number_of_buckets(ht), 150);

  for (int i = 75; i < 90; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t) {.int_v = i}, (elem_t) {.int_v = i});
  }
  CU_ASSERT_EQUAL(ioopm_hash_table_number_of_buckets(ht), 224);

  ioopm_hash_table_destroy(ht);
}

void test_save_and_load()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  int keys1[] = {ioopm_hash_table_number_of_buckets(ht) * 0, ioopm_hash_table_number_of_buckets(ht) * 2, ioopm_hash_table_number_of_buckets(ht) * 8, ioopm_hash_table_number_of_buckets(ht) * 3, ioopm_hash_table_number_of_buckets(ht), ioopm_hash_table_number_of_buckets(ht) - 1, ioopm_hash_table_number_of_buckets(ht) + 1};
  char *values1[] = {"test1", "test2", "test3", "test4", "test5", "test6", "test7"};
  for (int i = 0; i < 7; i++)
  {
    ioopm_hash_table_insert(ht, (elem_t){.int_v = keys1[i]}, (elem_t){.ptr_v = values1[i]});
  }
  ioopm_hash_table_save_to_file(ht, "ht.bin");
  ioopm_hash_table_destroy(ht);
  ioopm_hash_table_t *ht2 = ioopm_hash_table_load_from_file("ht.bin", simple_hash_int, compare_eq_int, compare_eq_string, compare_lt_int);
  for (int i = 0; i < 7; i++)
  {
    char *str = ioopm_hash_table_lookup(ht2, (elem_t){.int_v = keys1[i]})->ptr_v;
    CU_ASSERT_STRING_EQUAL(str, values1[i]);
  }
  ioopm_hash_table_destroy(ht2);
}

int main()
{
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("Test for Hash_table.c", init_suite, clean_suite);
  if (my_test_suite == NULL)
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

      /*(CU_add_test(my_test_suite, "Test for removing a non-existant entry", test_remove_non_existing_entry) == NULL) ||*/
      (CU_add_test(my_test_suite, "Test for removing a single entry", test_remove_single_entry) == NULL) ||
      (CU_add_test(my_test_suite, "Test for removing multiple entries in different buckets", test_remove_multiple_entries_in_different_buckets) == NULL) ||
      (CU_add_test(my_test_suite, "Test for removing multiple entries in the same bucket", test_remove_multiple_entries_in_same_bucket) == NULL) ||

      (CU_add_test(my_test_suite, "Test for size of empty hash table", test_size_empty_ht) == NULL) ||
      (CU_add_test(my_test_suite, "Test for size of hash table with single entry", test_size_one_entry) == NULL) ||
      (CU_add_test(my_test_suite, "Test for size of hash table with multiple entries in same bucket", test_size_same_bucket) == NULL) ||
      (CU_add_test(my_test_suite, "Test for size of hash table with multiple entries in different buckets", test_size_different_buckets) == NULL) ||

      (CU_add_test(my_test_suite, "Test that hash table with no entries is empty", test_empty_empty_ht) == NULL) ||
      (CU_add_test(my_test_suite, "Test that hash table with a single entry isn't empty", test_empty_one_entry) == NULL) ||
      (CU_add_test(my_test_suite, "Test that hash table with multiple entries isn't empty", test_empty_different_buckets) == NULL) ||

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

      (CU_add_test(my_test_suite, "Testing all combinations of type for keys and values", test_all_possible_elem_combinations) == NULL) ||

      (CU_add_test(my_test_suite, "Testing dynamic changing of number of buckets", test_dynamic_No_buckets) == NULL) ||

      (CU_add_test(my_test_suite, "Testing saving and loading a hash_table to and from a file", test_save_and_load) == NULL) ||

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
