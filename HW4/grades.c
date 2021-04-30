
#include <stdio.h>
#include <string.h>
#include "grades.h"
#include "linked-list.h"

#define MAX_GRADE 100
#define MIN_GRADE 0


struct grades {
	struct grades* next;
	struct grades* prev;
	struct student_info* student; 
};

struct student_info {
	int id;
	char* name;
	struct grades_sheet* grades_sheet;
};


struct grades_sheet {
	struct grades_sheet* next;
	struct grades_sheet* prev;
	char *course_name;
	int course_grade;
};

int clone_element (void *element, void **output){
	
	
	struct student_info *index= (struct student_info*)element;
	struct student_info *clone_student;
	//char *name=(char*)malloc(sizeof(char)*(strlen(index->name)+1));
	
	clone_student->name=(char*)malloc(sizeof(char)*(strlen(index->name)+1));
	
	if (!(clone_student->name)){
		//malloc error
		return 1;
	}	
	
	strcpy(clone_student->name,index->name);
	student_info->id=index->id;
	stundent_info->grades_sheet=index->grades_sheet;
	output=&clone_student;
	
	return 0;
}
/*
	//initialisng a new student node and inserting student info
	struct student_info new_student;
	new_student.id=id;
	new_student.name=malloc(sizeof(char)*(strlen(&name)+1));
	
	if(!(new_student.name)){
	//malloc error
	return 1;
	}
	strcpy(new_student.name,name);
	
	//a pointer which points at the newly made student node
	struct student_info* p_new_student=&new_student;

*/



void destroy_element (void *element){
	
	//free allocated memory
	
}


struct grade* grades_init() {
	
	struct grades* grades;
	element_clone_t elem_clone=clone_element;
	element_destroy_t elem_destroy;
	grades=list_init(elem_clone,elem_destroy);
	
	return grades;
	
};

void grades_destroy(struct grades *grades){
	
	//using list_destroy and destroy_element
}


int grades_add_student(struct grades *grades, const char *name, int id) {
		
	if(!grades){
		return 1;
	}
	if (is_exists(grades,id,NULL)) { //NULL fails
		return 1; //fail, as the student already exists
	}
	
	//initialisng a new student node and inserting student info
	struct student_info new_student;
	new_student.id=id;
	new_student.name=malloc(sizeof(char)*(strlen(&name)+1));
	
	if(!(new_student.name)){
	//malloc error
	return 1;
	}
	strcpy(new_student.name,name);
	
	//a pointer which points at the newly made student node
	struct student_info* p_new_student=&new_student;
	
	if(!list_push_back(grades, p_new_student)){
		return 1;
	}
	return 0;	
};


int grades_add_grades(struct grades *grades,const char *name,int id,int grade){
	
	if (!grades){
		return 1;
	}
	struct grades* selected_student_node;
	if (!is_exists(grades, id, selected_student_node)) {
		return 1; //fail, as the student does not exists
	}
	if (grade>MAX_GRADE|| grade<MIN_GRADE){
		return 1;
	}
	//checking if course exists in grades' sheet of selected student
	struct grades_sheet* grades_sheet;
	grades_sheet=(selected_student_node->student->grades_sheet);
	
	struct grades_sheet *list_iterator=list_begin(grades_sheet);
	struct grades_sheet *list_final_elem=list_end(grades_sheet);
	while(list_iterator!=list_final_elem){
		if(!strcmp(list_iterator->course_name,name)){
			return 1;
		}
		list_iterator=list_next(grades_sheet);
	}
	if(!strcmp(list_final_elem->course_name,name)){
		return 1;
	}
	
	//initialising new grades_sheet node and pointing a pointer on it
	struct grades_sheet new_course;
	new_course.course_grade=grade;
	new_course.name=malloc(sizeof(char)*(strlen(&name)+1));
	if(!(new_course.name)){
		//malloc error
		return 1;
	}
	strcpy(new_course.name,name);
	struct grades_sheet* p_grades_sheet=&new_course;
	

	if(!list_push_back(grades_sheet,p_grades_sheet)){
		return 1;
	}

};


	
	
	


//1 means existing, 0 means non existing
//if we attend to look whether a student is existing we use NULL pointer
//if we attend to look to return a specific student pointer, we dont use NULL

int is_exists(struct grades *grades,int id,struct grades *selected_student){
	struct grades *list_iterator=list_begin(grades);
	struct grades *list_final_elem=list_end(grades);
	while (list_iterator!=list_final_elem) {
		if (list_iterator->student->id==id) {
			if (!selected_student){
				selected_student=&list_iterator;
			}
			return 1;
		}
		list_iterator=list_next(grades);
	}
	if (list_final_elem->student->id==id) {
		if (!selected_student){
			selected_student=&list_iterator;
		}
		return 1;
	}
	return 0;
}
