#ifndef GLOBALSETTING_HPP
#define GLOBALSETTING_HPP

#include <string>

const std::string SLASH  = "/\\";

// global variable, singleton
class GlobalSetting 
{
    private:
        GlobalSetting() {}

    public:
        static GlobalSetting& getInstance()
        {
            static GlobalSetting g;
            return g;
        }    

        int totalPage;
        std::string inputFile;   // input file full path
        std::string file;
        std::string ext;
};

#endif
