#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>

// FUNCTIONS
// fork() -- trace the child's lineage -- return child's id if parent | 0 if child
pid_t forx(int *children, int lineage[], int *level, int *forkCounter, int *forkNum)
{
	pid_t f = fork();
	(*forkCounter)++;

	if (f)
		(*children)++;
	else
	{
		(*level)++;
		lineage[*level] = (*children);
		(*forkNum) = (*forkCounter);
		(*children) = 0;
	}

	return f;
}

// print out the lineage of the process and its output
void showLineage(int lineage[], int level, int forkNum, char *output)
{
	printf("(fork #%d) ", forkNum);

	for (int i = 0; i <= level; i++)
		printf("%s%d", (i > 0 ? " - " : ""), lineage[i]);

	if (strlen(output) > 0)
		printf(" : %s", output);
}

// MACROS
#define forkm() forx(&children, lineage, &level, &forkCounter, &forkNum)

#define outm(X, y)												\
{																\
	strcpy(outputc, output);									\
	snprintf(output, maxOutputLength-1, "%s"X, outputc, y);		\
}				

#define showm() showLineage(lineage, level, forkNum, output)

// CONSTANTS - CHANGE THESE IF YOU HAVE A LOT OF FORKS OR OUTPUTS
#define maxLineageLength 10
#define maxOutputLength 50

// MAIN
int main()
{
	// Process properties (used to trace the lineage):
	int lineage[maxLineageLength] = {0};
	int level = 0;
	int children = 0;
	int forkCounter = 0;
	int forkNum = 0;
	char output[maxOutputLength] = {0};
	char outputc[maxOutputLength] = {0};

	// use forkm() instead of fork()
	// you can use outm() instead of printf()
	// INSTRUCTIONS GO HERE:
	forkm();
	outm("Hello!", 0);

	// final results (each process's lineage and output):
	showm();

	printf("\n");
	exit(0);
}
