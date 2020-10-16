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