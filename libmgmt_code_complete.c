#include<stdio.h>
#include <time.h>
#define MAX_SIZE_USER_NAME 30
#define MAX_SIZE_PASSWORD  20
#include<stdlib.h>
#include<string.h>
#include<conio.h>

void add_books();
void search_books();
void delete_books();
void view_books();
void edit_books();
void delete_account();
void return_books();
void issue_books();
void view_issue();
void search_menu();
void search_author();
void search_category();
void create_account();

int  IsLeapYear(int year)
{
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}
typedef struct
{
    int yyyy;
    int mm;
    int dd;
} Date;


Date duedate;

// returns 1 if given date is valid.
int isValidDate(Date *validDate)
{
    //check range of year,month and day
    if (validDate->yyyy > 9999 ||
            validDate->yyyy < 1000)
        return 0;
    if (validDate->mm < 1 || validDate->mm > 12)
        return 0;
    if (validDate->dd < 1 || validDate->dd > 31)
        return 0;

    //Handle feb days in leap year
    if (validDate->mm == 2)
    {
        if (IsLeapYear(validDate->yyyy))
            return (validDate->dd <= 29);
        else
            return (validDate->dd <= 28);
    }

    //handle months which has only 30 days
    if (validDate->mm == 4 || validDate->mm == 6 ||
            validDate->mm == 9 || validDate->mm == 11)
        return (validDate->dd <= 30);

    return 1;
}


struct books
{
    int books_id; // declare the integer data type
    char bookName[50];// declare the character data type
    char authorName[50];// declare the character data type
    int total_copy;
    int available;
    int book_status;// 1=active 0=inactive
    char category[30];
    int edition;
};

struct books_issue
{
    int books_id; // declare the integer data type
    char studentID[50];// declare the character data type
    Date Issue_date;
    Date return_date;
};


struct person
{
    char username[MAX_SIZE_USER_NAME];
    char password[MAX_SIZE_PASSWORD];
    int type_account;
    int status;
};

void printMessageCenter(const char* message)
{
    int len =0;
    int pos = 0;

    //calculate how many space need to print
    len = (78 - strlen(message))/2;
    printf("\t\t\t");
    for(pos =0 ; pos < len ; pos++)
    {
        //print space
        printf(" ");
    }
    //print message
    printf("%s",message);

}

void headMessage(const char *message)
{
    system("cls");
    printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############      Library management System Project in C       ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printMessageCenter(message);
    printf("\n\t\t\t----------------------------------------------------------------------------");

}

void create_account()
{
    FILE *outfile;

    headMessage("Create Account");
    struct person inp[50];
    int i=0;

    // open file for writing
    outfile = fopen ("account.txt", "a");
    if (outfile == NULL)
    {
        fprintf(stderr, "\n\n\n\t\t\t\tError opening file\n");
        exit (1);
    }

    printf("\n\n\n\t\t\t\tUsername:");
    scanf("%s",inp[i].username);

    printf("\n\t\t\t\tPassword:");
    scanf("%s",inp[i].password);

    int validaccount = 1;

    while (validaccount)
    {
        printf("\n\t\t\t\tSign Up as \n\t\t\t\t1. Librarian\n\t\t\t\t2. Student\n\t\t\t\t");
        scanf("%d",&inp[i].type_account);

        if((inp[i].type_account<1) || (inp[i].type_account>2))
        {
            printf("\n\t\t\t\tEnter valid account type!");
        }
        else
        {
            inp[i].status = 1;
            // write struct to file

            fwrite (&(inp[i]), sizeof(struct person), 1, outfile);
            if(fwrite != 0)
                printf("\n\t\t\t\tcontents to file written successfully !\n");
            else
                printf("\n\t\t\t\terror writing file !\n");
            validaccount = 0;
        }
    }

    fclose (outfile);

    i=i+1;
    getch();
    system("cls");
}

