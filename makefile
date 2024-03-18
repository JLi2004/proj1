main: main.cpp predictors.h tournament.h btb.h
	g++ -o predictors main.cpp -I predictors.h tournament.h btb.h
clean:
	rm -f predictors
