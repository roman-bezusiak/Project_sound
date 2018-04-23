OBJ = main.o sound.o screen.o comm.o
APPNAME = sound.a

# Link rule
$(APPNAME) : $(OBJ)
	gcc -o $(APPNAME) $(OBJ) -lm -lcurl

# Compiling rule
%.o : %.c
	gcc -c -o $@ $<

# Cleaning rule
clean : 
	rm $(OBJ) $(APPNAME)

# Git adding rule
add :
	git add *.c *.h *.md *.php *.html *.js makefile	

# Git committing & pushing rule
git : 
	git commit -a --allow-empty-message -m ''
	git push origin master
	
