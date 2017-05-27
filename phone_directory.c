#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h> 

typedef struct contact_{
	char name[100];
	char fname[40];
	char lname[40];
	char mobile[15];
}Contact;

Contact list[100];
int count;

/* 
*  Read the file contents and add the contacts to the array of structs list
*/
void create(char * path){
	FILE * file = fopen(path,"r");
	char buffer[100];

	while(fgets(buffer,100,file) != NULL){
		int length = strlen(buffer);
		if(buffer[length-1] == '\n'){
			buffer[length-1] = '\0';
		}
		char * str = strtok(buffer,",");

		strcpy(list[count].name,str);
		strcpy(list[count].mobile,strtok(NULL," "));
		strcpy(list[count].fname,strtok(str," "));
		strcpy(list[count].lname,strtok(NULL," "));
		count++;
	}
	fclose(file);
}

/*
* Displays the contacts currently in store
*/
void display(){
	printf("\n\t\tContacts List\n\n");
	if(count == 0){
		printf("\n\n-----Empty------\n");
	}
	int i;
	for(i=0;i<count;i++){
		printf("%s, %s\n",list[i].name,list[i].mobile);
	}
	printf("\n");
}

/*
*	Accepts two indices and swaps them in the array of structs
*/
void swap(int a,int b){
	Contact temp = list[a];
	list[a] = list[b];
	list[b] = temp;
}

/*
*	Returns partition index based on the start and end indices
*/
int partition(Contact list[],int start,int end){

	char * pvt = list[end].fname;
	int pind = start;
	int i;
	for(i=start;i<end;i++){
		if(strcmp(list[i].fname,pvt) < 0){
			swap(i,pind);
			pind++;
		}
		// If first name is equal
		else if(strcmp(list[i].fname,pvt) == 0){
			char * pvt_last = list[end].lname;
			if(strcmp(list[i].lname,pvt_last) < 0){
				swap(i,pind);
				pind++;
			}
			// If last name is equal
			else if(strcmp(list[i].lname,pvt_last) == 0){
				char * pvt_mob = list[end].mobile;
				if(strcmp(list[i].mobile,pvt_mob) < 0){
					swap(i,pind);
					pind++;
				}
			}

		}
	}
	Contact temp = list[pind];
	list[pind] = list[end];
	list[end] = temp;
	return pind;
}


/*
* Quicksort the contacts list based on the priorities like
* first name,last name and mobile number
*/
void quicksort(Contact list[],int start,int end){
	if(start >= end){
		return;
	}
	//Randomize the last index
	srand(time(NULL));
	int ran = rand() % (end-start) + start;
	Contact tem = list[ran];
	list[ran] = list[end];
	list[end] = tem;

	int ind = partition(list,start,end);
	quicksort(list,start,ind-1);
	quicksort(list,ind+1,end);
}

/*
* Calls helper function quicksort to sort the contacts list
*/
void sort_contact(){
	quicksort(list,0,count-1);
}

/*
* Searches for a passed Name in the contacts list and print its index
*/
void search_binary(char * name,int start,int end){

	if(start > end){
		printf("\nName is not found\n\n");
		return;
	}
	int mid = (start+end)/2;
	if(strcmp(list[mid].name,name) == 0){
		printf("\nName found at index %d\n",mid);
		printf("\n%s, %s\n\n",list[mid].name,list[mid].mobile);
		return;
	}
	else if(strcmp(name,list[mid].name) < 0){
		return search_binary(name,start,mid-1);
	}
	else if(strcmp(name,list[mid].name) > 0){
		return search_binary(name,mid+1,end);
	}
}

/*
* Calls helper function search_binary to search the list for a name
*/
void search(char * name){
	sort_contact();
	search_binary(name,0,count-1);
}

/*
* Finds the specified name in the contact list and delete it from the list
*/
void delete(char * name){
	int i;
	for(i=0;i<count;i++){
		if(strcmp(list[i].name,name) == 0){
			int j = i;
			while(j < count-1){
				list[j] = list[j+1];
				j++;
			}
			count--;
			list[j].name[0] = '\0';
			list[j].fname[0] = '\0';
			list[j].lname[0] = '\0';
			list[j].mobile[0] = '\0';
			sort_contact();
			display();
			return;
		}
	}
	printf("Name is not found\n\n");
}

/*
* Inserts the new contact in the contacts list and display the list in sorted order
*/
void insert(char * name,char * phone_number){
	strcpy(list[count].name,name);
	strcpy(list[count].mobile,phone_number);
	char copyname[100];
	strcpy(copyname,name);
	strcpy(list[count].fname,strtok(copyname," "));
	strcpy(list[count].lname,strtok(NULL," "));
	count++;
	printf("\n");
	sort_contact();
}

/*
* Main function
*/
int main(char * argc,char * argv[]){

	// char * file_path = argv[1];
	create("input.txt");
	int choice;
	do{
		printf("\n1) sort_contact\n2) search\n3) delete\n4) insert");
		printf("\n--------------------------------------------------");
		printf("\n\nEnter the choice\n");
		
		scanf("%d",&choice);
	
		switch(choice){
			char input[100];

			case 1:	printf("\n");
					sort_contact();
					display();
					break;
			case 2: printf("\nEnter the Name -> ");
					scanf("\n");
					scanf("%[^\n]%*c",input);
					search(input);
					break;
			case 3: printf("\nEnter the Name -> ");
					scanf("\n");
					scanf("%[^\n]%*c",input);
					printf("\n");
					delete(input);
					break;
			case 4: printf("\nEnter the Name -> ");
					scanf("\n");
					scanf("%[^\n]%*c",input);
					
					char name[100];char mob[20];
					strcpy(name,strtok(input,","));
					strcpy(mob,strtok(NULL," "));
					insert(name,mob);
					display();
					break;
			default : printf("\nEnter valid choice\n\n");
		}	
	}while(choice < 5);
	return 0;
}
