// ----------------------------------------------------------------------------------------------------------------------------
// Priority Queue Implementation
// ----------------------------------------------------------------------------------------------------------------------------

typedef struct
{
	char name[50];
	char city[100];
	char address[200];
	char type; // S: Selling R: Renting
	int price;
	int available; // 1: available 0: occupied
	int size; // (in Sq. Feet)
	int bhk;
	int furnishing; // 1: Unfurnished 2: Semi Furnished 3: Fully Furnished
	float priority;
} house;

typedef struct
{
	house *list;
	int size;
	int availableCount;
	int capacity;
} PQueue;

PQueue * initQ(int size)
{
	PQueue *P = (PQueue *)malloc(sizeof(PQueue));
	
	// Initializing the size and capacity
	P->size = 0;
	P->availableCount = 0;
	P->capacity = size;
		
	// Initializing the array
	P->list = (house *)malloc(sizeof(house) * size);
	P->list[0].priority = 10000;
	
	return P;
}

int getSize(PQueue *P)
{
	return(P->availableCount);
}

int isFull(PQueue *P)
{
	if(P->size == P->capacity)
		return 1;
	return 0;
}

int isEmpty(PQueue *P)
{
	if(P->size == 0)
		return 1;
	return 0;
}

void reduceAvailable(PQueue *P)
{
	P->availableCount = P->availableCount - 1;
}

house readHouse()
{
	house h;
	char line[100];
	printf("\nEnter the name of the house: ");
	scanf(" %[^\n]",h.name);
	printf("Enter the city: ");
	scanf(" %[^\n]",h.city);
	printf("Enter the full address (2 lines): \n");
	scanf(" %[^\n]",h.address);
	scanf(" %[^\n]",line);
	strcat(h.address,"\n\t");
	strcat(h.address,line);
	
	do
	{	
		printf("\nAre you Selling the house or giving it for Rent? (S/R): ");
		scanf(" %c",&h.type);
	} while(h.type != 'S' && h.type != 'R');
	
	if(h.type == 'S')
		printf("Enter the price: ");
	else
		printf("Enter the rent per month: ");
	scanf(" %d",&h.price);
	
	printf("\nEnter the size in square feet: ");
	scanf("%d",&h.size);

	printf("Number of bedrooms: ");
	scanf("%d",&h.bhk);

	do
	{
		printf("\nHow furnished is the house\n1. Unfurnished\n2. Semi-Furnished\n3. Fully Furnished\n>>");
		scanf("%d",&h.furnishing);
	} while(h.furnishing < 1 || h.furnishing > 3);

	/*
	Priority is a combination of
	1. Number of bedrooms (directly)
	2. Level of furnishing (directly)
	3. Cost per square feet (inversely)

	Higher priority is given to the house with the higher priority rating
	*/

	float costPerSqFeet = ((float)h.price)/((float)h.size);

	h.priority = (h.bhk * h.furnishing) / costPerSqFeet;
	
	// Initially set to 1
	h.available = 1;

	return(h);
}

void insertQ(PQueue *P, house h)
{
	if(isFull(P))
		printf("\nQueue is full!");
	else
	{	
		int i;
		for(i = ++P->size; P->list[i/2].priority < h.priority; i/=2)
			P->list[i] = P->list[i/2];
		P->list[i] = h;
		P->availableCount++;
	}
}

house del(PQueue *P)
{
	if(isEmpty(P))
	{
		house e;
		e.price = -1;
		printf("\nQueue is empty or element not present!");
		return(e);
	}

	else
	{
		int child, i;
		house min = P->list[1];
		house lastel = P->list[P->size--];
		P->availableCount--;

		for(i = 1; (i*2) < P->size; i = child)
		{
			child = i*2;

			if(P->list[child+1].priority < P->list[child].priority)
				child++;

			if(lastel.priority > P->list[child].priority)
				P->list[i] = P->list[child];

			else break;
		}

		P->list[i]=lastel;
		return min;			
	}
}

