#include <CUnit/Basic.h>
#include <stdlib.h>
#include "linked_list.h"

typedef bool (*ioopm_int_predicate)(int value, void *extra);
typedef void (*ioopm_apply_int_function)(int *value, void *extra);

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

int list_entries[500] = {2, 3, -5, 7, 11, -1187, 251, -719, 1553, -1033, -1949, 1901, -367, 1471, -1867, 631, 1951, -211, -251, 353, 257, 487, -701, 829, -1950, 1039, -521, 1151, 1663, -191, 1907, -947, -389, 167, -1543, 1741, -787, -197, -37, 997, -809, -1787, -389, 1171, 499, -587, 743, -1759, 59, 643, 1451, 1013, 1297, 479, 1361, 619, -991, -773, 1301, -419, -5, -1889, -881, -823, -1163, 1163, 599, -1889, -263, 1847, -71, -131, -433, -383, -1459, -1319, -617, -1597, 1549, -251, -641, -19, -1877, 37, 997, 647, 593, -571, -1823, 1987, 1327, 1303, -227, -599, -571, 947, -1117, -1741, 1693, -1697, -149, 331, -1399, 1381, -1019, -743, 107, -131, -1697, 727, -257, 101, -1061, -1321, 1607, 1871, -1907, -877, -1973, -173, -773, -593, 179, 263, 1777, -859, 1811, -113, 1667, 137, -101, -79, -131, -1613, -43, 1907, -1621, 1259, -491, 1453, -773, -1877, 941, 491, 577, -1559, 1487, -631, 1319, 37, 1721, 2, -929, -29, -383, -1429, -613, -569, 79, 1153, 769, -1759, 1693, -1481, 677, -821, 1609, -773, 769, -1667, -617, -487, 1453, 83, -673, -547, 97, 1039, 557, -281, -139, -1913, 269, -571, -127, 1801, 701, -1181, -1451, -587, 1697, -857, 1879, 727, -149, -1277, -829, 317, 313, -1367, -227, 953, 1987, 659, 821, 977, -647, -769, 1601, 1753, 1543, 743, -523, -1663, -419, 337, -683, -1597, -653, -1831, 1747, 19, 139, 1571, 47, -1979, 919, -263, 1307, 1039, -409, 839, 947, -733, 1801, 929, -163, 1511, -233, 1409, 751, -1181, -173, 43, 1409, -227, 1907, -859, 751, -1697, 79, -877, 1097, -761, 853, -1987, -647, -1129, 1901, -1229, -661, -787, -1949, -863, -1409, -1733, 7, -211, -1319, 1489, 1033, 37, -1811, -37, 911, -1543, -317, -941, -829, 1367, -397, -79, -257, -1223, 1531, 751, 1847, 1789, -1373, 317, 1153, 1889, -563, -29, -1697, 1627, 739, 1171, 1697, -1151, -1201, -1151, -29, -1153, 151, 1471, 1951, 397, -1151, -719, 1733, 131, 1019, -1531, -1367, 1301, -1163, -29, -631, -449, 271, -853, 1759, 1069, 829, 1423, -1277, -1123, -797, -37, -491, -733, -293, -269, -1327, 661, 907, -379, -1069, 1543, -1283, -1483, -1613, 557, 137, -1051, -953, -71, 181, 541, 1907, 1699, -691, 887, -193, -463, -1877, -263, -743, -839, 139, -3, -593, -251, -317, -31, -1553, 1499, -2, 127, 937, -883, 1433, -1103, -769, -179, 11, 211, -107, -1321, -1249, -491, -1021, -281, -127, 587, -421, 1087, 877, 307, 823, -1291, 1097, 19, 1579, 953, -1787, 1283, -1621, -1979, 853, 947, -419, 821, -347, 1289, -59, -509, 947, 613, -2, 163, -547, 859, -109, 337, -1669, -1889, -463, -379, 859, 1201, 67, 1697, 181, 1483, -953, 1973, 227, 971, -941, 1693, -19, -1831, 43, 379, 389, -1033, 1549, 1493, -281, -773, -919, -233, -1609, 1229, 673, 631, 853, 1637, 1597, -571, 661, 839, 1613, -1447, -1933, 1223, 1669, -857, -619, 919, 211, 29, 29, 881, 653, 1861, -109, -3, 823, 641, -1721, -709, -1433, -563, 1693, -421, 1663, -1117, -1483, 127, 1579, -1637, 1549, -1579, 631, 647, -631, 1109, 1973, 359, -563, -269, -1063, -1597, 937, 131, -1301, 1787};