void delete_account()
{
    headMessage("CLOSE ACCOUNT");
    FILE *infile;
    struct person inp[50];
    struct person out[50];
    char username[30];
    int check_user;
    int i=0;
if (infile == NULL)
    {
        fprintf(stderr, "\n\n\n\t\t\t\tError opening file\n");
        exit (1);
    }

printf ("\n\n\n\t\t\t\tEnter Username for Closing account:  ");
scanf("%s",username);

// Open person.dat for reading
infile = fopen ("account.txt", "r+");
int found =0;

while(fread(&(inp[i]), sizeof(struct person), 1, infile))
{
    out[i]=inp[i];
	check_user = strcmpi(username,inp[i].username);
	if(inp[i].status)
    {
    	if(!check_user)
	{	printf("\n\n\t\t\t\t User Found !");
        found = 1;
		printf ("\n\t\t\t\tUser Name = %s \n",inp[i].username);
		printf ("\n\t\t\t\tType of Account = %d \n",inp[i].type_account);

        out[i].status = 0;
        //fseek(infile,i*sizeof(struct person),SEEK_SET);
        //fwrite(&inp,sizeof(struct person),1,infile);
        break;
	}
	}
	i++;
}
fclose(infile);
if(!found)
    printf("\n\n\t\t\t\tUser Not Found");
else
{
    infile=fopen("account.txt","w+");
    fwrite(&out,sizeof(struct person),i,infile);
}
getch();
system("cls");

}

void menu_librarian()
{
    int choice = 0;
    do
    {
        headMessage("LIBRARIAN MAIN MENU");
        printf("\n\n\n\t\t\t1.Add Book");
        printf("\n\t\t\t2.Search Book");
        printf("\n\t\t\t3.View Books");
        printf("\n\t\t\t4.Edit Book");
        printf("\n\t\t\t5.Delete Book");
        printf("\n\t\t\t6.Issue Book");
        printf("\n\t\t\t7.Return Book");
        printf("\n\t\t\t8.View Issued Books");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");

        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            add_books();
            break;
        case 2:
            search_menu();
            break;
        case 3:
            view_books();
            break;
        case 4:
            edit_books();
            break;
        case 5:
            delete_books();
            break;
        case 6:
            issue_books();
            break;
        case 7:
            return_books();
            break;
        case 8:
            view_issue();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
            //exit(1);
            getch();
            continue;
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
            getch();
        }                                            //Switch Ended
    }
    while(choice!=0);                                        //Loop Ended
getch();
}

void menu_student()
{
    int choice = 0;
    do
    {
        headMessage("STUDENT MAIN MENU");
        printf("\n\n\n\t\t\t1.Search Books");
        printf("\n\t\t\t2.View Books");

        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");

        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            search_menu();
            break;
        case 2:
            view_books();
            break;

        case 0:
            printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
            //exit(1);
            getch();
            continue;
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
            getch();
        }                                            //Switch Ended
    }
    while(choice!=0);                                        //Loop Ended

}

void acc_login()
{
    FILE *infile;
    char login_username[30];
    char login_password[20];

    int pass_check,user_check;
    headMessage("ACCOUNT LOGIN");
    struct person inp[50];
    int c=0,i=0;

    infile = fopen ("account.txt", "r");
    if (infile == NULL)
    {
        fprintf(stderr, "\n\n\n\t\t\t\tError opening file\n");
        exit (1);
    }

    printf("\n\n\n\t\t\t\tUsername:");
    scanf("%s",login_username);

    printf("\n\t\t\t\tPassword:");
    scanf("%s",login_password);

    while(fread(&(inp[i]), sizeof(struct person), 1, infile))
    	{
	//printf("%s,%s",inp[i].username,inp[i].password);
	user_check=strcmp(inp[i].username,login_username);
	pass_check=strcmp(inp[i].password,login_password);
	if((!user_check)&&(!pass_check)&&(inp[i].status))
	{
	c=1;
	printf("\n\n\t\t\t\tLogin successful !");
	time_t t;   // not a primitive datatype
    time(&t);
    printf("\n\t\t\t\tYou are logging in at (date and time): %s", ctime(&t));
    getch();
	if(inp[i].type_account==1)
	{
	 menu_librarian();
	 }
	if(inp[i].type_account==2)
	{
	 menu_student();
	 }
	}
	i++;
	}

    if(!c)
    {
    printf("\n\n\t\t\t\tLogin failed ,Retry !");
    getch();
    }
	fclose(infile);
}

