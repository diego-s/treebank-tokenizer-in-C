#include <treebank.h>

char* regex_replace(char* pattern, char* replacement, char* string) {
	//TODO: handle errors
	PCRE2_SIZE pattern_length = strlen(pattern);
	int error_code;
	PCRE2_SIZE error_offset;
	uint32_t options = PCRE2_SUBSTITUTE_GLOBAL;
	pcre2_code* regex = pcre2_compile((PCRE2_UCHAR *) pattern, 
		pattern_length, options, &error_code, &error_offset, NULL);
	if (regex == NULL) {
		fprintf(stderr, "Unable to compile pattern: %s\n", pattern);
		return NULL;
	}
	PCRE2_SIZE replacement_length = strlen(replacement);
	PCRE2_SIZE start_offset = 0;
	size_t substitution_length = 1000;
	PCRE2_UCHAR* substitution = malloc(sizeof(PCRE2_UCHAR) * 
		substitution_length);
        int string_length = strlen(string);
	int ret = pcre2_substitute(regex,(PCRE2_SPTR8) string, string_length, 
		start_offset, options, NULL, NULL, (PCRE2_SPTR8) replacement, 
		replacement_length, substitution, &substitution_length);
	if (ret < 0) {
		fprintf(stderr, "Failed to perform substitution: %s %d.\n",
			pattern, ret);
		return NULL;
	}
	char* result = strdup((const char *) substitution);
	return result;
}
