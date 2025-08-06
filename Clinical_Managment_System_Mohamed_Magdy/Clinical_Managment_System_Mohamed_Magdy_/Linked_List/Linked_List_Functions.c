#include<stdio.h>
#include<stdlib.h>
#include"Linked_List_Function.h"
/*============================================================================================================
 *------------------------------------ Linked List Functions Implementaions-----------------------------------
 *============================================================================================================
*/
// globale variable head

node*head=NULL;// لازم تعرف ال head هنا علشان تعرف تستخدمه في ال functions بتاعتك
/* main functions*/
res arr[5]={
		{"2:00 PM ---> 2:30 PM\n"},
		{"2:30 PM ---> 3:00 PM\n"},
		{"3:00 PM ---> 3:30 PM\n"},
		{"4:00 PM ---> 4:30 PM\n" },
		{"4:30 PM ---> 5:00 PM\n"},
};


/*=========================================
 * awl function m3aaana detect the id
 * ========================================
 */
u16 id_found(u16 id_input){
	struct node*founder=head;
	while(founder!=NULL){
		if(founder->data.ID==id_input){

			return 1; //which means that we found the patient with the same id
			// lw rg3 wa7d sa3tha condtion ely mawgood ta7t fe el insert hyb2 true
		}
		founder=founder->next;// dy blzbt bt3ml increament lkol node

	}
	return 0; //which means that the user not found
	// sa3tha el conditon hyb2a false w el id msh mtkrr
}




/*===================================================================
 * ---------------------- insert Function ---------------------------
 * ==================================================================
 */
void insert_first(const struct patient *const ptr){
	if(id_found(ptr->ID)){
		printf("sorry their is a Patinet With the same ID\n");
		return;
	}


node*link=(node*)malloc(sizeof(node));//create the node

/* protection just to make sure that memory is allocated*/
if(link==NULL){
	printf("Failed to allocate memory");
	return;
	
}
link->data=*ptr;// to insert the data
link->next=head;// to take the  address of the first node (head)
head=link;// to assign the new node the head address 
printf("Patinet with ID : %d Succesfully added To the list \n",ptr->ID);
}
/*======================================================================
 * --------------------   Display Function -----------------------------
 * =====================================================================
 */
void Display(u32 REQ_ID){
	node*printer=head;
	if(printer==NULL){
	printf("Sorry But The List is EMPTY");
	return;
	}
	printf("The User Record : \n");
	while(printer !=NULL){
		if(printer->data.ID==REQ_ID){
			printf("Patinet ID %d\n",printer->data.ID);
			printf("Patinet Name %s\n",printer->data.name);
			printf("Patinet Age %d\n",printer->data.age);
			printf("Patinet Gender %s\n",printer->data.gender);
			return;
		}
		printer=printer->next;

	}
	printf("Sorry No Patient with this id \n");
	printf("------------------------------\n");


}
/*======================================================================
 * ----------------------- Edit Patinet Record -------------------------
 * =====================================================================
 */
void Edit_Patinet(u32 REQ_ID){
node*editor=head;
if(head==NULL){
	printf("sorry But the List is empty\n");
	return;
}
while(editor!=NULL){

	if(editor->data.ID==REQ_ID){
	printf("Patinet Found with id %d\n",REQ_ID);

	// take care lw 7beet a3dl 3la id tmam w 5leet atnen bnfs el id sa3tha y2ol mynf3sh
	u32 new_id;
	            printf("Enter Patient New ID: ");
	            scanf("%d", &new_id);
	  node* temp = head;
	  while (temp != NULL) {
      if (temp->data.ID == new_id && temp != editor) {
	  printf("Error: ID %d is already used by another patient.\n", new_id);
	  return;
}
temp = temp->next;
}
editor->data.ID = new_id;


	printf("Enter Patient New Name\n");
	scanf("%s",editor->data.name);
	printf("Enter Patinet New Age\n");
	scanf("%d",&editor->data.age);
	printf("Enter Patinet New Gender\n");
	scanf("%s",editor->data.gender);
	printf("Patinet New record is saved \n");
	return;
	}
	editor=editor->next;


}
 printf("sorry But This id '%d' Not found in Patinet List\n",REQ_ID);


}
/*========================================================================
 * --------------------- reserved func displaying ------------------------
 * =======================================================================
 */