void acc_menu()
{
    int choice = 0;
    do
    {
        headMessage("LOGIN ACCESS MENU");
        printf("\n\n\n\t\t\t1.Login");
        printf("\n\t\t\t2.Sign-Up");
        printf("\n\t\t\t3.Close Account");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");

        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            acc_login();
            break;
        case 2:
            create_account();
            break;
        case 3:
            delete_account();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tThank you!!!\n");
            time_t t;   // not a primitive datatype
            time(&t);
            printf("\n\t\t\t\tYou are logging out at (date and time): %s", ctime(&t));
            getch();
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
            getch();
        }                                            //Switch Ended
    }
    while(choice!=0);                                        //Loop Ended

}

void search_menu()
{
    int choice = 0;
    do
    {
        headMessage("SEARCH BOOKS MENU");
        printf("\n\n\n\t\t\t1.Search by Book Name");
        printf("\n\t\t\t2.Search by Author Name");
        printf("\n\t\t\t3.Search by Category");
        printf("\n\t\t\t0.Back to Main Menu");
        printf("\n\n\n\t\t\tEnter choice => ");

        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            search_books();
            break;
        case 2:
            search_author();
            break;
        case 3:
            search_category();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tThank you!!!\n");
            getch();
            continue;
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
            getch();
        }                                            //Switch Ended
    }
    while(choice!=0);                                        //Loop Ended

}


void add_books()
{
    FILE *outfile;
    int i=0;
    int num;
    headMessage("ADD BOOKS: ");
    struct books Book[50];
    char temp;
    // open file for writing
    outfile = fopen ("book.txt", "a");
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }
    //fseek(outfile,i*sizeof(struct books),SEEK_SET);
    do{
    printf("\n\n\n\t\t\t\tBook ID NO  (Integers Only)  = ");
    scanf("%d",&(Book[i]).books_id);
    num = (Book[i].books_id>0)&&(Book[i].books_id<100001);
    //printf("\n%d",num);

    if(!num)
        {
            printf("\n\t\t\t\tEnter valid input");
            //scanf("%c",&temp);
            fflush(stdin);
        }
    }
    while(!num);

    printf("\t\t\t\tBook Name  = ");
    scanf("%c",&temp);
    scanf("%[^\n]",Book[i].bookName);
    //scanf("%s",Book[i].bookName);

    printf("\t\t\t\tAuthor Name  = ");
    scanf("%c",&temp);
    scanf("%[^\n]",Book[i].authorName);

    do{
    printf("\t\t\t\tTotal number of copies  (Integers Only) = ");
    scanf("%d",&(Book[i]).total_copy);
    num = (Book[i].total_copy>0)&&(Book[i].total_copy<101);
    printf("\n%d",num);

    if(!num)
        {
            printf("\n\t\t\t\tEnter valid input");
            //scanf("%c",&temp);
            fflush(stdin);
        }
    }
    while(!num);

    Book[i].available = Book[i].total_copy;
    Book[i].book_status=1;

    printf("\t\t\t\tCategory  = ");
    scanf("%c",&temp);
    scanf("%[^\n]",Book[i].category);

    do{
    printf("\t\t\t\tEdition  (Integers Only) = ");
    scanf("%d",&(Book[i]).edition);
    num = (Book[i].edition>0)&&(Book[i].edition<100);
    printf("\n%d",num);

    if(!num)
        {
            printf("\n\t\t\t\tEnter valid input");
            //scanf("%c",&temp);
            fflush(stdin);
        }
    }
    while(!num);

     // write structures to file
    fwrite (&(Book[i]), sizeof(struct books), 1, outfile);

    if(fwrite != 0)
        printf("\n\t\t\t\tcontents to file written successfully !\n");
    else
        printf("\n\t\t\t\terror writing file !\n");
    fclose (outfile);
    i++;
    getch();
    system("cls");
}

