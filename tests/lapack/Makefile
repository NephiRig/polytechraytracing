#LAPACK_PATH = /usr/lib/atlas

#all: testlapack testzlapack test3 testzlapack2
all: testlapack test3 testzlapack2
 	

testlapack: testlapack.cpp
	g++ testlapack.cpp -o testlapack -llapack_atlas -llapack -lblas -latlas -lm -lc

testzlapack: testzlapack.cpp
	g++ testzlapack.cpp -o testzlapack -llapack_atlas -llapack -lblas -latlas -lm -lc

testzlapack2: testzlapack2.cpp
	g++ testzlapack2.cpp -o testzlapack2 -llapack_atlas -llapack -lblas -latlas -lm -lc


# http://rcabreral.blogspot.com/2010/05/complex-matrix-inverse-clapack.html
test3:
	#g++ test3.cpp -o test3 -L$(LAPACK_PATH) -llapack -lblas -lm
	g++ test3.cpp -o test3 -llapack -lblas -lm



clean:
	rm -f testlapack testzlapack testzlapack2 test3

