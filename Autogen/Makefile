CXX			= g++
CXXFLAGS	= -I../inc -I./inc

objdir	=	../obj
libdir	=	../lib
	
clean:
	rm src/* inc/*

$(objdir)/Client.o:
	$(CXX) $(CXXFLAGS) -c -fPIC ../src/Client.cpp -o $@

$(objdir)/util.o:
	$(CXX) $(CXXFLAGS) -c -fPIC ../src/util.cpp -o $@

