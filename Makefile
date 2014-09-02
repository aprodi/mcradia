export SOFTDEVDIR=$(CURDIR)

all: mlradia libradia radclient

mlradia:
		cd build/linux_amd64/gcc; $(MAKE) -f Makefile-mlradia -j4
libradia:
		cd build/linux_amd64/gcc; $(MAKE) -f Makefile-libradia libradia -j4

radclient:
		cd build/linux_amd64/gcc; $(MAKE) -f Makefile-libradia radclient

.PHONY: all mlradia libradia radclient
