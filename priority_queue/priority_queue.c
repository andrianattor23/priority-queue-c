#include "priority_queue.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

void PriorityQueueInit(PriorityQueue* pq, int elem_size, int capacity, CmpFn cmp_fn, FreeFn free_fn) {
 pq->allocLen = capacity;
 pq->elemSize = elem_size;
 pq->free_fn = free_fn;
 pq->cmp_fn = cmp_fn;
 pq->logLen = 0;
 pq->base = malloc(pq->elemSize* pq->allocLen);
 assert(pq->base!=NULL);

}

void PriorityQueueDestroy(PriorityQueue* pq) {
  for(int i = 0; i<pq->logLen;i++){
    if(pq->free_fn!=NULL){
      pq->free_fn((char*)pq->base + pq->elemSize*i);
    }
  }
  free(pq->base);
}

int PriorityQueueNumElems(PriorityQueue* pq) {
  return pq->logLen;
}



bool PriorityQueuePush(PriorityQueue* pq, void* elem) {
  //pirveli davamate
  if(pq->logLen ==0){
    memcpy((char*)pq->base,elem,pq->elemSize);
    pq->logLen++;
   /* if(pq->free_fn!=NULL){
      pq->free_fn(elem);
    }
    free(elem); */
    return true;
  }

  //bolo elementi(yvelaze pataraze) tu naklebia gadmocemuli elementi
  if(pq->logLen == pq->allocLen && pq->cmp_fn(elem,(char*)pq->base+(pq->logLen-1)*pq->elemSize)<0){
    if(pq->free_fn!=NULL){
      pq->free_fn(elem);
    }
    //free(elem);
    return false;
  }else if(pq->logLen == pq->allocLen ){
      //bolo elementis washla
    if(pq->free_fn!=NULL){
      pq->free_fn((char*)pq->base+(pq->logLen-1)*pq->elemSize);
    }

    for(int i=0;i<pq->logLen;i++){
      if(pq->cmp_fn(elem,(char*)pq->base + i*pq->elemSize )>0){
         memmove((char*)pq->base + (i+1)*pq->elemSize,(char*)pq->base + i*pq->elemSize,(pq->logLen-i-1)*pq->elemSize);
        memcpy((char*)pq->base + i*pq->elemSize,elem,pq->elemSize);
       /* if(pq->free_fn!=NULL){
           pq->free_fn(elem);
        }*/
        return true;
      }  
     }

  }else{
    for(int i=0;i<pq->logLen;i++){
      if(pq->cmp_fn(elem,(char*)pq->base + i*pq->elemSize )>0){
        memmove((char*)pq->base + (i+1)*pq->elemSize,(char*)pq->base + i*pq->elemSize,(pq->logLen-i)*pq->elemSize);
        memcpy((char*)pq->base + i*pq->elemSize,elem,pq->elemSize);
        /*if(pq->free_fn!=NULL){
         pq->free_fn(elem);
        }*/
        pq->logLen++;
        return true;
      }
    }

  }
  memcpy((char*)pq->base + pq->logLen*pq->elemSize,elem,pq->elemSize);
 /* if(pq->free_fn!=NULL){
         pq->free_fn(elem);
  }*/
  pq->logLen++;
  return true;

  
  

}

void PriorityQueuePop(PriorityQueue* pq, void* elem) {
   pq->logLen--;
  memcpy(elem,(char*)pq->base,pq->elemSize);
  void* newBase = malloc(pq->elemSize*pq->allocLen);
  assert(newBase!=NULL);
  memcpy(newBase,(char*)pq->base+pq->elemSize,pq->logLen*pq->elemSize);
  free(pq->base);
  pq->base = newBase;
}

void PriorityQueueSetCapacity(PriorityQueue* pq, int capacity) {
  void* newBase = malloc(pq->elemSize*capacity);
  int bytes = 0;
  if(capacity<pq->logLen){
    bytes = capacity;
    pq->logLen=capacity;
  }else{
    bytes = pq->logLen;
  }
  memcpy(newBase,(char*)pq->base,bytes*pq->elemSize);
  free(pq->base);
  pq->base = newBase;
  pq->allocLen = capacity;

}
