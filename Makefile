all:
	mkdir -p bin
	cd src && $(MAKE) all

clean:
	rm -f bin/tokenize
	rmdir bin/ || true
	cd src && $(MAKE) clean
