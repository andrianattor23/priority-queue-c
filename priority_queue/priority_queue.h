#ifndef PARADIGMS_PROBLEMS_PRIORITY_QUEUE_H_
#define PARADIGMS_PROBLEMS_PRIORITY_QUEUE_H_

#include <stdbool.h>

typedef void(*FreeFn)(void* elem);
// აბრუნებს უარყოფით რიცხვის თუ პირველი ელემენტი ნაკლებია მეორეზე,
// დადებით რიცხვს თუ პირელი მეტია მეორეზე, ხოლო 0-ს ტოლობის შემთხვევაში.
typedef int(*CmpFn)(const void* a, const void* b);

typedef struct {
  void* base;
  int elemSize;
  int allocLen;
  CmpFn cmp_fn;
  FreeFn free_fn;
  int logLen;

} PriorityQueue;

// ინიციალიზაციას უკეთებს გადმოცემულ pq ობიექტს. elem_size განსაზღვრავს რიგში შესანახი ელემენტების ზომას ბაიტებში.
// capacity აღნიშნავს რიგის საწყის ზომას, ანუ მაქსიმუმ რამდენი ელემენტს შეინახავს იგი. cmp_fn უნდა გამოიყენოთ
// ელემენტების ერთმანეთთან შესადარებლად, და free_fn ელემენტების მეხსიერების გასათავისუფლებლად თუ იგი NULL-ის ტოლი არ არის.
void PriorityQueueInit(PriorityQueue* pq, int elem_size, int capacity, CmpFn cmp_fn, FreeFn free_fn);
// უნდა გაათავისუფლოს რიგის და მასში შენახული ელემენტების მიერ გამოყენებული მეხსიერება.
void PriorityQueueDestroy(PriorityQueue* pq);
// უნდა დააბრუნოს რიგში შენახული ელემენტების რაოდენობა.
int PriorityQueueNumElems(PriorityQueue* pq);
// უნდა დაამატოს რიგში მოცემული ელემენტი. თუ რიგი უკვე სავსეა და გადმოცემული ელემენტი რიგში შენახულ ელემენტებს შორის
// ყველაზე პატარაზე ნაკლებია, მაშინ ახალი ელემენტი არ უნდა დაამატოთ რიგში, წინააღმდეგ შემთხვევაში ყველაზე პატარა ელემენტი
// უნდა ამოვარდეს რიგიდან რათა ადგილი განთავისუფლდეს ახალი ელემენტისთვის.
// უნდა დააბრუნოთ true თუ ახალი ელემენტი დაემატა რიგში და false წინააღმდეგ შემთხვევაში.
// ყოველთვის იღებს მფლობელობას რიგში დასამატებელ ელემენტზე, მიუხედავად იმისა ის მართლა დაემატება თუ არა რიგში.
bool PriorityQueuePush(PriorityQueue* pq, void* elem);
// რიგიდან უნდა ამოვარდეს ყველაზე დიდი ელემენტი და მისი მნიშვნელობა ჩაიწეროს გადმოცემულ elem მისამართზე, სადაც elem_size ზომის
// მეხსიერება უკვე გამოყოფილია.
void PriorityQueuePop(PriorityQueue* pq, void* elem);
// უნდა შეცვალოს რიგში შესაძლო შესანახი ელემენტების მაქსიმალური რაოდენობა. თუ ახალი capacity რიგში ამჯერად შენახული ელემენტების
// რაოდენობაზე ნაკლებია, მაშინ რიგიდან უნდა ამოაგდოთ ყველაზე პატარა ელემენტები ისე რომ რიგში შენახული ელემენტების რაოდენობა
// გახდეს ახალი capacity.
void PriorityQueueSetCapacity(PriorityQueue* pq, int capacity);

#endif // PARADIGMS_PROBLEMS_PRIORITY_QUEUE_H_
