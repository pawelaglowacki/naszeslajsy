__start__: obj ./RSA_Optimization
	./RSA_Optimization

obj:
	mkdir -p obj

clean:
	rm -r obj RSA_Optimization

RSA_Optimization: obj/main.o obj/Network.o obj/NetworkOptimization.o obj/Traffic.o obj/Ant.o
	g++ obj/main.o obj/Ant.o obj/Network.o obj/Traffic.o obj/NetworkOptimization.o -o RSA_Optimization

obj/main.o: main.cpp
	g++ -Iinclude -Wall -pedantic -std=c++11  -c -o obj/main.o main.cpp

obj/Traffic.o: src/Traffic.cpp
	g++ -Iinclude -Wall -pedantic -std=c++11 -c -o obj/Traffic.o src/Traffic.cpp

obj/NetworkOptimization.o: src/NetworkOptimization.cpp
	g++ -Iinclude -Wall -pedantic -std=c++11 -c -o obj/NetworkOptimization.o src/NetworkOptimization.cpp

obj/Network.o: src/Network.cpp
	g++ -Iinclude -Wall -pedantic -std=c++11 -c -o obj/Network.o src/Network.cpp

obj/Ant.o: src/Ant.cpp
	g++ -Iinclude -Wall -pedantic -std=c++11 -c -o obj/Ant.o src/Ant.cpp
