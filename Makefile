all: mlradia libradia radclient

mlradia:
		cd build/linux_amd64/gcc; make -f Makefile-mlradia -j8
libradia:
		cd build/linux_amd64/gcc; make -f Makefile-libradia libradia -j8

radclient:
		cd build/linux_amd64/gcc; make -f Makefile-libradia radclient

.PHONY: all mlradia libradia radclient