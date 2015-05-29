/*
 * File name: data.cc
 * Author: Yang Tianyi, SYSU
 * Function: define data class(StopwordsList and DocumentFrequency)
 * Last edit: 2015-5-29
 *
 * Copyright (C) 2015 Yang Tianyi
 * E-mail: yeah-y@qq.com
 */

#include "data.h"

int GetHash(string s) {
  int k = 0;
  for (int i = 0; i < s.size(); ++i) {
    k += s[i];
  }
  return (k % kHashNumber);
}

StopwordsList::StopwordsList(const string dict_path) {
  cout << "Importing StopwordsList...\n";

  ifstream in(dict_path);
  if (!in.is_open())
    throw runtime_error("Failed to import StopwordsList, please check data...");
  string stopword;
  while (in >> stopword)
    this->add(stopword);

  cout << "Import succeed.\n";
}

bool StopwordsList::is_included(const string& to_check_) {
  int bin_number = GetHash(to_check_);
  for (int i = 0; i < this->get_data(bin_number).size(); ++i) {
    if (strcmp(this->get_data(bin_number).at(i).c_str(), to_check_.c_str()) == 0)
      return true;
  }
  return false;
}

void StopwordsList::add(const string& to_add_) {
  this->get_data(GetHash(to_add_)).push_back(to_add_);
}

DocumentFrequency::DocumentFrequency() {

}

DocumentFrequency::DocumentFrequency(const string dict_path) {
  cout << "Importing DocumentFrequencyList...\n";

  this->total_words_count_ = 0;
  ifstream in(dict_path);
  if (!in.is_open())
    throw runtime_error("Failed to import DocumentFrequencyList, please check data...");

  WordFrequency word_frequency;
  char temp_word[50];
  char temp_word2[2];
  while (in.getline(temp_word, 50, '\t')) {
    word_frequency.word = (string)temp_word;
    in >> word_frequency.frequency;
    in.getline(temp_word2, 2, '\n');
    this->add(word_frequency);
  }

  cout << "Import succeed.\n";
}

void DocumentFrequency::add(const WordFrequency& to_add_) {
  this->get_data(GetHash(to_add_.word)).push_back(to_add_);
  this->total_words_count_ += to_add_.frequency;
}

int DocumentFrequency::get_frequency(const string& to_get_) {
  int bin_number = GetHash(to_get_);
  for (int i = 0; i < this->get_data(bin_number).size(); ++i) {
    if (strcmp(this->get_data(bin_number).at(i).word.c_str(), to_get_.c_str()) == 0)
      return this->get_data(bin_number).at(i).frequency;
  }
  return 0; 
}

unsigned long DocumentFrequency::get_total_words_count() {
  return this->total_words_count_;
}

void DocumentFrequency::increase_frequency(const string& to_increase_) {
  int bin_number = GetHash(to_increase_);
  for (int i = 0; i < this->get_data(bin_number).size(); ++i) {
    if (strcmp(this->get_data(bin_number).at(i).word.c_str(), to_increase_.c_str()) == 0) {
      ++ this->get_data(bin_number).at(i).frequency;
      ++ this->total_words_count_;
      return;
    }
  }
  WordFrequency new_word;
  new_word.word = to_increase_;
  new_word.frequency = 1;
  this->add(new_word);
}

KeywordsList::KeywordsList(int keywords_count) {
  this->keywords_max_count_ = keywords_count;
  WordFrequency temp;
  temp.word = "null";
  temp.frequency = 0;
  temp.tf_idf = -1;
  this->data_ = new WordFrequency[keywords_count];
  for (int i = 0; i < this->keywords_max_count_; ++i) {
    this->data_[i] = temp;
  }
}

void KeywordsList::insert(WordFrequency new_word) {
  for (int i = 0; i < this->keywords_max_count_; ++i) {
    if (new_word.tf_idf > this->data_[i].tf_idf) {
      for (int j = this->keywords_max_count_-1; j > i; --j)
        this->data_[j] = this->data_[j-1];
      this->data_[i] = new_word;
      break;
    }
  }
}

WordFrequency KeywordsList::get(int i) {
  return this->data_[i];
}

KeywordsList::~KeywordsList() {
  delete [] this->data_;
}
