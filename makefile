main: main.cpp predictors.hpp tournament.hpp btb.hpp
	g++ -o predictors main.cpp -I predictors.hpp tournament.hpp btb.hpp
clean:
	rm -f predictors