bool int_compare_equal(elem_t a, elem_t b)
{
  return a.int_v == b.int_v;
}

bool unsigned_int_compare_equal(elem_t a, elem_t b)
{
  return a.u_int_v == b.u_int_v;
}

bool bool_compare_equal(elem_t a, elem_t b)
{
  return a.bool_v == b.bool_v;
}

bool float_compare_equal(elem_t a, elem_t b)
{
  return a.float_v == b.float_v;
}

bool char_compare_equal(elem_t a, elem_t b)
{
  return a.char_v == b.char_v;
}

bool pointer_compare_equal(elem_t a, elem_t b)
{
  return a.ptr_v == b.ptr_v;
}

// These are example test functions. You should replace them with
// functions of your own.
void test_create_destroy()
{
  ioopm_list_t *ll = ioopm_linked_list_create(int_compare_equal);
  CU_ASSERT_PTR_NOT_NULL(ll);
  ioopm_linked_list_destroy(ll);
}

static ioopm_list_t *make_test_list(int no_entries, int start_idx)
{
  ioopm_list_t *ll = ioopm_linked_list_create(int_compare_equal);
  for (int i = start_idx; i < no_entries + start_idx; i++)
  {
    ioopm_linked_list_append(ll, (elem_t) {.int_v = list_entries[i]});
  }
  return ll;
}

void test_append_empty_list()
{
  ioopm_list_t *ll = ioopm_linked_list_create(int_compare_equal);
  ioopm_linked_list_append(ll, (elem_t) {.int_v = 42});
  CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, 0), (elem_t) {.int_v = 42}));
  CU_ASSERT_EQUAL(ioopm_linked_list_length(ll), 1);
  ioopm_linked_list_destroy(ll);
}

void test_append_multiple_entries()
{
  ioopm_list_t *ll = ioopm_linked_list_create(int_compare_equal);
  for (int i = 0; i < 10; i++)
  {
    ioopm_linked_list_append(ll, (elem_t) {.int_v = list_entries[i]});
    CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, i), (elem_t) {.int_v = list_entries[i]}));
  }
  CU_ASSERT_EQUAL(ioopm_linked_list_length(ll), 10);
  for (int i = 0; i < 10; i++)
  {
    CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, i), (elem_t) {.int_v = list_entries[i]}));
  }
  ioopm_linked_list_destroy(ll);
}

void test_prepend_empty_list()
{
  ioopm_list_t *ll = ioopm_linked_list_create(int_compare_equal);
  ioopm_linked_list_prepend(ll, (elem_t) {.int_v = 42});
  CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, 0), (elem_t) {.int_v = 42}));
  CU_ASSERT_EQUAL(ioopm_linked_list_length(ll), 1);
  ioopm_linked_list_destroy(ll);
}

void test_prepend_multiple_entries()
{
  ioopm_list_t *ll = ioopm_linked_list_create(int_compare_equal);
  for (int i = 0; i < 10; i++)
  {
    ioopm_linked_list_prepend(ll, (elem_t) {.int_v = list_entries[i]});
    CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, 0), (elem_t) {.int_v = list_entries[i]}));
  }
  CU_ASSERT_EQUAL(ioopm_linked_list_length(ll), 10);
  for (int i = 0; i < 10; i++)
  {
    int idx = 9 - i;
    CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, i), (elem_t) {.int_v = list_entries[idx]}));
  }
  ioopm_linked_list_destroy(ll);
}

void test_append_prepend()
{
  ioopm_list_t *ll = ioopm_linked_list_create(int_compare_equal);
  for (int i = 0; i < 2; i++)
  {
    ioopm_linked_list_append(ll, (elem_t) {.int_v = list_entries[i+2]});
    ioopm_linked_list_prepend(ll, (elem_t) {.int_v = list_entries[i]});
  }
  for (int i = 0; i < 2; i++)
  {
    CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, i), (elem_t) {.int_v = list_entries[1-i]}));
    CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, i+2), (elem_t) {.int_v = list_entries[i+2]}));
  }
  ioopm_linked_list_destroy(ll);
}

