#include <treebank.h>

treebank_tokens_t* treebank_tokens_new() {
	treebank_tokens_t* treebank_tokens = malloc(sizeof(treebank_tokens_t));
	treebank_tokens->token_array = malloc(0);
	treebank_tokens->length = 0;
	return treebank_tokens;
}

void treebank_tokens_free(treebank_tokens_t* treebank_tokens) {
	int length = treebank_tokens->length;
	char** token_array = treebank_tokens->token_array;
	for (int i = 0; i < length; i++) free(token_array[i]);
	free(treebank_tokens);
}

void treebank_tokens_append(treebank_tokens_t* treebank_tokens, char* token) {
	treebank_tokens->length++;
	int length = treebank_tokens->length;
	treebank_tokens->token_array = realloc(treebank_tokens->token_array, 
		sizeof(char*) * length);
	treebank_tokens->token_array[length - 1] = strdup(token);
}
