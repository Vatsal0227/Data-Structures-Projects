# Define the machine object files for your program
OBJECTS = npu824Project0.o
# Define your include file
INCLUDES = Project0.h

# make for the executable
project0: ${OBJECTS}
	gcc -g -o project0 ${OBJECTS}

# Simple suffix rules for the .o
%.o: %.c ${INCLUDES}
	gcc -g -c $<

# Clean the .o files
clean:
	rm -f ${OBJECTS}
