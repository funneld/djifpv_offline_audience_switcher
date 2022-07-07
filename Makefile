

all: jni/*
	ndk-build	

install: all
	install -d ipk/data/opt/bin/
	install libs/armeabi-v7a/offline_audience_switcher ipk/data/opt/bin/

ipk: all
	$(MAKE) -C ipk clean
	$(MAKE) install
	$(MAKE) -C ipk
	mv ipk/*.ipk ./

clean:
	$(MAKE) -C ipk clean
	rm -f *.ipk
	rm -rf libs
	rm -rf obj
	rm ipk/data/opt/bin/offline_audience_switcher
    