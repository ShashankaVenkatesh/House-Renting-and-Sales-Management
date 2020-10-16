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