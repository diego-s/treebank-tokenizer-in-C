import nltk, sys

input_stream = open("corpus_raw.txt", "r")
output_stream = sys.stdout
text = "".join(list(input_stream.readlines()))
input_stream.close()
sentences = nltk.sent_tokenize(text)
for sentence in sentences:
  sentence = sentence.replace("\n", " ")
  sentence = sentence.replace("\r", " ")
  sentence = sentence.replace("\t", " ")
  output_stream.write(sentence + "\n")
output_stream.close()
