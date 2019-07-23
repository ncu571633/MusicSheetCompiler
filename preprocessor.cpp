#include <cstdio>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/mman.h>
#include <error.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <dirent.h>


void rmTmpJpg();
int countPGM(char *filePath);
// convert pdf file to .pgm
void convertIMG(ARG *arg);
void convertPdf(char *filePath, char *fileName);

void rmTmpJpg()
{
	pid_t c;  
	if ((c = fork()) < 0 )
	{
		perror("fork failed");
		exit(1);
	}

	if (!c)
	{
		printf("rm");
		char tmp[FILENAMEBUFFERSIZE];
		sprintf(tmp, "%s/*.jpg", TMPPATH);
		execl("/bin/rm", "rm", "-f", tmp, NULL);
		perror("execl() failure!\n\n");
		_exit(1);
	} 
	else 
		wait(NULL);
}

//if there are n pages in the pdf, n jpg files are generated
int countPGM(char *filePath)
{
	struct dirent *entry;
	DIR *dp;
	 
	dp = opendir(filePath);
	if (dp == NULL) 
	{
		perror("opendir");
		return -1;
	}
		 
	int count = 0;
	while((entry = readdir(dp)))
	{
		if(strstr(entry->d_name, ".pgm") != 0)
		{
			count++;
			//fprintf(stdout, "\t%s.\n", entry->d_name);
		}
	}
		   
	closedir(dp);
	return count;
}

void convertIMG(ARG *arg)
{//arg->ipath
	char filePath[FILENAMEBUFFERSIZE];
	char fileName[FILENAMEBUFFERSIZE];
	strcpy(filePath, arg->ipath);
	//remove path
	char * pch = strtok (arg->ipath,"/");
	while (pch != NULL)
	{
		pch = strtok (NULL, "/");
		if(pch != NULL)
			strcpy(fileName, pch);
		else
			strcpy(fileName, filePath);
	}

	//find out the last dot "."
//	printf ("fileName: %s\n",fileName);
	char *pch1 = strstr (fileName, ".");
	while(pch1 != NULL)
	{
		pch = pch1;
		pch1 = strstr (pch1+1, ".");
	}

	if(strcmp(pch+1, "pdf")==0)
	{
		fprintf(stdout, "Begin to convert the pdf file: %s.\n", fileName);
		rmTmpJpg();
		strcpy(arg->fileName, "attach"); 
		convertPdf(filePath, arg->fileName);
		arg->imgNO = countPGM(TMPPATH);
		fprintf(stdout, "Finished conversion: %d pages.\n", arg->imgNO);
		return ;
	}
	if(strcmp(pch+1, "pgm")==0 || strcmp(pch+1, "pbm")==0)
	{
		fprintf(stdout, "Begin to recognize pgm/pbm file.\n");
		arg->imgNO = 1;
		strcpy(arg->ipath, filePath);
		return ;
	}
	fprintf(stderr, "Can't recognize file format: %s\n", pch+1);
	exit(0);
}

//convert the file from .pdf to .pgm
void convertPdf(char *filePath, char *fileName) 
{
	pid_t c;  
	if ((c = fork()) < 0 )
	{
		perror("fork failed");
		exit(1);
	}

	char outFile[FILENAMEBUFFERSIZE];
	sprintf(outFile, "%s/%s%%d.pgm", TMPPATH, fileName);
	if (!c)
	{ 
		fprintf(stdout, "Begin converting: %s -> %s\n", filePath, outFile);
		execl("/usr/bin/convert", "convert", "-density", "256", "-compress", "none", filePath, outFile, NULL);
		perror("execl() failure!\n\n");
		_exit(1);
	} 
	else 
		wait(NULL);
}

#endif
