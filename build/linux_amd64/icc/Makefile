################################################################################
#
#  MCRADIA
#
# Makefile for RADIA4.3, simply type make on OSX, AIX, IRIX, OSF1, HP-UX, SunOS 
# or Linux to build the programme. Type make gulp_debug to build programme with 
# debugging on, type make clean to remove all objects or make clean_debug to 
# remove all objects from version with debug information. Type make tar to 
# create gzipped tar file of source code, documentation and examples. Type make 
# html to convert help.txt to help.html.
#
# Original makefile by O. Chubar, adapted for MCRADIA by AP
#
# Portions of this makefile require the use of GNU make.
# see http://www.gnu.org/software/make for more information.
#
################################################################################

SYS=		Linux-x86-64

# Variables relating to Mathematica local installation
MATHVERSION=	9.0
MLORIGDIR=	/usr/local/Wolfram/Mathematica/${MATHVERSION}/SystemFiles/Links/MathLink/DeveloperKit/${SYS}/CompilerAdditions
MLINCLUDEDIR=	$(MLORIGDIR)
MLINCLUDE=	-I$(MLINCLUDEDIR)
MLLIBDIR=	$(MLORIGDIR)
MLMPREP=	/usr/local/Wolfram/Mathematica/9.0/SystemFiles/Links/MathLink/DeveloperKit/Linux-x86-64/CompilerAdditions/mprep

# McRadia local installation
SOFTDEVDIR=	/home/andrea/tmp/mcradia
RADSRCDIR=	$(SOFTDEVDIR)/src
RADSRCGENDIR=	$(RADSRCDIR)/general
RADSRCTRIDIR=	$(RADSRCDIR)/triangle
RADSRCMLDIR=	$(RADSRCDIR)/mathlink
RADSRCDLLDIR=	$(RADSRCDIR)/dll
SHDIR=		$(SOFTDEVDIR)/shared
SHSRCDIR=	$(SHDIR)/src
SHSRCGMDIR=	$(SHSRCDIR)/genmath
SHSRCPARSEDIR=	$(SHSRCDIR)/auxparse
SHLIBDIR=	$(SHDIR)/lib
SHINCLUDE=	-I$(SHSRCGMDIR) -I$(SHSRCPARSEDIR)

RADBUILDIR=	$(SOFTDEVDIR)/build/linux_amd64/gcc


CC = /usr/bin/gcc
#CC = /usr/bin/icc
CXX = /usr/bin/g++
#CXX = /usr/bin/icc

AR = ar
RM = rm

RADSRCDEF=	-D__GCC__ -DFFTW_ENABLE_FLOAT -DNO_TIMER -DANSI_DECLARATORS -DTRILIBRARY -DLINUX

CFLAGS=		-O3 -fPIC -march=corei7-avx -mtune=corei7

LIB=		-L$(MLLIBDIR) -lML64i3 -L$(SHLIBDIR) -lfftw -lm -lpthread -lrt

OBJS= 	radapl1.o radapl2.o radapl3.o radapl4.o radapl5.o radapl6.o radapl7.o radarccu.o radcast.o radentry.o radexpgn.o radflm.o radg3d.o radg3dgr.o radgroup.o radinter.o radintrc.o radiobuf.o radmamet.o radmater.o radplnr1.o radplnr2.o radptrj.o radrec.o radrlmet.o radsbdac.o radsbdep.o radsbdrc.o radsbdvp.o radsend.o radvlpgn.o gmtrans.o gmfft.o triangle.o auxparse.o 

RADIALIB=	libradia.a
RADCLIENT=	radclient.exe
BINARIES =  libradia radclient

all : $(BINARIES)

libradia:	$(OBJS) 
		$(AR) rcs $(RADIALIB) $(OBJS) 

radapl1.o:	$(RADSRCGENDIR)/radapl1.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radapl1.cpp -O3 $(RADSRCDEF) $(MLINCLUDE) $(SHINCLUDE)

radapl2.o:	$(RADSRCGENDIR)/radapl2.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radapl2.cpp -O3 $(RADSRCDEF) $(MLINCLUDE) $(SHINCLUDE)

radapl3.o:	$(RADSRCGENDIR)/radapl3.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radapl3.cpp -O3 $(RADSRCDEF) $(MLINCLUDE) $(SHINCLUDE)

radapl4.o:	$(RADSRCGENDIR)/radapl4.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radapl4.cpp -O3 $(RADSRCDEF) $(MLINCLUDE) $(SHINCLUDE)
 
radapl5.o:	$(RADSRCGENDIR)/radapl5.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radapl5.cpp -O3 $(RADSRCDEF) $(MLINCLUDE) $(SHINCLUDE)

radapl6.o:	$(RADSRCGENDIR)/radapl6.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radapl6.cpp -O3 $(RADSRCDEF) $(MLINCLUDE) $(SHINCLUDE)

radapl7.o:	$(RADSRCGENDIR)/radapl7.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radapl7.cpp -O3 $(RADSRCDEF) $(MLINCLUDE) $(SHINCLUDE) -I$(RADSRCTRIDIR)

radarccu.o:	$(RADSRCGENDIR)/radarccu.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radarccu.cpp -O3 $(RADSRCDEF) $(MLINCLUDE) $(SHINCLUDE)

radcast.o:	$(RADSRCGENDIR)/radcast.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radcast.cpp -O3 $(RADSRCDEF) $(SHINCLUDE)

