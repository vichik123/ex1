CC = gcc
CFLAGS = -std=c99 -Itool -Wall -pedantic-errors -Werror -DNDEBUG
SRCS = tool/AsciiArtTool.c tool/main.c RLEList.c
OBJS = $(SRCS:.c=.o)

TARGET = AsciiArtTool

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ $(CFLAGS) -o $@


AsciiArtTool.o: tool/AsciiArtTool.c tool/RLEList.h tool/RLEListPlus.h
	$(CC) $(CFLAGS) -c $< -o $@
main.o: tool/main.c AsciiArtTool.h RLEList.h
	$(CC) $(CFLAGS) -c $< -o $@
RLEList.o: RLEList.c tool/RLEList.h tool/RLEListPlus.h
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
