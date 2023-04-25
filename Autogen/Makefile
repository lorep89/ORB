CXX			= g++
CXXFLAGS	= -I../inc -I./inc

objdir	=	../obj
libdir	=	../lib
libObjs =
	
clean:
	rm -f src/* inc/* $(libObjs)

$(objdir)/Client.o:
	$(CXX) $(CXXFLAGS) -c -fPIC ../src/Client.cpp -o $@

$(objdir)/util.o:
	$(CXX) $(CXXFLAGS) -c -fPIC ../src/util.cpp -o $@

