libhdbUtils.so:
	clang -ffast-math -shared -fPIC -std=c++23 hdbUtils.cpp -o libhdbUtils.so

install: libhdbUtils.so
	cp -r ./ /usr/include/hdbUtils/
	cp libhdbUtils.so /usr/lib/

clean:
	rm libhdbUtils.so
