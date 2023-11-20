#include "RLEList.h"
#include <stdlib.h>



//implement the functions here

RLEList RLEListCreate() {
    RLEList list = malloc(sizeof(struct RLEList_t));
    if (list != NULL) {
        list->next = NULL;
    }
    return list; // If malloc fails this will be NULL
}

void RLEListDestroy(RLEList list) {
    RLEList next = list->next;

    while (list != NULL) {
        next = list->next;
        free(list);
        list = next;
    }
}

RLEListResult RLEListAppend(RLEList list, char value) {
    if (list == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    while (list->next != NULL) {
        list = list->next;
    }

    if (list->c == value) {
        list->n++; // If the character already at end of list increase count
    } else {
        list->next = malloc(sizeof(struct RLEList_t)); // Otherwise allocate new node
        if (list->next == NULL) {
            return RLE_LIST_OUT_OF_MEMORY;
        }
        list->next->next = NULL;
        list->next->c = value;
        list->next->n = 1;
    }

    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list) {
    if (list == NULL) {
        return -1;
    }

    int len = 0;
    while (list != NULL) {
        len++;
        list = list->next;
    }

    return len;
}

RLEListResult RLEListRemove(RLEList list, int index) {
    if (list == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    int listLength = RLEListSize(list);
    if (index < 1 || index >= listLength) {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

    RLEList nextNext = NULL;

    for (int i = 0; i < index - 1; i++) {
        list = list->next;
    }

    // list->next is not NULL since index is in bounds
    nextNext = list->next->next;
    free(list->next);
    list->next = nextNext; // If nextNext is null then the list will simply be shortened
    return RLE_LIST_SUCCESS;
}

char RLEListGet(RLEList list, int index, RLEListResult *result) {
    if (list == NULL) {
        *result = RLE_LIST_NULL_ARGUMENT;
        return 0;
    }
    int listLength = RLEListSize(list);
    if (index < 0 || index >= listLength) {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return 0;
    }

    for (int i = 0; i < index; i++) {
        list = list->next;
    }

    *result = RLE_LIST_SUCCESS;
    return list->c;
}

int intLength(int num) {
    int length = 1;
    while (num >= 10) {
        num /= 10;
        length++;
    }
    return length;
}

int encodedListLength(RLEList list) {
    if (list == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    int length = 0;
    while (list != NULL) {
        length += 2; // Adding space for the character and a comma
        length += intLength(list->n); // Adding space for the number of times the character appears
        list = list->next;
    }
    return length;
}

char *RLEListExportToString(RLEList list, RLEListResult *result) {
    if (list == NULL) {
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }

    int listLength = RLEListSize(list);
    int stringLength = encodedListLength(list) + 1;
    char *string = malloc(sizeof(char) * stringLength);
    if (string == NULL) {
        *result = RLE_LIST_ERROR;
        return NULL;
    }
    int index = 0;
    for (int i = 0; i < listLength; i++) {
        string[index++] = list->c;
        int currIntLength = intLength(list->n);
        int tmpInt = list->n;
        for (int k = 0; k < currIntLength; k++) {
            string[index++] = '0' + tmpInt % 10;
            tmpInt /= 10;
        }
        string[index++] = '\n';
        list = list->next;
    }
    string[index] = 0;

    *result = RLE_LIST_SUCCESS;
    return string;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function) {
    if (list == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    while (list != NULL) {
        list->c = map_function(list->c);
        list = list->next;
    }

    return RLE_LIST_SUCCESS;
}