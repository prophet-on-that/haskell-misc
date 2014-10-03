/* A (non-type safe) C implementation of Haskell's Maybe monad */
#include <malloc.h>

// Not type-safe, of course
typedef struct Maybe 
{
  int isJust; // Non-zero for Just value
  int value;
} Maybe;

// caller deallocates
Maybe *
just (int z)
{
  Maybe *maybe = malloc (sizeof (Maybe));
  maybe->isJust = 1;
  maybe->value = z;
  return maybe;
}

// caller deallocates
Maybe *
nothing ()
{
  Maybe *maybe = malloc (sizeof (Maybe));
  maybe->isJust = 0;
  return maybe;
}

Maybe *
bind (Maybe *a, Maybe * (*f) (int))
{
  if (a->isJust)
    return f (a->value);
  return nothing ();
}

typedef struct List
{
  int key;
  int value;
  struct List *next;
} List;

Maybe *
lookup (int key, List *list)
{
  if (list == NULL)
    return nothing ();
  for (; list->next != NULL; list = list->next)
    if (key == list->key)
      return just (list->value);
  return nothing ();
}

int
f (int n)
{
  return n * 2;
}

Maybe *
g (int z)
{
  return just (f (z));
}

Maybe *
lookup_and_double (int key, List *list)
{
  return bind (lookup (key, list), g);
}

// stub
int main ()
{
  return 0;
}
