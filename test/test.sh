set -e

# sentence detection
python sentence_detect.py > corpus_sentences.txt

# gold standard results generation
mkdir -p results
sed -f sed_tokenize.sed corpus_sentences.txt > results/sed.txt
python nltk_tokenize.py > results/nltk.txt

# generation of our the treebank-tokenizer-in-c results
echo -ne > results/treebank-tokenizer-in-c.txt
echo -ne > log.txt
while read SENTENCE; do
	../bin/tokenize "$SENTENCE" >> results/treebank-tokenizer-in-c.txt 2>> \
		log.txt
done < corpus_sentences.txt

# compare results
diff results/nltk.txt results/sed.txt
diff results/treebank-tokenizer-in-c.txt results/nltk.txt
