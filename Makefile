#compile and link the application
all: main

#run the application
run: main
	./main

#link main.o and student.o to executable main
main: main.o student.o database.o 
	g++ -g -o main main.o student.o database.o

#compile the main.cpp to main.o
main.o: main.cpp
	g++ -g -c main.cpp -std=c++11

#compile the student.cpp to student.o
student.o: student.cpp
	g++ -g -c student.cpp -std=c++11

#compile the database.cpp to student.o
database.o: database.cpp
	g++ -g -c database.cpp -std=c++11

#remove built files
clean:
	rm -rf main main.o student.o database.o *~
