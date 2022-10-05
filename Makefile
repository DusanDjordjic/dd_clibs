LIBDIR=lib
LIBINC=lib/include

.PHONY : libs libvector libio clean

libs: $(LIBDIR) $(LIBINC) libvector libio


libvector: 
	cd vector && $(MAKE) MAKEFLAGS=lib 

libio: 
	cd io && $(MAKE) MAKEFLAGS=lib 

$(LIBDIR):
	mkdir $@

$(LIBINC):
	mkdir $@

clean:
	rm -rf $(LIBDIR) **/*.o
