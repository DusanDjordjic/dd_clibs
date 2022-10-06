LIBDIR=lib
LIBINC=lib/include

.PHONY : libs libvector libio clean

libs: clean
libs: $(LIBDIR) $(LIBINC) libvector libio


libvector: $(LIBDIR) $(LIBINC)
	$(MAKE) -C vector lib 

libio: $(LIBDIR) $(LIBINC)
	$(MAKE) -C io lib 

$(LIBDIR):
	mkdir $@

$(LIBINC):
	mkdir $@

clean:
	rm -rf $(LIBDIR);\
	$(MAKE) -C io clean;\
	$(MAKE) -C vector clean
