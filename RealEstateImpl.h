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