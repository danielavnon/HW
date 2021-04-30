
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "grades.h"
#include "linked-list.h"

#define MAX_GRADE 100
#define MIN_GRADE 0
#define ERROR 1

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

int clone_student (void *element, void **output){
	
	struct student *original= (struct student*)element;
	struct student *replica;
	replica->name=(char*)malloc(sizeof(char)*(strlen(original->name)+1));
	
	if (!(replica->name)){
		//malloc error
		return ERROR;
	}	
	
	strcpy(replica->name,original->name);
	replica->id=original->id;
	replica->course_list=original->course_list;
	output=&replica;
	
	return 0;
}

void destroy_student (void *element){
	
	struct student *student_to_destroy=(struct student*)element;
	free(student_to_destroy->name);
	list_destroy(student_to_destroy->course_list);
	free(student_to_destroy);
}

int clone_course (void *element, void **output){
	
	struct course *original= (struct course*)element;
	struct course *replica;
	replica->name=(char*)malloc(sizeof(char)*(strlen(original->name)+1));
	
	if (!(replica->name)){
		//malloc error
		return ERROR;
	}	
	
	strcpy(replica->name,original->name);
	replica->grade=original->grade;
	output=&replica;
	
	return 0;
}

void destroy_course (void *element){
	
	struct course *course_to_destroy=(struct course*)element;
	free(course_to_destroy->name);
	free(course_to_destroy);
}

//initialising student list w/o course list
struct grades* grades_init() {
	
	struct grades* grades;
	
	element_clone_t student_clone=clone_student;
	element_destroy_t student_destroy=destroy_student;
	
	element_clone_t course_clone=clone_course;
	element_destroy_t course_destroy=destroy_course;
	
	grades->student_list=list_init(student_clone,student_destroy);

	return grades;
	
}

void grades_destroy(struct grades *grades){
	
	//using destroy_course and destroy_student
}


int grades_add_student(struct grades *grades, const char *name, int id) {
		
	if(!grades){
		return ERROR;
	}
	if (student_exists(grades->student_list,id,NULL)) { //NULL fails
		return ERROR; //fail, as the student already exists
	}
	
	//initialisng a new student node and feeding student info
	struct student new_student;
	new_student.id=id;
	new_student.name=malloc(sizeof(char)*(strlen(name)+1));
	
	if(!(new_student.name)){
	//malloc error
	return ERROR;
	}
	strcpy(new_student.name,name);
	
	//a pointer which points at the newly made student node
	struct student* p_new_student=&new_student;
	
	return list_push_back(grades->student_list, p_new_student);
}


int grades_add_grades(struct grades *grades,const char *name,int id,int grade){
	
	if (!grades){
		return ERROR;
	}
	if (grade>MAX_GRADE|| grade<MIN_GRADE){
		return ERROR;
	}
	struct student* selected_student_node;
	if (!(student_exists(grades->student_list, id, selected_student_node))){
		return ERROR;
	}
	//checking if course exists in grades' list of selected student
	
	//course=(selected_student_node->student->grades_sheet);
	if(course_exists(selected_student_node->course_list,name)){
		return ERROR;
	}

	struct course new_course;
	
	new_course.grade=grade;
	new_course.name=malloc(sizeof(char)*(strlen(name)+1));
	if(!(new_course.name)){
		//malloc error
		return ERROR;
	}
	strcpy(new_course.name,name);
	
	struct course* p_new_course=&new_course;
	
	return list_push_back(selected_student_node->course_list,p_new_course)
}

/*
float grades_calc_avg(struct grades *grades,int id,char **out){
	
	
	
	
	
	
}	
	
int grades_print_student(struct grades *grades, int id){
	
	
	
	
	
}

int grades_print_all(struct grades *grades){
	
	
	
	
	
}

*/

//1 means existing, 0 means non existing
//if we attend to look whether a student is existing we use NULL pointer
//if we attend to look to return a specific student pointer, we dont use NULL

int student_exists(struct list *list,int id,struct student *selected_student){
	
	struct iterator *student_iterator=list_begin(list);
	struct student *current_student;
	while(!student_iterator){
		current_student=list_get(student_iterator);
		if(current_student->id==id){
			if(selected_student){
				selected_student=current_student;
			}
			return 1;	
		}
		student_iterator=list_next(student_iterator);	
	}
	
	return 0;	
}
	

//1 means existing, 0 means non existing
int course_exists(struct list* list, char* name){
	struct iterator *course_iterator=list_begin(list);
	struct course *current_course;
	while(!course_iterator){
		current_course=list_get(course_iterator);
		if(!(strcmp(current_course->name,name))){
			return 1;
		}
		course_iterator=list_next(course_iterator);
	}
	return 0;
}
