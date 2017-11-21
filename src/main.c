#include "info_struct.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * default teacher_age teacher_sex
 * default student_age student_sex
 */
int const teacher_age = 20;
char *teacher_sex = "f";
int const student_age = 18;
char *student_sex = "f";

static void
data_init(struct school *sch_info){
	int strlen = 0;
	if(!sch_info){
		return;
	}

	memset(sch_info, 0, sizeof(*sch_info));
	strlen = snprintf(sch_info->school_name, sizeof(sch_info->school_name), "shanghai_xueyuan");
	if(strlen < 0){
		SNPRINTF_INFO("sch_info->school_name");
		exit(1);
	}
	sch_info->tea = (struct teacher *)malloc(sizeof(struct teacher));
	if(sch_info == NULL){
		MALLOC_INFO("sch_info->tea");
		exit(1);
	}
	sch_info->stu = (struct student *)malloc(sizeof(struct student));
	if(sch_info->stu == NULL){
		MALLOC_INFO("sch_info->stu");
		exit(1);
	}
	strlen = 0;
	strlen = snprintf(sch_info->tea->teacher_name, sizeof(sch_info->tea->teacher_name), "lisi");
	if(strlen < 0){
		SNPRINTF_INFO("sch_info->tea->teacher_name");
		exit(1);
	}
	sch_info->tea->age = teacher_age;
	strlen = 0;
	strlen = snprintf(sch_info->tea->sex, sizeof(sch_info->tea->sex), "%s", teacher_sex);
	if(strlen < 0){
		SNPRINTF_INFO("sch_info->tea->sex");
		exit(1);
	}
	strlen = 0;
	strlen = snprintf(sch_info->stu->student_name, sizeof(sch_info->stu->student_name), "zhangsan");
	if(strlen < 0){
		SNPRINTF_INFO("sch_info->stu->student_name");
		exit(1);
	}
	sch_info->stu->age = student_age;
	strlen = 0;
	strlen = snprintf(sch_info->stu->sex, sizeof(sch_info->stu->sex), "%s", student_sex);
	if(strlen < 0){
		SNPRINTF_INFO("sch_info->stu->sex");
		exit(1);
	}
}

static void
usage(const char *app_name){
	printf("%s: options\n", app_name);
	printf("\ts: school name\n");
	printf("\tt: teacher name\n");
	printf("\ta: teacher age\n");
	printf("\tn: teacher sex\n");
	printf("\tm: student name\n");
	printf("\te: student age\n");
	printf("\tx: student sex\n");
}

static void
usage_start(char *app_name){
	printf("%s: options\n", app_name);
	printf("\t1: display_info\n");
	printf("\t2: add_info\n");
	printf("\t3: delete_info\n");
	printf("\t4: update_info\n");
	printf("\t5: trave_info\n");
	printf("\t6: clear up\n");

	return;
}

static void
parse_args(int argc, char **argv, struct school *get_school_info){
	int op;

	while((op = getopt(argc, argv, "s:t:a:n:m:e:x:")) != -1){
		switch(op){
		case 's':
				snprintf(get_school_info->school_name, sizeof(get_school_info->school_name), "%s", optarg);
				break;
		case 't':
				snprintf(get_school_info->tea->teacher_name, sizeof(get_school_info->tea->teacher_name), "%s", optarg);
				break;
		case 'a':
				get_school_info->tea->age = atoi(optarg);
				break;
		case 'n':
				snprintf(get_school_info->tea->sex, sizeof(get_school_info->tea->sex), "%s", optarg);
				break;
		case 'm':
				snprintf(get_school_info->stu->student_name, sizeof(get_school_info->stu->student_name), "%s", optarg);
				break;
		case 'e':
				get_school_info->stu->age = atoi(optarg);
				break;
		case 'x':
				snprintf(get_school_info->stu->sex, sizeof(get_school_info->stu->sex), "%s", optarg);
				break;
		default:
				usage(argv[0]);
		}
	}
}

int
main(int argc, char *argv[]){

	struct school sch_info;
	PNODE pHead;
	//if(argc != 4){
	//	fprintf(stderr, "argc: %s school_name teacher_name student_name\n", argv[0]);
	//	exit(1);
	//}
	data_init(&sch_info);

	while(1){
		int cmd;
		int exit_flag = 0;

		usage_start(argv[0]);
		printf("Please input options: ");
		if(!scanf("%d", &cmd)){
			printf("inval command: command be must number 1-5\n");
			while(getchar()!= '\n');
			usage_start(argv[0]);
			continue;
		}
		switch(cmd){
		case 1:
				display_info(&sch_info);
				break;
		case 2:
				parse_args(argc, argv, &sch_info);
				pHead = list_add_info(&sch_info);
				break;
		case 3:
				list_delete_info();
				break;
		case 4:
				list_update_info();
				break;
		case 5:
				if(!pHead){
					fprintf(stderr, "info is empty\n");
					break;
				}
				list_trave_info(pHead);
				break;
		case 6:
				//clear_up();
				exit_flag = 1;
				break;
		default:
				fprintf(stderr, "%d input error!\n", cmd);
				break;	
		}

		if(exit_flag){
			break;
		}
		while(getchar() != '\n');
		printf("Please Enter to display cmd menu...\n");
		while(getchar() != '\n');
		usage_start(argv[0]);
	}

/*
	parse_args(argc, argv, &sch_info);

	printf("school_name: %s\n", sch_info.school_name);
	printf("tea_name: %s\n", sch_info.tea->teacher_name);
	printf("tea_age: %d\n", sch_info.tea->age);
	printf("tea_sex: %s\n", sch_info.tea->sex);
	printf("stu_name: %s\n", sch_info.stu->student_name);
	printf("stu_age: %d\n", sch_info.stu->age);
	printf("stu_sex: %s\n", sch_info.stu->sex);
*/

	free(sch_info.tea);
	free(sch_info.stu);

	return 0;
}