void test_prepend_append()
{
  ioopm_list_t *ll = ioopm_linked_list_create(int_compare_equal);
  for (int i = 0; i < 2; i++)
  {
    ioopm_linked_list_prepend(ll, (elem_t) {.int_v = list_entries[i]});
    ioopm_linked_list_append(ll, (elem_t) {.int_v = list_entries[i+2]});
  }
  for (int i = 0; i < 2; i++)
  {
    CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, i), (elem_t) {.int_v = list_entries[1-i]}));
    CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, i+2), (elem_t) {.int_v = list_entries[i+2]}));
  }
  ioopm_linked_list_destroy(ll);
}

void test_length_empty_list()
{
  ioopm_list_t *ll = make_test_list(0, 0);
  CU_ASSERT_EQUAL(ioopm_linked_list_length(ll), 0);
  ioopm_linked_list_destroy(ll);
}

void test_length_single_entry()
{
  ioopm_list_t *ll = make_test_list(1, 0);
  CU_ASSERT_EQUAL(ioopm_linked_list_length(ll), 1);
  ioopm_linked_list_destroy(ll);
}

void test_length_multiple_entries()
{
  for (int i = 2; i < 10; i++)
  {
    ioopm_list_t *ll = make_test_list(i, i);
    CU_ASSERT_EQUAL(ioopm_linked_list_length(ll), i);
    ioopm_linked_list_destroy(ll);
  }
}

void test_get_first_element()
{
  ioopm_list_t *ls = make_test_list(5, 0);
  CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ls, 0), (elem_t) {.int_v = list_entries[0]}));
  ioopm_linked_list_destroy(ls);
}

void test_get_middle_element()
{
  ioopm_list_t *ls = make_test_list(5, 0);
  CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ls, 2), (elem_t) {.int_v = list_entries[2]}));
  ioopm_linked_list_destroy(ls);
}

void test_get_last_element()
{
  ioopm_list_t *ls = make_test_list(5, 0);
  CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ls, 4), (elem_t) {.int_v = list_entries[4]}));
  ioopm_linked_list_destroy(ls);
}

void test_clear_empty_list()
{
  ioopm_list_t *ll = make_test_list(0, 0);
  ioopm_linked_list_clear(ll);
  CU_ASSERT(ioopm_linked_list_is_empty(ll));
  ioopm_linked_list_destroy(ll);
}

void test_clear_single_entry()
{
  ioopm_list_t *ll = make_test_list(1, 0);
  ioopm_linked_list_clear(ll);
  CU_ASSERT(ioopm_linked_list_is_empty(ll));
  ioopm_linked_list_destroy(ll);
}

void test_clear_multiple_entries()
{
  for (int i = 2; i < 10; i++)
  {
    ioopm_list_t *ll = make_test_list(i, i);
    ioopm_linked_list_clear(ll);
    CU_ASSERT(ioopm_linked_list_is_empty(ll));
    ioopm_linked_list_destroy(ll);
  }
}

void test_insert_empty_list()
{
  ioopm_list_t *ll = make_test_list(0, 0);
  ioopm_linked_list_insert(ll, 0, (elem_t) {.int_v = 42});
  CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, 0), (elem_t) {.int_v = 42}));
  ioopm_linked_list_destroy(ll);
}

void test_insert_single_element_start()
{
  ioopm_list_t *ll = make_test_list(1, 0);
  ioopm_linked_list_insert(ll, 0, (elem_t) {.int_v = 42});
  CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, 0), (elem_t) {.int_v = 42}));
  CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, 1), (elem_t) {.int_v = list_entries[0]}));
  ioopm_linked_list_destroy(ll);
}

void test_insert_single_element_end()
{
  ioopm_list_t *ll = make_test_list(1, 0);
  ioopm_linked_list_insert(ll, 1, (elem_t) {.int_v = 42});
  CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, 1), (elem_t) {.int_v = 42}));
  CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, 0), (elem_t) {.int_v = list_entries[0]}));
  ioopm_linked_list_destroy(ll);
}

