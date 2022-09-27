#include <CUnit/Basic.h>
#include <stdlib.h>
#include "linked_list.h"
//#include "linked_list.c"
#include "iterator.h"
//#include "iterator.c"
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

// These are example test functions. You should replace them with
// functions of your own.

static ioopm_list_t *make_test_list(int no_entries, int start_idx)
{
  ioopm_list_t *ll = ioopm_linked_list_create();
  for (int i = start_idx; i < no_entries + start_idx; i++)
  {
    ioopm_linked_list_append(ll, list_entries[i]);
  }
  return ll;
}

void test_create_destroy()
{
  ioopm_list_t *ll = make_test_list(2, 0);
  ioopm_list_iterator_t *iter = ioopm_iterator_create(ll);
  CU_ASSERT_PTR_NOT_NULL(iter);
  ioopm_iterator_destroy(iter);
  ioopm_linked_list_destroy(ll);
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
