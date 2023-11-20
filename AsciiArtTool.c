#include "RLEList.h"
#include <stdlib.h>

int encodedListLength(RLEList pList);

int intLength(int n);

RLEList asciiArtRead(FILE *in_stream) {
    if (in_stream == NULL) {
        return RLEListCreate();
    }

    RLEList head = RLEListCreate();
    RLEList currNode = head;
    char currentChar;
    int count = 1;

    // Scanning for the first character
    if (fscanf(in_stream, "%c", &currentChar) != 1) {
        return head;
    } else {
        currNode->n = count;
        currNode->c = currentChar;
    }

    while (fscanf(in_stream, "%c", &currentChar) == 1) {
        if (currentChar == currNode->c) {
            count++;
        } else {
            RLEList newNode = malloc(sizeof(struct RLEList_t));
            if (newNode == NULL) {
                currNode->n = count;
                return head;
            } else {
                newNode->c = currentChar;
                newNode->n = 1;
            }
            currNode->n = count;
            currNode->next = newNode;
            currNode = newNode;
            count = 1;
        }
    }
    currNode->n = count;
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
    for (RLEList temp = list; temp->next != NULL; temp = temp->next) {
        length += 2; // Adding space for the character and a comma
        length += intLength(temp->n); // Adding space for the number of times the character appears
    }
    return length;
}


RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream) {
    if (list == NULL || out_stream == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    int listLength = RLEListSize(list);
    int stringLength = encodedListLength(list);
    char *string = malloc(stringLength); // Each node will be represented as 2 chars [c][n]
    if (string == NULL) {
        return RLE_LIST_OUT_OF_MEMORY; // Not on the HW to return anything but NULL_ARGUMENT and SUCCESS...
    }

    RLEListResult exportResult;
    string = RLEListExportToString(list, &exportResult);

    int index = 0;
    switch (exportResult) {
        case RLE_LIST_SUCCESS:
            for (int i = 0; i < listLength; i++) {
                string[index++] = list->c;
                int currIntLength = intLength(list->n);
                int tmpInt = list->n;
                for (int k = 0; k < currIntLength; k++) {
                    string[index++] = '0' + tmpInt % 10;
                    tmpInt /= 10;
                }
                string[index++] = ',';
                list = list->next;
            }
            break;
        case RLE_LIST_ERROR:
            free(string);
            return RLE_LIST_ERROR;
    }

    fprintf(out_stream, "%s", string);
    free(string);
    return RLE_LIST_SUCCESS;
}


RLEListResult asciiArtPrintInverted(RLEList list, FILE *out_stream) {
    if (list == NULL || out_stream == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    while (list != NULL) {
        if (list->c == ' ') {
            list->c = '@';
        }
        list = list->next;
    }

    return asciiArtPrint(list, out_stream);
}