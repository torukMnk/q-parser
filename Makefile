OBJETS=src/qparser.o libs/libqparser.o
CXXFLAGS=-Ilibs

qparser: $(OBJETS)
				g++ $(OBJETS) -o qparser

libs/libqparser.o: libs/libqparser.cpp

src/qparser.o: src/qparser.cpp libs/libqparser.h

clean:
				rm $(OBJETS)
				rm qparser
