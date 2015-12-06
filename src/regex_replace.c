#include <treebank.h>

char* regex_replace(char* pattern, char* replacement, char* string, size_t string_length) {
	//TODO: handle errors
	PCRE2_SIZE pattern_length = strlen(pattern);
	int error_code;
	PCRE2_SIZE error_offset;
	uint32_t options = PCRE2_SUBSTITUTE_GLOBAL;
	pcre2_code* regex = pcre2_compile((PCRE2_UCHAR *) pattern, pattern_length, options,
		&error_code, &error_offset, NULL);
	if (regex == NULL) {
		fprintf(stderr, "Unable to compile pattern: %s\n", pattern);
		return NULL;
	}
	PCRE2_SIZE replacement_length = strlen(replacement);
	PCRE2_SIZE start_offset = 0;
	size_t substitution_length = 1000;
	PCRE2_UCHAR* substitution = malloc(string_length);

	int ret = pcre2_substitute(regex, string, string_length, start_offset,
		options, NULL, NULL, replacement, replacement_length,
		substitution, &substitution_length);
	if (ret < 0) {
		fprintf(stderr, "Failed to perform substitution. Pattern: %s Ret: %d Input: %s. Returning original string.\n",
			pattern, ret, string);
		return string;
	}
	if (ret == 0) {
		fprintf(stderr, "No substitution to perform: %s %d.\n", pattern, ret);
		return string;
	}
	fprintf(stderr, "Found something. Pattern: %s Ret: %d input: %s resultstring: %s outlen: %d.\n", pattern, ret, string, substitution, substitution_length);

	char* result = strdup(substitution);
	fprintf(stderr, "Copied result: %s.\n", result);
	return result;
}
