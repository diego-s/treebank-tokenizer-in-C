all:
	mkdir -p bin libs
	cd src && $(MAKE) all

clean:
	rm -rf bin libs
	cd src && $(MAKE) clean
