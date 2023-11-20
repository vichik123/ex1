#include "RLEList.h"
#include <stdlib.h>

int encodedListLength(RLEList pList);

int intLength(int n);

RLEList asciiArtRead(FILE *in_stream) {
    if (in_stream == NULL) {
        return RLEListCreate();
    }

    RLEList head = RLEListCreate();
    char currentChar;
    if (fscanf(in_stream, "%c", &currentChar) == 1) {
        head->c = currentChar;
        head->n = 1;
    } else {
        return head;
    }

    while (fscanf(in_stream, "%c", &currentChar) == 1) {
        RLEListAppend(head, currentChar);
    }

    return head;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream) {
    if (list == NULL || out_stream == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    while (list != NULL) {
        for (int i = 0; i < list->n; i++) {
            fprintf(out_stream, "%c", list->c);
        }
        list = list->next;
    }

    return RLE_LIST_SUCCESS;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream) {
    if (list == NULL || out_stream == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    RLEListResult exportResult;
    char *string = RLEListExportToString(list, &exportResult);
    if (string == NULL) {
        return RLE_LIST_OUT_OF_MEMORY; // Not on the HW to return anything but NULL_ARGUMENT and SUCCESS...
    }
    if (exportResult != RLE_LIST_SUCCESS) {
        return exportResult;
    }

    fprintf(out_stream, "%s", string);
    free(string);
    return RLE_LIST_SUCCESS;
}

char invertSpace(char c) {
    if (c == ' ') {
        return '@';
    } else if (c == '@') {
        return ' ';
    }
    return c;
}

RLEListResult asciiArtPrintInverted(RLEList list, FILE *out_stream) {
    if (list == NULL || out_stream == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    RLEListMap(list, invertSpace);

    return asciiArtPrint(list, out_stream);
}