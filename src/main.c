#include <treebank.h>

int main(int argc, char** argv) {
	char* content;
	if (argc > 1) { content = argv[1]; }
	else { content = read_stdin(); }
	treebank_tokens_t* tokens = treebank_tokenize(content);
	int num_tokens = tokens->length;
	for (int i = 0; i < num_tokens; i++) printf("%s\n", 
		tokens->token_array[i]);
	treebank_tokens_free(tokens);
	return 0;
}
