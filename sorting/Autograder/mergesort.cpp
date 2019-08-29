// Merge Sort
//
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "mergesort.h"

void MergeSort(std::vector<int>* numbers, int *comp, int *mem) {
   MergeSortRecurse(numbers, 0, numbers->size() - 1, comp, mem);
}


void MergeSortRecurse(std::vector<int>* numbers, int i, int k, int *comp, int *mem) {
   int j = 0;

   if (i < k) {
      j = (i + k) / 2;  // Find the midpoint in the partition

      // Recursively sort left and right partitions
      MergeSortRecurse(numbers, i, j, comp, mem);
      MergeSortRecurse(numbers, j + 1, k, comp, mem);

      // Merge left and right partition in sorted order
      Merge(numbers, i, j, k, comp, mem);
   }
}

void Merge(std::vector<int>* numbers, int i, int j, int k, int *comp, int *mem) {
   int mergedSize = k - i + 1;                // Size of merged partition
   int mergePos = 0;                          // Position to insert merged number
   int leftPos = 0;                           // Position of elements in left partition
   int rightPos = 0;                          // Position of elements in right partition
   std::vector<int> mergedNumbers;
   mergedNumbers.resize(mergedSize);



         // Dynamically allocates temporary array
                                              // for merged numbers

   leftPos = i;                               // Initialize left partition position
   rightPos = j + 1;                          // Initialize right partition position

   // Add smallest element from left or right partition to merged numbers
   while (leftPos <= j && rightPos <= k) {
      if ((*numbers)[leftPos] < (*numbers)[rightPos]) {
         mergedNumbers[mergePos] = (*numbers)[leftPos];
         ++(*comp);
         (*mem) = (*mem) + 4;
         ++leftPos;
      }
      else {
         mergedNumbers[mergePos] = (*numbers)[rightPos];
         (*mem) = (*mem) + 4;
         ++(*comp);
         ++rightPos;

      }
      ++mergePos;
   }

   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= j) {
      mergedNumbers[mergePos] = (*numbers)[leftPos];
      ++leftPos;
      ++mergePos;
      (*mem) = (*mem) + 2;

   }


   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= k) {
      mergedNumbers[mergePos] = (*numbers)[rightPos];
      ++rightPos;
      ++mergePos;
      (*mem) = (*mem) + 2;

   }

   // Copy merge number back to numbers
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      (*numbers)[i + mergePos] = mergedNumbers[mergePos];
      (*mem) = (*mem) + 2;

   }
}
