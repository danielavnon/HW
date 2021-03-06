#include "string.h"
#include "ip.h"
#include <cstring>

#define NULL_SIGN '\0'
#define SPACE_SIGN ' '
#define DOT_SIGN '.'


    /**
     * @brief allocates and copy a new string
     * @param *str a pointer to a given string
     * @param size the size of the given string
     * @return a pointer to a string which is a copy of the
     * given string
     */
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
	if (str == NULL){
		data = new char[1];
		data[0] = NULL_SIGN;
		length = 0;
	}
	else{
	length = strlen(str);
	data = allocate_and_copy(str,length);
	}
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
	
	if((length == rhs.length) && !strcmp(data, rhs.data)){
		return true;
	}
	else{
	    return false;
	}
}

bool String::equals(const char *rhs) const{
	
	if(!(strcmp(data,rhs))){
		return true;
	}
	else return false;
}

void String::split(const char *delimiters, String **output, size_t *size) const{
	
	//input correctness checks

	if(delimiters == NULL || data == NULL){
		return;
	}

	int i, i_deli, i_substring = 0;
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
	if(output == NULL){
		return;
	}

	*output = new String[substrings_count];
	//int j=0;
	for (i = 0; i < len+1; i++){

		if(data_clone[i]==NULL_SIGN && i>0 && data_clone[i-1]!=NULL_SIGN){
			(*output)[i_substring]=String(&data_clone[start]);
			//j=i;
			//while(data_clone[j]==NULL_SIGN){
			//	j++;
			//}
			//start=j;
			i_substring++;
			start = i + 1;
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
	trimmed_string[end-start]=NULL_SIGN;

	String trimmed_structure= String(trimmed_string);

	return trimmed_structure;
	
}


char* allocate_and_copy(const char* str,int size){

	if(size == 0){
		return NULL;
	}
	else return strcpy(new char[size+1],str);
}

