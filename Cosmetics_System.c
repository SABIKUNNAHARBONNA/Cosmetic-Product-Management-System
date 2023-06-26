#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>

struct item
{
	char cosmeticproductname[40],cosmeticproductcomp[40],c;
	int cosmeticproductid;
	int cosmeticprice;
	int cosmeticquantity;
}st;

void gotoxy(short x, short y)
{
	COORD pos ={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void menu(){
    system("color 17");
    int choice;
	system("cls");

    printf("\n======== Welcome to Cosmetic Product Management System =========");
	printf("                                                                                          ");

	printf("\n\t\tEnter 1: Add Cosmetics");
	printf("\n\t\tEnter 2: Delete Cosmetics");
	printf("\n\t\tEnter 3: View Cosmetics");
	printf("\n\t\tEnter 4: Edit Cosmetics");
	printf("\n\t\tEnter 5: Exit!");

	printf("\n\n\t\tEnter your choice[1-5]:");
	scanf("%i", &choice);

	system("cls");

	switch(choice)
	{
		case 1:
			add_item();
			break;
		case 2:
			deleteproduct();
			break;

		case 3:
		    read_item();
			break;
		case 4:
			edit_item();
			break;
		case 5:
		printf("System Exit");
		exit(0);
		break;


		default:
		printf("Invalid Choice! System Exit\n");
			getch();
	}
}

void add_item()
{
	int cn=5757;
	int ind, val;
	char c;
	int a=0;


	FILE *fp;

		system("cls");
		printf("Company code is %d\n", cn);
		printf("============ Enter Product Details ============");
		int ID;

		fp = fopen("ViewStorage.dat","a+");

		if((fp = fopen("ViewStorage.dat","a+"))!=NULL)
		{
			I:
			printf("\nCosmetic Code\t :");
			scanf("%i",&ID);
			while(fscanf(fp,"%s %s %i %i %i", st.cosmeticproductname, st.cosmeticproductcomp, &st.cosmeticprice, &st.cosmeticproductid,&st.cosmeticquantity)!=EOF)
			{

				if(ID == st.cosmeticproductid)
				{
					printf("\n\tThe Cosmetic Code already exists.Kindly enter a different Cosmetic Code.\n");
					goto I;
				}
			}
			st.cosmeticproductid = ID;
		}
		else//runs if sfile is empty
		{
			printf("\nCosmetic Code\t :");
			scanf("%i",&st.cosmeticproductid);
		}

	//add Cosmetic Name
		do
		{
			fflush(stdin);
			printf("\nCosmetic Name\t :");
			gets(st.cosmeticproductname); // get input string
			st.cosmeticproductname[0]=toupper(st.cosmeticproductname[0]);
			//iterate for every character in string
			for (ind=0; ind<strlen(st.cosmeticproductname); ++ind)
			{	//check if character is val or not
				if(isalpha(st.cosmeticproductname[ind]))
					val = 1;
				else
				{
					val = 0;
					break;
				}
			}
			if (!val)
			{
				printf("\n Name contains invalid characters. Please 'Enter' the Cosmetic Name again");
				getch();


			}
		}while(!val);	//while end here


		//Cosmetic Company
        do{
			char cosmeticproductcomp[40];
			fflush(stdin);
			printf("\nCosmetic Company\t :");
			gets(st.cosmeticproductcomp); // get input string
			st.cosmeticproductcomp[0]=toupper(st.cosmeticproductcomp[0]);
			//iterate for every character in string
			for (ind=0; ind<strlen(st.cosmeticproductcomp); ++ind)
			{	//check if character is val or not
				if(isalpha(st.cosmeticproductcomp[ind]))
					val = 1;
				else
				{
					val = 0;
					break;
				}
			}
			if (!val)
			{
				printf("\n Name contains invalid character. Please 'Enter' the Cosmetic Company again");
				getch();


			}
		}while(!val);

		//cosmeticproductid

				printf("\nCosmetic Price\t:");
				scanf("%i",&st.cosmeticprice);



				printf("\nCosmetic Quantity :");
				scanf("%i",&st.cosmeticquantity);



		fp=fopen("ViewStorage.dat","a");
		fprintf(fp,"\n%s %s %i %i %i", st.cosmeticproductname, st.cosmeticproductcomp,st.cosmeticprice, st.cosmeticproductid,st.cosmeticquantity);
		fclose(fp);

		printf("\nPress 'Enter' to add more item and any other key to go to main menu");
		char chose = getch();
		if(chose == 13){
            add_item();
		}else{
            menu();
		}
}


void deleteproduct(void)
{
	char target[40];
	int found=0;
	FILE *sfile, *tfile;
	sfile=fopen("ViewStorage.dat","r");
	tfile=fopen("DeletedStorage.dat","w+");
	printf("\n Enter Cosmetic Name: ");
	fflush(stdin);
	scanf("%s",target);
	target[0]=toupper(target[0]);
	while (fscanf(sfile,"%s %s %i %i %i\n",st.cosmeticproductname,st.cosmeticproductcomp, &st.cosmeticprice,&st.cosmeticproductid,&st.cosmeticquantity)!=EOF)
	{
		if(strcmp(target,st.cosmeticproductname)==0)
		{
			found=1;
		}
		else
		{
			fprintf(tfile,"%s %s %i %i %i\n", st.cosmeticproductname,st.cosmeticproductcomp, st.cosmeticprice,st.cosmeticproductid,st.cosmeticquantity);
		}
	}
			if(!found)
			{
				printf("\n Cosmetic Product Record not found");
				getch();

			}
			else
			{
				printf("\n Cosmetic Product Record deleted");
			}
			fclose(sfile);
			fclose(tfile);
			remove("ViewStorage.dat");
			rename("DeletedStorage.dat","ViewStorage.dat");

			printf("\nPress any key to go to Main Menu!");
            if(getch()){
                menu();
            }

}
void read_item()
{
	FILE *f;
	int i, q;

	if((f=fopen("ViewStorage.dat","r"))==NULL)
	{

		gotoxy(10,3);
		printf("NO COSMETIC RECORD found");
		printf("\n\t\tPress any key to go back to Menu.");
		getch();



	}
	else
	{

		gotoxy(0,5);
			for(i=0;i<100;i++)
		{
			printf("-");
		}
		gotoxy(5,6);
		printf("Cosmetic Name");
		gotoxy(25,6);
		printf("Cosmetic Price");
		gotoxy(40,6);
		printf("Cosmetic Company");
		gotoxy(60,6);
		printf("Cosmetic Code");
		gotoxy(80,6);
		printf("Cosmetic Quantity\n");

		for(i=0;i<100;i++)
		{
			printf("-");
		}
		q=8;
		while(fscanf(f,"%s %s %i %i %i\n", st.cosmeticproductname,st.cosmeticproductcomp, &st.cosmeticprice, &st.cosmeticproductid,&st.cosmeticquantity)!=EOF)
		{
			gotoxy(5,q);
			printf("%s",st.cosmeticproductname);
			gotoxy(25,q);
			printf("%i",st.cosmeticprice);
			gotoxy(40,q);
			printf("%s",st.cosmeticproductcomp);
			gotoxy(60,q);
			printf("%i",st.cosmeticproductid);
			gotoxy(80,q);
			printf("%i",st.cosmeticquantity);

			q++;
		}
		printf("\n");
		for(i=0;i<100;i++)
			printf("-");
	}
	fclose(f);

	printf("\nPress any key to go to Main Menu!");
		if(getch()){
            menu();
        }

}
void edit_item()
{
	int ind, val;
	char target[40];
	FILE *fp, *rp;
	int a=0;
	int id;
	char Edit;
	long int size=sizeof(st);
	if((fp=fopen("ViewStorage.dat","r+"))==NULL)
	{
		printf("NO COSMETIC RECORD ADDED.");

	}
	else
	{
		rp = fopen("DeletedStorage.dat","a");
		system("cls");
		printf("Enter Cosmetic Code:");
		scanf("%i",&id);
		fflush(stdin);
		while(fscanf(fp,"%s %s %i %i %i\n", st.cosmeticproductname,st.cosmeticproductcomp, &st.cosmeticprice, &st.cosmeticproductid,&st.cosmeticquantity)!=EOF)
		{
			if(id==st.cosmeticproductid)
			{

				a=1;
				printf("\n\t*****  Cosmetic Record found  *****");
				printf("\nCosmetic Name\t\t: %s",st.cosmeticproductname);
				printf("\nCosmetic Company\t\t: %s",st.cosmeticproductcomp);
				printf("\nCosmetic Price\t\t\t: %i",st.cosmeticprice);
				printf("\nCosmetic Code\t\t: %i",st.cosmeticproductid);
				printf("\nCosmetic Quantity\t:%i",st.cosmeticquantity);

				printf("\n\n\t*** Cosmetic New Record ***");
			do
				{

					fflush(stdin);
					printf("\nEnter New Cosmetic Name\t\t: ");
					gets(st.cosmeticproductname); // get input string
					st.cosmeticproductname[0]=toupper(st.cosmeticproductname[0]);
					//iterate for every character in string
					for (ind=0; ind<strlen(st.cosmeticproductname); ++ind)
					{	//check if character is val or not
						if(isalpha(st.cosmeticproductname[ind]))
							val = 1;
						else
						{
							val = 0;
							break;
						}
					}
					if (!val)
					{
						printf("\n Name contains invalid characters. Please 'Enter' the name again");
						getch();


					}
				}while(!val);	//while end here


				//Cosmetic Company
				do
				{
					char cosmeticproductcomp[40];
					fflush(stdin);
					printf("\nEnter New Cosmetic Company\t\t:");
					gets(st.cosmeticproductcomp); // get input string
					st.cosmeticproductcomp[0]=toupper(st.cosmeticproductcomp[0]);
					//iterate for every character in string
					for (ind=0; ind<strlen(st.cosmeticproductcomp); ++ind)
					{	//check if character is val or not
						if(isalpha(st.cosmeticproductcomp[ind]))
							val = 1;
						else
						{
							val = 0;
							break;
						}
					}
					if (!val)
					{
						printf("\n Name contains invalid characters. Please 'Enter' the Cosmetic Company again");
						getch();


					}
				}while(!val);


				printf("\nNew Price Taka:");
				scanf("%i",&st.cosmeticprice);


				printf("\nEnter New Cosmetic Code\t\t:");
				scanf("%i",&st.cosmeticproductid);


				printf("\nNew Quantity [1-500]\t:");
				scanf("%i",&st.cosmeticquantity);



				printf("Press 'y' to Edit the existing record or any key to cancel...");
				Edit=getche();
				if(Edit=='y' || Edit=='Y')
				{
					fprintf(rp,"%s %s %i %i %i\n", st.cosmeticproductname, st.cosmeticproductcomp, st.cosmeticprice, st.cosmeticproductid,st.cosmeticquantity);
					fflush(stdin);
					printf("\n\n\t\tYOUR RECORD IS SUCCESSFULLY EDITED!!!");
				}
			}
			else
			{
				fprintf(rp,"%s %s %i %i %i\n", st.cosmeticproductname, st.cosmeticproductcomp, st.cosmeticprice, st.cosmeticproductid,st.cosmeticquantity);
				fflush(stdin);
			}

		}
		if(!a)
		{
			printf("\n\nTHIS COSMETIC PRODUCT DOESN'T EXIST!!!!");
		}
		fclose(rp);
		fclose(fp);
		remove("ViewStorage.dat");
		rename("DeletedStorage.dat","ViewStorage.dat");
		printf("\nPress 'Enter' to add more item and any other key to go to main menu");
		char chose = getch();
		if(chose == 13){
            edit_item();
		}else{
            menu();
		}
	}

}
int main()
{
	menu();
}