void showDetails(house h)
{
	int n = 50 - strlen(h.name),i;
	printf("\n\n----------------------------------------------------\n|");
	for(i=0;i<n/2;i++)
		printf(" ");
	printf("%s",h.name);
	for(i=0;i<n/2;i++)
		printf(" ");
	printf("|\n----------------------------------------------------\n");

	switch(h.furnishing)
	{
		case 1: printf("\n\tUnfurnished "); break;
		case 2: printf("\n\tSemi furnished "); break;
		case 3: printf("\n\tFully furnished "); break;
	}

	printf("%d sq. feet %d BHK house\n",h.size,h.bhk);

	if(h.type == 'S')
		printf("\n\tFor SALE at Rs. %d\n",h.price);
	else
		printf("\n\tFor RENT at Rs. %d per month\n",h.price);

	printf("\n----------------------------------------------------\n");
	printf("\n\tFull Address: \n\n\t%s",h.address);
	printf("\n");
	printf("\n----------------------------------------------------\n");
	printf("----------------------------------------------------\n");
}

int printTabs(int depth)
{
	for(int i = 0; i<depth; i++)
		printf("\t");
}

void display(PQueue *P)
{
	if(P->size == 0)
	{ printf("\nSorry, there are no available houses!"); return; }

	int n = P->size,i,j;
	house h[100];

	for(i=1,j=1; i<=n; i++)
	{
		h[i] = del(P);
		if(h[i].available)
		{
			printf("\n-----");
			printf("\n| %d |",j++);
			printf("\n-----");
			showDetails(h[i]);
		}
	}

	for(i=1; i<=n; i++)
		insertQ(P, h[i]);
}

// ----------------------------------------------------------------------------------------------------------------------------
// Priority Queue Interface
// ----------------------------------------------------------------------------------------------------------------------------

// To initialize the priority queue
PQueue * initQ(int size);
// To return the size of the queue
int getSize(PQueue *P);
// To check if the queue is full
int isFull(PQueue *P);
// To check if the queue is empty
int isEmpty(PQueue *P);
// To insert an element into the priority queue
void insertQ(PQueue *P, house h);
 // To delete the front node and return the details
house del(PQueue *P);
// To display all details of h
void showDetails(house h);
// To print 'depth' number of tab spaces
int printTabs(int depth);
// Reduce the count of available number of houses by one
void reduceAvailable(PQueue *P);
// TO display the entire queue
void display(PQueue *P);

// ----------------------------------------------------------------------------------------------------------------------------
// AVL Tree Implementation
// ----------------------------------------------------------------------------------------------------------------------------

typedef struct
{
	char name[100];
	PQueue *selling, *renting;
} cityList;

struct treeADT
{
	cityList city;
	struct treeADT *left, *right;
	int height;
};

int max(int a, int b)
{
	return (a>b)?a:b;
}

int findHeight(struct treeADT *t)
{
	if(t == NULL)
		return -1;
	return t->height;
}

cityList initCityList(char name[100])
{
	cityList city;

	strcpy(city.name,name);

	city.selling = initQ(100);
	city.renting = initQ(100);

	return(city);
}

struct treeADT * singleRotateRight(struct treeADT *t)
{
	struct treeADT *k = t->right;
	t->right = k->left;
	k->left = t;

	t->height = max(findHeight(t->left), findHeight(t->right)) + 1;
	k->height = max(findHeight(k->right), findHeight(t)) + 1;

	return k;
}

struct treeADT * singleRotateLeft(struct treeADT *t)
{
	struct treeADT *k = t->left;
	t->left = k->right;
	k->right = t;

	t->height = max(findHeight(t->left), findHeight(t->right)) + 1;
	k->height = max(findHeight(k->left), findHeight(t)) + 1;

	return k;
}

struct treeADT * doubleRotateLeft(struct treeADT *t)
{
	t->left = singleRotateRight(t->left);
	return singleRotateLeft(t);
}

struct treeADT * doubleRotateRight(struct treeADT *t)
{
	t->right = singleRotateLeft(t->right);
	return singleRotateRight(t);
}

struct treeADT * insert(struct treeADT *t, cityList city)
{
	int hdiff;

	if(t == NULL)
	{
		t = (struct treeADT *) malloc(sizeof(struct treeADT));
		t -> city = city;
		t -> height = 0;
		t -> left = t -> right = NULL;
	}

	else if(strcmp(t->city.name,city.name) > 0)
	{
		t->left = insert(t->left, city);
		hdiff = findHeight(t->left) - findHeight(t->right);

		if(hdiff == 2 || hdiff == -2)
		{
			if(strcmp((t->right)->city.name,city.name) > 0)
				t->left = singleRotateLeft(t->left);
			else
				t->left = doubleRotateLeft(t->left);			
		}
	}
	
