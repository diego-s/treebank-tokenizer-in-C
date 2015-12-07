#include <treebank.h>

static char* preprocess(char* string, size_t inputlen) {
	
	//starting quotes
	string = regex_replace("^\"", "``", string, inputlen);
	string = regex_replace("(``)", " $1 ", string, inputlen);
	string = regex_replace("([ (\\[{<])\"", "$1 `` ", string, inputlen);

	//punctuation
	string = regex_replace("([:,])([^\\d])", " $1 $2", string, inputlen);
	string = regex_replace("([:,])$", " $1 ", string, inputlen);
	string = regex_replace("\\.\\.\\.", " ... ", string, inputlen);
	string = regex_replace("[;@#$%&]", " $1 ", string, inputlen);
	string = regex_replace("([^\\.])(\\.)([\\]\\)}>\"']*)\\s*$", "$1 $2$3 ", 
		string, inputlen);
	string = regex_replace("([?!])", " $1 ", string, inputlen);
	
	string = regex_replace("([^'])' ", "$1 ' ", string, inputlen);

	//parens, brackets, etc.
	string = regex_replace("([\\]\\[\\(\\)\\{\\}\\<\\>])", " $1 ", string, inputlen);
	string = regex_replace("--", " -- ", string, inputlen);
	
	//add extra space to make things easier
	char* tmpstring = malloc(sizeof(char) * (inputlen + 3));
	strcpy(tmpstring, " ");
	strcat(tmpstring, string);
	strcat(string, " ");
	inputlen += 3;
	
	//ending quotes
	string = regex_replace("\"", " '' ", string, inputlen);
	string = regex_replace("(\\S)('')", " $1 $2 ", string, inputlen);
	
	string = regex_replace("([^' ])('[sS]|'[mM]|'[dD]|') ", "$1 $2 ", string, inputlen);
	string = regex_replace("([^' ])('ll|'LL|'re|'RE|'ve|'VE|n't|N'T) ", 
		"$1 $2 ", string, inputlen);
	
	//contractions 2
	string = regex_replace("(?i)\b(can)(not)\b", " $1 $2 ", string, inputlen);
	string = regex_replace("(?i)\b(d)('ye)\b", " $1 $2 ", string, inputlen);
	string = regex_replace("(?i)\b(gim)(me)\b", " $1 $2 ", string, inputlen);
	string = regex_replace("(?i)\b(gon)(na)\b", " $1 $2 ", string, inputlen);
	string = regex_replace("(?i)\b(got)(ta)\b", " $1 $2 ", string, inputlen);
	string = regex_replace("(?i)\b(lem)(me)\b", " $1 $2 ", string, inputlen);
	string = regex_replace("(?i)\b(mor)('n)\b", " $1 $2 ", string, inputlen);
	string = regex_replace("(?i)\b(wan)(na) ", " $1 $2 ", string, inputlen);
	
	//contractions 3
	string = regex_replace("(?i) ('t)(is)\b", " $1 $2 ", string, inputlen);
	string = regex_replace("(?i) ('t)(was)\b", " $1 $2 ", string, inputlen);

	//non-treebank modification: newlines
	string = regex_replace("[\r\n]", " ", string, inputlen);
	
	return string;
}

treebank_tokens_t* treebank_tokenize(char* sentence) {
	size_t inputlen = strlen(sentence);

	char* procsent = preprocess(sentence, inputlen);
	char* delimiters = " ";
	treebank_tokens_t* tokens = treebank_tokens_new();
	char* token = strsep(&procsent, delimiters);
	while (token != NULL) {
		if (strlen(token) > 0) treebank_tokens_append(tokens, token);
		token = strsep(&procsent, delimiters);
	}
	return tokens;
}
