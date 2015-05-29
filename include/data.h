#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace std;

#ifdef WIN32
const char kStopwordsListPath[] = ".\\data\\stop_words_list.log";
const char kDocumentFrequencyPath[] = ".\\data\\document_frequency.log";
#else
const char kStopwordsListPath[] = "./data/stop_words_list.log";
const char kDocumentFrequencyPath[] = "./data/document_frequency.log";
#endif

const int kHashNumber = 47;

int GetHash(string s);

template <typename T>
class Container { //inspired by vector
public:
  virtual void add(const T& to_add_) = 0;
  vector<T> & get_data(int bin_number) {
    return data_[bin_number];
  }

protected:

private:
  vector<T> data_[kHashNumber];

};

class StopwordsList : public Container<string> {
public:
  StopwordsList(const string dict_path);
  bool is_included(const string& to_check_);
  void add(const string& to_add_);

protected:

private:

};

struct WordFrequency {
  string word;
  unsigned long frequency;
  double tf_idf;
};

class DocumentFrequency : public Container<WordFrequency>{
public:
  DocumentFrequency();
  DocumentFrequency(const string dict_path);
  void add(const WordFrequency& to_add_);
  int get_frequency(const string& to_get_);
  unsigned long get_total_words_count();
  void increase_frequency(const string& to_increase_);

protected:

private:
  unsigned long total_words_count_;

};

class KeywordsList {
public:
  KeywordsList(int keywords_count);
  void insert(WordFrequency new_word);
  WordFrequency get(int i);
  ~KeywordsList();

protected:

private:
  WordFrequency* data_;
  int keywords_max_count_;

};

#endif