void test_insert_multiple_elements_start()
{
  ioopm_list_t *ll = make_test_list(10, 0);

  ioopm_linked_list_insert(ll, 0, (elem_t) {.int_v = 42});
  CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, 0), (elem_t) {.int_v = 42}));
  for (int i = 0; i < 11; i++)
  {
    if(i != 0)
    {
      CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, i), (elem_t) {.int_v = list_entries[i-1]}));
    }
    else
    {
      CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, 0), (elem_t) {.int_v = 42}));
    }
  }
  
  ioopm_linked_list_destroy(ll);
}

void test_insert_multiple_elements_end()
{
  ioopm_list_t *ll = make_test_list(10, 0);
  ioopm_linked_list_insert(ll, 10, (elem_t) {.int_v = 42});
  CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, 10), (elem_t) {.int_v = 42}));
  for (int i = 0; i < 11; i++)
  {
    if(i != 10)
    {
      CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, i), (elem_t) {.int_v = list_entries[i]}));
    }
    else
    {
      CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, i), (elem_t) {.int_v = 42}));
    }
  }
  
  ioopm_linked_list_destroy(ll);
}

void test_insert_multiple_elements_middle()
{
  ioopm_list_t *ll = make_test_list(10, 0);
  ioopm_linked_list_insert(ll, 5, (elem_t) {.int_v = 42});
  CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, 5), (elem_t) {.int_v = 42}));
  for (int i = 0; i < 11; i++)
  {
    if(i < 5)
    {
      CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, i), (elem_t) {.int_v = list_entries[i]}));
    }
    else if (i>5)
    {
      CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, i), (elem_t) {.int_v = list_entries[i-1]}));
    }
    else
    {
      CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, 5), (elem_t) {.int_v = 42}));
    }
  }
  
  ioopm_linked_list_destroy(ll);
}

bool predicate_not_true_any(elem_t value, void *extra)
{
  int *ext_p = extra;
  bool got_extra = *ext_p == 2;
  return got_extra || value.int_v == 0;
}                 

bool predicate_not_true_all(elem_t value, void *extra)
{
  int *ext_p = extra;
  bool got_extra = *ext_p == 7;
  return got_extra || value.int_v == 4;
}         

bool predicate_true_any(elem_t value, void *extra)
{
  int *ext_p = extra;
  bool got_extra = *ext_p == 3;
  return got_extra && value.int_v == 8;
}         

bool predicate_true_all(elem_t value, void *extra)
{
  int *ext_p = extra;
  bool got_extra = *ext_p == 3;
  return got_extra && value.int_v%4 == 0;
}         

ioopm_predicate_ll predicates[4] = {predicate_not_true_any, predicate_not_true_all, predicate_true_any, predicate_true_all};

void test_apply_predicates_empty()
{
  ioopm_list_t *ll = ioopm_linked_list_create(int_compare_equal);
  int extra = 3;
  for (int i = 0; i < 4; i+=2)
  {
    CU_ASSERT_FALSE(ioopm_linked_list_any(ll, predicates[i], &extra));
    CU_ASSERT_FALSE(ioopm_linked_list_all(ll, predicates[i+1], &extra));
  }
  ioopm_linked_list_destroy(ll);
}

void test_apply_predicates_single()
{
  ioopm_list_t *ll = ioopm_linked_list_create(int_compare_equal);
  int extra = 3;
  elem_t value = {.int_v = 8};
  ioopm_linked_list_append(ll, value);
  CU_ASSERT_FALSE(ioopm_linked_list_any(ll, predicates[0], &extra));
  CU_ASSERT_FALSE(ioopm_linked_list_all(ll, predicates[1], &extra));
  CU_ASSERT(ioopm_linked_list_any(ll, predicates[2], &extra));
  CU_ASSERT(ioopm_linked_list_all(ll, predicates[3], &extra));
  ioopm_linked_list_destroy(ll);
}

