#ifndef __LIST_H__
#define __LIST_H__

#include "info_struct.h"

typedef struct Node {

	/* school && teacher && student info */
	struct school info;

	/* pNext until point next node */
	struct Node *pNext;
} NODE, *PNODE;

/*
 *display about school info.
 */
void display_info(struct school *sch_info);

/*
 *add about school info.
 */
PNODE list_add_info(struct school *info, int register_total);

/*
 *delete about school info.
 */
void list_delete_info();

/*
 *update about school info.
 */
void list_update_info();

/*
 *trave about school info.
 */
void list_trave_info(PNODE);

/*
 *clear about school info and exit application.
 */
void clear_up();

#endif /* __LIST_H__ */
