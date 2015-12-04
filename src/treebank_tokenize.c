#include <treebank.h>

static char* preprocess(char* string) {
	
	//starting quotes
	string = regex_replace("^\"", "``", string);
	string = regex_replace("(``)", " $1 ", string);
    string = regex_replace("([ (\\[{<])\"", "$1 `` ", string);

	//punctuation
	string = regex_replace("([:,])([^\\d])", " $1 $2", string);
	string = regex_replace("([:,])$", " $1 ", string);
	string = regex_replace("\\.\\.\\.", " ... ", string);
	string = regex_replace("[;@#$%&]", " $1 ", string);
	string = regex_replace("([^\\.])(\\.)([\\]\\)}>\"']*)\\s*$", "$1 $2$3 ", 
		string);
	string = regex_replace("([?!])", " $1 ", string);
	
	string = regex_replace("([^'])' ", "$1 ' ", string);

	//parens, brackets, etc.
	string = regex_replace("([\\]\\[\\(\\)\\{\\}\\<\\>])", " $1 ", string);
	string = regex_replace("--", " -- ", string);
	
	//add extra space to make things easier
	char* string_2 = malloc(sizeof(char*) * strlen(string) + 3);
	strcpy(string_2, " ");
	strcat(string_2, string);
	strcat(string_2, " ");
	
	//ending quotes
	string = regex_replace("\"", " '' ", string);
	string = regex_replace("(\\S)('')", " $1 $2 ", string);
	
	string = regex_replace("([^' ])('[sS]|'[mM]|'[dD]|') ", "$1 $2 ", string);
	string = regex_replace("([^' ])('ll|'LL|'re|'RE|'ve|'VE|n't|N'T) ", 
		"$1 $2 ", string);
	
	//contractions 2
	string = regex_replace("(?i)\b(can)(not)\b", " $1 $2 ", string);
	string = regex_replace("(?i)\b(d)('ye)\b", " $1 $2 ", string);
	string = regex_replace("(?i)\b(gim)(me)\b", " $1 $2 ", string);
	string = regex_replace("(?i)\b(gon)(na)\b", " $1 $2 ", string);
	string = regex_replace("(?i)\b(got)(ta)\b", " $1 $2 ", string);
	string = regex_replace("(?i)\b(lem)(me)\b", " $1 $2 ", string);
	string = regex_replace("(?i)\b(mor)('n)\b", " $1 $2 ", string);
	string = regex_replace("(?i)\b(wan)(na) ", " $1 $2 ", string);
	
	//contractions 3
	string = regex_replace("(?i) ('t)(is)\b", " $1 $2 ", string);
	string = regex_replace("(?i) ('t)(was)\b", " $1 $2 ", string);

	//non-treebank modification: newlines
	string = regex_replace("[\r\n]", " ", string);
	
	return string;
}

treebank_tokens_t* treebank_tokenize(char* sentence) {
	char* procsent = preprocess(sentence);
	char* delimiters = " ";
	treebank_tokens_t* tokens = treebank_tokens_new();
	int num_tokens = 0;
	char* token = strsep(&procsent, delimiters);
	while (token != NULL) {
		if (strlen(token) > 0) treebank_tokens_append(tokens, token);
		token = strsep(&procsent, delimiters);
	}
	return tokens;
}
