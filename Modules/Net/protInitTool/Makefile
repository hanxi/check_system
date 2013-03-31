protTool : main.o conf.o log.o
	g++ -o protTool main.o conf.o log.o

confpath = ../../Conf
logpath = ../../Log

main.o : main.cpp $(confpath)/conf.h $(logpath)/log.h
	g++ -c main.cpp -I$(confpath) -I$(logpath)
conf.o : $(confpath)/conf.cpp $(confpath)/conf.h $(logpath)/log.h
	g++ -c $(confpath)/conf.cpp -I$(confpath) -I$(logpath)
log.o : $(logpath)/log.cpp $(logpath)/log.h
	g++ -c $(logpath)/log.cpp -I$(logpath)

clean :
	rm *.o
