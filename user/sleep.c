#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"

int main(int argc, char *argv[])
{
	int time;
	if(argc < 2)
	{
		fprintf(2, "Error. Need sleep second.\n");
		exit();
	}
	
	time = atoi(argv[1]);
	sleep(time);
	exit();
}
