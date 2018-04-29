# Defining object files
OBJ = main.o comm.o screen.o sound.o

# Defining dependencies
DEPS = comm.h screen.h sound.h

# Defining the application 
APPNAME = sound.a

# Link rule
$(APPNAME) : $(OBJ)
	gcc -o $(APPNAME) $(OBJ) -lm -lcurl

# Compiling rule
%.o : %.c $(DEPS)
	gcc -c -o $@ $<

# Cleaning rule
clean : 
	rm $(OBJ) $(APPNAME)