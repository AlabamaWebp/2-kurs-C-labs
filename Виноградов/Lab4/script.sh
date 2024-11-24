g++ -c -Iinclude main.cpp -o main.o
g++ vector.cpp -o lab4 main.o -Llib -lsfml-graphics -lsfml-window -lsfml-system
./lab4