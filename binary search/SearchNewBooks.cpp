// Copyright 2018 Brian Nguyen
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <chrono> //NOLINT (build/c++11)

class SearchNewBooks {
 public:
        int isbn;
        std::string condition;


    // std::vector<SearchNewBooks>newBooks;

    // void readIn(string fileName, vector<SearchNewBooks> newBooks);
};

class TimeElapsed {
 public:
};

std::vector<SearchNewBooks*> readIn(std::string fileName) {
  std::vector<SearchNewBooks*>bookVector;
  std::ifstream booksFile(fileName);  // opens the file

  // checks if file is valid
  if (!booksFile) {
  std::cerr << "Cannot open the file: " << fileName << std::endl;
        exit(1);
  } else {
      std::string line, line2;
      int counter = 1;
      int vectorIndex = 0;

      while (getline(booksFile, line)) {
          std::stringstream ss(line);
          bookVector.vector::push_back(new SearchNewBooks);

                while (getline(ss, line2, ',')) {
            // std::cout << line << std::endl;

                    if (counter%2 == 1) {
                    bookVector[vectorIndex]->isbn = stoi(line2);
                    counter++;
                    } else {
                    bookVector[vectorIndex]->condition = line2;
                    counter++;
                    }
                }
                vectorIndex++;
      }
        booksFile.close();
  }
    return bookVector;
}

int linearSearch(std::vector<SearchNewBooks*>newBooks,
  std::vector<SearchNewBooks*>requiredBooks,
  std::vector<SearchNewBooks*>foundBooks) {
    std::vector<SearchNewBooks*>::iterator itr1, itr2;

    int index = 0;

    for (itr1 = newBooks.begin() ; itr1 != newBooks.end() ; itr1++) {
        for (itr2 = requiredBooks.begin(); itr2 != requiredBooks.end();
        itr2++) {
            if (((*itr1)->isbn == (*itr2)->isbn) &&
            ((*itr1)->condition == (*itr2)->condition)) {
                foundBooks.vector::push_back(new SearchNewBooks);
                foundBooks[index]->isbn = (*itr1)->isbn;
                foundBooks[index]->condition = (*itr1)->condition;
                // std::cout << foundBooks[index]->isbn << " " <<
                // foundBooks[index]->condition << std::endl;
                index++;
            }
        }
    }
    return index;
}


bool sortVector(SearchNewBooks *lhs, SearchNewBooks *rhs) {
    if (lhs->isbn > rhs->isbn) {
        return false;
    } else if (lhs->isbn == rhs->isbn) {
        if (lhs->condition == rhs->condition)
               return false;

        else if (lhs->condition == "digital")
            return false;

        else if (lhs->condition == "used")
            return true;

        else if (lhs->condition == "new" && rhs->condition == "used")
            return false;

        else if (lhs->condition == "new" && rhs->condition == "digital")
            return true;
    } else {
        return true;
    }
    return true;
}


  int binarySearch(std::vector<SearchNewBooks*>newBooks,
    std::vector<SearchNewBooks*>requiredBooks,
    std::vector<SearchNewBooks*>foundBooks) {
    // std::vector<SearchNewBooks*>::newBooks;



    // for (int i = 0; i < 8; i++ )
    // {std::cout << newBooks[i]->isbn << " "
    // << newBooks[i]->condition << std::endl;}


    int low = 0;
    int high = newBooks.size() - 1;
    int mid;
    int index = 0;

    for (int i = 0; (unsigned)i < requiredBooks.size(); i++) {
        int y = low;
        int z = high;

        while (y < z) {
            mid = (y + z)/2;

            if (sortVector(newBooks[mid], requiredBooks[i]))
                y = mid + 1;

            else
                z = mid;
        }



        if (requiredBooks[i]->isbn == newBooks[y]->isbn &&
          requiredBooks[i]->condition == newBooks[y]->condition) {
            foundBooks.push_back(new SearchNewBooks);
            foundBooks[index] = requiredBooks[i];

           // std::cout << foundBooks[index]->isbn
           // << " " << foundBooks[index]->condition << std::endl;
            index++;
        }
    }
    return index;
}

void writeResult(int counter, std::string fileName) {
    std::ofstream resultsFile;
    resultsFile.open(fileName);
    resultsFile << counter << std::endl;
    resultsFile.close();
}

void TimeElapsed(std::vector<SearchNewBooks*>newBooks,
  std::vector<SearchNewBooks*>requiredBooks,
  std::vector<SearchNewBooks*>foundBooks, std::string fileName) {
    char input;
    std::cout << "Choice of search method ([l]inear, [b]inary)?" << std::endl;
    std::cin >> input;
    int counting;
    switch (input) {
        case 'l':
            {
            // std::chrono::high_resolution_clock::time_point start;
            auto start = std::chrono::high_resolution_clock::now();

            counting = linearSearch(newBooks, requiredBooks, foundBooks);

            auto end1 = std::chrono::high_resolution_clock::now();
            double elapsed_us = std::chrono::duration<double,
            std::micro>(end1-start).count();
            std::cout << "CPU time: " << elapsed_us
            << " microseconds" << std::endl;
            writeResult(counting, fileName);
            }

            break;


        case 'b':
            {
            // std::chrono::high_resolution_clock::time_point start;
            std::sort(newBooks.begin(), newBooks.end(), sortVector);
            auto start = std::chrono::high_resolution_clock::now();

            counting = binarySearch(newBooks, requiredBooks, foundBooks);

            auto end1 = std::chrono::high_resolution_clock::now();
            double elapsed_us = std::chrono::duration<double,
            std::micro>(end1-start).count();
            std::cout << "CPU time: " << elapsed_us
            << " microseconds" << std::endl;
            writeResult(counting, fileName);
            }

            break;

        default:
            std::cout << "Incorrect choice" << std:: endl;
            TimeElapsed(newBooks, requiredBooks, foundBooks, fileName);
    }
}


int main(int argc, char **argv) {
    std::vector<SearchNewBooks*>newBooks;
    std::vector<SearchNewBooks*>requiredBooks;
    std::vector<SearchNewBooks*>foundBooks;

    std::string file1;
    std::string file2;
    std::string fileName;

    if (argc != 4) {
      std::cerr << "Usage: .SearchNewBooks <newBooks.dat> ";
      std::cerr << " <request.dat> <result_file.dat>" << std::endl;

    } else if ((argc = 4)) {
    file1 = argv[1];
    file2 = argv[2];
    fileName = argv[3];

    // SearchNewBooks * books = NULL;
    newBooks = readIn(file1);
    requiredBooks = readIn(file2);

    TimeElapsed(newBooks, requiredBooks, foundBooks, fileName);
      }

  return 0;
  i}