	else if(strcmp(t->city.name,city.name) < 0)
	{
		t->right = insert(t->right, city);
		hdiff = findHeight(t->left) - findHeight(t->right);

		if(hdiff == 2 || hdiff == -2)
		{
			if(strcmp((t->right)->city.name,city.name) < 0) 
				t->right = singleRotateRight(t->right);
			else
				t->right = doubleRotateRight(t->right);
		}
	}
	
	t->height = max(findHeight(t->left), findHeight(t->right)) + 1;
	return t;
}

struct treeADT * search(struct treeADT *t, char cityName[100])
{
	if(t == NULL)
		return(NULL);

	else if(strcmp(t->city.name, cityName) == 0)
		return(t);
	
	else if(strcmp(t->city.name, cityName) < 0)
		return(search(t->right, cityName));
	
	else
		return(search(t->left, cityName));
}

int searchAndDisplay(struct treeADT *t, char cityName[100], int type)
{
	if(t == NULL)
		return(0);

	if(strcmp(t->city.name, cityName) == 0)
	{
		// Selling is type 0
		// Renting is type 1
		if(type)
		{
			if(isEmpty(t->city.renting))
				return(0);
			
			display(t->city.renting);
			return(getSize(t->city.renting));
		}

		else
		{
			if(isEmpty(t->city.selling))
				return(0);

			display(t->city.selling);
			return(getSize(t->city.selling));
		}	
	}
	
	if(strcmp(t->city.name, cityName) < 0)
		return(searchAndDisplay(t->right, cityName, type));
	
	return(searchAndDisplay(t->left, cityName, type));
}

void sell(struct treeADT *t, int type, int index)
{
	int n,i,j;
	house h[100];

	// Selling is type 0
	// Renting is type 1
	if(type)
	{
		n = ((t->city).renting)->size;

		for(i=1,j=1; i<=n; i++)
		{
			h[i] = del(t->city.renting);
			if(h[i].available)
			{
				if(index == j)
					h[i].available = 0;
				j++;
			}
		}

		for(i=1; i<=n; i++)
			insertQ(t->city.renting,h[i]);
		reduceAvailable(t->city.renting);
	}

	else
	{
		n = ((t->city).selling)->size;

		for(i=1,j=1; i<=n; i++)
		{
			h[i] = del(t->city.selling);
			if(h[i].available)
				if(index == j++)
					h[i].available = 0;
		}

		for(i=1; i<=n; i++)
			insertQ(t->city.selling,h[i]);
		reduceAvailable(t->city.selling);
	}
}

// To add house h to an existing node
struct treeADT * addHouse(struct treeADT *t, house h)
{
	struct treeADT *node = search(t,h.city);

	if(h.type == 'S')
		insertQ(node->city.selling,h);
	else
		insertQ(node->city.renting,h);

	return(t);
}

// Only accesible by the administrator
void displayTree(struct treeADT *t, int depth)
{
	if(t == NULL) return;

	printf("\n");
	printTabs(depth);
	printf("City: %s\n",t->city.name);
	printTabs(depth);
	printf("\nSelling: ");
	display(t->city.selling);
	printTabs(depth);
	printf("\nRenting: ");
	display(t->city.renting);

	if(t->left)
	{
		printf("\n");
		printTabs(depth + 1);
		printf("LEFT:");
		displayTree(t->left, depth + 1);
	}

	if(t->right)
	{
		printf("\n");
		printTabs(depth + 1);
		printf("RIGHT:");
		displayTree(t->right, depth + 1);
	}
}

// ----------------------------------------------------------------------------------------------------------------------------
// AVL Tree Interface
// ----------------------------------------------------------------------------------------------------------------------------

// Function to initialize a cityList (node of the tree)
cityList initCityList(char name[100]);
// Function to find the height of the passed node
int findHeight(struct treeADT *t);
// To perform a single right rotation
struct treeADT * singleRotateRight(struct treeADT *t);
// To perform a single left rotation
struct treeADT * singleRotateLeft(struct treeADT *t);
// To perform a double left rotation
struct treeADT * doubleRotateLeft(struct treeADT *t);
// To perform a double right rotation
struct treeADT * doubleRotateRight(struct treeADT *t);
// To insert a node into the tree
struct treeADT * insert(struct treeADT *t, cityList city);
// Searches for the city in the tree, returns 1 if found, 0 if not
struct treeADT * search(struct treeADT *t, char cityName[100]);
// To search for the node containing the given city,
// and display one of the two priority queues (Selling is type 1, Renting is type 0)
int searchAndDisplay(struct treeADT *t, char cityName[100], int type);
// To sell the house of passed type in the node at passed index
void sell(struct treeADT *t, int type, int index);
// To add a house to the correct node of the tree
struct treeADT * addHouse(struct treeADT *t, house h);
// To display the tree [ADMIN ONLY]
void displayTree(struct treeADT *t, int depth);

