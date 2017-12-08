#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PNODE pHead = NULL;
PNODE pTail;
/* point until point creat new node */
PNODE point;

void
display_info(struct school *sch_info)
{

	if (!sch_info) {
		return;
	}

	printf("school_name: %s\n", sch_info->school_name);
	printf("tea_name: %s\n", sch_info->tea->teacher_name);
	printf("tea_age: %d\n", sch_info->tea->age);
	printf("tea_sex: %c\n", sch_info->tea->sex);
	printf("stu_name: %s\n", sch_info->stu->student_name);
	printf("stu_age: %d\n", sch_info->stu->age);
	printf("stu_sex: %c\n", sch_info->stu->sex);

	return;
}

PNODE
list_add_info(struct school *info, int register_flag)
{
/*
	struct teacher tea = {0};
	struct student stu = {0};
	char teacher_sex = ' ';
	char student_sex = ' ';
*/
	//PNODE pHead;
	PNODE pTail;

	if (!info) {
		return NULL;
	}

	/* Head node only create once when register_flag == 1 */
	if (register_flag) {
		pHead = (PNODE)malloc(sizeof(NODE));
		if (pHead == NULL) {
			MALLOC_INFO("pHead");
			exit(1);
		}
	}

	pTail = pHead;
	PNODE pNew;
	/* Create every data node */
	pNew = (PNODE)malloc(sizeof(NODE));
	if (pNew == NULL) {
		MALLOC_INFO("pNew");
		exit(1);
	}

	/*
	snprintf(pNew->info.school_name, sizeof(pNew->info.school_name), "%s", info->school_name);
	pNew->info.tea = &tea;
	snprintf(pNew->info.tea->teacher_name, sizeof(pNew->info.tea->teacher_name), "%s", info->tea->teacher_name);
	pNew->info.tea->age = info->tea->age;
	snprintf(pNew->info.tea->sex, sizeof(pNew->info.tea->sex), "%s", info->tea->sex);
	pNew->info.stu = &stu;
	snprintf(pNew->info.stu->student_name, sizeof(pNew->info.stu->student_name), "%s", info->stu->student_name);
	pNew->info.stu->age = info->stu->age;
	snprintf(pNew->info.stu->sex, sizeof(pNew->info.stu->sex), "%s", info->stu->sex);
	*/

	//pNew->info.tea->sex = &teacher_sex;
	//pNew->info.stu->sex = &student_sex;

	printf("Please input school name:\n");
	scanf("%s", pNew->info.school_name);

	pNew->info.tea = (struct teacher *)malloc(sizeof(struct teacher));
	if (pNew->info.tea == NULL) {
		MALLOC_INFO("Tea");
		exit(1);
	}
	printf("Please input teacher name:\n");
	scanf("%s", pNew->info.tea->teacher_name);
	printf("Please input teacher age:\n");
	scanf("%d", &pNew->info.tea->age);
	printf("Please input teacher sex:\n");
	scanf("%c", &pNew->info.tea->sex);
	//pNew->info.tea->sex = getchar();
	//pNew->info.tea->sex = fgetc(stdin);

	pNew->info.stu = (struct student *)malloc(sizeof(struct student));
	if (pNew->info.stu == NULL) {
		MALLOC_INFO("Stu");
		exit(1);
	}
	printf("Please input stdent name:\n");
	scanf("%s", pNew->info.stu->student_name);
	printf("Please input student age:\n");
	scanf("%d", &pNew->info.stu->age);
	printf("Please input student sex:\n");
	scanf("%c", &pNew->info.stu->sex);
	//pNew->info.stu->sex = getchar();
	//pNew->info.stu->sex = fgetc(stdin);

	/* if is first node, pNew->pNext = NULL */
	if (register_flag) {
		pTail->pNext = pNew;
		pNew->pNext = NULL;
		point = pNew;
	}
	/* every new node point next node */
	else {
		pTail->pNext = pNew;
		pNew->pNext = point;
		point = pNew;
	}

	return pHead;
}

void
list_delete_info()
{

}

void
list_update_info()
{

}

void
list_trave_info(PNODE pHead)
{

	PNODE p;
	p = pHead;
	while (p->pNext != NULL) {
		printf("school name: %10s\n", p->pNext->info.school_name);
		printf("teacher name: %10s\n", p->pNext->info.tea->teacher_name);
		printf("teacher age: %10d\n", p->pNext->info.tea->age);
		printf("teacher sex: %10c\n", p->pNext->info.tea->sex);
		printf("student name: %10s\n", p->pNext->info.stu->student_name);
		printf("student age: %10d\n", p->pNext->info.stu->age);
		printf("student sex: %10c\n", p->pNext->info.stu->sex);
		p = p->pNext;

	}

}
