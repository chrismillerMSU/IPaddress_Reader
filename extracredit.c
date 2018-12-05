/*
 * Christopher Miller
 * MSU
 * 12/4/2018
 * This program takes in up to 100 ipaddresses and their associated nicknames. Then it prints out which machines are pairs of lcoal machines. Then it prints out all ipaddress and nickname pairs.
 */


#include <stdio.h>
#include <string.h>
#include <math.h>
#define TRUE 1
#define FALSE 0
//Define data structure for holding ipaddresses and nicknames
typedef struct address{
    int firstNum;
    int secondNum;
    int thirdNum;
    int fourthNum;
    char nickName[20];
    int isPair;
} address_t;
//Takes in an ipaddress as a string with periods separting the numbers, and breaks in apart into ints and add's them to a address_t data structure.
void breakApart(address_t* address,char* ip, char* name){

    int val=0,size,i=0;
    char* result;

    result = strtok(ip, "."); //Create first token
    while(result != NULL){ //Loops through whole string breaking it apart by "."
	size = strlen(result)-1; //gets size of current token
        while(size>=0){ //Transforms string number in int data type py taking last number and multiplying it by 10 to the power of its position. EX: 3rd number in a number gets multplyed by 10^3
            val += (result[size] - 48)*pow(10,size);
            size--;
        }
	i++;//Incrments counter which identifies which number in a ipaddress we are on
	switch(i){//This switch stament detemines where to put a converted number in address data structure. 
	    case 1:
		address->firstNum = val;
		break;
	    case 2:
		address->secondNum = val;
		break;
	    case 3:
		address->thirdNum = val;
                break;
	    case 4:
		address->fourthNum = val;
                break;
	    default:
		printf("error");
		break;
	}
	result = strtok(NULL, ".");//get next token
	val=0;//reset val to 0 for next number
    }
    strcpy(address->nickName,name);//copy in nickname to address data structure
}
//Takes in a file pointer, array of address data structres and the size of said array. Prints all addressess in address data structure array.
void  printAll(FILE* fp, address_t* addresses,int size){
    int i;
    fp = fopen("output.txt" , "a"); //Open and create if it does not exist "output.txt" for apending.
    fprintf(fp,"IP Address    Nickname\n\n");
    for(i=0;i<size;i++){//Go through address array a print all ipaddresses and nicknames
	fprintf(fp,"%d.%d.%d.%d    %s\n",addresses[i].firstNum,addresses[i].secondNum,addresses[i].thirdNum,addresses[i].fourthNum,addresses[i].nickName);
    }
    fclose(fp);//Close file "output.txt"
}
//Takes in a file pointer, array of address data structres and the size of said array. Prints all local machine pairs and calls method to print all addressess in address data structure array.
void printResults(FILE* fp, address_t* addresses,int size){
    int i,j;
    fp = fopen("output.txt" , "a");//Open and create if it does not exist "output.txt" for apending.
    for(i=0;i<size;i++){//nested for loop checks all possible pairs for if they are a local machine pair and if both are already 
	for(j=i+1;j<size;j++){
	    if(addresses[i].firstNum == addresses[j].firstNum && addresses[i].secondNum == addresses[j].secondNum){//Print out message if they are a local machine pair
		fprintf(fp,"Machines %s and %s are on the same local network\n\n", addresses[i].nickName, addresses[j].nickName);
	    }
	}
    }
    fclose(fp);//Close "output.txt"
    printAll(fp,addresses,size);//call method to print all ipaddresses and nicknames
}
int main(){

    char ip[25];//array to hold ip's to break apart
    char name[20];//array to hold nickname
    FILE* fp;//file pointer for whole program
    int i =0;
    address_t myAddress[100];//create address_t array of size 100
    fp = fopen("ipaddresses.txt" , "r");//open "ipaddresses.txt" for reading
    fscanf(fp,"%s %s",ip,name);//get first line of "ipaddresses.txt"
    while(strcmp(ip,"0.0.0.0") != 0){//keep reading lines of "ipaddresses.txt" untill sentinal line of "0.0.0.0"
	breakApart(&myAddress[i],ip,name);//break apart into ints and add to address array ipaddress. add to address array nickname
        i++;
	fscanf(fp,"%s %s",ip,name);//read in  next line of "ipaddresses.txt"
    }
    fclose(fp);//close "ipaddresses.txt"
    printResults(fp,myAddress,i);//Print results of reading in "ipaddresses.txt"
    return(0);
}
