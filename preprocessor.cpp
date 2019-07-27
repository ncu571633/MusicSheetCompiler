#include <string>
#include <iostream>

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
#include <dirent.h>

#include "preprocessor.hpp"

template<typename... Args>
void preprocessor::externalCall(Args... args)
{
	pid_t c;  
	if ((c = fork()) < 0 )
	{
		perror("fork failed");
		exit(1);
	}

	if (!c)
	{
		execl(args...);
		perror("execl() failure!\n\n");
		_exit(1);
	} 
	else 
		wait(NULL);
}

//if there are n pages in the pdf, n jpg files are generated
int preprocessor::countPGM(std::string& filePath)
{
	struct dirent *entry;
	DIR *dp;
	 
	dp = opendir(filePath.c_str());
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
		}
	}
		   
	closedir(dp);
	return count;
}

// entry point
void preprocessor::convertIMG(GlobalSetting& setting)
{
    std::size_t found = setting.file.find_last_of("/\\");
    std::string filePath = setting.file.substr(0, found);
    std::string fileFullName = setting.file.substr(found+1);
	
    found = fileFullName.find_last_of("/\\");
    std::string fileName = fileFullName.substr(0, found);
    std::string fileExt = fileFullName.substr(found + 1);
	
    std::cout << "Begin to convert input file: " + fileName + "\n";
    
    if (fileExt == "pgm")
    {
        return ;
    }

    // remove existing pgm file
    {
	    // execl("/bin/rm", "rm", "-f", tmp, NULL);
    }

    if (fileExt == "pdf")
    {
		// strcpy(arg->fileName, "attach"); 

		// execl("/usr/bin/convert", "convert", "-density", "256", "-compress", "none", filePath, outFile, NULL);
		// arg->imgNO = countPGM(TMPPATH);
		return ;
	}
}
