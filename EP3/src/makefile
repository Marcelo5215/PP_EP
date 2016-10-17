CXX = mpicxx
CXXFLAGS = -I$(IDIR) -g
IDIR = ../include
ODIR = ../obj
LIBS = -lpthread -lm

_DEPS = ocean.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = ocean.o main.o
OBJ= $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(LIBS)

testEP3: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~
