#generates time from the time in seconds since the start of UNIX time.
# (c) Max Goren 2020 MIT License

all: about time done
 
time:
	@echo
	@echo
	@echo "Compiling:   gcc time2.c -o time2" 
	@gcc -Wno-implicit time2.c timeNetExt.c -o time2

about:
	@echo "obtains the time from the elapsed time in seconds since the start of UNIX time."
	@echo "use time2 -v for a more wordsome explaination"
	@echo "use time2 -r <remote server> to compare against remote"
	@echo "use time2 -sr <remote server> to set local date & time from remote"
done:
	@echo "All done: use make install for syste wide use or ./time2"

install:
	@cp time2 /usr/local/bin/
	echo "Done.";
