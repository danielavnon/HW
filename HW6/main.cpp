#include "port.h"
#include "string.h"
#include "field.h"
#include "ip.h"
#include <iostream>
#include <cstring>



#define ERROR -1
#define FILTER_NUM 2
#define DELIM "="
#define SOURCE_IP "src-ip"
#define SOURCE_PORT "src-port"
#define DEST_IP "dst-ip"
#define DEST_PORT "dst-port"


extern int check_args(int, char**);
extern void parse_input(Field&);
/**
 * @brief main method of rule initialisation, value setting and parsing
 * @param argc used to check the input arguments
 * @param argv a pointer to a string which consists of the input
 * @return ERROR is all cases of an error, else 0
 * @note
 */




int main(int argc,char** argv){


	if(check_args(argc,argv)){
		return ERROR;
	}
	
	String argument(argv[1]);
	String* substrings;
	size_t size=0;


	argument.split(DELIM, &substrings,&size);

	if ((int)size != FILTER_NUM){
		delete[] substrings;
		return ERROR;
	}

	String field_type = substrings[0].trim();
	String field_value = substrings[1].trim();


	if(field_type.equals(SOURCE_PORT) || field_type.equals(DEST_PORT)){
		Port input_port(field_type);
		input_port.set_value(field_value);
		parse_input(input_port);
	}
	else if(field_type.equals(SOURCE_IP) || field_type.equals(DEST_IP)){
		Ip input_ip(field_type);
		input_ip.set_value(field_value);
		parse_input(input_ip);
	}
	else{
		delete[] substrings;
		return ERROR;
	}

	
	delete[] substrings;
	return 0;
}
