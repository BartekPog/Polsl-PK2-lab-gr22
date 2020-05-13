kompilator=gcc
standard=-std=gnu11 # -std=c11
optymalizacja=-O3
errors=-pedantic-errors
profilowanie=-pg

.PHONY: clean

__ : main
	./main   
	            
	            
main : main.o states.o circular_buffer.o utils.o output.o
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -o $@ $^ 	-lm            
	            
main.o : main.c
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^ -lm   

circular_buffer.o : circular_buffer.c
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^ -lm   
 
states.o : states.c
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^ -lm 
 
utils.o : utils.c
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^ -lm   

output.o : output.c
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^ -lm 


# libs/stmr.o : 
# 	echo "cool"
	# $(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^

profil : main.c
	if [ -f main ]; then rm main ; fi ;
	$(kompilator) $(standard)  $(profilowanie) -o main main.c
	# 
	./main
	gprof main > profil.txt
	
	
clean : 	
	for f in `ls *.o` ; do  if [ -f $$f ] ; then rm $$f  ; fi;   done;
	if [ -f main ] ; then rm main ; fi ;
