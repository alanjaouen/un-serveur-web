#include "status.h"

void status_msg(int fd, int status, size_t len)
{
  char *str_status = malloc(sizeof(char) * 3);

  char *title = status_title(status);

  sprintf(str_status, "%d", status);

  send(fd, "HTTP/1.1 ", 9, 0);
  send(fd, str_status, 3, 0);
  send(fd, title, strlen(title), 0);

  print_time(fd);

  if (status == 200)
  {
    send(fd, "Content-Length: ", 16, 0);
    char *slen = malloc(sizeof (char) * 1024);
    sprintf(slen, "%zu\r\n", len);
    send(fd, slen, strlen(slen), 0);
    free(slen);
  }

  send(fd, "\r\n", 2, 0);

  free(str_status);
}

char *status_title(int status)
{
  if (status == 200)
    return " OK\r\n";
  if (status == 403)
    return " Forbidden\r\n";
  if (status == 404)
    return " Not Found\r\n";
  if (status == 505)
    return " HTTP Version Not Supported\r\n";
  return NULL;
}

void print_time(int fd)
{
  time_t cur_time;
  struct tm *info;
  time(&cur_time);
  info = gmtime(&cur_time);

  char *s = malloc(sizeof (char) * 39);
  strftime(s, 38, "Date: %a, %d %b %Y %R:%S GMT\r\n", info);
  send(fd, s, 38, 0);

  free(s);
}
