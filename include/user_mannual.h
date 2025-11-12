#ifndef USER_MANNUAL_H
#define USER_MANNUAL_H

#include <string>
#include <cstdio>
#include <cstdlib>
using namespace std;

class UserMannual {
public:
  UserMannual(string file_name);
  void print_welcome_info();
  void print_help();

protected:

private:
  string file_name_;
  const string version_info = "Keyword Extractor Version 1.0";
};

#endif
