/**********************************
* timeNet.c
*  (c) 2020 Max Goren MIT Free Software License.
*
* connects to a time server to
* compare to your system time.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy   │LICENSE.mit README      makefile    time2       time2.c
* of this software and associated documentation files (the "Software"), to deal  │[maxs-MacBook-Pro:time_install]% nano time2.c
* in the Software without restriction, including without limitation the rights   │[maxs-MacBook-Pro:time_install]% gcc time2.c -o time2
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      │[maxs-MacBook-Pro:time_install]% ./time2 -v
* copies of the Software, and to permit persons to whom the Software is          │it has been 1591406439 seconds since UNIX time began on January 1st, 1970 @ 
* furnished to do so, subject to the following conditions:                       │7pm.
*                                                                                │That means the time is currently: Friday [09:20] [06/05/2020] EDT
* The above copyright notice and this permission notice shall be included in all │[maxs-MacBook-Pro:time_install]% ./time2
* copies or substantial portions of the Software.                                │Friday [09:20] [06/05/2020] EDT
*                                                                                │[maxs-MacBook-Pro:time_install]% ls
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     │LICENSE.mit README      makefile    time2       time2.c
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       │[maxs-MacBook-Pro:time_install]% cp time2.c ../
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    │[maxs-MacBook-Pro:time_install]% cd ../
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         │[maxs-MacBook-Pro:rakudo]% cp time2.c cont/
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  │[maxs-MacBook-Pro:rakudo]% cd cont/
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  │[maxs-MacBook-Pro:cont]% ls
* SOFTWARE.
***********************************/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int check_rtime(char host[256], char time2check[256], int flag)
{
  char buff[256];
  char timebuff[256];
  int sockfd, port, n;
  struct tm ts;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  port = 13;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    printf("Couldn't open socket");
    exit(0);
  }

  server = gethostbyname(host);
  if (server == NULL)
  {
    printf("There was a problem resolving the host address");
  }
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);
  memcpy(&serv_addr.sin_addr, server->h_addr, server->h_length);
  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
    printf("Connect(): Failed.\n");
    exit(0);
  }
  
  while ((n = read(sockfd, buff, 230)) > 0)
  {
      buff[25] = '\0'; //how you like me now newline
      strptime(buff, "%d %b %Y %H:%M:%S %Z", &ts);
      strftime(timebuff, sizeof(timebuff), "%aday [%I:%M%p] [%m/%d/%Y] %Z", &ts);
      printf("remote: %s\n", timebuff);
      printf("system: %s\n", time2check);
      if (flag == 2)
      {
      	memset(timebuff, 0, sizeof(timebuff));
      	printf("Setting system time from %s ", host);
      	strftime(timebuff, sizeof(timebuff), "%m%d%H%M%Y.%S", &ts);
      	printf("using string %s\n", timebuff);
      	execv("/bin/date", (char *const*)timebuff);
      	printf("Done.\n");
      }
      if (strcmp(timebuff,time2check) == 0)
      {
        return 1; //time matches.
      } else {
        return 0;
      }
  }
  return 0;
}
