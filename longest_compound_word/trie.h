
#define NO_OF_CHARS 27 //note that 27th char is the string termination char

typedef struct TNODE {
    struct TNODE *next[NO_OF_CHARS];
    char c;
    int is_valid_word:1;

}TNODE;

void initTnode(TNODE* tnode);
TNODE* createTrieNode();
int isLeaf(TNODE* node);
int  searchWordInTrie(TNODE* troot, char *word);
TNODE* addWordInTrie(char *word, TNODE* troot);
void print_trie(TNODE *root);