void view_books()
{
headMessage("VIEW BOOKS");
FILE *infile;
struct books Book;

infile = fopen ("book.txt", "r");

int i=1;
if (infile == NULL)
    {
        fprintf(stderr, "\n\n\n\t\t\tError opening file\n");
        exit (1);
    }

//fseek(infile,0,2);
//size=ftell(infile);
//printf("\n %d",size);
printf("\n\n");
while(fread(&Book, sizeof(struct books), 1, infile))
{
    if(Book.book_status)
    {
        printf("\n\t\t\tSerial no. %d",i);
        printf ("\n\t\t\t\tBook ID = %d ",Book.books_id);
		printf ("\n\t\t\t\tBook Name = %s ",Book.bookName);
		printf ("\n\t\t\t\tAuthor Name = %s ",Book.authorName);
		printf ("\n\t\t\t\tCategory = %s ",Book.category);
		printf ("\n\t\t\t\tEdition = %d ",Book.edition);
		printf ("\n\t\t\t\tTotal copies = %d ",Book.total_copy);
		printf ("\n\t\t\t\tAvailable Copies = %d ",Book.available);
        printf("\n");
        i++;
    }
}
fclose(infile);
getch();
system("cls");

}


void view_issue()
{
headMessage("VIEW ISSUED BOOKS");
FILE *infile;
struct books_issue issue;


infile = fopen ("issue.txt", "r");
int i=1;
if (infile == NULL)
    {
        fprintf(stderr, "\n\n\n\t\t\t\tError opening file\n");
        exit (1);
    }

//fseek(infile,0,2);
//size=ftell(infile);
//printf("\n %d",size);
printf("\n\n");
while(fread(&issue, sizeof(struct books_issue), 1, infile))
{
        printf("\n\t\t\tSerial no. %d",i);
        printf ("\n\t\t\t\tBook ID = %d ",issue.books_id);
		printf ("\n\t\t\t\tStudent ID = %s ",issue.studentID);

		printf ("\n\t\t\t\tIssued Date = %d/%d/%d ",issue.Issue_date.dd,issue.Issue_date.mm,issue.Issue_date.yyyy);
		printf ("\n\t\t\t\tReturn Date = %d/%d/%d ",issue.return_date.dd,issue.return_date.mm,issue.return_date.yyyy);
        i++;
        printf("\n");
		}
fclose(infile);
getch();
system("cls");

}
void search_books()
{
headMessage("SEARCH BOOKS");
FILE *infile;
struct books Book;
char userbook[50];
int check_book;
char temp;
if (infile == NULL)
    {
        fprintf(stderr, "\n\n\n\t\t\t\tError opening file\n");
        exit (1);
    }


printf ("\n\n\n\t\t\t\tEnter Book Name for searching: ");
scanf("%c",&temp);
scanf("%[^\n]",userbook);
//scanf("%s",userbook);

// Open person.dat for reading
infile = fopen ("book.txt", "r");
int found = 0;
while(fread(&Book, sizeof(struct books), 1, infile))
{
	//check_book = strcmpi(userbook,Book.bookName);
	check_book = strstr(Book.bookName,userbook);
	if(Book.book_status)
    {
        if(check_book!=NULL)
        {	printf("\n\n\n\t\t\t\t Book Found !");
            printf ("\n\n\t\t\t\tBook ID = %d ",Book.books_id);
            printf ("\n\t\t\t\tBook Name = %s ",Book.bookName);
            printf ("\n\t\t\t\tAuthor Name = %s ",Book.authorName);
            printf ("\n\t\t\t\tCategory = %s ",Book.category);
            printf ("\n\t\t\t\tEdition = %d ",Book.edition);
            printf ("\n\t\t\t\tTotal copies = %d ",Book.total_copy);
            printf ("\n\t\t\t\tAvailable Copies = %d ",Book.available);
            found = 1;
        }
	}
}
fclose(infile);
if(!found)  printf("\n\n\t\t\t\tBook Not Found");
getch();
system("cls");

}

