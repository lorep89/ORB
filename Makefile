CXX			= g++
CXXFLAGS	= -I./inc -I./Autogen/inc -Wall -pedantic
LDFLAGS		= -L./lib -lCar -lPlane -lORB

srcdir	=	./src
objdir	=	./obj
bindir  =	./bin
libdir	=	./lib
testdir =	./test

serverexe	= testServer
clientexe	= testClient

ORB_SRCS = util.cpp Client.cpp SkelServer.cpp ORB.cpp
NS_SRCS = util.cpp NameServer.cpp

ORB_OBJS = $(addprefix $(objdir)/,$(patsubst %.cpp,%.o,$(ORB_SRCS)))
NS_OBJS = $(addprefix $(objdir)/,$(patsubst %.cpp,%.o,$(NS_SRCS)))

.PRECIOUS: $(objdir)/ $(objdir)%/ $(bindir)/ $(bindir)%/ $(libdir)/ $(libdir)%/

all: parse ns orb

parse: $(bindir)/parse

ns: $(bindir)/NameServer

orb: $(libdir)/libORB.so

$(clientexe): $(bindir)/$(clientexe)

$(bindir)/$(clientexe):
	$(CXX) $(CXXFLAGS) $(testdir)/$(clientexe).cpp -o $@ $(LDFLAGS)

$(serverexe): $(bindir)/$(serverexe)
	
$(bindir)/$(serverexe):
	$(CXX) $(CXXFLAGS) $(testdir)/$(serverexe).cpp -o $@ $(LDFLAGS)

$(bindir)/NameServer: $(NS_OBJS) | $(bindir)/
	$(CXX) $(CXXFLAGS) $(srcdir)/InitNS.cpp	$^ -o $@

$(libdir)/libORB.so: $(ORB_OBJS) | $(libdir)/
	$(CXX) $(CXXFLAGS) -shared -Wl,-soname,libORB.so $^ -o $@

$(bindir)/parse: $(objdir)/utilParse.o
	$(CXX) $(CXXFLAGS) $(objdir)/utilParse.o $(srcdir)/parse.cpp -o $@

$(objdir)/:
	mkdir -p $@

$(objdir)%/:
	mkdir -p $@

$(bindir)/:
	mkdir -p $@

$(bindir)%/:
	mkdir -p $@

$(libdir)/:
	mkdir -p $@

$(libdir)%/:
	mkdir -p $@

$(objdir)/utilParse.o:
	$(CXX) $(CXXFLAGS) -c -fPIC $(srcdir)/utilParse.cpp	-o $@

$(objdir)/NameServer.o:
	$(CXX) $(CXXFLAGS) -c $(srcdir)/NameServer.cpp -o $@

$(objdir)/SkelServer.o:
	$(CXX)	$(CXXFLAGS)	-c -fPIC $(srcdir)/SkelServer.cpp -o $@

$(objdir)/Client.o:
	$(CXX) $(CXXFLAGS) -c -fPIC $(srcdir)/Client.cpp -o $@

$(objdir)/ORB.o:
	$(CXX) $(CXXFLAGS) -c -fPIC	$(srcdir)/ORB.cpp -o $@

$(objdir)/util.o:
	$(CXX) $(CXXFLAGS) -c -fPIC	$(srcdir)/util.cpp -o $@

cleanNameServer:
	rm -f $(NS_OBJS) $(bindir)/NameServer

cleanServer:	
	rm -f $(bindir)/$(serverexe)

cleanClient:	
	rm -f $(bindir)/$(clientexe)

cleanParse:
	rm -f $(objdir)/utilParse.o $(bindir)/parse

cleanOrb:
	rm -f $(ORB_OBJS) $(libdir)/libORB.so

clean: 
	rm -f $(objdir)/*.o $(bindir)/*
