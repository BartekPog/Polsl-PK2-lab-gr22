
 
kompilator=gcc
standard=-std=c11
optymalizacja=-O3
errors=-pedantic-errors
profilowanie=-pg

.PHONY: clean

__ : main
	./main   
	            
	            
main : main.o libs/stmr.o document.o textManip.o
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -o $@ $^ 		            
	            
main.o : main.c
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^ 

structures.o : document.c
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^ 

textManip.o : textManip.c
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^ 


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