// ----------------------------------------------------------------------------------------------------------------------------
// Real Estate Application - Design Implementations
// ----------------------------------------------------------------------------------------------------------------------------

// To delay excecution by 't' milliseconds
void delay(int t)
{
	clock_t T=clock();
	while(clock()<T+t);
}

// To set the console cursor to the centre of the window,
// shifted by half the length of the stuff to be printed
void centre(int l,int i)
{
	for(;i<83-(l/2);i++)
		printf(" ");
}

// To left align, 'l' being the extra indent
void left(int l)
{
	for(int i=0;i<20+l;i++)
		printf(" ");
}

// To display the welcome page
int opening(int mode)
{
	if(mode)
	{
		int op;
		printf("\n\n");
		left(20);
		printf(">>");
		scanf("%d",&op);

		return(op);
	}

	char s[]="{ S-CUBE REAL ESATE AGENCY }",ch;
	int l=strlen(s),i,j,op;
	delay(25);

	scanf("%c",&ch);
	printf("\n\n\n");
	
	centre(l,-2);
	for(i=0;i<l;i++)
	{
		printf("-");
		delay(2);
	}

	printf("\n");
	
	centre(l,-2);
	for(i=0;i<l;i++)
	{
		printf("%c",s[i]);
		delay(10);
	}
	
	printf("\n");
	
	centre(l,-2);
	for(i=0;i<l;i++)
		printf("-");

	
	printf("\n\n");
	left(11);
	for(i=0;i<110;i++)
		printf("_");
	printf("\n");
	

	for(i=0;i<3;i++)
	{
		left(14);
		printf("||");
		for(j=0;j<100;j++)
			printf(" ");
		printf("||\n");
		delay(5);
	}
	
	// Printing "Welcome" and the underline
	left(14);
	printf("||");
	strcpy(s,"WELCOME");	
	centre(strlen(s),34);
	printf("%s",s);
	for(j=0;j<47;j++)
			printf(" ");
	printf("||\n");
	left(14);
	printf("||");
	strcpy(s,"---------");	
	centre(strlen(s),34);
	printf("%s",s);
	for(j=0;j<46;j++)
			printf(" ");
	printf("||\n");
	
	for(i=5;i<7;i++)
	{
		left(14);
		printf("||");
		for(j=0;j<100;j++)
			printf(" ");
		printf("||\n");
		delay(5);
	}
	
	left(14);
	printf("||");
	strcpy(s,"1. Buy or Rent a house");	
	printf("     ");
	printf("%s",s);
	for(j=0;j<73;j++)
			printf(" ");
	printf("||\n");

	for(;i<9;i++)
	{
		left(14);
		printf("||");
		for(j=0;j<100;j++)
			printf(" ");
		printf("||\n");
		delay(5);
	}

	left(14);
	printf("||");
	strcpy(s,"2. Sell or Put a house for Rent");
	printf("     ");
	printf("%s",s);
	for(j=0;j<64;j++)
			printf(" ");
	printf("||\n");

	for(;i<11;i++)
	{
		left(14);
		printf("||");
		for(j=0;j<100;j++)
			printf(" ");
		printf("||\n");
		delay(5);
	}

	left(14);
	printf("||");
	strcpy(s,"3. Exit");
	printf("     ");
	printf("%s",s);
	for(j=0;j<88;j++)
			printf(" ");
	printf("||\n");

	for(;i<13;i++)
	{
		left(14);
		printf("||");
		for(j=0;j<100;j++)
			printf(" ");
		printf("||\n");
		delay(5);
	}


	left(11);
	for(i=0;i<110;i++)
		printf("=");


	printf("\n\n");
	left(20);
	printf(">>");
	scanf("%d",&op);

	return(op);
}