radexpgn.o:	$(RADSRCGENDIR)/radexpgn.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radexpgn.cpp -O3 $(RADSRCDEF) $(MLINCLUDE) $(SHINCLUDE)

radflm.o:	$(RADSRCGENDIR)/radflm.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radflm.cpp -O3 $(RADSRCDEF) $(MLINCLUDE) $(SHINCLUDE)

radg3d.o:	$(RADSRCGENDIR)/radg3d.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radg3d.cpp -O3 $(RADSRCDEF) $(MLINCLUDE) $(SHINCLUDE)

radg3dgr.o:	$(RADSRCGENDIR)/radg3dgr.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radg3dgr.cpp -O3 $(RADSRCDEF) $(MLINCLUDE) $(SHINCLUDE)

radgroup.o:	$(RADSRCGENDIR)/radgroup.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radgroup.cpp -O3 $(RADSRCDEF) $(MLINCLUDE) $(SHINCLUDE)

radinter.o:	$(RADSRCGENDIR)/radinter.cpp 
		cc $(CFLAGS) -c $(RADSRCGENDIR)/radinter.cpp -O3 $(RADSRCDEF) $(MLINCLUDE) $(SHINCLUDE)	 

radintrc.o:	$(RADSRCGENDIR)/radintrc.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radintrc.cpp -O3 $(RADSRCDEF) $(SHINCLUDE)

radiobuf.o:	$(RADSRCGENDIR)/radiobuf.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radiobuf.cpp -O3 $(RADSRCDEF)

radmamet.o:	$(RADSRCGENDIR)/radmamet.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radmamet.cpp -O3 $(RADSRCDEF) $(SHINCLUDE)

radmater.o:	$(RADSRCGENDIR)/radmater.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radmater.cpp -O3 $(RADSRCDEF) $(SHINCLUDE)

radplnr1.o:	$(RADSRCGENDIR)/radplnr1.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radplnr1.cpp -O3 $(RADSRCDEF) $(MLINCLUDE) $(SHINCLUDE)

radplnr2.o:	$(RADSRCGENDIR)/radplnr2.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radplnr2.cpp -O3 $(RADSRCDEF) $(MLINCLUDE) $(SHINCLUDE)

radptrj.o:	$(RADSRCGENDIR)/radptrj.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radptrj.cpp -O3 $(RADSRCDEF) $(SHINCLUDE)

radrec.o:	$(RADSRCGENDIR)/radrec.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radrec.cpp -O3 $(RADSRCDEF) $(MLINCLUDE) $(SHINCLUDE)

radrlmet.o:	$(RADSRCGENDIR)/radrlmet.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radrlmet.cpp -O3 $(RADSRCDEF) $(MLINCLUDE) $(SHINCLUDE)

radsbdac.o:	$(RADSRCGENDIR)/radsbdac.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radsbdac.cpp -O3 $(RADSRCDEF) $(MLINCLUDE) $(SHINCLUDE)

radsbdep.o:	$(RADSRCGENDIR)/radsbdep.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radsbdep.cpp -O3 $(RADSRCDEF) $(MLINCLUDE) $(SHINCLUDE)

radsbdrc.o:	$(RADSRCGENDIR)/radsbdrc.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radsbdrc.cpp -O3 $(RADSRCDEF) $(MLINCLUDE) $(SHINCLUDE)

radsbdvp.o:	$(RADSRCGENDIR)/radsbdvp.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radsbdvp.cpp -O3 $(RADSRCDEF) $(MLINCLUDE) $(SHINCLUDE)

radsend.o:	$(RADSRCGENDIR)/radsend.cpp 
		cc $(CFLAGS) -c $(RADSRCGENDIR)/radsend.cpp -O3 $(RADSRCDEF) $(MLINCLUDE) $(SHINCLUDE)

radvlpgn.o:	$(RADSRCGENDIR)/radvlpgn.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCGENDIR)/radvlpgn.cpp -O3 $(RADSRCDEF) $(MLINCLUDE) $(SHINCLUDE)

triangle.o:	$(RADSRCTRIDIR)/triangle.c 
		$(CC) $(CFLAGS) -c $(RADSRCTRIDIR)/triangle.c -O $(RADSRCDEF) -I$(RADSRCTRIDIR)

gmtrans.o:	$(SHSRCGMDIR)/gmtrans.cpp 
		$(CC) $(CFLAGS) -c $(SHSRCGMDIR)/gmtrans.cpp -O3 $(RADSRCDEF)

gmfft.o:	$(SHSRCGMDIR)/gmfft.cpp 
		$(CC) $(CFLAGS) -c $(SHSRCGMDIR)/gmfft.cpp -O3 $(RADSRCDEF) 

auxparse.o:	$(SHSRCPARSEDIR)/auxparse.cpp 
		$(CC) $(CFLAGS) -c $(SHSRCPARSEDIR)/auxparse.cpp -O3 $(RADSRCDEF) 

radentry.o:	$(RADSRCDLLDIR)/radentry.cpp 
		$(CC) $(CFLAGS) -c $(RADSRCDLLDIR)/radentry.cpp -O3 $(RADSRCDEF) $(SHINCLUDE) -I$(RADSRCGENDIR)

radclient: 	$(RADBUILDIR)/radclient.cpp
		$(CXX) $(CFLAGS) -I$(RADBUILDIR) -o $(RADCLIENT) $(RADBUILDIR)/radclient.cpp libradia.a $(LIB) $(LIB)   

clean:
		@ $(RM) -rf $(OBJS) 
clobber:
		@ $(RM) -rf $(OBJS) $(RADIALIB)
