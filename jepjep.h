# include <stdlib.h>
# include<json-c/json.h>
# include <curl/curl.h>
# include<stdio.h> //printf
# include<string.h>    //strlen
# include<sys/socket.h>    //socket
# include<arpa/inet.h> //inet_addr
# include <fcntl.h> // for tcp open
# include <unistd.h> // for tcp close
# define RESET   "\033[0m"
# define BLACK   "\033[30m"      /* Black */
# define RED     "\033[31m"      /* Red */
# define GREEN   "\033[32m"      /* Green */
# define YELLOW  "\033[33m"      /* Yellow */
# define BLUE    "\033[34m"      /* Blue */
# define MAGENTA "\033[35m"      /* Magenta */
# define CYAN    "\033[36m"      /* Cyan */
# define WHITE   "\033[37m"      /* White */
# define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
# define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
# define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
# define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
# define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
# define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
# define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
# define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
struct string
{
   char *ptr;
   size_t len;
};

int checkport(const char* cport,const char* shost,const char* sname);
static long check_url(const char* url);
int http_check(const char* url, const char* resp,const char* sname, const char* action);
int json_get(const char* name, const char* url,const char* key, const char*value);
int execute( const char* cmd);
void init_string(struct string *s);
void print_all(FILE *stream);