// To display the border on every screen
void border()
{
	int i,j;

	system("cls");

	for(i=0;i<3;i++)
		for(j=0;j<84;j++)
			printf("/\\");

	printf("\n\n\n\n\n");
}

// ----------------------------------------------------------------------------------------------------------------------------
// Real Estate Application - Design Interface
// ----------------------------------------------------------------------------------------------------------------------------

// To delay excecution by 't' milliseconds
void delay(int t);
// To set the console cursor to the centre of the window,
// shifted by half the length of the string to be printed
void centre(int l,int i);
// To left align, 'l' being the extra indent
void left(int l);
// To display the welcome page
int opening(int mode);
// To display the border on every screen
void border();

// ----------------------------------------------------------------------------------------------------------------------------
// Real Estate Application
// ----------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "PriorityQueueImpl.h"
#include "PriorityQueueIf.h"
#include "AVLTreeImpl.h"
#include "AVLTreeIf.h"
#include "RealEstateImpl.h"
#include "RealEstateIf.h"

void main()
{
	int op,f = 0,opt,n;
	char city[100],ch;

	// The AVL Tree
	struct treeADT *dataBase = NULL;

	// Used for checking conditions and operations of the sort
	struct treeADT *t = NULL;

	do
	{
		border();
		op = opening(f);

		if(op == 1)
		{
			buy:
			border();
			printf("\n\nEnter the city you want to search in: ");
			scanf(" %[^\n]",city);

			t = search(dataBase,city);

			// If city isn't in the tree
			if(t == NULL)
			{
				printf("Sorry, we haven't expanded to %s yet\n",city);

				a:
				printf("\nDo you want to search in another city (Y/N): ");
				scanf(" %c",&ch);
				if(ch != 'Y' && ch != 'N')
					goto a;

				if(ch == 'Y')
					goto buy;
			}

			// If city is in the tree
			else
			{
				printf("Enter your choice:\n1. Buy a house\n2. Rent a house\n>>");
				scanf("%d",&opt);

				n = searchAndDisplay(dataBase, city, opt-1);

				// If there are available houses of the type requested for
				if(n)
				{
					printf("\nAre you interested in buying any of these houses? (Y/N): ");
					scanf(" %c",&ch);

					// If they want to buy any of the houses
					if(ch == 'Y')
					{
						int number;
						
						b:
						printf("\nEnter the number of the house you want to purhcase or rent: ");
						scanf("%d",&number);
						if(number>n || number<1)
						{
							printf("\nPlease enter a valid choice!\n");
							goto b;
						}

						sell(t,opt-1,number);
						printf("\n\n\n---------------------------");
						printf("\n| Successfully purhcased! |\n");
						printf("---------------------------\n\n");
						printf("\nPress ENTER to go back to Main Menu...\n");
						getch();
					}

					else
					{
						printf("\nWould you like to search in another city? (Y/N): ");
						scanf(" %c",&ch);

						if(ch == 'Y')
							goto buy;
					}
				}

				// If there are no available houses in that city of the type requested
				else
				{
					printf("\nSorry, there are no available houses of that type in the requested city");
					printf("\nWould you like to search again? (Y/N): ");
					scanf(" %c",&ch);

					if(ch == 'Y')
						goto buy;
				}
			}
		}

		else if (op == 2)
		{
			border();
			printf("\nPlease enter the details of the house: \n");
			house h = readHouse();

			t = search(dataBase,h.city);

			// If city isn't already in the database
			if(t == NULL)
			{
				// Creating a new city list
				cityList city = initCityList(h.city);

				// Inserting the house just registered
				if(h.type == 'S')
					insertQ(city.selling,h);
				else
					insertQ(city.renting,h);

				// Inserting this new city list into the data base
				dataBase = insert(dataBase,city);
			}

			else
				addHouse(dataBase,h);

			printf("\n\n\n----------------------------------------------------------------------------");
			printf("\n| Thank You for using our service, your house will be displayed to buyers! |\n");
			printf("----------------------------------------------------------------------------\n\n");
			printf("\nPress ENTER to go back to Main Menu...\n");
			getch();
		}

		else if(op == 4)
		{
			displayTree(dataBase,0);
			getch();
		}

		else if (op != 3)
		{
			printf("\n\n");
			left(20);
			printf("Please choose a valid option!");
			f = 1;
		}

	} while (op != 3);
}