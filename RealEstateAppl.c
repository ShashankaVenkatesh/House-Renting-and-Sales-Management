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