void search_author()
{
headMessage("SEARCH BOOKS");
FILE *infile;
struct books Book;
char userbook[50];
int check_book;
char temp;
if (infile == NULL)
    {
        fprintf(stderr, "\n\n\n\t\t\t\tError opening file\n");
        exit (1);
    }


printf ("\n\n\n\t\t\t\tEnter Author Name for searching: ");
scanf("%c",&temp);
scanf("%[^\n]",userbook);
//scanf("%s",userbook);

// Open person.dat for reading
infile = fopen ("book.txt", "r");
int found = 0;
while(fread(&Book, sizeof(struct books), 1, infile))
{
	//check_book = strcmpi(userbook,Book.bookName);
	check_book = strstr(Book.authorName,userbook);
	if(Book.book_status)
    {
        if(check_book!=NULL)
        {	printf("\n\n\n\t\t\t\t Book Found !");
            printf ("\n\n\t\t\t\tBook ID = %d ",Book.books_id);
            printf ("\n\t\t\t\tBook Name = %s ",Book.bookName);
            printf ("\n\t\t\t\tAuthor Name = %s ",Book.authorName);
            printf ("\n\t\t\t\tCategory = %s ",Book.category);
            printf ("\n\t\t\t\tEdition = %d ",Book.edition);
            printf ("\n\t\t\t\tTotal copies = %d ",Book.total_copy);
            printf ("\n\t\t\t\tAvailable Copies = %d ",Book.available);
            found = 1;
        }
	}
}
fclose(infile);
if(!found)  printf("\n\n\t\t\t\tBook Not Found");
getch();
system("cls");

}

void search_category()
{
headMessage("SEARCH BOOKS");
FILE *infile;
struct books Book;
char userbook[50];
int check_book;
char temp;
if (infile == NULL)
    {
        fprintf(stderr, "\n\n\n\t\t\t\tError opening file\n");
        exit (1);
    }


printf ("\n\n\n\t\t\t\tEnter category for searching: ");
scanf("%c",&temp);
scanf("%[^\n]",userbook);
//scanf("%s",userbook);

// Open person.dat for reading
infile = fopen ("book.txt", "r");
int found = 0;
while(fread(&Book, sizeof(struct books), 1, infile))
{
	//check_book = strcmpi(userbook,Book.bookName);
	check_book = strstr(Book.category,userbook);
	if(Book.book_status)
    {
        if(check_book!=NULL)
        {	printf("\n\n\n\t\t\t\t Book Found !");
            printf ("\n\n\t\t\t\tBook ID = %d ",Book.books_id);
            printf ("\n\t\t\t\tBook Name = %s ",Book.bookName);
            printf ("\n\t\t\t\tAuthor Name = %s ",Book.authorName);
            printf ("\n\t\t\t\tCategory = %s ",Book.category);
            printf ("\n\t\t\t\tEdition = %d ",Book.edition);
            printf ("\n\t\t\t\tTotal copies = %d ",Book.total_copy);
            printf ("\n\t\t\t\tAvailable Copies = %d ",Book.available);
            found = 1;
        }
	}
}
fclose(infile);
if(!found)  printf("\n\n\t\t\t\tBook Not Found");
getch();
system("cls");

}



