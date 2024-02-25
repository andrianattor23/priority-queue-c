#include "priority_queue.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASSERT_TRUE(a) {						\
    bool actual = (a);							\
    if (!actual) {							\
      printf("%s:%d Assertion failed: expected true got false\n", __FILE__, __LINE__); \
      return false;							\
    }									\
  }

#define ASSERT_FALSE(a) {						\
    bool actual = (a);							\
    if (actual) {							\
      printf("%s:%d Assertion failed: expected false got true\n", __FILE__, __LINE__); \
      return false;							\
    }									\
  }

#define ASSERT_INT_EQ(a, b) {						\
    int expected = (a);							\
    int actual = (b);							\
    if (expected != actual) {						\
      printf("%s:%d Assertion failed: expected %d got %d\n", __FILE__, __LINE__, expected, actual); \
      return false;							\
    }									\
  }

#define ASSERT_STR_EQ(a, b) {						\
    char* expected = (a);						\
    char* actual = (b);							\
    if (strcmp(expected, actual) != 0) {				\
      printf("%s:%d Assertion failed: expected \"%s\" got \"%s\"\n", __FILE__, __LINE__, expected, actual); \
      return false;							\
    }									\
  }

#define TEST(t) {				\
    printf("-- TESTING: %s\n", #t);		\
    if (t()) {					\
      printf("TEST %s: SUCCEEDED\n", #t);	\
    }						\
    else {					\
      printf("TEST %s: FAILED\n", #t);		\
    }						\
    printf("####\n\n");				\
  }

// ---- INTEGERS ----

int IntCmp(const void* a, const void* b) {
  return *(const int*)a - *(const int*)b;
}

bool Integers_EnoughCapacity() {
  PriorityQueue pq;
  PriorityQueueInit(&pq, sizeof(int), /*capacity=*/10, IntCmp, NULL);
  int x = 3, y = 7, z = 6, w = 2;
  ASSERT_TRUE(PriorityQueuePush(&pq, &x));
  ASSERT_INT_EQ(1, PriorityQueueNumElems(&pq));
  ASSERT_TRUE(PriorityQueuePush(&pq, &y));
  ASSERT_INT_EQ(2, PriorityQueueNumElems(&pq));
  ASSERT_TRUE(PriorityQueuePush(&pq, &z));
  ASSERT_INT_EQ(3, PriorityQueueNumElems(&pq));
  ASSERT_TRUE(PriorityQueuePush(&pq, &w));
  ASSERT_INT_EQ(4, PriorityQueueNumElems(&pq));
  int r;
  PriorityQueuePop(&pq, &r);
  ASSERT_INT_EQ(7, r);
  ASSERT_INT_EQ(3, PriorityQueueNumElems(&pq));
  PriorityQueuePop(&pq, &r);
  ASSERT_INT_EQ(6, r);
  ASSERT_INT_EQ(2, PriorityQueueNumElems(&pq));
  PriorityQueuePop(&pq, &r);
  ASSERT_INT_EQ(3, r);
  ASSERT_INT_EQ(1, PriorityQueueNumElems(&pq));
  PriorityQueuePop(&pq, &r);
  ASSERT_INT_EQ(2, r);
  ASSERT_INT_EQ(0, PriorityQueueNumElems(&pq));
  PriorityQueueDestroy(&pq);
  return true;
}

bool Integers_NotEnoughCapacity() {
  PriorityQueue pq;
  PriorityQueueInit(&pq, sizeof(int), /*capacity=*/2, IntCmp, NULL);
  int x = 3, y = 7, z = 6, w = 2;
  ASSERT_TRUE(PriorityQueuePush(&pq, &x));
  ASSERT_INT_EQ(1, PriorityQueueNumElems(&pq));
  ASSERT_TRUE(PriorityQueuePush(&pq, &y));
  ASSERT_INT_EQ(2, PriorityQueueNumElems(&pq));
  ASSERT_TRUE(PriorityQueuePush(&pq, &z));
  ASSERT_INT_EQ(2, PriorityQueueNumElems(&pq));
  ASSERT_FALSE(PriorityQueuePush(&pq, &w));
  ASSERT_INT_EQ(2, PriorityQueueNumElems(&pq));
  int r;
  PriorityQueuePop(&pq, &r);
  ASSERT_INT_EQ(7, r);
  ASSERT_INT_EQ(1, PriorityQueueNumElems(&pq));
  PriorityQueuePop(&pq, &r);
  ASSERT_INT_EQ(6, r);
  ASSERT_INT_EQ(0, PriorityQueueNumElems(&pq));
  PriorityQueueDestroy(&pq);
  return true;
}

bool Integers_EnoughCapacity_ButResize() {
  PriorityQueue pq;
  PriorityQueueInit(&pq, sizeof(int), /*capacity=*/10, IntCmp, NULL);
  int x = 3, y = 7, z = 6, w = 2;
  ASSERT_TRUE(PriorityQueuePush(&pq, &x));
  ASSERT_TRUE(PriorityQueuePush(&pq, &y));
  ASSERT_TRUE(PriorityQueuePush(&pq, &z));
  ASSERT_TRUE(PriorityQueuePush(&pq, &w));
  ASSERT_INT_EQ(4, PriorityQueueNumElems(&pq));
  int r;
  PriorityQueuePop(&pq, &r);
  ASSERT_INT_EQ(7, r);
  PriorityQueueSetCapacity(&pq, 2);
  ASSERT_INT_EQ(2, PriorityQueueNumElems(&pq));
  PriorityQueuePop(&pq, &r);
  ASSERT_INT_EQ(6, r);
  PriorityQueuePop(&pq, &r);
  ASSERT_INT_EQ(3, r);
  ASSERT_INT_EQ(0, PriorityQueueNumElems(&pq));
  PriorityQueueDestroy(&pq);
  return true;
}

bool Integers_EnoughCapacity_EvenAfterResize() {
  PriorityQueue pq;
  PriorityQueueInit(&pq, sizeof(int), /*capacity=*/10, IntCmp, NULL);
  int x = 3, y = 7, z = 6, w = 2;
  ASSERT_TRUE(PriorityQueuePush(&pq, &x));
  ASSERT_TRUE(PriorityQueuePush(&pq, &y));
  ASSERT_TRUE(PriorityQueuePush(&pq, &z));
  ASSERT_TRUE(PriorityQueuePush(&pq, &w));
  ASSERT_INT_EQ(4, PriorityQueueNumElems(&pq));
  int r;
  PriorityQueuePop(&pq, &r);
  ASSERT_INT_EQ(7, r);
  PriorityQueueSetCapacity(&pq, 6);
  ASSERT_INT_EQ(3, PriorityQueueNumElems(&pq));
  PriorityQueuePop(&pq, &r);
  ASSERT_INT_EQ(6, r);
  ASSERT_INT_EQ(2, PriorityQueueNumElems(&pq));
  PriorityQueuePop(&pq, &r);
  ASSERT_INT_EQ(3, r);
  ASSERT_INT_EQ(1, PriorityQueueNumElems(&pq));
  PriorityQueuePop(&pq, &r);
  ASSERT_INT_EQ(2, r);
  ASSERT_INT_EQ(0, PriorityQueueNumElems(&pq));
  PriorityQueueDestroy(&pq);
  return true;
}

bool Integers_NotEnoughCapacity_NotFullyEmptied() {
  PriorityQueue pq;
  PriorityQueueInit(&pq, sizeof(int), /*capacity=*/10, IntCmp, NULL);
  for (int i = 0; i < 100; i++) {
    ASSERT_TRUE(PriorityQueuePush(&pq, &i));
  }
  ASSERT_INT_EQ(10, PriorityQueueNumElems(&pq));
  int r;
  for (int i = 0; i < 5; ++i) {
    PriorityQueuePop(&pq, &r);
    ASSERT_INT_EQ(99 - i, r);
  }
  ASSERT_INT_EQ(5, PriorityQueueNumElems(&pq));
  PriorityQueueDestroy(&pq);
  return true;
}

// ---- STRINGS ----

int StrCmp(const void* a, const void* b) {
  return strcmp(*(const char**)a, *(const char**)b);
}

void StrFree(void* elem) {
  free(*(char**)elem);
}

bool Strings() {
  PriorityQueue pq;
  PriorityQueueInit(&pq, sizeof(char*), /*capacity=*/3, StrCmp, StrFree);
  char* a = strdup("foo");
  char* b = strdup("abcd");
  char* c = strdup("bar");
  char* d = strdup("abc");
  char* e = strdup("bc");
  ASSERT_TRUE(PriorityQueuePush(&pq, &a));
  ASSERT_TRUE(PriorityQueuePush(&pq, &b));
  ASSERT_TRUE(PriorityQueuePush(&pq, &c));


  ASSERT_FALSE(PriorityQueuePush(&pq, &d));

  ASSERT_TRUE(PriorityQueuePush(&pq, &e));
  ASSERT_INT_EQ(3, PriorityQueueNumElems(&pq));
  char* r;
  PriorityQueuePop(&pq, &r);
  ASSERT_STR_EQ("foo", r);
  ASSERT_INT_EQ(2, PriorityQueueNumElems(&pq));
  PriorityQueueSetCapacity(&pq, 1);
  ASSERT_INT_EQ(1, PriorityQueueNumElems(&pq));
  PriorityQueuePop(&pq, &r);
  ASSERT_STR_EQ("bc", r);
  ASSERT_INT_EQ(0, PriorityQueueNumElems(&pq));
  char* x = strdup("slkdufyhqwer");
  ASSERT_TRUE(PriorityQueuePush(&pq, &x));
  ASSERT_INT_EQ(1, PriorityQueueNumElems(&pq));
  PriorityQueueDestroy(&pq);
  return true;
}

// ---- Pairs ----

typedef struct {
  int x;
  char y;
} Pair;

Pair NewPair(int x, char y) {
  Pair p;
  p.x = x;
  p.y = y;
  return p;
}

int PairCmp(const void* a, const void* b) {
  const Pair* p = a;
  const Pair* q = b;
  if (p->x != q->x) {
    return p->x - q->x;
  }
  return p->y - q->y;
}

bool Pairs() {
  PriorityQueue pq;
  PriorityQueueInit(&pq, sizeof(Pair), /*capacity=*/2, PairCmp, NULL);
  Pair a = NewPair(1, 'f');
  Pair b = NewPair(3, 'b');
  Pair c = NewPair(2, 'd');
  Pair d = NewPair(2, 'n');
  Pair e = NewPair(2, 'e');
  ASSERT_TRUE(PriorityQueuePush(&pq, &a));
  ASSERT_TRUE(PriorityQueuePush(&pq, &b));
  ASSERT_INT_EQ(2, PriorityQueueNumElems(&pq));
  ASSERT_TRUE(PriorityQueuePush(&pq, &c));
  ASSERT_INT_EQ(2, PriorityQueueNumElems(&pq));
  ASSERT_TRUE(PriorityQueuePush(&pq, &d));
  ASSERT_INT_EQ(2, PriorityQueueNumElems(&pq));
  ASSERT_FALSE(PriorityQueuePush(&pq, &e));
  ASSERT_INT_EQ(2, PriorityQueueNumElems(&pq));
  Pair r;
  PriorityQueuePop(&pq, &r);
  ASSERT_TRUE(3 == r.x && 'b' == r.y);
  ASSERT_INT_EQ(1, PriorityQueueNumElems(&pq));
  PriorityQueuePop(&pq, &r);
  ASSERT_TRUE(2 == r.x && 'n' == r.y);
  ASSERT_INT_EQ(0, PriorityQueueNumElems(&pq));
  PriorityQueueDestroy(&pq);
  return true;
}

int main(int argc, char** argv) {
  // Integers
  TEST(Integers_EnoughCapacity);
  TEST(Integers_NotEnoughCapacity);
  TEST(Integers_EnoughCapacity_ButResize);
  TEST(Integers_EnoughCapacity_EvenAfterResize);
  TEST(Integers_NotEnoughCapacity_NotFullyEmptied);
  // Strings
  TEST(Strings);
  // Pairs
  TEST(Pairs);
  return 0;
}
