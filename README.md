> This project now serve as a toy project for testing purpose.

# Test Instruction
- `conan install . --output-folder=build --build=missing --profile=default`
- `cd build; cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release`
- `cmake --build .`

# KeywordExtractor
Extract keywords form given text, using the method of statistics, previously trained with corpus from University of Oxford Text Archive.

#### Features
  -TF-IDF & cosine resemblance

  -Keyword Extraction

  -Article Resemblance Check

#### Corpus List
  Stop Words list: http://www.ranks.nl/stopwords

  British National Corpus: http://www.natcorp.ox.ac.uk/

  American National Corpus: http://www.anc.org/

  Leipzig Corpora Collection: http://corpora.informatik.uni-leipzig.de/download.html
