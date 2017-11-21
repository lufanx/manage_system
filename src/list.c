#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
display_info(struct school *sch_info){

	if(!sch_info){
		return;
	}

	printf("school_name: %s\n", sch_info->school_name);
	printf("tea_name: %s\n", sch_info->tea->teacher_name);
	printf("tea_age: %d\n", sch_info->tea->age);
	printf("tea_sex: %s\n", sch_info->tea->sex);
	printf("stu_name: %s\n", sch_info->stu->student_name);
	printf("stu_age: %d\n", sch_info->stu->age);
	printf("stu_sex: %s\n", sch_info->stu->sex);

	return;
}

PNODE
list_add_info(struct school *info){

	struct teacher tea;
	struct student stu;
	printf("%s\n", __FUNCTION__);
	if(!info){
		return NULL;
	}

	PNODE pHead;
	PNODE pTail;

	pHead = (PNODE)malloc(sizeof(NODE));
	if(pHead == NULL){
		MALLOC_INFO("pHead");
		exit(1);	
	}
	pTail = pHead;
	PNODE pNew;
	pNew = (PNODE)malloc(sizeof(NODE));
	if(pNew == NULL){
		MALLOC_INFO("pNew");
		exit(1);
	}
	snprintf(pNew->info.school_name, sizeof(BUFFER), "%s", info->school_name);
	pNew->info.tea = &tea;
	snprintf(pNew->info.tea->teacher_name, sizeof(BUFFER), "%s", info->tea->teacher_name);
	printf("-------------\n");
	pNew->info.tea->age = info->tea->age;
	snprintf(pNew->info.tea->sex, sizeof(BUFFER), "%s", info->tea->sex);
	pNew->info.stu = &stu;
	snprintf(pNew->info.stu->student_name, sizeof(BUFFER), "%s", info->stu->student_name);
	pNew->info.stu->age = info->stu->age;
	snprintf(pNew->info.stu->sex, sizeof(BUFFER), "%s", info->stu->sex);

	pTail->pNext = pNew;
	pNew->pNext = NULL;
	pTail = pNew;

	return pHead;
}

void
list_delete_info(){

}

void
list_update_info(){

}

void
list_trave_info(PNODE pHead){
	
	PNODE p;
	p = pHead;
	while(p->pNext != NULL){
		printf("school name: %10s\n", p->pNext->info.school_name);
		printf("teacher name: %10s\n", p->pNext->info.tea->teacher_name);
		printf("teacher age: %10d\n", p->pNext->info.tea->age);
		printf("teacher sex: %10s\n", p->pNext->info.tea->sex);
		printf("student name: %10s\n", p->pNext->info.stu->student_name);
		printf("student age: %10d\n", p->pNext->info.stu->age);
		printf("student sex: %10s\n", p->pNext->info.stu->sex);
		p = p->pNext;
	
	}

}
