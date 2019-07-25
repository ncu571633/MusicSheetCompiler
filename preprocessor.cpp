#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
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

/*
Input preprocesor:
covert all input source into pgm format image
*/

class preprocessor
{
    public:
        static void rmTmpJpg();
        static int countPGM(char *filePath);
        
        // convert pdf file to .pgm
        static void convertIMG(ARG *arg);
        static void convertPdf(std::string filePath, std::string fileName);
};


void preprocesor::rmTmpJpg()
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
int preprocesor::countPGM(char *filePath)
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



//convert the file from .pdf to .pgm
void preprocesor::convertPdf(char *filePath, char *fileName) 
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

// entry point
void preprocesor::convertIMG(std::string file)
{
    std::size_t found = file.find_last_of("/\\");
    std::string filePath = str.substr(0, found);
    std::string fileFullName = str.substr(found+1);
	
    found = fileFullName.find_last_of("/\\");
    std::string fileName = str.substr(0, found);
    std::string fileExt = str.substr(found + 1);
	    
    if (fileExt == "pdf")
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
#endif
