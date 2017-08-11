//forward declaration

#define NO_OF_CHARS 27 //note that 27th char is the string termination char
typedef struct TNODE {
    char c;
    int word_count;
    struct TNODE *next[NO_OF_CHARS];
}TNODE;

void initTnode(TNODE* tnode);
TNODE* createTrieNode();
int isLeaf(TNODE* node);
//retruns true only of the whole word matches
int  searchWholeWordInTrie(TNODE* troot, char *word);

// returns true even if there is a partial match, for eg if trie has geeks
// then g . gee, geek would all return true
int  searchPartialWordInTrie(TNODE* troot, char *word);
TNODE* addWordInTrie(char *word, TNODE* troot);
void print_words(TNODE *troot, char *path, int cnt);
void print_trie(TNODE* root);
