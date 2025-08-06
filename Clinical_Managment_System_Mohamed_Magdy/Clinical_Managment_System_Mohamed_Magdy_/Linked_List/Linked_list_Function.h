#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include<stdio.h>
#include<stdlib.h>
#include"../common/std_types.h"
#define reserved 1
#define not_reserved 0
typedef struct patient{
	u32 ID;
	u8 name[30];
	u32 age;
	u8 gender[20];
	
}patient;

typedef struct res{
	u8 time[50];
	u8 res_flag; // 0 for not reserved and 1 for reserved
	u32 id_res;
}res;

/*===========================================================================================================================================================================
 *------------------------------------------------------------------ Functions Decleration ----------------------------------------------------------------------------------
 *===========================================================================================================================================================================
*/
typedef struct node{
	patient data;
	struct node*next;
}node;
/*===========================================================================================================================================================================
 *------------------------------------------------------------------ Insert at first Function ----------------------------------------------------------------------------------
 *===========================================================================================================================================================================
*/
void insert_first(const struct patient *const ptr);
void Delete_Reservation(u32);
void Display(u32 REQ_ID);
void Edit_Patinet(u32);
void Display_res(void);
void res_done(u32,u16);
void delete_patinet(u32);
void display_list(void);

#endif
