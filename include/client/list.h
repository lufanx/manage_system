#ifndef __LIST_H__
#define __LIST_H__

#include "info_struct.h"

typedef struct Node {

	/* school && teacher && student info */
	struct school info;

	/* pNext until point next node */
	struct Node *pNext;
} NODE, *PNODE;

/* Display about school info.  */
void display_info(struct school *sch_info);

/* Ddd about school info.  */
PNODE list_add_info(struct school *info, int register_total);

/* Delete about school info.  */
void list_delete_info();

/* Update about school info.  */
void list_update_info();

/* Trave about school info.  */
void list_trave_info(PNODE);

/* Clear about school info and exit application.  */
void clear_up();

#endif /* __LIST_H__ */
