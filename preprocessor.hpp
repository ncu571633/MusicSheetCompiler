#include "GlobalSetting.hpp"

/*
Input preprocesor:
covert all input source into pgm format image
*/

class preprocessor
{
    private:
        template<typename... Args>
        static void externalCall(Args... args);
    
    public:
        static int countPGM(std::string& filePath);
        static void convertIMG(GlobalSetting& setting);
};
