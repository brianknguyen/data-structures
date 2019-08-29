// Insertion Sort
//
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks
#include "insertionsort.h"

void InsertionSort(std::vector<int>* numbers, int* comp, int* mem) {
   int i = 0;
   int j = 0;
   int temp = 0;  // Temporary variable for swap
   //(*mem) = (*mem) + 3;

   for (i = 1; i < numbers->size(); ++i) {
      j = i;
      //++(*mem);
      // Insert numbers[i] into sorted part
      // stopping once numbers[i] in correct position
    //  if (j>0){
      //  ++(*mem) = (*mem) +2;
      while (j>0) {
        if ((*numbers)[j] < (*numbers)[j - 1]){
         ++(*comp);
         // Swap numbers[j] and numbers[j - 1]
         temp = (*numbers)[j];
         (*numbers)[j] = (*numbers)[j - 1];
         (*numbers)[j - 1] = temp;
         (*mem) = (*mem) + 6;
         --j;

         }
         else
         {
             ++(*comp);
             (*mem) = (*mem) + 2;
             break;
         }

      }
      //(*mem) = (*mem) + 2;
      //}
   }

   return;
}
