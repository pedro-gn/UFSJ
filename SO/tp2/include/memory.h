#ifndef _MEMORY_H
#define _MEMORY_H

typedef struct Page Page;


/* *
 *
 * */
 
void AddNewPage(Page** first, Page** last, int numPages, int* usedPages, char value[9]);
void LRU(Page** first, Page** last, int numPages, int* usedPages, char value[9]);
void FIFO(Page** first, Page** last, int numPages, int* usedPages, char value[9]);
void Random(Page** first, int usedPages, char value[9]);
bool Find(Page** first, Page** last, char value[9], const char* alg);
void ReplacePage(const char* alg, Page** first, Page** last, int numPages, int* usedPages, char value[9]);
void WriteAddress(Page** first, Page** last, int numPages, int* usedPages, char tmpAddress[9], int* faults, int* writes);
void FreeMemory(Page* first);


#endif /* __MEMORY_H */