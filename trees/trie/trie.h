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
int  searchWordInTrie(TNODE* troot, char *word);
TNODE* addWordInTrie(char *word, TNODE* troot);
void print_words(TNODE *troot, char *path, int cnt);
void print_trie(TNODE* root);
