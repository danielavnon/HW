
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

//---------------------------------------------------------------------------//
//returns EXISTS, in case found, NON_EXISTING otherwise
int student_exists(struct grades* grades, int id){
printf("d1\n");
	struct iterator* iterator=list_begin(grades->student_list);
	printf("d2\n");
	struct student* current_student;
	printf("d3\n");
	while(!iterator){
	printf("d4\n");
		current_student=list_get(iterator);
			printf("d5\n");
		if(!current_student){
					printf("d6\n");
			return NON_EXISTING;
		}
		if(current_student->id==id){
			printf("d7\n");
			return EXISTS;
		}
			printf("d8\n");
		iterator=list_next(iterator);
	}	printf("d9\n");
	return NON_EXISTING;
} 

//---------------------------------------------------------------------------//

//returns a pointer to the selected student node, in case found
//otherwise, NULL
struct student* student_finder(struct list* list, int id){
	struct iterator* iterator=list_begin(list);
	struct student* current_student;
	while(!iterator){
		current_student=list_get(iterator);
		if(current_student->id==id){
			return current_student;
		}
		iterator=list_next(iterator);
	}
	return NULL;
} 


//---------------------------------------------------------------------------//
//returns EXISTS, in case found, NON_EXISTING otherwise
int course_exists(struct list* list, char* name){
	struct iterator* iterator=list_begin(list);
	struct course* current_course;
	while(!iterator){
		current_course=list_get(iterator);
		if(!(strcmp(current_course->name,name))){
			return EXISTS;
		}
		iterator=list_next(iterator);
	}
	return NON_EXISTING;
}


//---------------------------------------------------------------------------//
int clone_student (void *element, void **output){
	
	//declarations
	struct student *original=(struct student*)element;
	struct student **replica=(struct student**)(output);
	*replica=(struct student*)malloc(sizeof(struct student));
	if(!replica){
		free(replica);
		return ERROR;
	}
	
	//cloning name (as a string)
	char* name;
	name=(char*)malloc(sizeof(char)*(strlen(original->name)+1));
	if (!name){
		free(name);
		return ERROR;
	}	
	strcpy(name,original->name);
	
	//cloning id
	(*replica)->id=original->id;
	
	//cloning course list
	(*replica)->course_list=original->course_list;
	
	//freeing original given student struct
	free(original);
	
	return SUCCESS;
}

//---------------------------------------------------------------------------//
void destroy_student (void *element){
	
	struct student *student_to_destroy=(struct student*)element;
	free(student_to_destroy->name);
	list_destroy(student_to_destroy->course_list);
	free(student_to_destroy);
}

//---------------------------------------------------------------------------//
int clone_course (void *element, void **output){
	
	//declarations
	struct course *original=(struct course*)element;
	struct course **replica=(struct course**)(output);
	*replica=(struct course*)malloc(sizeof(struct course));
	
	if(!replica){
		free(replica);
		return ERROR;
	}
	
	//cloning name (as a string)
	char* name=(char*)malloc(sizeof(char)*(strlen(original->name)+1));
	
	if(!name){
		free(replica);
		return ERROR;
	}
	
	strcpy(name,original->name);
	(*replica)->name=name;
	
	//cloning grade 
	(*replica)->grade=original->grade;
	
	//freeing original given course struct
	free(original);
	
	return SUCCESS;
}


//---------------------------------------------------------------------------//
void destroy_course (void *element){
	
	struct course *course_to_destroy=(struct course*)element;
	free(course_to_destroy->name);
	free(course_to_destroy);
}

//---------------------------------------------------------------------------//
//initialising student list w/o course list
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
	printf("1\n");	
	if(!grades){
	printf("2\n");
		return ERROR;
	}
	printf("3\n");
	if(student_exists(grades,id)) {
		printf("4\n");
		return ERROR;
	}
	printf("5\n");
	//initialisng a new student node
	struct student* new_student;
	printf("6\n");
	new_student=(struct student*)malloc(sizeof(struct student));
	printf("7\n");
	if(!new_student){
		printf("8\n");
		free(new_student);
		printf("9\n");
		return ERROR;
	}
	printf("10\n");
	//feeding name (as a string)
	new_student->name=(char*)malloc(sizeof(char)*(strlen(name)+1));
	if(!(new_student->name)){
		free(new_student->name);
		return ERROR;
	}
	strcpy(new_student->name,name);
	
	//feeding id
	new_student->id=id;

	element_clone_t course_clone=clone_course;
	element_destroy_t course_destroy=destroy_course;


	//creating a course list of the newly initialised student
	new_student->course_list=list_init(course_clone,course_destroy);
	
	return list_push_back(grades->student_list, new_student);
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
	printf("add_grade1\n");
	//checking if student exists in student list
	struct student* selected_student_node;
	selected_student_node=student_finder(grades->student_list, id);
	printf("add_grade2\n");
	if(!(student_exists(grades,id))){
	printf("add_grade3\n");
		return ERROR;
	}
	printf("add_grade4\n");
	//checking if course exists in grades' list of selected student	
	if(course_exists(selected_student_node->course_list,name)){
	printf("add_grade5\n");
		return ERROR;
	}
	printf("add_grade6\n");
	//initialising a new course node
	struct course* new_course;
	new_course=(struct course*)malloc(sizeof(struct course));
	printf("add_grade7\n");
	if(!new_course){
	printf("add_grade8\n");
		free(new_course);
		return ERROR;
	}printf("add_grade9\n");
	//feeding name (as a string)
	new_course->name=(char*)malloc(sizeof(char)*(strlen(name)+1));
	printf("add_grade10\n");
	if(!(new_course->name)){
		free(new_course->name);
		return ERROR;
	}
	strcpy(new_course->name,name);
	
	//feedind grade
	new_course->grade=grade;
printf("add_grade11\n");
	return list_push_back(selected_student_node->course_list,new_course);
}

//---------------------------------------------------------------------------//
float grades_calc_avg(struct grades *grades,int id,char **out){
	
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
	
	//initialising variables to calulate the average grade
	int tally=0;
	int courses_count=list_size(selected_student_node->course_list);
	
	if(!courses_count){
		return tally;
	}
	
	//iterating on every course grade and extracting its grade
	struct iterator* iterator=list_begin(selected_student_node->course_list);
	
	if (!iterator){
		out=NULL;
		return ERROR;
	}
	
	struct course* current_course;
	while(iterator){
		current_course=list_get(iterator);
		tally+=(current_course->grade);
		iterator=list_next(iterator);
	}
	
	//char* name=
	//(char*)malloc(sizeof(char)*(strlen(selected_student_node->name)+1);

	strcpy(*out,selected_student_node->name);
	return (float)(tally/courses_count);
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

