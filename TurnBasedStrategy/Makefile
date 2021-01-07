#CC - компилятор
CC=c++
# CFLAG - флаги компиляции
#CFLAG=-lX11 -lpthread -c -Wall
CFLAG=-c -Wall

all: TBS

TBS: TurnBasedStrategy.o Engine.o TbsInterface.o Map.o
	$(CC) TurnBasedStrategy.o Engine.o TbsInterface.o Map.o -o TBS

TurnBasedStrategy.o: TurnBasedStrategy.cpp
	$(CC) $(CFLAG) TurnBasedStrategy.cpp

Engine.o: Engine.cpp
	$(CC) $(CFLAG) Engine.cpp

TbsInterface.o: TbsInterface.cpp
	$(CC) $(CFLAG) TbsInterface.cpp

Map.o: Map.cpp
	$(CC) $(CFLAG) Map.cpp

clean:
	rm -rf *.o TBS