void issue_books()
{   headMessage("ISSUE BOOK");
    struct books Book[50];
    struct books out[50];
    struct books_issue issue;
    FILE *booksfile,*issuefile,*outfile;
    int check_book;
    int i=0;
    char temp;
    char userbook[50];
    booksfile = fopen("book.txt", "r+");
    printf ("\n\n\n\t\t\t\tEnter Book Name for Issuing: ");
    //scanf("%s",userbook);
    scanf("%c",&temp);
    scanf("%[^\n]",userbook);
    int found = 0;
    int status;
    int j=0;
    while(fread(&(Book[i]), sizeof(struct books), 1, booksfile))
    {
	check_book = strcmpi(userbook,Book[i].bookName);
    out[i]=Book[i];
	if(Book[i].book_status && (Book[i].available>0) && (!check_book) && (!found) ) {
        found = 1;
        out[i].available--;
		//Book.available--;
		//fseek(booksfile,i*sizeof(struct books),SEEK_SET);
        //fwrite(&Book,sizeof(struct books),1,booksfile);

        issuefile = fopen("issue.txt", "a+");
        issue.books_id=Book[i].books_id;
        j++;
        printf("\n\t\t\t\tStudent ID  = ");
        scanf("%s",issue.studentID);
        do
        {
        printf("\t\t\t\tIssue Date(dd/mm/yyyy)  = ");
        scanf("%d/%d/%d",&issue.Issue_date.dd,&issue.Issue_date.mm,&issue.Issue_date.yyyy);
        status = isValidDate(&issue.Issue_date);
        if (!status)
        {
            printf("\n\t\t\tPlease enter a valid date.\n");
        }
        }
        while(!status);
        issue.return_date.dd=0;
        issue.return_date.mm=0;
        issue.return_date.yyyy=0;

        if((issue.Issue_date.mm==1)||(issue.Issue_date.mm==3)||(issue.Issue_date.mm==5)||(issue.Issue_date.mm==7)||(issue.Issue_date.mm==8)||(issue.Issue_date.mm==10)||(issue.Issue_date.mm==12))
        {
            if(issue.Issue_date.dd + 20>=32)
            {
                if(issue.Issue_date.mm==12)
                {
                    duedate.dd = 20-(31-(issue.Issue_date.dd));
                    duedate.mm =  1;
                    duedate.yyyy = issue.Issue_date.yyyy + 1;
                }
                else
                {
                    duedate.dd = 20-(31-(issue.Issue_date.dd));
                    duedate.mm = issue.Issue_date.mm + 1;
                    duedate.yyyy = issue.Issue_date.yyyy ;

                }
            }
            if(((issue.Issue_date.dd + 20)<32))
            {
                duedate.dd = issue.Issue_date.dd + 20;
                duedate.mm = issue.Issue_date.mm ;
                duedate.yyyy = issue.Issue_date.yyyy ;
            }
        }
        if((issue.Issue_date.mm==4)||(issue.Issue_date.mm==6)||(issue.Issue_date.mm==9)||(issue.Issue_date.mm==11))
        {
            if((issue.Issue_date.dd + 20)<31)
            {
                duedate.dd = issue.Issue_date.dd + 20;
                duedate.mm = issue.Issue_date.mm ;
                duedate.yyyy = issue.Issue_date.yyyy ;
            }
            if((issue.Issue_date.dd + 20)>=31)
            {
                duedate.dd = 20-(30-(issue.Issue_date.dd));
                duedate.mm = issue.Issue_date.mm + 1;
                duedate.yyyy = issue.Issue_date.yyyy ;
            }

        }
        if(issue.Issue_date.mm == 2)
        {
            if((issue.Issue_date.dd + 20)<29)
            {
                duedate.dd = issue.Issue_date.dd + 20;
                duedate.mm = issue.Issue_date.mm ;
                duedate.yyyy = issue.Issue_date.yyyy ;
            }
            if((issue.Issue_date.dd + 20)>=29)
            {
                duedate.dd = 20-(28-(issue.Issue_date.dd));
                duedate.mm = issue.Issue_date.mm + 1;
                duedate.yyyy = issue.Issue_date.yyyy ;
            }
        }

        printf("\t\t\t\tDue Date(dd/mm/yyyy)  = %d/%d/%d",duedate.dd,duedate.mm,duedate.yyyy);
        getch();
        fwrite(&issue,sizeof(struct books_issue),1,issuefile);
        fclose(issuefile);

	}
	i++;
	}

fclose(booksfile);
if(found)
{
    outfile=fopen("book.txt","w+");
    fwrite(&out,sizeof(struct books),i,outfile);
    fclose(outfile);
}
else
    printf("\n\n\t\t\t\tBook Not Found");

getch();
}

