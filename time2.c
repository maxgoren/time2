/***************************************************************************
*    Copyright (c) 2020 Max Goren <maxgoren@icloud.com>
*
*	time2: get system time & date via UNIX Epoch.
*	       check system time & date against remote server.
*	       Set system date & time from remote server.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
***************************************************************************/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int main(int args, char *argv[])
{
	time_t now;
	struct tm ts;
	char tme[80];
	char tme2[80];
	int ret;
	time(&now);
	ts = *localtime(&now);
	strftime(tme2, sizeof(tme2), "%s", &ts);
	strftime(tme, sizeof(tme), "%aday [%I:%M%p] [%m/%d/%Y] %Z", &ts);
	if (args > 1)
	{
	 if (strncmp(argv[1], "-v", sizeof("-v")) == 0)
	 {
	    printf("it has been %s seconds since UNIX time began on January 1st, 1970 @ 7pm.\n", tme2);
	    printf("That means the time is currently: %s\n", tme);
	 } else if (strncmp(argv[1], "-r", sizeof("-r")) == 0) {
	    ret = check_rtime(argv[2], tme, 1);
	    if (ret == 1)
	    {
	       printf("Your system time is calibrated.\n");
	    } else if (ret == 0) {
	      printf("local and remote time are not in sync.\n");
	    }
	 } else if (strncmp(argv[1], "-sr", sizeof("-sr")) == 0) {
	    ret = check_rtime(argv[2], tme, 2);
	 }
	} else {
	  printf("%s\n", tme);
	}
	return 0;
}
