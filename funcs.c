#include "jepjep.h"

void init_string(struct string *s)
{
   s->len = 0;
   s->ptr = malloc(s->len+1);
   if (s->ptr == NULL)
     {
	fprintf(stderr, "malloc() failed\n");
	exit(EXIT_FAILURE);
  }
   s->ptr[0] = '\0';
}

void init_string(struct string *s);

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
{
   size_t new_len = s->len + size*nmemb;
   s->ptr = realloc(s->ptr, new_len+1);
   if (s->ptr == NULL)
     {
	fprintf(stderr, "realloc() failed\n");
	exit(EXIT_FAILURE);
  }
   memcpy(s->ptr+s->len, ptr, size*nmemb);
   s->ptr[new_len] = '\0';
   s->len = new_len;

   return size*nmemb;
}
void print_all(FILE *stream)
{
   int c;
   while ((c = getc(stream)) != EOF)
     putchar(c);
}

int http_check(const char* url, const char* resp,const char* sname, const char* action)
{

   long http_code =0;
   long val = 0;
   val = atol(resp);
   http_code = check_url(url);
   //   printf("DEBUG val=%ld  http_code=%ld", val,http_code);
   if((int)val == (int)http_code)
     {
	printf("%s\t\t%s%ld%s\n",sname,GREEN,http_code,RESET);
}
   else
     {

	printf("%s\t\t%s%ld%s\n",sname,RED,http_code,RESET);
	printf("%s%s failed execute %s%s",YELLOW,sname,action,RESET);
	execute (action);
     }
   return 1;
}

long check_url(const char* url)
{

   CURL *curl = curl_easy_init();
   long response_code=0;
   if(curl)
     {
	CURLcode res;
	curl_easy_setopt(curl, CURLOPT_URL, url);
	//no output
	curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
	res = curl_easy_perform(curl);
	if(res == CURLE_OK)
	  {

	     curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

	     curl_easy_cleanup(curl);
}
}
   return response_code;

}

int json_get(const char* name, const char* url,const char* key, const char*value)
{
   CURL *curl;
   CURLcode res;
   struct json_object *parsed_json;
   struct json_object *system;

   curl = curl_easy_init();
   if(curl)
     {
	struct string s;
	init_string(&s);

	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
	res = curl_easy_perform(curl);
	parsed_json = json_tokener_parse(s.ptr);
	json_object_object_get_ex(parsed_json, key, &system);
	printf("json value is %s \n",json_object_get_string(system));
	free(s.ptr);

	curl_easy_cleanup(curl);
  }

   return 1;
}

int execute(const char* cmd)
{

   FILE *stream;

   if ((stream = popen(cmd, "r")) == NULL)
     return 1;

   print_all(stream);
   pclose(stream);
   return 0;

   return 1;
}

int checkport(const char* cport,const char* shost, const char* cname)
{
   int sock;
   int sport=0;
   sport=atoi(cport);
   struct sockaddr_in server;

   sock = socket(AF_INET , SOCK_STREAM , 0);
   if (sock == -1)
     {
        printf("Could not create socket to port %d",sport);
    }

   server.sin_addr.s_addr = inet_addr(shost);
   server.sin_family = AF_INET;
   server.sin_port = htons(sport);

   if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
     {
        perror("connect failed. Error");
	printf("port %s host %s failed",cport,shost);
        return 1;
    }

   printf("%s %s %s %s\t\tconnected%s\n",cname, shost,cport,GREEN,RESET);

   close(sock);
   return 0;
}
