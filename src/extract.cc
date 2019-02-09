/*
 * File name: extract.cc
 * Author: Yang Tianyi, SYSU
 * Function: the implemention of function Extract
 * Last edit: 2015-5-29
 *
 * Copyright (C) 2015 Yang Tianyi
 * E-mail: yeah-y@qq.com
 */ 

#include "data.h"
#include <cmath>

void Extract(istream & in, int keywords_count) {
  DocumentFrequency corpus_document_frequency(kDocumentFrequencyPath);
  DocumentFrequency text_document_frequency;
  StopwordsList stopwords_list(kStopwordsListPath);
  KeywordsList keywords_list(keywords_count);

  string single_word;
  while (in >> single_word) {
    text_document_frequency.increase_frequency(single_word);
  }

  if (keywords_count >= text_document_frequency.get_total_words_count())
    throw runtime_error("Not enough words to extract");

  double tf, idf;
  for (int bin_number = 0; bin_number < kHashNumber; ++bin_number) {
    for (int i = 0; i < text_document_frequency.get_data(bin_number).size(); ++i) {
      tf = text_document_frequency.get_data(bin_number).at(i).frequency / \
        text_document_frequency.get_total_words_count();
      idf = log(corpus_document_frequency.get_total_words_count() / \
        (corpus_document_frequency.get_frequency(text_document_frequency.get_data(bin_number).at(i).word) + 1));
      text_document_frequency.get_data(bin_number).at(i).tf_idf = tf * idf;
      keywords_list.insert(text_document_frequency.get_data(bin_number).at(i));
    }
  }

  cout << "\n--------------------Keywords--------------------\n";
  for (int i = 0; i < keywords_count; ++i) {
    cout << keywords_list.get(i).word << ' ';
  }  
  cout << "\n\n";

}/*----Extract----*/
