################################################################################
#
# to build and install
#
#
################################################################################

TARGET = read_others friend_secret

all: $(TARGET)

install: $(TARGET)
	cp $^ /tmp
	chmod 04755 /tmp/read_others
	chmod 04755 /tmp/friend_secret
read_others: read_others.cpp
	g++ -o $@ $^
friend_secret:friend_secret.c
	g++ -o $@ $^


clean:
	rm -f $(TARGET)

















