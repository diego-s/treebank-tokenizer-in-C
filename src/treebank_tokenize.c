#include <treebank.h>

static char* preprocess(char* string, size_t input_length) {
	
	//starting quotes
	string = regex_replace("^\"", "``", string, input_length);
	string = regex_replace("(``)", " $1 ", string, input_length);
	string = regex_replace("([ (\\[{<])\"", "$1 `` ", string, input_length);

	//punctuation
	string = regex_replace("([:,])([^\\d])", " $1 $2", string, input_length);
	string = regex_replace("([:,])$", " $1 ", string, input_length);
	string = regex_replace("\\.\\.\\.", " ... ", string, input_length); 
	string = regex_replace("[;@#$%&]", " $1 ", string, input_length);
	string = regex_replace("([^\\.])(\\.)([\\]\\)}>\"']*)\\s*$", 
		"$1 $2$3 ", string, input_length);
	string = regex_replace("([?!])", " $1 ", string, input_length);
	
	string = regex_replace("([^'])' ", "$1 ' ", string, input_length);

	//parens, brackets, etc.
	string = regex_replace("([\\]\\[\\(\\)\\{\\}\\<\\>])", " $1 ", string, 
		input_length);
	string = regex_replace("--", " -- ", string, input_length);
	
	//add extra space to make things easier
	char* temp_string = malloc(sizeof(char) * (input_length + 3));
	strcpy(temp_string, " ");
	strcat(temp_string, string);
	strcat(string, " ");
	input_length += 3;
	
	//ending quotes
	string = regex_replace("\"", " '' ", string, input_length);
	string = regex_replace("(\\S)('')", " $1 $2 ", string, input_length);
	
	string = regex_replace("([^' ])('[sS]|'[mM]|'[dD]|') ", "$1 $2 ", 
		string, input_length);
	string = regex_replace("([^' ])('ll|'LL|'re|'RE|'ve|'VE|n't|N'T) ", 
		"$1 $2 ", string, input_length);
	
	//contractions 2
	string = regex_replace("(?i)\b(can)(not)\b", " $1 $2 ", string, 
		input_length);
	string = regex_replace("(?i)\b(d)('ye)\b", " $1 $2 ", string, input_length);
	string = regex_replace("(?i)\b(gim)(me)\b", " $1 $2 ", string, 
		input_length);
	string = regex_replace("(?i)\b(gon)(na)\b", " $1 $2 ", string, 
		input_length);
	string = regex_replace("(?i)\b(got)(ta)\b", " $1 $2 ", string, 
		input_length);
	string = regex_replace("(?i)\b(lem)(me)\b", " $1 $2 ", string, 
		input_length);
	string = regex_replace("(?i)\b(mor)('n)\b", " $1 $2 ", string, 
		input_length);
	string = regex_replace("(?i)\b(wan)(na) ", " $1 $2 ", string, input_length);
	
	//contractions 3
	string = regex_replace("(?i) ('t)(is)\b", " $1 $2 ", string, input_length);
	string = regex_replace("(?i) ('t)(was)\b", " $1 $2 ", string, input_length);

	//non-treebank modification: newlines
	string = regex_replace("[\r\n]", " ", string, input_length);
	
	return string;
}

treebank_tokens_t* treebank_tokenize(char* sentence) {
	size_t input_length = strlen(sentence);
	char* processed_sentence = preprocess(sentence, input_length);
	char* delimiters = " ";
	treebank_tokens_t* tokens = treebank_tokens_new();
	char* token = strsep(&processed_sentence, delimiters);
	while (token != NULL) {
		if (strlen(token) > 0) treebank_tokens_append(tokens, token);
		token = strsep(&processed_sentence, delimiters);
	}
	return tokens;
}
