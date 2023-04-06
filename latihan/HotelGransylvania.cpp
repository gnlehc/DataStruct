#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SIZE 100

struct Booking
{
	char ID[7];
	char name[100];
	char number[17];
	int age;
	char roomType[15];
	int nights;

	struct Booking *next;
	struct Booking *prev;
} *head[SIZE], *tail[SIZE];

struct Booking *newBooking(char name[], char number[], int age, char roomType[], int nights)
{
	struct Booking *node = (Booking *)malloc(sizeof(struct Booking));
	node->next = node->prev = NULL;

	// getting the user ID based of the instruction
	char genID[7];
	int a = rand() % 10;
	int b = rand() % 10;
	int c = rand() % 10;
	sprintf(genID, "%c%c%d%d%d", roomType[0], roomType[1] - 32, a, b, c);

	// copying all of the data to my own struct
	strcpy(node->name, name);
	strcpy(node->number, number);
	node->age = age;
	strcpy(node->roomType, roomType);
	node->nights = nights;
	strcpy(node->ID, genID);

	return node;
}

int hash(char ID[])
{ // DE174
	int hashkey = 0;

	for (int i = 2; i < 5; i++)
	{
		hashkey += ID[i];
	}

	hashkey -= 1;
	return hashkey % SIZE;
}

void insertData(struct Booking *node)
{
	int index = hash(node->ID);

	if (head[index] == NULL)
	{
		head[index] = tail[index] = node;
	}
	else
	{
		tail[index]->next = node;
		node->prev = tail[index];
		tail[index] = node;
	}
}

void printDataNULL(int simpen)
{
	if (simpen == 0)
	{
		puts("+--------------------------+");
		puts("| There is no booking yet! |");
		puts("+--------------------------+");
	}
	else
	{
		return;
	}
}

void printData()
{
	int simpen = 0;
	for (int i = 0; i < SIZE; i++)
	{
		if (head[i] == NULL)
		{
			simpen += 0;
		}
		struct Booking *curr = head[i];
		while (curr != NULL)
		{
			puts("+------------------------------------+");
			printf("| Booking ID: %-22s |\n", curr->ID);
			puts("+------------------------------------+");
			printf("| Full Name: %-23s |\n", curr->name);
			printf("| Phone Number: %-20s |\n", curr->number);
			printf("| Room Type: %-23s |\n", curr->roomType);
			printf("| Night Stay: %d night(s)             |\n", curr->nights);
			puts("+------------------------------------+");
			puts("");
			curr = curr->next;
			simpen += 1;
		}
	}
}

void deleteData(char ID[])
{
	int hashkey = hash(ID);

	if (head[hashkey] == NULL)
	{
		puts("+------------------------------------------------+");
		printf("| Fail to delete, there is no data with %s ID |\n", ID);
		puts("+------------------------------------------------+");
		return;
	}

	if (head[hashkey] == tail[hashkey] && strcmp(head[hashkey]->ID, ID) == 0)
	{
		free(head[hashkey]);
		head[hashkey] = NULL;
		tail[hashkey] = NULL;
		puts("+------------------------------------------+");
		printf("| BookingID %s is successfully deleted! |\n", ID);
		puts("+------------------------------------------+");
		return;
	}
	else if (strcmp(head[hashkey]->ID, ID) == 0)
	{
		struct Booking *temp = head[hashkey];
		head[hashkey] = head[hashkey]->next; // NULL<-2

		head[hashkey]->prev = NULL;
		temp->next = NULL;

		free(temp);
		temp = NULL;
		puts("+------------------------------------------+");
		printf("| BookingID %s is successfully deleted! |\n", ID);
		puts("+------------------------------------------+");
		return;
	}
	else if (strcmp(tail[hashkey]->ID, ID) == 0)
	{
		struct Booking *temp = tail[hashkey];
		tail[hashkey] = tail[hashkey]->prev;

		tail[hashkey]->next = NULL;
		temp->prev = NULL;

		free(temp);
		temp = NULL;
		puts("+------------------------------------------+");
		printf("| BookingID %s is successfully deleted! |\n", ID);
		puts("+------------------------------------------+");
		return;
	}
	else
	{
		struct Booking *curr = head[hashkey]->next;

		while (curr != NULL && strcmp(curr->ID, ID) != 0)
		{
			curr = curr->next;
		}

		if (curr == NULL)
		{
			puts("+------------------------------------------------+");
			printf("| Fail to delete, there is no data with %s ID |\n", ID);
			puts("+------------------------------------------------+");
		}
		else
		{
			struct Booking *afterCurr = curr->next;
			struct Booking *beforeCurr = curr->prev;

			afterCurr->prev = beforeCurr;
			beforeCurr->next = afterCurr;

			curr->next = NULL;
			curr->prev = NULL;
			free(curr);
			curr = NULL;
			puts("+------------------------------------------+");
			printf("| BookingID %s is successfully deleted! |\n", ID);
			puts("+------------------------------------------+");
			return;
		}
	}
}

