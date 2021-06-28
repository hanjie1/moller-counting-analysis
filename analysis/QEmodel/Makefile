PROGRAM = CheckQE
CFLAGS = $(shell $(ROOTSYS)/bin/root-config --cflags)
LIBS   = $(shell $(ROOTSYS)/bin/root-config --libs)
GLIBS  = $(shell $(ROOTSYS)/bin/root-config --glibs)
XEMCDIR = ./

CFLAGS += -Wall -g
INCLUDE := -I${ROOTSYS}/include -I$(XEMCDIR)
RTLIBS := -L${ROOTSYS}/lib -lCore  # /usr/lib/libg2c.so.0 #use /usr/lib64/ for ifarm
SYSLIBS:= -lstdc++ -lgfortran
#RTLIBS := -L${ROOTSYS}/lib -lCore ${x2}/mylib/libg2c.so.0 # /usr/lib/libg2c.so.0 #use /usr/lib64/ for ifarm
#RTLIBS := -L${ROOTSYS}/lib -lCore /usr/lib64/libg2c.so.0 # /usr/lib/libg2c.so.0 #use /usr/lib64/ for ifarm
#RTLIBS := -L${ROOTSYS}/lib -lCore  /usr/lib/libg2c.so.0 #use /usr/lib64/ for ifarm
all: $(PROGRAM)

GFORTRAN := gfortran
#GFORTRAN := f77
#FFLAGS = -C -g -m32 -fbounds-check -finit-local-zero -fno-automatic 
FFLAGS = -C -g -m64 -fbounds-check -finit-local-zero -fno-automatic # use -m64 on ifarm, which is a 64bit system

${XEMCDIR}/F1F221.o: ${XEMCDIR}/F1F221.f
	rm -f $@
	cd ${XEMCDIR} ; $(GFORTRAN) $(FFLAGS) -c F1F221.f;

$(PROGRAM): $(PROGRAM).o $(XEMCDIR)/F1F221.o
	gcc -o $(PROGRAM) $(PROGRAM).o $(CFLAGS) $(LIBS) $(SYSLIBS)  $(RTLIBS) $(XEMCDIR)/F1F221.o 

$(PROGRAM).o: $(PROGRAM).C
	gcc $(CFLAGS) -c -o $(PROGRAM).o $(PROGRAM).C ${INCLUDE}

clean:
	rm -f *.o
