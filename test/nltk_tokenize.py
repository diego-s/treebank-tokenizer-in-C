import nltk, sys

input_stream = open("corpus_sentences.txt", "r")
output_stream = sys.stdout
sentences = list(input_stream.readlines())
input_stream.close()
for sentence in sentences:
    tokens = nltk.word_tokenize(sentence)
    output_stream.write(" ".join(tokens) + " \n")
output_stream.close()
