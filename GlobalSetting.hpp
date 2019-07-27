#ifndef GLOBALSETTING_HPP
#define GLOBALSETTING_HPP

#include <string>

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
        std::string file;   // file full path
        std::string fileName;
};

#endif
