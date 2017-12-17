#ifndef __INFO_H__
#define __INFO_H__

#define NAME_BUF 20
#define SNPRINTF_INFO(info_name)	fprintf(stderr, "%s snprintf failed\n", info_name)
#define MALLOC_INFO(info_name)	fprintf(stderr, "%s malloc failed\n", info_name)

struct student {
	char student_name[NAME_BUF];
	char sex;
	int age;
};

struct teacher {
	char teacher_name[NAME_BUF];
	char sex;
	int age;
};

struct school {
	char school_name[NAME_BUF];
	struct teacher *tea;
	struct student *stu;
};

enum list_handle_select {
	ADD_LIST_SELECT = 2,
	DELETE_LIST_SELECT,
	UPDATE_LIST_SELECT,
	TRAVE_LIST_SELECT,
};

#endif /* __INFO_H__ */
