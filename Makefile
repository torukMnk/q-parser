OBJETS=src/qparser.o \
				libs/qcore.o \
				libs/assignation.o \
				libs/operation.o \
				libs/qmake.o

CXXFLAGS=-Ilibs

qparser: $(OBJETS)
				g++ $(OBJETS) -o qparser

libs/qcore.o: libs/qcore.cpp
libs/assignation.o: libs/assignation.cpp
libs/operation.o: libs/operation.cpp
libs/qmake.o: libs/qmake.cpp
src/qparser.o: src/qparser.cpp

clean:
				rm $(OBJETS)
				rm qparser
