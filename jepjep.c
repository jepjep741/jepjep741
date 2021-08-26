#include "jepjep.h"

int main(int argc, char **argv)
{
   FILE *fp;
   char buffer[1024];
   struct json_object *parsed_json;
   struct json_object *system;
   struct json_object *services;
   struct json_object *services3;
   struct json_object *service_url;
   struct json_object *service_name;
   struct json_object *service_port;
   struct json_object *service_host;
   struct json_object *service_tcp_name;
   struct json_object *service_healthy_response;
   struct json_object *service_action;
   struct json_object *service_json_name;
   struct json_object *service_json_url;
   struct json_object *service_json_key;
   struct json_object *service_json_value;
   struct json_object *service_type;
   size_t n_services;
   //Wrapper to dericated  nested
   json_object * json_object_object_get_nested(json_object * obj, const char * name)
     {
	json_object * sub;
	return json_object_object_get_ex(obj, name, & sub) ? sub : NULL;
}

   size_t i;
   fp = fopen("jepjep.json","r");
   fread(buffer, 1024, 1, fp);
   fclose(fp);
   parsed_json = json_tokener_parse(buffer);
   json_object_object_get_ex(parsed_json, "system", &system);
   json_object_object_get_ex(parsed_json, "services", &services);
   n_services = json_object_array_length(services);
   printf(" \033[2J");
   printf("%s has %lu services \n\n",json_object_get_string(system),n_services);
   // http, tcp allowed TODO own funcs
   // json reguired option checking missing TODO
   for(i=0;i<n_services;i++)

     {
	services3 = json_object_array_get_idx(services, i);
	service_type=json_object_object_get_nested(services3,"type");

	if(!strcmp(json_object_get_string(service_type),"http"))
	  {

	     service_url = json_object_object_get_nested(services3, "url");

	     service_name = json_object_object_get_nested(services3, "name");
	     service_healthy_response= json_object_object_get_nested(services3, "healthy_response");
	     //if execute args is set then run the action
	     	service_action = json_object_object_get_nested(services3, "exec");
	     http_check(json_object_get_string(service_url),json_object_get_string(service_healthy_response),json_object_get_string(service_name),json_object_get_string(service_action));
	  }
	else if(!strcmp(json_object_get_string(service_type),"tcp"))
{
   service_port =json_object_object_get_nested(services3, "port");
   service_host = json_object_object_get_nested(services3, "host");
   service_tcp_name = json_object_object_get_nested(services3, "name");
   checkport(json_object_get_string(service_port),json_object_get_string(service_host),json_object_get_string(service_tcp_name));

}
	else if(!strcmp(json_object_get_string(service_type),"json"))
{

     	     service_json_name = json_object_object_get_nested(services3, "name");
	     service_json_url = json_object_object_get_nested(services3, "url");
	     service_json_key = json_object_object_get_nested(services3, "key");
	     service_json_value = json_object_object_get_nested(services3, "value");
json_get(json_object_get_string(service_json_name),json_object_get_string(service_json_url),json_object_get_string(service_json_key),json_object_get_string(service_json_value));
	
}
     }
   //end of services for
   return 0;

}