void return_books()
{   headMessage("RETURN BOOK");
    struct books Book[50];
    struct books_issue issue[50];
    struct books out_Book[50];
    struct books_issue out_issue[50];
    FILE *booksfile,*issuefile,*out_booksfile,*out_issuefile;
    int check_book,check_issue1,check_issue2;
    int i=0;
    int k=0;
    int status;
    int book_id,j;
    char student_id[50];
    int found =0;
    issuefile = fopen("issue.txt", "r+");
    printf ("\n\n\n\t\t\t\tEnter Student ID: ");
    scanf("%s",student_id);
    printf ("\t\t\t\tEnter Book ID  (Integers Only): ");
    scanf("%d",&book_id);

    while(fread(&(issue[i]), sizeof(struct books_issue), 1, issuefile))
    {
    out_issue[i]=issue[i];
	check_issue1 = strcmpi(student_id,issue[i].studentID);
	check_issue2 = book_id-issue[i].books_id;
    if((!check_issue1)&&(!check_issue2)&&(!out_issue[i].return_date.dd))
	{
	    found = 1;
	    do
        {
        printf("\n\t\t\t\tReturn Date(dd/mm/yyyy)  = ");
        scanf("%d/%d/%d",&out_issue[i].return_date.dd,&out_issue[i].return_date.mm,&out_issue[i].return_date.yyyy);
        status = isValidDate(&out_issue[i].return_date);
        if (!status)
        {
            printf("\n\t\t\tPlease enter a valid date.\n");
        }
        }
        while(!status);
        printf("\t\t\t\tDue Date(dd/mm/yyyy)  = %d/%d/%d",duedate.dd,duedate.mm,duedate.yyyy);
        if(out_issue[i].return_date.dd==duedate.dd)    printf("\n\n\t\t\t\tReturned on time!");
        if(out_issue[i].return_date.dd!=duedate.dd)    printf("\n\n\t\t\t\tPassed the due date!");

        //fseek(issuefile,i*sizeof(struct books_issue),SEEK_SET);
        //fwrite(&issue,sizeof(struct books_issue),1,issuefile);

        booksfile = fopen("book.txt", "r+");
        j=0;
        while(fread(&(Book[j]), sizeof(struct books), 1, booksfile))
		{
		    out_Book[j]=Book[j];
            check_book= book_id-Book[j].books_id;

            if(!check_book)
		    {
		        out_Book[j].available++;
                //fseek(booksfile,j*sizeof(struct books),SEEK_SET);
                //fwrite(&Book,sizeof(struct books),1,booksfile);
		    }
		    j++;
		}
		fclose(booksfile);
	}
	i++;
	k++;
	}
fclose(issuefile);
if(found)
{
    out_booksfile=fopen("book.txt","w+");
    fwrite(&out_Book,sizeof(struct books),j,out_booksfile);
    fclose(out_booksfile);

    out_issuefile = fopen("issue.txt","w+");
    fwrite(&out_issue,sizeof(struct books_issue),i,out_issuefile);
    fclose(out_issuefile);
}
else
    printf("\n\n\t\t\t\tBook Not Issued to Student");
getch();
}