void Display_res(void){
for(u8 i=0;i<5;i++){
if(arr[i].res_flag==not_reserved){
	printf("%d --- %s\n",i+1,arr[i].time);
}
else if(arr[i].res_flag==reserved){
	printf("==============================================================================\n");
	printf("--------------------------- Reserved --------------------------------- ID : %d\n",arr[i].id_res);
	printf("==============================================================================\n");
}
}
}
/*=======================================================================
 * ----------------------- reservation function -------------------------
 * ======================================================================
 */
void res_done(u32 id,u16 time){
	node*looper=head;
	if(head==NULL){
		printf("sorry But The List Is Empty Add Patinets Then Continue\n");
		return;
	}
	while(looper!=NULL){
		if(looper->data.ID==id){
			printf("The id is founded in the List\n");
			Display_res();
			printf("Enter the Desired Reservation time\n");
			u8 selector=time;
			if(selector<0 || selector>5){
				printf("invalid input please choose from the menu\n");
				printf("Returning To Main Menu...\n");
				return;
			}
			// 3lshan t5leeeeeh y7gz me3ad wa7d bs
			for (u8 i = 0; i < 5; i++) {
			    if (arr[i].res_flag == reserved && arr[i].id_res == id) {
			        printf("Sorry, this patient has already made a reservation.\n");
			        return;
			    }
			}
			 if(selector>0 && selector<=5){
				if(arr[selector-1].res_flag==not_reserved){
					arr[selector-1].res_flag=reserved;
					arr[selector - 1].id_res = id;// تربط الوقت بال id
					printf("Reservation success\n");
					return;
				}
				else if(arr[selector-1].res_flag==reserved){
					printf("sorry the Desired Reservation is already reserved\n");
					return;
}
}
}
		looper = looper->next;
}
printf("sorry But No Patinet With Such id %d\n",id);
return;
}

/*========================================================================================
 * ----------------------------- Delete Function -----------------------------------------
 * =======================================================================================
 */
void Delete_Reservation(u32 deleted_id){
	u8 founder=0;
	for(u8 i=0;i<5;i++){
		if(arr[i].res_flag==reserved &&arr[i].id_res==deleted_id){
			arr[i].res_flag=not_reserved;
			printf("Reservation Canceled Successfully\n");
			founder=1;
			return;

		}
	}
	if(!founder){
		printf("Sorry Patinet With ID: %d didn't Make a Reservation\n",deleted_id);
		return;
	}
}
/*=====================================================================================
 * ---------------------------------- delete_patinet ----------------------------------
 * ====================================================================================
 */
void delete_patinet(u32 d_id){
	Delete_Reservation(d_id);
	node*deletor=head;
	node*saver=NULL;
	if(head==NULL){
		printf("Sorrt But the List is Empty\n");
		return;
	}
// deleting the patinet at the first of the list
	if(head->data.ID==d_id){
		printf("Patinet With ID: %d Deleted Successfully\n",d_id);
		node*temp=head;
			head=head->next;
			free(temp);
			return;
	}

while(deletor!=NULL && deletor->data.ID!=d_id){
	saver=deletor;
	deletor=deletor->next;
}

if(deletor==NULL){
	printf("Sorry But No Patinet with Such ID %d\n",d_id);
	return;
}
else{
	saver->next=deletor->next;
	free(deletor);
	printf("Patinet with ID: %d Successfully Deleted\n",d_id);
	return;

}


}
/*=====================================================================================
 * --------------------------- Display The Whole List ---------------------------------
 *=====================================================================================
 */


void display_list(void){
	node*printer=head;
	if(head==NULL){
		printf("Sorry But the List is Empty\n");
		return;
	}
	printf("Here is all the Patinets Records\n");
	while(printer!=NULL){
		printf("Patinet ID: %d\n",printer->data.ID);
		printf("Patinet Name: %s\n",printer->data.name);
		printf("Patinet Age: %d\n",printer->data.age);
		printf("Patinet Gender: %s\n",printer->data.gender);
		printf("========================\n");
		printer=printer->next;


	}
	u8 garbage;
	printf("Enter any value to Return to Main Menu\n");
	scanf("%d",&garbage);
	return;


}


	
	



