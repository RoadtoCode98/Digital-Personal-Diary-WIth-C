#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void read_diary();
void write_diary();
void delete_diary();
void list_diary();
void protect_diary();


void main(){
	int choice;
	char title[] = "WELCOME TO YOUR PERSONAL DIARY FAM";
	printf("************************************************************************************************************************\n");
	printf("%73s\n\n", title);
	printf("************************************************************************************************************************\n\n");
	
	do{
	printf("%66s\n\n","What's your choice mate?");
	printf("%40s %40s\n\n %40s %44s\n\n %30s\n\n", "1. Write a diary", "2. Read a diary", "3. Delete a diary", "4. List your diaries", "5. Exit");
	scanf("%d", &choice);
	
	switch(choice){
		case 1:
			write_diary();
			break;
		case 2:
			read_diary();
			break;
		case 3:
			delete_diary();
			break;
		case 4:
			list_diary();
			break;
		case 5:
	        exit(1);
		default:
			printf("%20s", "\nInvalid choice buddy :-)");
	}}while(choice!=5);
}

void write_diary(){
	char date_entry[30], title[50], recepient[30], metadata[110];
	int n, i;
	
	printf("\nEnter the date: ");
	fseek(stdin,0,SEEK_END);
	fgets(date_entry, 30, stdin);
	
	printf("\nEnter diary title: ");
	fseek(stdin,0,SEEK_END);
	fgets(title, 50, stdin);
	
	printf("\nAny special recepient? ");
	fseek(stdin,0,SEEK_END);
	fgets(recepient, 30, stdin);
	if(title[strlen(title)-1]=='\n') title[strlen(title)-1] = 0;
	printf("\nEnter number of lines you want to write? \n");
	scanf("%d", &n);
	
	strcat(metadata, date_entry);
	if(metadata[strlen(metadata)-1]=='\n') metadata[strlen(metadata)-1] = ',';
	
	strcat(metadata, recepient);
	if(metadata[strlen(metadata)-1]=='\n') metadata[strlen(metadata)-1] = ',';
	
	strcat(metadata, title);
	strcat(metadata, "\n");
	//entering metadata about the file created 
	FILE *temp;
	temp = fopen("metadata.txt", "a");
	fprintf(temp, metadata);
	fclose(temp);
	
	FILE *fp;
	strcat(title,".txt");
	fp = fopen(title, "w");
	
	fseek(stdin,0,SEEK_END);
	for(i=0; i<n; i++){
		char data[150];
		fgets(data, 150, stdin);
		fprintf(fp, data);
		free(data);
	}
	fclose(fp);
}
void read_diary(){
	char c, name[30];
	
	FILE *fp;
	
	list_diary();
	printf("\nEnter the name of the file to read: ");
	scanf("\n");
	fgets(name, 30, stdin);
	if(name[strlen(name)-1]=='\n') name[strlen(name)-1] = 0;
	fp = fopen(name,"r");
	while((c=fgetc(fp))!=EOF){  
	printf("%c",c);  
	}  
	fclose(fp);  
}
void delete_diary(){
	char choice[50];
	list_diary();
	
	printf("\nEnter name of the diary you want to delete: ");
	scanf("\n");
	fgets(choice, 50, stdin);
	
	if(choice[strlen(choice)-1]=='\n') choice[strlen(choice)-1] = 0;
	if(remove(choice)==0) printf("\nDeleted Successfully\n\n");
	else printf("\nUnable to delete\n\n");
}
void protect_diary(){
	printf("hello");
}
void list_diary(){
	printf("\n\nList of files: \n\n");
    
    struct dirent *de;
    DIR *dr = opendir(".");
    if(dr==NULL){
    	printf("Could not open current directory");
    	return;
	}
	while ((de = readdir(dr)) != NULL) 
            printf("%s\n", de->d_name); 
  
    closedir(dr);
	
	return;	
}
