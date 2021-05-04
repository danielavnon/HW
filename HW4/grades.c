
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "grades.h"
#include "linked-list.h"

#define MAX_GRADE 100
#define MIN_GRADE 0
#define ERROR 1
#define SUCCESS 0
#define EXISTS 1
#define NON_EXISTING 0
#define AVERAGE_ERROR (-1)


//---------------------------------------------------------------------------//
struct grades {
	struct list* student_list;
};

struct student {
	int id;
	char* name;
	struct list* course_list;
};

struct course {
	char *name;
	int grade;
};
/**
*@brief Clones course
*@return SUCCESS in case of a success, ERROR otherwise
*@note failes if given element is invalid or memory allocation problem
*/

//---------------------------------------------------------------------------//
int clone_course (void *element, void **output){
	
	//declarations
	struct course *original=(struct course*)element;
	struct course *replica=(struct course*)malloc(sizeof(struct course));
	if(!replica){
		return ERROR;
	}
	
	//cloning name (as a string)

	replica->name=malloc(sizeof(char)*(strlen(original->name)+1));
	
	if(!(replica->name)){
		free(replica);
		return ERROR;
	}
	
	strcpy(replica->name,original->name);
	
	//cloning grade
	replica->grade=original->grade;

	*output=replica;
	return SUCCESS;
}
/**
*@brief Destroys course
*@return nothing as the function is void
*@note failes if given element is invalid
*/

//---------------------------------------------------------------------------//
void destroy_course (void *element){
	
	struct course *course_to_destroy=(struct course*)element;
	free(course_to_destroy->name);
	free(course_to_destroy);
}

//---------------------------------------------------------------------------//
/**
*@brief checks if the student exists in grades list
*@return EXISTS in case of existance, NON_EXISTING otherwise
*/
int student_exists(struct grades* grades, int id){

	struct iterator* iterator=list_begin(grades->student_list);
	struct student* current_student;
	while(iterator){
		current_student=list_get(iterator);
		if(!current_student){
			return NON_EXISTING;
		}
		if(current_student->id==id){
			return EXISTS;
		}
		iterator=list_next(iterator);
	}
	return NON_EXISTING;
} 

//---------------------------------------------------------------------------//

/**
*@brief checks if the studnet exists in grades list
*@return a pointer on the student in case found, NULL otherwise
*/
struct student* student_finder(struct list* list, int id){
	struct iterator* iterator=list_begin(list);
	struct student* current_student;
	while(iterator){
		current_student=list_get(iterator);
		if(current_student->id==id){
			return current_student;
		}
		iterator=list_next(iterator);
	}
	return NULL;
} 


//---------------------------------------------------------------------------//
/**
*@brief checks if the course exists in course list
*@return EXISTS in case of a existance, NON_EXISTING otherwise
*/
int course_exists(struct list* list, const char* name){
	struct iterator* iterator=list_begin(list);
	struct course* current_course;
	while(iterator){
		current_course=list_get(iterator);
		if(!(strcmp(current_course->name,name))){
			return EXISTS;
		}
		iterator=list_next(iterator);
	}
	return NON_EXISTING;
}

/**
*@brief Clones student
*@return SUCCESS in case of a success, ERROR otherwise
*@note failes if given element is invalid or memory allocation problem
*/
//---------------------------------------------------------------------------//
int clone_student (void *element, void **output){
	
	//declarations
	struct student *original=(struct student*)element;
	struct student *replica=(struct student*)(*output);
	replica=(struct student*)malloc(sizeof(struct student));
	if(!replica){
		free(replica);
		return ERROR;
	}
	
	//cloning name (as a string)
	replica->name=(char*)malloc(sizeof(char)*(strlen(original->name)+1));
	
	if (!(replica->name)){
		free(replica);
		return ERROR;
	}	
	strcpy(replica->name,original->name);
	
	//cloning id
	replica->id=original->id;
	
	//initialising course list and cloning it
	
	element_clone_t course_clone=clone_course;
	element_destroy_t course_destroy=destroy_course;

	struct list* course_list=list_init(course_clone,course_destroy);
	if(!course_list){
		free(replica->name);
		return ERROR;
	}
	
	replica->course_list=course_list;
	*output=replica;
	
	return SUCCESS;
}
//---------------------------------------------------------------------------//
/**
*@brief Destroys student
*@return nothing as the function is void
*@note failes if given element is invalid
*/


void destroy_student (void *element){
	
	struct student *student_to_destroy=(struct student*)element;
	free(student_to_destroy->name);
	list_destroy(student_to_destroy->course_list);
	free(student_to_destroy);
}

//---------------------------------------------------------------------------//
struct grades* grades_init() {
	
	struct grades* grades;
	grades=(struct grades*)malloc(sizeof(struct grades));
	if(!grades){
		free(grades);
		return NULL;
	}
	
	element_clone_t student_clone=clone_student;
	element_destroy_t student_destroy=destroy_student;
	
	grades->student_list=list_init(student_clone,student_destroy);

	return grades;
}

//---------------------------------------------------------------------------//
void grades_destroy(struct grades *grades){
	
	list_destroy(grades->student_list);
	free(grades);
}

