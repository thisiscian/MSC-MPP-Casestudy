CC = mpicc
CC_FLAGS = -cc=gcc
SOURCE = main.c edgeview.c pgmio.c reconstruct.c
HEADER = edgeview.h reconstruct.h
EXECUTABLE_FOLDER = ../bin
EXECUTABLE = edgeview

$(EXECUTABLE): $(SOURCE) Makefile $(HEADER)
	$(CC) $(CC_FLAGS) $(SOURCE) -o $(EXECUTABLE_FOLDER)/$@

run: $(EXECUTABLE)
	./$(EXECUTABLE_FOLDER)/$(EXECUTABLE)

clean:
	-@ rm *.o  
	-@ rm $(EXECUTABLE_FOLDER)/$(EXECUTABLE)
