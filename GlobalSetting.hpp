#ifndef GLOBALSETTING_HPP
#define GLOBALSETTING_HPP

#include <string>

// global variable, singleton
class GlobalSetting 
{
    private:
        GlobalSetting() {}
        static GlobalSetting* instance;
        static std::unique_ptr<GlobalSetting> uniquePtrInstance;

    public:
        static GlobalSetting* getInstance();
        static std::unique_ptr<GlobalSetting> getUniquePtrInstance();

        int totalPage;
};

#endif
