#include "stdinc.h"

#include "client/info_struct.h"
#include "client/list.h"
#include "client/socket_client.h"
#include "common_handle.h"
#include "log.h"

/*
 * default teacher_age teacher_sex
 * default student_age student_sex
 */
int const teacher_age = 20;
char teacher_sex = 'f';
int const student_age = 18;
char student_sex = 'f';

static void
data_init(struct school *sch_info)
{
	if (!sch_info) {
		return;
	}

	memset(sch_info, 0, sizeof(*sch_info));
	snprintf(sch_info->school_name, sizeof(sch_info->school_name), "ShangHai_XueYuan");
	sch_info->tea = (struct teacher *)malloc(sizeof(struct teacher));
	if (sch_info == NULL) {
		MALLOC_INFO("sch_info->tea");
		exit(1);
	}
	sch_info->stu = (struct student *)malloc(sizeof(struct student));
	if (sch_info->stu == NULL) {
		MALLOC_INFO("sch_info->stu");
		exit(1);
	}
	snprintf(sch_info->tea->teacher_name, sizeof(sch_info->tea->teacher_name), "LiSi");
	sch_info->tea->age = teacher_age;
	sch_info->tea->sex = teacher_sex;
	snprintf(sch_info->stu->student_name, sizeof(sch_info->stu->student_name), "ZhangSan");
	sch_info->stu->age = student_age;
	sch_info->stu->sex = student_sex;
}

/*
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
*/

static void
usage_start(char *app_name)
{
	printf("%s: options\n", app_name);
	printf("\t1: display_info\n");
	printf("\t2: add_info\n");
	printf("\t3: delete_info\n");
	printf("\t4: update_info\n");
	printf("\t5: trave_info\n");
	printf("\t6: clear up\n");

	return;
}

/*
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
*/

void
sig_handle(int signo)
{
	if (signo == SIGINT) {
		printf("Client SIGINT handle\n");
		kill(getpid(), SIGKILL);
	}
}

int
main(int argc, char *argv[])
{

	struct school sch_info;
	struct list_select client_list_select;
	PNODE pHead = NULL;
	int		register_flag = 1;
	int sockfd;
	enum list_handle_select list_st;	/* About handle list select  */

	client_list_select.pHead = (PNODE)malloc(sizeof(NODE));
	if (client_list_select.pHead == NULL) {
		LOG_ERROR_INFO("%s", "Client_list_select.pHead malloc failed\n");
		exit(1);
	}

	if (signal(SIGINT, sig_handle) == SIG_ERR) {
		LOG_ERROR_INFO("Client SIGINT handle error\n");
	}

	data_init(&sch_info);
	sockfd = connect_server(argc, argv);

	while (1) {
		int cmd;
		int exit_flag = 0;

		usage_start(argv[0]);
		printf("Please input options: ");
		if (!scanf("%d", &cmd)) {
			printf("inval command: command be must number 1-5\n");
			while (getchar() != '\n');
			usage_start(argv[0]);
			continue;
		}
		switch (cmd) {
		case 1:
			display_info(&sch_info);
			break;
		case 2:
			//parse_args(argc, argv, &sch_info);
			pHead = list_add_info(&sch_info, register_flag);
			register_flag = 0;
			list_st = ADD_LIST_SELECT;
			break;
		case 3:
			list_delete_info();
			list_st = DELETE_LIST_SELECT;
			break;
		case 4:
			list_update_info();
			list_st = UPDATE_LIST_SELECT;
			break;
		case 5:
			if (!pHead) {
				fprintf(stderr, "info is empty\n");
				break;
			}
			list_trave_info(pHead);
			list_st = TRAVE_LIST_SELECT;
			break;
		case 6:
			//clear_up();
			exit_flag = 1;
			break;
		default:
			fprintf(stderr, "%d input error!\n", cmd);
			break;
		}
		client_list_select.pHead = pHead;
		client_list_select.select = list_st;
		send_data_server(&client_list_select, sockfd);

		if (exit_flag) {
			break;
		}
		while (getchar() != '\n');
		printf("Please Enter to display cmd menu...\n");
		while (getchar() != '\n');
		//usage_start(argv[0]);
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

	free(client_list_select.pHead);
	free(sch_info.tea);
	free(sch_info.stu);
	close(sockfd);

	return 0;
}
