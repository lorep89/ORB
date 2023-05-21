CXX		= g++
CXXFLAGS	= -I./inc -I./Autogen/inc -Wall -pedantic
LDFLAGS		= -L./lib -lCar -lPlane -lORB -Wl,-rpath,./lib

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

all: ns parse orb

parse: $(bindir)/parse

ns: $(bindir)/NameServer

orb: $(libdir)/libORB.so

test: $(serverexe) $(clientexe)

$(clientexe): $(bindir)/$(clientexe)

$(bindir)/$(clientexe): $(testdir)/$(clientexe).cpp | $(bindir)/
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(serverexe): $(bindir)/$(serverexe)
	
$(bindir)/$(serverexe): $(testdir)/$(serverexe).cpp | $(bindir)/
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(bindir)/NameServer: $(NS_OBJS) | $(bindir)/
	$(CXX) $(CXXFLAGS) $(srcdir)/InitNS.cpp	$^ -o $@

$(libdir)/libORB.so: $(ORB_OBJS) | $(libdir)/
	$(CXX) $(CXXFLAGS) -shared -Wl,-soname,libORB.so $^ -o $@

$(bindir)/parse: $(objdir)/utilParse.o $(srcdir)/parse.cpp | $(bindir)/
	$(CXX) $(CXXFLAGS) $^ -o $@

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

$(objdir)/utilParse.o: $(srcdir)/utilParse.cpp | $(objdir)/
	$(CXX) $(CXXFLAGS) -c -fPIC $^	-o $@

$(objdir)/NameServer.o: $(srcdir)/NameServer.cpp | $(objdir)/
	$(CXX) $(CXXFLAGS) -c $^ -o $@

$(objdir)/SkelServer.o: $(srcdir)/SkelServer.cpp | $(objdir)/
	$(CXX) $(CXXFLAGS) -c -fPIC $^ -o $@

$(objdir)/Client.o: $(srcdir)/Client.cpp | $(objdir)/
	$(CXX) $(CXXFLAGS) -c -fPIC $^ -o $@

$(objdir)/ORB.o: $(srcdir)/ORB.cpp | $(objdir)/
	$(CXX) $(CXXFLAGS) -c -fPIC	$^ -o $@

$(objdir)/util.o: $(srcdir)/util.cpp | $(objdir)/
	$(CXX) $(CXXFLAGS) -c -fPIC	$^ -o $@

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
	rm -f $(objdir)/* $(bindir)/* $(libdir)/libORB.so
	
cleanIfaces:
	@sed -i "1,108!d"	./Makefile
	make -C ./Autogen clean
	@sed -i "1,15!d"	./Autogen/Makefile
	
