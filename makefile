OBJ = main.o sound.o screen.o
APPNAME = sound.a

#link rule
$(APPNAME) : $(OBJ)
	gcc -o $(APPNAME) $(OBJ) -lm

#compiling rule
%.o : %.c
	gcc -c -o $@ $<

clean : 
	rm $(OBJ) $(APPNAME)

tar :
	tar cf project.tar *

backup :
	scp project.tar e1700684@shell.puv.fi:.

add :
	git add *.c *.h *.txt *.wav makefile	

git : 
	git commit -a --allow-empty-message -m ''
	git push origin master
	
