#include<stdio.h>
#include<string.h>

#define MAX 100

struct Book
{
    int id;
    char title[100];
    char author[100];
    int quantity;
};

struct Book b[MAX];
int count = 0;
void saveBook();
void loadBooks();

void AddBook()
{
    if(count>=MAX)
    {
        printf("Library is full\n");
        return;
    }
    printf("Enter Book ID: ");
    scanf("%d", &b[count].id);

    printf("Enter Book Title: ");
    scanf("%[^\n]", b[count].title);

    printf("Enter Author Name: ");
    scanf("%[^\n]", b[count].author);

    printf("Enter Quantity: ");
    scanf("%d", &b[count].quantity);

    count++;
    saveBook();

    printf("Book Added Successfully!\n");
}

void displayBook()
{
    if(count == 0)
    {
        printf("No books available.\n");
        return;
    }

    for(int i = 0; i < count; i++)
    {
        printf("\nBook %d\n", i + 1);
        printf("ID: %d\n", b[i].id);
        printf("Title: %s\n", b[i].title);
        printf("Author: %s\n", b[i].author);
        printf("Quantity: %d\n", b[i].quantity);
    }
}

void searchBook()
{
    int id;

    printf("Enter Book ID to search: ");
    scanf("%d", &id);

    for(int i = 0; i < count; i++)s
    {
        if(b[i].id == id)
        {
            printf("\nBook Found!\n");
            printf("Title: %s\n", b[i].title);
            printf("Author: %s\n", b[i].author);
            printf("Quantity: %d\n", b[i].quantity);
            return;
        }
    }

    printf("Book not found!\n");
}

void IssueBook()
{
    int id;

    printf("Enter Book ID: ");
    scanf("%d", &id);

    for(int i = 0; i < count; i++)
    {
        if(b[i].id == id)
        {
            if(b[i].quantity > 0)
            {
                b[i].quantity--;
                saveBook();
                printf("Book Issued Successfully!\n");
            }
            else
            {
                printf("Book is not available.\n");
            }

            return;
        }
    }

    printf("Book not found!\n");
}

void ReturnBook()
{
    int id;

    printf("Enter Book ID: ");
    scanf("%d", &id);

    for(int i = 0; i < count; i++)
    {
        if(b[i].id == id)
        {
           b[i].quantity++;
           saveBook();
           printf("Book Returned Successfully!\n");
           return;
        }
    }


    printf("Book not found!\n");
}
void DeleteBook(){
    int id;
    printf("enter Book id");
    scanf("%d",&id);
    for(int i=0;i<count;i++){
        if(b[i].id==id)
        {
            for (int j=i;j<count-1;j++)
            {
                b[j]=b[j+1];
            }
            count--;
            saveBook();
            printf("Book deleted successfully!\n");
            return;
        }
    }
    printf("Book not found!\n");
}
void saveBook()
{
    FILE *fp=fopen("books.dat","wb");
    if (fp==NULL){
        printf("error in opening file\n");
        return;
    }
    fwrite(&count,sizeof(int),1,fp);
    fwrite(b,sizeof(struct Book),count,fp);
    fclose(fp);
}
void loadBooks()
{
    FILE *fp=fopen("books.dat","rb");
    if (fp==NULL)
    {
        count=0;
        return;
    }
    fread(&count, sizeof(int), 1, fp);
    fread(b, sizeof(struct Book), count, fp);
    fclose(fp);
}
int main()
{
    int choice;
    loadBooks();

    do
    {
        printf("\n===== LIBRARY MANAGEMENT SYSTEM =====\n");
        printf("1. Add Book\n");
        printf("2. Display Book\n");
        printf("3. Search Book\n");
        printf("4. Issue Book\n");
        printf("5. Return Book\n");
        printf("6. Delete Book\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                AddBook();
                break;

            case 2:
                displayBook();
                break;

            case 3:
                searchBook();
                break;

            case 4:
                IssueBook();
                break;

            case 5:
                ReturnBook();
                break;

            case 6:
                DeleteBook();
                break;

            case 7:
                printf("Thank you for using the Library Management System!\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    } while(choice != 7);

    return 0;
}

