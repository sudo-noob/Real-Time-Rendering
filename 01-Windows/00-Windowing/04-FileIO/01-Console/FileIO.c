#include <stdio.h>

int main(void)
{
	//code
	//Variable Declaration
	FILE* pfile = NULL;

	if(fopen_s(&pfile, "SSMLog.txt", "w") != 0)
	{
		printf("Cannot open desired file\n");
		exit(0);
	}

	fprintf(pfile, "India is my country.\n");
		fclose(pfile);
		pfile = NULL;

	return(0);
}