//---------------------------------------------------------------------------//
int grades_add_student(struct grades *grades, const char *name, int id) {
	if(!grades){

		return ERROR;
	}
	if(student_exists(grades,id)) {

		return ERROR;
	}

	//initialisng a new student node
	struct student* new_student;
	new_student=(struct student*)malloc(sizeof(struct student));
	if(!new_student){
		return ERROR;
	}

	//feeding name (as a string)
	new_student->name=(char*)malloc(sizeof(char)*(strlen(name)+1));
	if(!(new_student->name)){
		free(new_student);
		return ERROR;
	}

	strcpy(new_student->name,name);
	

	//feeding id
	new_student->id=id;

	element_clone_t course_clone=clone_course;
	element_destroy_t course_destroy=destroy_course;
	struct list* course_list=list_init(course_clone,course_destroy);
	if(!course_list){
		free(new_student->name);
		free(new_student);
		return ERROR;
	}
	
	//creating a course list of the newly initialised student
	new_student->course_list=course_list;
	if((list_push_back(grades->student_list, new_student))){
		free(new_student->name);
		list_destroy(new_student->course_list);
		free(new_student);
		return ERROR;
	}
	free(new_student->name);
	list_destroy(new_student->course_list);
	free(new_student);
	return SUCCESS;
}

//---------------------------------------------------------------------------//
int grades_add_grade(struct grades *grades,const char *name,int id,int grade){
	
	//checking feasibility of the inputs
	if (!grades){
		return ERROR;
	}
	if (grade>=MAX_GRADE||grade<=MIN_GRADE){
		return ERROR;
	}
	
	//checking if student exists in student list
	struct student* selected_student_node;
	selected_student_node=student_finder(grades->student_list, id);
	if(!(student_exists(grades,id))){
		return ERROR;
	}
	
	//checking if course exists in grades' list of selected student	
	if(course_exists(selected_student_node->course_list,name)){
		return ERROR;
	}
	
	//initialising a new course node
	struct course* new_course;
	new_course=(struct course*)malloc(sizeof(struct course));
	if(!new_course){
		return ERROR;
	}
	//feeding name (as a string)
	new_course->name=(char*)malloc(sizeof(char)*(strlen(name)+1));

	if(!(new_course->name)){
		free(new_course);
		return ERROR;
	}
	strcpy(new_course->name,name);
	
	//feedind grade
	new_course->grade=grade;
	
	if(!(list_push_back(selected_student_node->course_list,new_course))){
		free(new_course->name);
		free(new_course);
		return SUCCESS;
	}
	else {
		free(new_course->name);
		free(new_course);
		return ERROR;
	}
}

//---------------------------------------------------------------------------//
float grades_calc_avg(struct grades *grades,int id,char **out){
	
	//checking feasibility of inputs
	if(!grades){
		out=NULL;
		return AVERAGE_ERROR;
	}
	if(!(student_exists(grades,id))){
		out=NULL;
		return AVERAGE_ERROR;
	}
	
	
	//initialising a pointer on selected student node
	struct student* selected_student_node;
	selected_student_node=student_finder(grades->student_list, id);
	
	
	//copying selected student name into out
	int selected_student_name_len=(strlen(selected_student_node->name)+1);
	char* name=(char*)malloc(sizeof(char)*(selected_student_name_len));
	
	if(!name){
		out=NULL;
		free(name);
		return AVERAGE_ERROR;
	}

	strcpy(name,selected_student_node->name);
	*out=name;

	
	//initialising variables to calulate the average grade
	float tally=0;
	int courses_count=list_size(selected_student_node->course_list);
	
	if(!courses_count){
		out=NULL;
		return tally;
	}
	
	//iterating on every course grade and extracting its grade
	struct iterator* iterator=list_begin(selected_student_node->course_list);
	
	if (!iterator){
		out=NULL;
		return AVERAGE_ERROR;
	}
	
	struct course* current_course;
	while(iterator){
		current_course=list_get(iterator);
		tally+=(current_course->grade);
		iterator=list_next(iterator);
		
	}
	float average=((tally)/(courses_count));
	return average;
}	

//---------------------------------------------------------------------------//	
int grades_print_student(struct grades *grades, int id){
	
	//checking feasibility of inputs
	if(!grades){
		return ERROR;
	}
	if(!(student_exists(grades,id))){
		return ERROR;
	}
	//initialising a pointer on selected student node
	struct student* selected_student_node;
	selected_student_node=student_finder(grades->student_list, id);
	
	//printing the prefix as formatted
	printf("%s %d:",selected_student_node->name,id);
	
	struct iterator* iterator=list_begin(selected_student_node->course_list);
	
	struct course* current_course;
	
	//printing while iterating through course list
	while(iterator){
		current_course=list_get(iterator);
		printf(" %s %d",current_course->name,current_course->grade);
		iterator=list_next(iterator);
		if(iterator){
			printf(",");
		}
	}
	printf("\n");
	return SUCCESS;
}

//---------------------------------------------------------------------------//
int grades_print_all(struct grades *grades){
	
	//checking feasibility of input
	if(!grades){
		return ERROR;
	}
	
	struct student* current_student;
	struct iterator* iterator=list_begin(grades->student_list);
	
	while(iterator){
		current_student=list_get(iterator);
		grades_print_student(grades,current_student->id);
		iterator=list_next(iterator);	
	}
	
	return SUCCESS;
}
