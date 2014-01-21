.PHONY: python clean

python: mcradialpy.so

mcradialpy.so:
	python setup.py build_ext --build-lib='../gcc'
#	cp ../gcc/mcradialpy.so ../../../bin/mcradia_python/
	rm -rf build

clean:
	rm -rf build
	rm -f ../gcc/mcradialpy.so