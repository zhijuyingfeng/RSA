a.out:main.cpp rsa.o bigint.o oaep.o SHA1.o mpn.o
	g++ -o a.out -O3 rsa.o main.cpp bigint.o oaep.o SHA1.o mpn.o
mpn.o:mpn.cpp
	g++ -O3 -o mpn.o mpn.cpp -c
SHA1.o:SHA1.cpp
	g++ -O3 -o SHA1.o SHA1.cpp -c
bigint.o:bigint.cpp mpn.o
	g++ -O3 -o bigint.o bigint.cpp mpn.o -c
oaep.o:SHA1.o oaep.cpp
	g++ -O3 -o oaep.o SHA1.o oaep.cpp -c
rsa.o:rsa.cpp bigint.o
	g++ -O3 -o rsa.o rsa.cpp bigint.o -c
clean:
	rm rsa.o mpn.o oaep.o  bigint.o SHA1.o
