#include<stdio.h>
#include"../common/std_types.h"
#include"../Linked_List/Linked_list_Function.h"
int main(void){
	struct patient user;
	setbuf(stdout,NULL);
	fflush(stdout);
	static u16 pass=1234;

	static u16 mode;
	static u16 try;
	static u8 pass_counter;
	static u8 cases;
	static u8 user_input;
	static u16 patinet_id_req;
	static u16 req_res;
	printf("\n===========================================================================\n");
	printf("----------------- Welcome TO The Clinical Management System----------------\n");
	printf("===========================================================================\n");
	while(1){
	printf("\n===========================================================================\n");
    printf("---------------------------    Home Page        ---------------------------\n");
	//printf("--------- For the Admin Mode press 1 and For User Mode Press 0 ------------\n");
	printf("===========================================================================\n");
	printf("->Admin Mode press : ( 1 )\n");
	printf("->User Mode Press : ( 0 )\n");
	printf("->User input :");
	scanf("%d",&mode);
	printf("---------------------------------------------------------------------------\n\n");
	
//user mode	
if(mode ==0){
	
printf("===========================================================================\n");	
printf("-----------------------Welcome TO the User Page---------------------------\n");
printf("===========================================================================\n");
	printf("\n");
printf("===========================================================================\n");
printf("-----------------------        Main Menu        ---------------------------\n");
printf("===========================================================================\n");
while(1){
printf("\nPlease Select From the Menu\n");
printf("1 --- View patient record\n");
printf("2 --- View today's reservations\n");
printf("3 --- Return To Home Page\n");
printf("---------------------------------------------------------------------------\n");
scanf("%d",&user_input);

switch(user_input){
	case 1://view patinet record
		printf("enter the ID you want to search for\n");
        scanf("%d",&patinet_id_req);
        Display(patinet_id_req);
	break;
	
	
	case 2:printf("Here is all The  Available Reservation For Today\n");
	printf("---------------------------------------------------------------------------\n");
	Display_res();
	break;
	case 3:
	break;
	
	default:
	printf("Invalid Input\n");
	break;
	
	
}
if(user_input==3){
	break;
}
}	
}


// admin mode	
if(mode==1){
printf("===========================================================================\n");	
printf("-----------------------Welcome TO the admin Page---------------------------\n");
printf("===========================================================================\n");
printf("\nPlease Enter the Password\n");

for(pass_counter=3;pass_counter>0;pass_counter--){
	scanf("%d",&try);
	if(pass!=try){
	printf("Wrong PASSWORD %d  Try left\n",pass_counter-1);
	if(pass_counter==1){
		printf("===========================================================================\n");
		printf("-------------------- No More Tries Exiting The Program ...--------------------\n");
		printf("===========================================================================\n");
		return 0;
	}
	}
	else if(try==pass){
		printf("Access granted Displaying Main Menu ...\n");
		break;
	}

	
	
	
}
//Displaying THE Main Menu code
while(1){
printf("===========================================================================\n");
printf("-----------------------        Main Menu        ---------------------------\n");
printf("===========================================================================\n");
printf("\nPlease Select From the Menu\n");
printf("1 --- Add new patient record\n");
printf("2 --- Edit patient record\n");
printf("3 --- Reserve a slot with the doctor\n");
printf("4 ---  Cancel reservation\n");
printf("5 --- Delete Patinet Record\n");
printf("6 --- Display All The Patinet Records\n");
printf("7 --- Return To home Page\n");
printf("---------------------------------------------------------------------------\n");
scanf("%d",&cases);
switch(cases){
	case 1://insert patinet data
	printf("Enter The ID of Patient\n");
	scanf("%d",&(user.ID));
    printf("Enter the name of Patient\n");
    scanf("%s",user.name);
    printf("Enter the Age of The Patient\n");
    scanf("%d",&(user.age));
    printf("Enter the Gender of the Patient\n");
    printf("for Female write 'F' for Male Write 'M'\n");
    scanf(" %c",&(user.gender));
	insert_first(&user);
	break;
	case 2:// Edit Patient Record
		printf("Enter The Patinet ID\n");
        scanf("%d",&patinet_id_req);
        Edit_Patinet(patinet_id_req);
	break;
	case 3://reserve a slot with doctor
		Display_res();
		printf("=======================\n");
		printf("Enter the Patinet ID\n");
		scanf("%d",&patinet_id_req);
		printf("Enter the Desired Reservation Time\n");
		printf("=======================\n");

        scanf("%d",&req_res);
        res_done(patinet_id_req,req_res);


	break;
	case 4:
		printf("Enter The Patinet ID you want to Delete\n");
		scanf("%d",&patinet_id_req);
		Delete_Reservation(patinet_id_req);
	break;
	case 5:
		printf("Enter The Patinet Of the ID You want to delete\n");
		scanf("%d",&patinet_id_req);
		delete_patinet(patinet_id_req);

		break;
	case 6:
		display_list();
		break;
	case 7:
	break;
	default:
	printf("Invalid Input please enter from the list\n");
	break;
	
}
if(cases==7){
break;
	
}
	
	
}
}

// corner case
if(mode>1){
	printf("Invalid input Please Enter 0 or 1\n");
	printf("Returning To Home Page...\n");
}
	




	
	}
}
