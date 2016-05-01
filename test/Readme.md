## Test Suite

# Basic Idea

The purpose of this test is to make sure that the output of the program matches 
the output of other "gold standard" programs. With that in mind, we've taken a
text corpus from the Wikipedia entry for the Rb tumor suppressor [1], extracted 
the sentences from this text and prepared the resulting tokenization results 
using two "gold standards", NLTK and the Treebank tokenization sed script [3].

The raw text (corpus_raw.txt) is first divided in sentences using NLTK 
(sentence_detect.py) and written to corpus_sentences.txt. Sentences are then 
tokenized and their tokens separated by spaces. Each sentence's tokenization 
results are written to a new line.  Results are compared using diff, and an 
exact match is expected.

# References

[1] https://en.wikipedia.org/wiki/Retinoblastoma_protein
[2] http://www.nltk.org/
[3] https://www.cis.upenn.edu/~treebank/tokenization.html
