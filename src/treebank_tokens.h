typedef struct treebank_tokens {
	char** token_array;
	int length;
} treebank_tokens_t;

treebank_tokens_t* treebank_tokens_new();

void treebank_tokens_free(treebank_tokens_t* treebank_tokens);

void treebank_tokens_append(treebank_tokens_t* treebank_tokens, char* token);
