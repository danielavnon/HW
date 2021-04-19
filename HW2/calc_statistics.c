/*
 * course_statistics.c
 *
 *  Created on: 14 Apr 2021
 *      Author: mamat
 */

/* Welcome to Mamat, 044101
 *
 * Use this project as a template for other C/C++ projects.
 * To copy this project, right-click on the project name "hello-world"
 * in the "project explorer" tab (left), then "copy" and finally "paste".
 *
 * To compile the project use "gcc" within the terminal.
 * To debug the project use "gdb" within the terminal.
 *
 * The red vertical line (right) represents the code width limit (80 chars).
 * Make sure not to cross it. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TOP_GRADE 100
#define BOTTOM_GRADE 1
#define PASS_GRADE 55
#define PERCENT_FACTOR 100
#define DIGITS_IN_LINE 10
#define LINE_COUNT 10
#define ERROR 1

/**
 * @brief Calculates statistical analysis of grades
 * @param argc Number of arguments = 1
 * @param argv Pointer to arguments to grades.txt
 * @param input_file contains the grades linely ordered
 * @param outout_file contains the anaylis, formatted as demanded
 * @return Non-zero value in case of an error
 */
int main(int argc, char *argv[]) {
	if (argc < 1) {
		fprintf(stderr, "Error\n");
		return 1;
	}
	FILE *input_file, *output_file;
	input_file = fopen("grades.txt", "r");
	output_file = fopen("course_statistics.txt", "w");
	if (input_file == NULL || output_file == NULL){
		fprintf(stderr, "Reading error\n");
		return ERROR;
	}
	// if we've gotten till here, the input and output files are in order
	int hist[TOP_GRADE] = {0};
	int students_count = 0;
	int grades_sum = 0;
	int pass_count = 0;
	double mean_grade = 0;
	int med_grade = 0;
	int max_grade = BOTTOM_GRADE;
	int min_grade = TOP_GRADE;
	double pass_percent = 0;

	int current_grade = 0;
	//scanning grades and stores them
	while (fscanf(input_file, "%d\n", &current_grade) != EOF){
	
		hist[current_grade-1]++;
		students_count++;
		grades_sum += current_grade;
		if (current_grade >= PASS_GRADE){
			pass_count++;
		}
		if (current_grade > max_grade){
			max_grade = current_grade;
		}
		else if (current_grade <= min_grade){
			min_grade = current_grade;
		}
	}
	//calculating median grade
	int grade_counter;
	int median_position=((students_count+1)/2);
	for (int grade=0; grade<=TOP_GRADE-1; grade++){
		grade_counter=hist[grade];
		while (grade_counter!=0){
			grade_counter--;
			median_position--;
			if (median_position==0){
				med_grade=(grade+1);
			}
		}
	}
	//analysing the grade which were stored beforehand
	mean_grade = ((double)grades_sum/(double)students_count);
	pass_percent = ((double)pass_count/(double)students_count)*PERCENT_FACTOR;
	
	fprintf(output_file,"num of students = %d\n",students_count);
	fprintf(output_file,"avg = %.3f\n",mean_grade);
	fprintf(output_file,"the median is = %d\n", med_grade);
	fprintf(output_file,"max grade = %d, min grade = %d\n",max_grade,min_grade);
	fprintf(output_file,"pass rate = %.2f%%\n",pass_percent);
	
	//matrix printing
	for (int num=0; num<=TOP_GRADE-1; num++){
		fprintf(output_file, "%d",hist[num]);
		if((num+1)%DIGITS_IN_LINE !=0){
			fprintf(output_file," ");
		}
		else {
			fprintf(output_file,"\n");
		}		
	}
	fclose (output_file);
	fclose (input_file);
	if (input_file == NULL || output_file == NULL){
		fprintf(stderr, "Closing error\n");
		return ERROR;
	}
	return 0;
}