void test_apply_predicates_multiple()
{
  ioopm_list_t *ll = ioopm_linked_list_create(int_compare_equal);
  int extra = 3;
  int ints[7] = {4, 16, 8, 12, 20, 32, 28};
  for (int i = 0; i < 7; i++)
  {
    ioopm_linked_list_append(ll, (elem_t) {.int_v = ints[i]});
  }
  CU_ASSERT_FALSE(ioopm_linked_list_any(ll, predicates[0], &extra));
  CU_ASSERT_FALSE(ioopm_linked_list_all(ll, predicates[1], &extra));
  CU_ASSERT(ioopm_linked_list_any(ll, predicates[2], &extra));
  CU_ASSERT(ioopm_linked_list_all(ll, predicates[3], &extra));
  ioopm_linked_list_destroy(ll);
}

int values1[5] = {1, 2, 3, 4, 5};
int values2[5] = {6, 7, 8, 9, 10};

void test_function(elem_t *value, void *extra)
{
  for (int i = 0; i < 5; i++)
  {
    if (value->int_v == values1[i])
    {
      value->int_v = values2[i];
      return;
    }
  }
}

bool predicate_test_function(elem_t value, void *extra)
{
  for (int i = 0; i < 5; i++)
  {
    if (value.int_v == values2[i])
    {
      return true;
    }
  }
  return false;
}

void test_apply_func_empty()
{
  ioopm_list_t *ll = ioopm_linked_list_create(int_compare_equal);
  CU_ASSERT_FALSE(ioopm_linked_list_all(ll, predicate_test_function, NULL));
  ioopm_linked_list_apply_to_all(ll, test_function, NULL);
  CU_ASSERT_FALSE(ioopm_linked_list_all(ll, predicate_test_function, NULL));
  CU_ASSERT_EQUAL(ioopm_linked_list_length(ll), 0);
  ioopm_linked_list_destroy(ll);  
}

void test_apply_func_single()
{
  ioopm_list_t *ll = ioopm_linked_list_create(int_compare_equal);
  ioopm_linked_list_append(ll, (elem_t) {.int_v = values1[2]});
  CU_ASSERT_FALSE(ioopm_linked_list_all(ll, predicate_test_function, NULL));
  ioopm_linked_list_apply_to_all(ll, test_function, NULL);
  CU_ASSERT(ioopm_linked_list_all(ll, predicate_test_function, NULL));
  CU_ASSERT_EQUAL(ioopm_linked_list_length(ll), 1);
  ioopm_linked_list_destroy(ll);  
}

void test_apply_func_multiple()
{
  ioopm_list_t *ll = ioopm_linked_list_create(int_compare_equal);
  for (int i = 0; i < 5; i++)
  {
    ioopm_linked_list_append(ll, (elem_t) {.int_v = values1[i]});
  }
  CU_ASSERT_FALSE(ioopm_linked_list_all(ll, predicate_test_function, NULL));
  ioopm_linked_list_apply_to_all(ll, test_function, NULL);
  CU_ASSERT(ioopm_linked_list_all(ll, predicate_test_function, NULL));
  CU_ASSERT_EQUAL(ioopm_linked_list_length(ll), 5);
  ioopm_linked_list_destroy(ll);  
}

void test_contains_empty()
{
  ioopm_list_t *ll = make_test_list(0, 0);
  CU_ASSERT_FALSE(ioopm_linked_list_contains(ll, (elem_t) {.int_v = 42}))
  ioopm_linked_list_destroy(ll);
}

void test_contains_single()
{
  ioopm_list_t *ll = make_test_list(1, 0);
  CU_ASSERT(ioopm_linked_list_contains(ll, (elem_t) {.int_v = list_entries[0]}))
  CU_ASSERT_FALSE(ioopm_linked_list_contains(ll, (elem_t) {.int_v = list_entries[1]}))
  ioopm_linked_list_destroy(ll);
}

void test_contains_multiple()
{
  ioopm_list_t *ll = make_test_list(16, 0);
  for (int i = 0; i < 16; i++)
  {
    CU_ASSERT(ioopm_linked_list_contains(ll, (elem_t) {.int_v = list_entries[i]}))
    CU_ASSERT_FALSE(ioopm_linked_list_contains(ll, (elem_t) {.int_v = list_entries[16+i]}))
  }
  ioopm_linked_list_destroy(ll);
}

void test_remove_from_list_single_entry()
{
  ioopm_list_t *ll = ioopm_linked_list_create(int_compare_equal);
  ioopm_linked_list_append(ll, (elem_t) {.int_v = 0});
  ioopm_linked_list_remove(ll, 0);
  CU_ASSERT(ioopm_linked_list_is_empty(ll));
  ioopm_linked_list_destroy(ll);
}

