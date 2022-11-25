CC= gcc
ASCII_ART_TOOL = tool/AsciiArtTool
RLEList=/home/mtm/public/2223a/ex1/RLEList
MAIN = tool/main
OBJS= RLEList.o $(ASCII_ART_TOOL).o $(MAIN).o
EXEC= AsciiArtTool
DEBUG_FLAG= -g
CFLAG = -std=c99 -Wall -Werror -I/home/mtm/public/2223a/ex1 -Itool
$(EXEC):$(OBJS)
	$(CC) $(CFLAG) $(OBJS) -o $@
$(MAIN).o: $(MAIN).c $(ASCII_ART_TOOL).c $(ASCII_ART_TOOL).h $(RLEList).h RLEList.c
	$(CC) -c $(CFLAG) $(DEBUG_FLAG) $*.c -o $*.o
$(ASCII_ART_TOOL).o: $(ASCII_ART_TOOL).c $(ASCII_ART_TOOL).h RLEList.c $(RLEList).h
	$(CC) -c $(CFLAG) $(DEBUG_FLAG) $*.c -o $*.o
RLEList.o: RLEList.c $(RLEList).h
	$(CC) -c $(CFLAG) $(DEBUG_FLAG) $*.c
clean:
	rm -f $(EXEC) $(OBJS)
