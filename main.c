#include <stdio.h>
#include "AsciiArtTool.h"
#include <stdbool.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Invalid arguments!");
        return 0;
    }

    char* flag = argv[0];
    char* source_path = argv[1];
    char* destination_path = argv[2];

    FILE* source_file = fopen(source_path, "r");
    if (source_file == NULL) {
        printf("Couldn't open source file %s", source_path);
        return 0;
    }
    FILE* destination_file = fopen(destination_path, "w");
    if (destination_file == NULL) {
        printf("Couldn't open destination file %s", destination_path);
        return 0;
    }

    RLEList source = asciiArtRead(source_file);

    if (flag[0] == '-' && flag[1] == 'e') {
        asciiArtPrintEncoded(source, destination_file);
    } else if (flag[0] == '-' && flag[1] == 'i') {
        asciiArtPrintInverted(source, destination_file);
    } else {
        printf("Invalid flag!");
        return 0;
    }

    fclose(source_file);
    fclose(destination_file);
}