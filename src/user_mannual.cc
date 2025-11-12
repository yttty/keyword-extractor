#include "user_mannual.h"

UserMannual::UserMannual(string file_name) {
  this->file_name_ = file_name;
}

void UserMannual::print_welcome_info() {
  printf("--------------------About--------------------\n");
  printf("Name:\t\t %s\n", this->version_info.c_str());
  printf("Function:\t This program can extract 2 to 10 keywords from a given text.\n");
  printf("Author:\t\t Terrill Yang, SYSU.\n");
  printf("E-mail:\t\t tyyang_cn@foxmail.com\n\n");
}

void UserMannual::print_help() {
  system("cat ./README.md");
}
