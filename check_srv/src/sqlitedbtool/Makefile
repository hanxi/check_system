sqliteDBTool : main.o log.o
	g++ -g -o sqliteDBTool main.o log.o -L$(ligpath) -lsqlite3 -lpthread -ldl

logpath = ../../../Modules/Log
ligpath = ../../../lib

main.o : main.cpp $(logpath)/log.h
	g++ -g -c main.cpp -I$(logpath)
log.o : $(logpath)/log.cpp $(logpath)/log.h
	g++ -g -c $(logpath)/log.cpp -I$(logpath)

clean :
	rm *.o
