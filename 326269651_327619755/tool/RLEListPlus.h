struct RLEList_t {
    char c; // The character the node represents
    int n; // The number of times the character appears
    struct RLEList_t *next; // Pointer to the next node
};


int intLength(int num);

int encodedListLength(RLEList list);
