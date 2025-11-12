#include "data.h"

bool WriteBackSucceed(DocumentFrequency& document_frequency) {
  ofstream out(kDocumentFrequencyPath, ios::trunc);
  if (!out.is_open())
    return false;
  for (int bin_number = 0; bin_number < kHashNumber; ++bin_number) {
    for (int i = 0; i < document_frequency.get_data(bin_number).size(); ++i) {
      out << document_frequency.get_data(bin_number).at(i).word << '\t'
          << document_frequency.get_data(bin_number).at(i).frequency << endl;
    }
  }
  return true;
}

void Train(istream & in) {
  DocumentFrequency document_frequency(kDocumentFrequencyPath);
  StopwordsList stopwords_list(kStopwordsListPath);
  string word;
  while (in >> word) {
    if (word == (string)"_end_")
      break;
    if (!stopwords_list.is_included(word)) {
     document_frequency.increase_frequency(word);
    }
  }
  if (!WriteBackSucceed(document_frequency))
    throw runtime_error("Failed to Update DocumentFrequencyList");
  cout << "Successfully trained." << endl;
}/*----Train----*/
