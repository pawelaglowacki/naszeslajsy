__start__: obj ./ant
	./ant

obj:
	mkdir -p obj

ant: obj/main.o obj/uni.o obj/pat.o obj/net.o obj/len.o obj/analyzePath.o obj/any.o
	g++ obj/main.o obj/uni.o obj/pat.o obj/net.o obj/len.o obj/analyzePath.o obj/any.o -o ant

obj/main.o: main.cpp
	g++ -Iinclude -Wall -pedantic -c -o obj/main.o main.cpp

obj/analyzePath.o: src/analyzePath.cpp
	g++ -Iinclude -Wall -pedantic -c -o obj/analyzePath.o src/analyzePath.cpp

obj/uni.o: src/uni.cpp
	g++ -Iinclude -Wall -pedantic -c -o obj/uni.o src/uni.cpp

obj/pat.o: src/pat.cpp
	g++ -Iinclude -Wall -pedantic -c -o obj/pat.o src/pat.cpp

obj/any.o: src/any.cpp
	g++ -Iinclude -Wall -pedantic -c -o obj/any.o src/any.cpp

obj/net.o: src/net.cpp
	g++ -Iinclude -Wall -pedantic -std=c++11	-c -o obj/net.o src/net.cpp

obj/len.o: src/len.cpp
	g++ -Iinclude -Wall -pedantic -c -o obj/len.o src/len.cpp

clean:
	rm obj/*

main.o: main.cpp
	g++ -c main.cpp

