#include "SearchNewBooks.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class SearchNewBooks {

public:

    int ISBN;
    string condition;

    vector<SearchNewBooks>newBooks;

    //void readIn(string fileName, vector<SearchNewBooks> newBooks);

};

void readIn(string fileName, vector<SearchNewBooks> newBooks) {
   std::ifstream booksFile(fileName); //opens the file

   //checks if file is valid
   if (!booksFile)
   {
      cout << "Cannot open the File: " << fileName << endl;

   }

   else
   {
      std::string line;
      int counter = 1;

      while (getline(booksFile, line,','))
      {
            std::cout << line << std::endl;

            if (counter%2 == 1)
            {
                //booksFile[counter -1].isbn = line;
                counter++;
            }

      }

      booksFile.close();
   }

}

int main(int argc, char **argv) {

    vector<SearchNewBooks>newBooks;

    char* file1;
  //char* file2;

    file1 =  argv[1];
  //file2 =  argv[2];

    SearchNewBooks * books = NULL;
    books->readIn(file1,newBooks);

   return 0;


}
