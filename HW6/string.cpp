#include "string.h"
#include <cstring>
#include <iostream>
#include "ip.h"

#define NULL_SIGN '\0'
#define SPACE_SIGN ' '
#define DOT_SIGN '.'


char* allocate_and_copy(const char* str,int size);

String::String(){
	data = new char[1];
	data[0] = NULL_SIGN;
	length = 0;
}

String::String(const String &str){
	length = str.length;
	data = allocate_and_copy(str.data,length);
}

String::String(const char *str){
	length = strlen(str);
	data = allocate_and_copy(str,length);
}

String::~String(){
	if(data != NULL){
		delete[] data;
	}
}

String& String::operator=(const String &rhs){
	if (this == &rhs){
		return *this;
	}
	delete[] data;
	length = rhs.length;
	data = allocate_and_copy(rhs.data,length);
	return *this;
}

String& String::operator=(const char *str){
	if(!(strcmp(data,str))){
		return *this;
	}
	delete[] data;
	length = strlen(str);
	data = allocate_and_copy(str,length);
	return *this;
}

bool String::equals(const String &rhs) const{
	
	if(this == &rhs){
		return true;
	}
	else return false;
}

bool String::equals(const char *rhs) const{
	
	if(!(strcmp(data,rhs))){
		return true;
	}
	else return false;
}

void String::split(const char *delimiters, String **output, size_t *size) const{
	
	//input correctness checks

	if(output == NULL || delimiters == NULL || data == NULL){
		return;
	}

	int i, j, i_deli, i_substring = 0;
	int substrings_count = 1;
	int num_delimiters;
	int start = 0;
	int len = length;

	char data_clone[len+1];
	strcpy(data_clone,data);
	num_delimiters = strlen(delimiters);
	for (i = 0; i < len; i++){
		for(i_deli = 0; i_deli < num_delimiters ; i_deli++){
			if (data_clone[i] == delimiters[i_deli]){
				data_clone[i] = NULL_SIGN;
				if (i>0 && data_clone[i-1] != NULL_SIGN && i<(len-1)){
					substrings_count++;
				}
			}
		}
	}

	*size = substrings_count;
	*output = new String[substrings_count];
	
	for (i = 0; i < len; i++){

		if(data_clone[i]==NULL_SIGN && i>0 && data_clone[i-1]!=NULL_SIGN){
			(*output)[i_substring]=String(&data_clone[start]);
			j=i;
			while(data_clone[j]==NULL_SIGN){
				j++;
			}
			start=j;
			i_substring++;
		}
	}
	return;
}


int String::to_integer() const{
	return atoi(data);
}

String String::trim() const{
	int start = 0;
	int end = length -1;

	while(data[start] == SPACE_SIGN){
		start++;
	}

	while(data[end]== SPACE_SIGN){
		if(end==start){
			return String(); // string which consists only spaces, disputed
		}
		end--;
	}
	
	end++;
	char trimmed_string[end-start+1];
	strncpy(trimmed_string,&data[start],end-start);
	trimmed_string[end-start]=SPACE_SIGN;

	String trimmed_structure= String(trimmed_string);

	return trimmed_structure;
	
}


char* allocate_and_copy(const char* str,int size){

	if(size == 0){
		return NULL;
	}
	else return strcpy(new char[size+1],str);
}

