#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define R 0
#define W 1

int main()
{
	int first, v;
	int *read_fd, *write_fd;
	int first_fd[2], second_fd[2];
	pipe(first_fd);

	if(fork() > 0 )
	{//parent: feed process
		close(first_fd[R]);
		for(int i = 2; i < 36; i++)
			write(first_fd[W], &i, sizeof(int));
		close(first_fd[W]);
		wait();//wait for child process
	}
	else
	{//child process
		read_fd = first_fd;
		write_fd = second_fd;//change name for better understanding

		while(1)
		{
			//need a pipe writing to child
			pipe(write_fd);

			close(read_fd[W]);
			if(read(read_fd[R], &first, sizeof(int)))
				printf("prime %d\n", first);
			else
				break;
			
			if(fork() > 0)
			{
				close(write_fd[R]);
				while(read(read_fd[R], &v, sizeof(int)))
				{
					if(v % first == 0)
						continue;
					else
						write(write_fd[W], &v, sizeof(int));
				}
				close(read_fd[R]);
				close(write_fd[W]);
				wait();
				break;
			}
			else
			{
				close(read_fd[R]);
				//parent write pipe is my read pipe
				int *tmp = read_fd;
				read_fd = write_fd;
				write_fd = tmp;
			}
		}
	}
	exit();
}
