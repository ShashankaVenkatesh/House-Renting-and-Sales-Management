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