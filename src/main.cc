#include <string>
#include <stdexcept>
#include <fstream>
#include <iostream>
using namespace std;

#include <cstring>
#include <cstdio>
#include "user_mannual.h"
#include "data.h"


void Train(istream & in);
void Extract(istream & in, int keywords_count);

int main(int argc, char const *argv[])
{
  string file_name(argv[0]);
  UserMannual usage(file_name);

  usage.print_welcome_info();
  if (argc == 1) {
    usage.print_help();
    return 0;
  }

  try {
    if (argc < 3) {
      throw runtime_error("Too few argument!");
    }

    if ((strcmp(argv[1], "-train") == 0) || (strcmp(argv[1],"-t") == 0)) {
      if ((strcmp(argv[2], "-file") == 0) || (strcmp(argv[2], "-f") == 0)) {
        printf("--------------------Train mode(-file)--------------------\n");
        printf("Input path of corpus(*.txt):\n");
        string path;
        cin >> path;
        ifstream in(path);
        if (!in.is_open())
          throw runtime_error("Failed to open file! Please check file path...");
        Train(in);
      } else if ((strcmp(argv[2], "-keyboard") == 0) || (strcmp(argv[2], "-k") == 0)) {
        printf("--------------------Train mode(-keyboard)--------------------\n");
        printf("Waiting for input:(Type \"_end_\" to end input)\n");
        Train(cin);
      } else {
        throw runtime_error("Invalid argument!");
      }
    } else if ((strcmp(argv[1], "-extract") == 0) || (strcmp(argv[1], "-e") == 0)) {
      int keywords_count = 0;
      if ((strcmp(argv[2], "-file") == 0) || (strcmp(argv[2], "-f") == 0)) {
        printf("--------------------Extract mode(-file)--------------------\n");

        while ((keywords_count < 2) || (keywords_count > 10)) {
          printf("Input number of keywords to extract(max: 10 , min: 2):\n");
          cin >> keywords_count;
        }

        printf("Input path of corpus(*.txt):\n");
        string path;
        cin >> path;
        ifstream in(path);
        if (!in.is_open())
          throw runtime_error("Failed to open file! Please check file path...");
        Extract(in, keywords_count);
      } else if ((strcmp(argv[2], "-keyboard") == 0) || (strcmp(argv[2], "-k") == 0)) {
        printf("--------------------Extract mode(-keyboard)--------------------\n");
        printf("Waiting for input:(Type \"_end_\" to end input)\n");
        while ((keywords_count < 2) || (keywords_count > 10)) {
          printf("Input number of keywords to extract(max: 10 , min: 2):\n");
          cin >> keywords_count;
        }

        Extract(cin, keywords_count);
      } else {
        throw runtime_error("Invalid argument!");
      }
    } else {
      throw runtime_error("Invalid argument!");
    }
  }
  catch (runtime_error& ex) {
    printf("RUNTIME_ERROR: %s\n\n", ex.what());
    usage.print_help();
  }
  catch (...) {
    printf("Unknown Error, please contact the author...\n\n");
  }

  return 0;
}/*----main----*/

