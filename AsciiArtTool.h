
#ifndef RLELIST_H
#define RLELIST_H
#include "RLEList.h"
#endif



/*
 * This function open a file that includes Ascii Art
 * and return an RLEList that represents it.
 */
RLEList asciiArtRead(FILE* in_stream);

/*
 * This function writes the RLEList
 * into the given file.
 */
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);

/*
 * This function writes to the out_stream file the RLEList
 * that's encoded by the RLEListExportToString function.
 */
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);

/*
 * This function writes to the out_stream file,
 * changing all the spaces from the list file to a '@' character.
 */
RLEListResult asciiArtPrintInverted(RLEList list, FILE *out_stream);

/*
 * This function calculates the length of an RLEList as a string
 */
int encodedListLength(RLEList list);