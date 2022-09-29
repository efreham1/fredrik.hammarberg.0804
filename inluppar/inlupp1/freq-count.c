#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"
#include "linked_list.h"
#include "iterator.h"
#include "data_structure.h"

#define Delimiters "+-#@()[]{}.,:;!? \t\n\r"

static int cmpstringp(const void *p1, const void *p2)
{
  return strcmp(*(char *const *)p1, *(char *const *)p2);
}

void sort_keys(char *keys[], size_t no_keys)
{
  qsort(keys, no_keys, sizeof(char *), cmpstringp);
}

void process_word(char *word, ioopm_hash_table_t *ht)
{
  // FIXME: Rewrite to match your own interface, error-handling, etc.
  int freq =
    ioopm_hash_table_has_key(ht, (elem_t) {.ptr_v = word})?
    (ioopm_hash_table_lookup(ht, (elem_t) {.ptr_v = word}))->int_v:
    0;
  ioopm_hash_table_insert(ht, (elem_t) {.ptr_v = strdup(word)}, (elem_t) {.int_v = freq + 1});
}

void process_file(char *filename, ioopm_hash_table_t *ht)
{
  FILE *f = fopen(filename, "r");

  while (true)
  {
    char *buf = NULL;
    size_t len = 0;
    getline(&buf, &len, f);

    if (feof(f))
    {
      free(buf);
      break;
    }

    for (char *word = strtok(buf, Delimiters);
         word && *word;
         word = strtok(NULL, Delimiters))
    {
      process_word(word, ht);
    }

    free(buf);
  }

  fclose(f);
}

int string_sum_hash(elem_t e, int buckets)
{
  char *str = e.ptr_v;
  int result = 0;
  do
    {
      result += *str;
    }
  while (*++str != '\0');
  return result%buckets; 
}

bool string_eq(elem_t e1, elem_t e2)
{
  return (strcmp(e1.ptr_v, e2.ptr_v) == 0);
}

bool int_eq(elem_t e1, elem_t e2)
{
  return e1.int_v == e2.int_v;
}

bool string_lt(elem_t e1, elem_t e2)
{
  return (strcmp(e1.ptr_v, e2.ptr_v) < 0);
}

int main(int argc, char *argv[])
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create((ioopm_hash_function) string_sum_hash, string_eq, int_eq, string_lt);

  if (argc > 1)
  {
    for (int i = 1; i < argc; ++i)
    {
      process_file(argv[i], ht);
    }

    // FIXME: If the keys are returned as a list, transfer them into 
    // an array to use `` (perhaps using an iterator?)
    ioopm_list_t *keys_list= ioopm_hash_table_keys(ht);


    int list_length = ioopm_linked_list_length(keys_list);
    char *keys[list_length-1];
    ioopm_list_iterator_t *iter = ioopm_iterator_create(keys_list);
    int idx = 0;
    while (ioopm_iterator_has_next(iter))
    {
      keys[idx] = ioopm_iterator_current(iter).ptr_v;
      idx++;
      ioopm_iterator_next(iter);
    }
    ioopm_iterator_destroy(iter);
    ioopm_linked_list_destroy(keys_list);

    sort_keys(keys, list_length-1);

    FILE *file = fopen("output.txt", "w");
    for (int i = 0; i < list_length-1; ++i)
    {
      // FIXME: Update to match your own interface, error handling, etc.
      int freq = (ioopm_hash_table_lookup(ht, (elem_t) {.ptr_v = keys[i]}))->int_v;
      fprintf(file, "%s: %d\n", keys[i], freq);
    }
    fclose(file);
  }
  else
  {
    puts("Usage: freq-count file1 ... filen");
  }

  // FIXME: Leaks memory! Use valgrind to find out where that memory is 
  // being allocated, and then insert code here to free it.
  ioopm_hash_table_destroy(ht);
}