void test_remove_from_list_multiple_entries()
{
  ioopm_list_t *ll = ioopm_linked_list_create(int_compare_equal);
  elem_t first = (elem_t) {.int_v = 0};
  elem_t middle_left = (elem_t) {.int_v = 5};
  elem_t middle_right = (elem_t) {.int_v = 7};
  elem_t last = (elem_t) {.int_v = 10};
  elem_t elements_to_append[4] = {first, middle_left, middle_right,last};
  for (int i = 0; i < 4; i++){
    ioopm_linked_list_append(ll, elements_to_append[i]);
  }
  //test remove middle element
  elem_t middle_left_returned = ioopm_linked_list_remove(ll, 1);
  CU_ASSERT(int_compare_equal(middle_left_returned, middle_left));
  CU_ASSERT_EQUAL(ioopm_linked_list_length(ll), 3); 
  CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, 0), first));
  CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, 1), middle_right));
  CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, 2), last));

  //test remove first element
  elem_t first_returned = ioopm_linked_list_remove(ll, 0);
  CU_ASSERT(int_compare_equal(first_returned, first));
  CU_ASSERT_EQUAL(ioopm_linked_list_length(ll), 2);
  CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, 0), middle_right));
  CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, 1), last));

  //test remove last element
  elem_t last_removed = ioopm_linked_list_remove(ll, 1);
  CU_ASSERT(int_compare_equal(last_removed, last));
  CU_ASSERT_EQUAL(ioopm_linked_list_length(ll), 1);
  CU_ASSERT(int_compare_equal(ioopm_linked_list_get(ll, 0), middle_right));

  ioopm_linked_list_destroy(ll);
}

void test_contains_unsigned_int()
{
  ioopm_list_t *ll = ioopm_linked_list_create(unsigned_int_compare_equal);
  ioopm_linked_list_append(ll, (elem_t) {.u_int_v = 42});
  CU_ASSERT(ioopm_linked_list_contains(ll, (elem_t) {.u_int_v = 42}));
  ioopm_linked_list_destroy(ll);
}

void test_contains_bool()
{
  ioopm_list_t *ll = ioopm_linked_list_create(bool_compare_equal);
  ioopm_linked_list_append(ll, (elem_t) {.bool_v = true});
  CU_ASSERT(ioopm_linked_list_contains(ll, (elem_t) {.bool_v = true}));
  ioopm_linked_list_destroy(ll);
}

void test_contains_float()
{
  ioopm_list_t *ll = ioopm_linked_list_create(float_compare_equal);
  ioopm_linked_list_append(ll, (elem_t) {.float_v = 6.9});
  CU_ASSERT(ioopm_linked_list_contains(ll, (elem_t) {.float_v = 6.9}));
  ioopm_linked_list_destroy(ll);
}

void test_contains_char()
{
  ioopm_list_t *ll = ioopm_linked_list_create(char_compare_equal);
  ioopm_linked_list_append(ll, (elem_t) {.char_v = 'd'});
  CU_ASSERT(ioopm_linked_list_contains(ll, (elem_t) {.char_v = 'd'}));
  ioopm_linked_list_destroy(ll);
}