void edit_books()
{   headMessage("EDIT BOOK RECORD");
    FILE *editfile;
    struct books Book[50];
    struct books out[50];
    char userbook[50];
    int check_book;
    int i=0;
    char temp;
    char temp_2;
    if (editfile == NULL)
    {
        fprintf(stderr, "\n\n\n\t\t\t\tError opening file\n");
        exit (1);
    }

    printf ("\n\n\n\t\t\t\tEnter Book Name for Editing: ");
    scanf("%c",&temp);
    scanf("%[^\n]",userbook);
    //scanf("%s",userbook);

// Open person.dat for reading
    editfile = fopen ("book.txt", "r+");
    int flag = 1;
    int found = 0;
    int num;

while(fread(&(Book[i]), sizeof(struct books), 1, editfile))
{
    out[i]=Book[i];
	check_book = strcmpi(userbook,Book[i].bookName);
	if( (Book[i].book_status) && (flag) && (!check_book)  )
    {
        found = 1;
		printf ("\n\t\t\t\tBook Found !");
		printf ("\n\n\t\t\t\tBook ID = %d ",Book[i].books_id);
		printf ("\n\t\t\t\tBook Name = %s ",Book[i].bookName);
		printf ("\n\t\t\t\tAuthor Name = %s ",Book[i].authorName);
		printf ("\n\t\t\t\tCategory = %s ",Book[i].category);
		printf ("\n\t\t\t\tEdition = %d ",Book[i].edition);
		printf ("\n\t\t\t\tTotal copies = %d ",Book[i].total_copy);
		printf ("\n\t\t\t\tAvailable Copies = %d ",Book[i].available);

        int edit_choice;
        while(flag)
        {
            printf("\n\n\t\t\t\t1.Update Category");
            printf("\n\t\t\t\t2.Update Edition");
            printf("\n\t\t\t\t3.Exit");
            printf("\n\n\t\t\t\tEnter choice:");
            scanf("%d",&edit_choice);

            switch(edit_choice)
            {
            case 1:
                printf("\n\t\t\t\tEnter new category:  ");
                scanf("%c",&temp_2);
                scanf("%[^\n]",out[i].category);
                //fseek(editfile,i*sizeof(struct books),SEEK_SET);
                //fwrite(&(Book[i]),sizeof(struct books),1,editfile);
                break;
            case 2:

                do{
                printf("\n\t\t\t\tEnter new edition  (Integers only) :  ");
                scanf("%d",&out[i].edition);
                num = (out[i].edition>0)&&(out[i].edition<100);
                printf("\n%d",num);

                if(!num)
                {
                    printf("\n\t\t\t\tEnter valid input");
            //scanf("%c",&temp);
                    fflush(stdin);
                }
                }
                while(!num);
                printf("serial number: %d", i);
                //fseek(editfile,i*sizeof(struct books),SEEK_SET);
                //fwrite(&(Book[i]),sizeof(struct books),1,editfile);
                break;
            case 3:
                flag=0;

                break;
            default:
                printf("\n\t\t\t\tEnter 1 /2 /3");
            }
        }
	}
	i++;
	}

    fclose(editfile);
    if(found)
    {
        editfile=fopen("book.txt","w+");
        fwrite(&out,sizeof(struct books),i,editfile);
        fclose(editfile);
    }
    else
        printf("\n\n\t\t\t\tBook Not Found");
    getch();
    system("cls");

}



void delete_books()
{   headMessage("DELETE BOOK");
    FILE *infile;
    struct books Book[50];
    struct books out[50];
    char userbook[50];
    int check_book;
    int i=0;
    char temp;
if (infile == NULL)
    {
        fprintf(stderr, "\n\n\n\t\t\t\tError opening file\n");
        exit (1);
    }


printf ("\n\n\n\t\t\tEnter Book Name for Deleting: ");
//scanf("%s",userbook);
scanf("%c",&temp);
scanf("%[^\n]",userbook);

int found = 0;
// Open person.dat for reading
infile = fopen ("book.txt", "r+");
while(fread(&(Book[i]), sizeof(struct books), 1, infile))
{
    out[i]=Book[i];
	check_book = strcmpi(userbook,Book[i].bookName);
	if ((Book[i].book_status) && (!check_book) )
	{	printf("\n\n\t\t\t\tBook Found !");
        found = 1;
		printf ("\n\n\t\t\t\tBook ID = %d ",Book[i].books_id);
		printf ("\n\t\t\t\tBook Name = %s ",Book[i].bookName);
		printf ("\n\t\t\t\tAuthor Name = %s ",Book[i].authorName);
		printf ("\n\t\t\t\tCategory = %s ",Book[i].category);
		printf ("\n\t\t\t\tEdition = %d ",Book[i].edition);
		printf ("\n\t\t\t\tTotal copies = %d ",Book[i].total_copy);
		printf ("\n\t\t\t\tAvailable Copies = %d ",Book[i].available);
        out[i].book_status=0;

	}
	i++;
}
fclose(infile);
if(found)
{infile=fopen("book.txt","w+");
fwrite(&out,sizeof(struct books),i,infile);
fclose(infile);
}
else
    printf("\n\n\t\t\t\tBook Not Found");
getch();
system("cls");

}

int main()
{
acc_menu();

return 0;
}
