#ifndef __INFO_H__
#define __INFO_H__

#define BUFFER 1024
#define SNPRINTF_INFO(info_name)	fprintf(stderr, "%s snprintf failed\n", info_name)
#define MALLOC_INFO(info_name)	fprintf(stderr, "%s malloc failed\n", info_name)

struct student {
	char student_name[BUFFER];
	int age;
	char sex[BUFFER];
};

struct teacher {
	char teacher_name[BUFFER];
	int age;
	char sex[BUFFER];
};

struct school {
	char school_name[BUFFER];
	struct teacher *tea;
	struct student *stu;
};

#endif
