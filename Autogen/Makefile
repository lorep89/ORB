CXX			= g++
CXXFLAGS	= -I../inc -I./inc

objdir	=	../obj
libdir	=	../lib
	
clean:
	rm -f src/* inc/*

$(objdir)/Client.o:
	$(CXX) $(CXXFLAGS) -c -fPIC ../src/Client.cpp -o $@

$(objdir)/util.o:
	$(CXX) $(CXXFLAGS) -c -fPIC ../src/util.cpp -o $@

CarObjs = $(addprefix $(objdir)/,util.o Client.o CarProxy.o CarSkel.o Carservice.o)

Car: $(libdir)/libCar.so

$(libdir)/libCar.so: $(CarObjs)
	$(CXX) $(CXXFLAGS) -shared -Wl,-soname,libCar.so $^ -o $@

$(objdir)/CarSkel.o:
	$(CXX) $(CXXFLAGS) -c -fPIC ./src/CarSkel.cpp -o $@

$(objdir)/CarProxy.o:
	$(CXX) $(CXXFLAGS) -c -fPIC ./src/CarProxy.cpp -o $@

$(objdir)/Carservice.o:
	$(CXX) $(CXXFLAGS) -c -fPIC ./imp/Carservice.cpp -o $@

cleanCar:
	rm -f $(objdir)/CarProxy.o $(objdir)/CarSkel.o $(objdir)/Carservice.o $(libdir)/libCar.so


PlaneObjs = $(addprefix $(objdir)/,util.o Client.o PlaneProxy.o PlaneSkel.o Planeservice.o)

Plane: $(libdir)/libPlane.so

$(libdir)/libPlane.so: $(PlaneObjs)
	$(CXX) $(CXXFLAGS) -shared -Wl,-soname,libPlane.so $^ -o $@

$(objdir)/PlaneSkel.o:
	$(CXX) $(CXXFLAGS) -c -fPIC ./src/PlaneSkel.cpp -o $@

$(objdir)/PlaneProxy.o:
	$(CXX) $(CXXFLAGS) -c -fPIC ./src/PlaneProxy.cpp -o $@

$(objdir)/Planeservice.o:
	$(CXX) $(CXXFLAGS) -c -fPIC ./imp/Planeservice.cpp -o $@

cleanPlane:
	rm -f $(objdir)/PlaneProxy.o $(objdir)/PlaneSkel.o $(objdir)/Planeservice.o $(libdir)/libPlane.so