void test_contains_pointer()
{
  ioopm_list_t *ll = ioopm_linked_list_create(pointer_compare_equal);
  ioopm_list_t *list_ptr = ioopm_linked_list_create(int_compare_equal);
  ioopm_linked_list_append(ll, (elem_t) {.ptr_v = list_ptr});
  CU_ASSERT(ioopm_linked_list_contains(ll, (elem_t) {.ptr_v = list_ptr}));
  ioopm_linked_list_destroy(ll);
  ioopm_linked_list_destroy(list_ptr);
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

      (CU_add_test(my_test_suite, "Test appending with a single entry in empty list", test_append_empty_list) == NULL) ||
      (CU_add_test(my_test_suite, "Test appending with multiple entries", test_append_multiple_entries) == NULL) ||

      (CU_add_test(my_test_suite, "Test prepending with a single entry", test_prepend_empty_list) == NULL) ||
      (CU_add_test(my_test_suite, "Test prepending with multiple entries", test_prepend_multiple_entries) == NULL) ||
      
      (CU_add_test(my_test_suite, "Test prepending and appending", test_prepend_append) == NULL) ||
      (CU_add_test(my_test_suite, "Test appending  and prepending", test_append_prepend) == NULL) ||

      (CU_add_test(my_test_suite, "Test length of an empty list", test_length_empty_list) == NULL) ||
      (CU_add_test(my_test_suite, "Test length of a list with a single entry", test_length_single_entry) == NULL) ||
      (CU_add_test(my_test_suite, "Test length of a list with multiple entries", test_length_multiple_entries) == NULL) ||

      (CU_add_test(my_test_suite, "Get first element in list", test_get_first_element) == NULL) ||
      (CU_add_test(my_test_suite, "Get middle element in list", test_get_middle_element) == NULL) ||
      (CU_add_test(my_test_suite, "Get last element in list", test_get_last_element) == NULL) ||

      (CU_add_test(my_test_suite, "Test clear on an empty list", test_clear_empty_list) == NULL) ||
      (CU_add_test(my_test_suite, "Test clear on a list with a single entry", test_clear_single_entry) == NULL) ||
      (CU_add_test(my_test_suite, "Test clear on a list with multiple entries", test_clear_multiple_entries) == NULL) ||

      (CU_add_test(my_test_suite, "Test insert on an empty list", test_insert_empty_list) == NULL) ||
      (CU_add_test(my_test_suite, "Test insert at start on a list with a single entry", test_insert_single_element_start) == NULL) ||
      (CU_add_test(my_test_suite, "Test insert at end on a list with a single entry", test_insert_single_element_end) == NULL) ||
      (CU_add_test(my_test_suite, "Test insert at start on a list with multiple entries", test_insert_multiple_elements_start) == NULL) ||
      (CU_add_test(my_test_suite, "Test insert at end on a list with multiple entries", test_insert_multiple_elements_end) == NULL) ||
      (CU_add_test(my_test_suite, "Test insert in middle on a list with multiple entries", test_insert_multiple_elements_middle) == NULL) ||

      (CU_add_test(my_test_suite, "Test predicates on an empty list", test_apply_predicates_empty) == NULL) ||
      (CU_add_test(my_test_suite, "Test predicates on a list with a single entry", test_apply_predicates_single) == NULL) ||
      (CU_add_test(my_test_suite, "Test predicates on a list with multiple entries", test_apply_predicates_multiple) == NULL) ||

      (CU_add_test(my_test_suite, "Test apply function to all on an empty list", test_apply_func_empty) == NULL) ||
      (CU_add_test(my_test_suite, "Test apply function to all on a list with a single entry", test_apply_func_single) == NULL) ||
      (CU_add_test(my_test_suite, "Test apply function to all on a list with multiple entries", test_apply_func_multiple) == NULL) ||

      (CU_add_test(my_test_suite, "Test remove entry from list with single entry", test_remove_from_list_single_entry) == NULL) ||
      (CU_add_test(my_test_suite, "Test remove entries (first, middle, last) from list with multiple entries", test_remove_from_list_multiple_entries) == NULL) ||
      
      (CU_add_test(my_test_suite, "Test contains on an empty list", test_contains_empty) == NULL) ||
      (CU_add_test(my_test_suite, "Test contains on a list with a single entry", test_contains_single) == NULL) ||
      (CU_add_test(my_test_suite, "Test contains on a list with multiple entries", test_contains_multiple) == NULL) ||
      (CU_add_test(my_test_suite, "Test contains on a list with multiple entries", test_contains_multiple) == NULL) ||
      (CU_add_test(my_test_suite, "Test contains when elem_t is unsigned int", test_contains_unsigned_int) == NULL) ||
      (CU_add_test(my_test_suite, "Test contains when elem_t is bool", test_contains_bool) == NULL) ||
      (CU_add_test(my_test_suite, "Test contains when elem_t is float", test_contains_float) == NULL) ||
      (CU_add_test(my_test_suite, "Test contains when elem_t is char", test_contains_char) == NULL) ||
      (CU_add_test(my_test_suite, "Test contains when elem_t is void ptr", test_contains_pointer) == NULL) ||
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
