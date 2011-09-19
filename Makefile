all:
	g++ -o phsp-conf phsp-conf.cpp
	g++ -o phsp phsp.cpp
	g++ -o phsp-conf-gtk phsp-conf-gtk.cpp `pkg-config --cflags --libs gtk+-2.0`
install:
	mkdir ~/.phsp/
	chmod a+rwx ~/.phsp
	mkdir ~/.phsp/profiles
	chmod a+rwx ~/.phsp/profiles
	cp test.phsp ~/.phsp/profiles
	chmod a+rwx ~/.phsp/profiles/test.phsp
	cp phsp-conf phsp /usr/bin
	mkdir /usr/share/phsp
	cp phsp-userset test.phsp /usr/share/phsp
	chmod a+rwx /usr/share/phsp/*
	cp phsp-conf-gtk /usr/bin
userset:
	mkdir ~/.phsp/
	chmod a+rwx ~/.phsp
	mkdir ~/.phsp/profiles
	chmod a+rwx ~/.phsp/profiles
	cp test.phsp ~/.phsp/profiles
	chmod a+rwx ~/.phsp/profiles/test.phsp
