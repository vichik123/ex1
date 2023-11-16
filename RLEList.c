#include "RLEList.h"
#include <stdlib.h>

struct RLEList_t {
    char c; // The character the node represents
    int n; // The number of times the character appears
    struct RLEList_t *next; // Pointer to the next node
};

//implement the functions here

RLEList RLEListCreate() {
    RLEList list = malloc(sizeof(struct RLEList_t));
    return list; // If malloc fails this will be NULL
}

void RLEListDestroy(RLEList list) {
    RLEList next = list->next;

    while (next != NULL) {
        next = list->next;
        free(list);
        list = next;
    }
}

RLEListResult RLEListAppend(RLEList list, char value) {
    if (list == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    RLEList next = list->next;
    RLEList temp = list;
    while (next != NULL) {
        next = next->next;
        temp = temp->next;
    }

    if (temp->c == value) {
        temp->n++; // If the character already at end of list increase count
    } else {
        temp->next = malloc(sizeof(struct RLEList_t)); // Otherwise allocate new node
        if (temp->next == NULL) {
            return RLE_LIST_OUT_OF_MEMORY;
        }
        temp->next->c = value;
        temp->next->n = 1;
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
    if (index < 0 || index >= listLength) {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

    RLEList nextNext = NULL;
    //Checks in case list length is 1
    if (list->next != NULL) {
        nextNext = list->next->next;
    }else {
        //Since index is in bounds here index be 0
        free(list);
        return RLE_LIST_SUCCESS;
    }

    //In case (length > 1) and (index == 0)
    if (index == 0) {
        RLEList temp = list;
        list = list->next;
        free(temp);
        return RLE_LIST_SUCCESS;
    }

    //Here (length > 1) and (index != 0)
    for (int i = 0; i < index - 1; i++) {
        list = list->next;
        nextNext = nextNext->next;
    }

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

char* RLEListExportToString(RLEList list, RLEListResult* result) {
    if (list == NULL) {
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }

    int sum = 0;
    while (list != NULL) {
        sum += list->n;
        list = list->next;
    }
    int listLength = RLEListSize(list);

    char* string = malloc(sizeof(char) * sum);
    if (string == NULL) {
        *result = RLE_LIST_ERROR;
        return NULL;
    }
    int index = 0;
    for (int i = 0; i < listLength; i++) {
        for (int j = 0; j < list->n; j++, index++) {
            string[index] = list->c;
        }
        list = list->next;
    }

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