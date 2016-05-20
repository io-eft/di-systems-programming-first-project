all: typing-assistant

typing-assistant: typing-assistant.o mytrie.o mytriemylist.o mytriemyleaflist.o leaf.o customlist.o myfunctions.o nameslist.o mytrieuserinput.o
	g++ -g -Wall typing-assistant.o mytrie.o mytriemylist.o mytriemyleaflist.o leaf.o customlist.o myfunctions.o nameslist.o mytrieuserinput.o -o typing-assistant

typing-assistant.o: typing-assistant.cpp
	g++ -c -g3 typing-assistant.cpp

myinode.o: mytrie.cpp
	g++ -c -g3 mytrie.cpp

mytriemylist.o: mytriemylist.cpp
	g++ -c -g3 mytriemylist.cpp

mytriemyleaflist.o: mytriemyleaflist.cpp
	g++ -c -g3 mytriemyleaflist.cpp

leaf.o: leaf.cpp
	g++ -c -g3 leaf.cpp

customlist.o: customlist.cpp
	g++ -c -g3 customlist.cpp

myfunctions.o: myfunctions.cpp
	g++ -c -g3 myfunctions.cpp

nameslist.o: nameslist.cpp
	g++ -c -g3 nameslist.cpp

mytrieuserinput.o: mytrieuserinput.cpp
	g++ -c -g3 mytrieuserinput.cpp

clean:
	rm -rf *.o