void updateData(char ID[], int nights)
{
	int hashKey = hash(ID);

	if (head == NULL)
	{
		printf("NO DATA SLAYAGE!\n");
		return;
	}
	else
	{
		struct Booking *curr = head[hashKey];

		while (curr != NULL && strcmp(curr->ID, ID) != 0)
		{
			curr = curr->next;
		}

		if (curr == NULL)
		{
			printf("Item not found!\n");
			return;
		}
		else
		{
			curr->nights = curr->nights - nights;
			//			strcpy(curr->itemName, itemName);
			//			curr->price = price;
		}
	}
}

void mainMenu();
void firstMenu();
void secondMenu();
void thirdMenu();
void fourthMenu();
void fifthMenu();

int main()
{
	mainMenu();
	srand(time(0));

	return 0;
}

void mainMenu()
{
	puts("+--------------------+");
	puts("| Hotel GrAnsylvania |");
	puts("+--------------------+");
	puts(" ");
	puts("1. Booking Hotel");
	puts("2. View Bookings");
	puts("3. Delete Booking");
	puts("4. Exit");
	puts("5. Change Night to Stay");
	printf(">> ");

	int input;
	scanf("%d", &input);
	getchar();
	while (input < 1 || input > 5)
	{
		puts("Sorry, only can choose 1-5 from the menu!");
		scanf("%d", &input);
		getchar();
	}

	switch (input)
	{
	case 1:
		firstMenu();
		break;
	case 2:
		secondMenu();
		break;
	case 3:
		thirdMenu();
		break;
	case 4:
		fourthMenu();
		break;
	case 5:
		fifthMenu();
		break;
	}
}

void firstMenu()
{
	char name[100];
	printf("Input Full Name [3..30]: ");
	scanf("%[^\n]", &name);
	getchar();

	char number[17];
	printf("Input Phone Number: ");
	scanf("%[^\n]", &number);
	getchar();

	int age;
	printf("Input Age [Minimum 18]: ");
	scanf("%d", &age);
	getchar();

	char roomType[15];
	printf("Input Room Type [Regular | Deluxe | Suite] (Case Sensitive): ");
	scanf("%[^\n]", &roomType);
	getchar();

	int nights;
	printf("Input How Many Night You Will Stay [1..30]: ");
	scanf("%d", &nights);
	getchar();

	insertData(newBooking(name, number, age, roomType, nights));
	printData();
	printf("Press ENTER to continue...");
	getchar();
	system("cls");
	mainMenu();
}

void secondMenu()
{
	printData();
	printf("Press ENTER to continue...");
	getchar();
	system("cls");
	mainMenu();
}

void thirdMenu()
{
	char deleteID[7];
	printf("Input Booking ID (Case Sensitive): ");
	scanf("%s", &deleteID);
	getchar();

	deleteData(deleteID);
	printf("Press ENTER to continue...");
	getchar();
	system("cls");
	mainMenu();
}

void fourthMenu()
{
	system("cls");
	puts("Thankyou for using this program!");
	puts("Have a nice day ^-^");
}

void fifthMenu()
{
	char ID[7];
	printf("Input ID you want to change: ");
	scanf("%s", &ID);
	getchar();

	int ubah;
	printf("Input minus nights you want to change: ");
	scanf("%d", &ubah);
	getchar();

	updateData(ID, ubah);
	printf("Press ENTER to continue...");
	getchar();
	system("cls");
	mainMenu();
}
