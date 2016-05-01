# Treebank Tokenizer in C

This is a C implementation of the [Treebank Tokenizer](https://www.cis.upenn.edu/~treebank/tokenization.html) and, more precisely a direct translation of the Python implementation present in [NLTK](http://www.nltk.org/_modules/nltk/tokenize/treebank.html). This was developed on my spare time as an exercise to get more familiar with development in C. No thorough validation of the outputs nor performance comparisons between this and other implementations have been performed at this point.

# But why didn't you use the [sed script](https://www.cis.upenn.edu/~treebank/tokenizer.sed)???

Shut up.

# What remains to be done?

This being just a for fun, \#do-it-in-C, project, I don't have any clear goals on its future. However, it would be nice to:

1. Validate the outputs (by comparing them to the NLTK ones and the Treebank sed script for example.
2. Similarly benchmark its performance and memory efficiency.
3. Add usage and other nice features.
4. Fix the rushed Makefile.
5. Add compilation of static and dynamic libraries (should be straight forward).

# Installation

1. Download and compile [PCRE2](ftp://ftp.csx.cam.ac.uk/pub/software/programming/pcre/).
2. Edit the *PCRE2_DIR* variable in *src/Makefile* to let it know where the static library is.
3. Go to the root project directory and *make*.

# Usage

```
[diego@localhost bin]$ ./tokenize "The p53 gene like the Rb gene, is a tumor suppressor gene."
The p53 gene like the Rb gene , is a tumor suppressor gene .
```
Or, equivalently:
```
[diego@localhost bin]$ echo "The p53 gene like the Rb gene, is a tumor suppressor gene." | ./tokenize
The p53 gene like the Rb gene , is a tumor suppressor gene .
```

# Licensing

This program is being released under the GNU GPL v3 license (see License.md for more information).

# What now?

Use it!! And fix the bugs!!! :)
