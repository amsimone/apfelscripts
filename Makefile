CXX = clang++

CXXFLAGS += -O3 -fPIC -std=c++11

# LHAPDF
LHAPDFINCS = $(shell lhapdf-config --cppflags)
LHAPDFLIBS = $(shell lhapdf-config --ldflags)

# APFEL++
APFELPPINCS = $(shell apfelxx-config --cppflags)
APFELPPLIBS = $(shell apfelxx-config --ldflags)

# Now set up the compiler and link flags and libs
CXXFLAGS += $(APFELPPINCS) $(LHAPDFINCS)
LDFLAGS  += $(APFELPPINCS) $(LHAPDFINCS)

CLIBS += $(APFELPPLIBS) $(LHAPDFLIBS)

install : all
all : LHAPDFGrid

LHAPDFGrid: LHAPDFGrid.o
	$(CXX) $(LDFLAGS) -o $@ $< $(CLIBS)

.SUFFIXES : .cc .o .f .c

.cxx.o:	 
	$(CXX) $(CXXFLAGS) -c $< 

.f.o:	 
	$(F77)  -c $< 

clean:
	rm -rf *.lo *.o *.la LHAPDFGrid *~
