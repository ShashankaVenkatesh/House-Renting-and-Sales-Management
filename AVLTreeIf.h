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