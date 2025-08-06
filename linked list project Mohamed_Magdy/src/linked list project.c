/*
 ============================================================================
 Name        : linked.c
 Author      : Mohamed Magdy
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
struct student{
	int id;
	char name [50];
	int age;
	float gpa;


};
struct node{
	struct student data;
	struct node*next;

};
struct node*head=NULL;
int idExists(int id) {
    struct node* current = head;
    while (current != NULL) {
        if (current->data.id == id)
            return 1; // ID found
        current = current->next;
    }
    return 0; // ID not found
}
/*THE START OF THE FIRST FUNCTION*/

void addStudent(const struct student *const ptr){
	if(idExists(ptr->id)){
	printf("the id : %d is already exist",ptr->id);
	return;
	}

	   struct node* newNode = (struct node*)malloc(sizeof(struct node));
	    if (newNode == NULL) {
	        printf("can't allocate memory");
	        return;
}
	    newNode->data = *ptr;
	       newNode->next = NULL;


	       if (head == NULL) {
	             head = newNode;
	         } else {
	             struct node* temp = head;
	             while (temp->next != NULL) {
	                 temp = temp->next;
	             }
	             temp->next = newNode;
	         }

	         printf("student with id:%d is successfully added", ptr->id);
	   }
/*first function implementation*/
/*second function implementation*/
void displayStudents(void){
	struct node*current =head;
	printf("THE List of the students");
	if(head==NULL){
		printf("the List of the students is empty");
		return;
	}
	else {
		while(current!=NULL){
			printf("NAME: %s\n",current->data.name);
			printf("ID: %d\n",current->data.id);
			printf("Age:%d\n",current->data.age);
			printf("GPA: %f\n",current->data.gpa);
			current=current->next;
		}

	}

}
/*End of the second function*/
/*3rd function*/
void searchStudentByID(int id){
    struct node* current = head;
     while(current!=NULL){
    if(current->data.id==id){
    	printf("the student found and here is the data");
    	printf("NAME: %s\n",current->data.name);
    	printf("ID:%d\n",current->data.id);
     	printf("age:%d\n",current->data.age);
     	printf("GPA:%f\n",current->data.gpa);

    }
    else {
    printf("the student with  id: %d not found",id);
     }
    current=current->next;


}
/*END OF THE FUNCTION 3*/
void updateStudent(int id){
struct node* current = head;
while(current!=NULL){
	if(current->data.id==id){
		printf("the student with id: %d exist",id);
		printf("enter the new name:\n");
		scanf("%s",current->data.name);
		printf("enter the age:\n");
		scanf("%d",&current->data.age);
		printf("enter the new GPA:\n");
		scanf("%f",&current->data.gpa);

	}
	else{
		printf("the student with id: %d not found",id);
	}
current=current->next;

}
}/*the start of the new function*/
float calculateAverageGPA(void){
struct node* current = head;
if(head==NULL){

	return 0.0;
}
 int count=0;
 float total=0.0;
while(current!=NULL){
	total=total+current->data.gpa;
	count++;
	current=current->next;
}
if(count>0){
	return total/count;
}
else{
	return 0.0;

}
}/*the start of the new fucntion*/
void searchHighestGPA(void) {
    if (head == NULL) {
        printf("No students in the list.\n");
        return;
    }

    struct node* current = head;
    struct node* topStudent = head;

    while (current != NULL) {
        if (current->data.gpa > topStudent->data.gpa) {
            topStudent = current;
        }
        current = current->next;
    }

    printf("Student with the highest GPA:\n");
    printf("ID: %d, Name: %s, GPA: %.2f\n",
           topStudent->data.id,
           topStudent->data.name,
           topStudent->data.gpa);
}
void deleteStudent(int id) {
    struct node* current = head;
    struct node* previous = NULL;

    while (current != NULL) {
        if (current->data.id == id) {
            if (previous == NULL) {
                // Deleting the head node
                head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            printf("Student with ID %d deleted successfully.\n", id);
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("Student with ID %d not found.\n", id);
}


int main(void)
{

	int choice;
	int searchid;
	int updatestudent;
	int deleteid;

	do {
		printf("--- the program menu---");
		printf("1.add student");
		printf("2.Display student");
		printf("3.Search by id");
		printf("4.Update student by id");
		printf("5.Delete student by id");
		printf("6.Calculate AVG GPA");
		printf("7.Search for the Highest GPA");
		printf("8.Exit the program");
		scanf("%d",&choice);
		struct student s;

		switch(choice){
		case 1:
			printf("enter the id");
			scanf("%d",&s.id);
			printf("enter name of the student");
			scanf("%s",s.name);
			printf("enter the age of the student");
			scanf("%d",&s.age);
			printf("Enter the GPA of the student");
			scanf("%f",&s.gpa);
			addStudent(&s);
			break;
		case 2:
			displayStudents();
			break;

		case 3:
			printf("enter the id you want to search");
			scanf("&d",&searchid);
			searchStudentByID(searchid);
			break;
		case 4:
			printf("enter the id of the student you want to update");
				scanf("%d",&updatestudent);
				updateStudent(updatestudent);
			break;
		case 5:
			printf("enter the id you want to delete");
			scanf("%d",&deleteid);
			deleteStudent(deleteid);
			break;
		case 6:
			printf("Average GPA of all students: %.2f\n", calculateAverageGPA());
			    break;
		case 7:
			searchHighestGPA();
			break;
		case 8:
			printf("the program is terminated thank you");
			break;
			default:
				printf("invalid choice please try again");
				break;
		}
	}
	while(choice!=0);

}
}





