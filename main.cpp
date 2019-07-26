#include <memory>  // unique_ptr

#include "GlobalSetting.hpp"

#include "lib/netPbm/netPbm/NetPbmImage.hpp"

int main(int arg, char* argv[])
{
    // global setting info
    std::unique_ptr<GlobalSetting> setting = std::make_unique<GlobalSetting>(GlobalSetting.getInstance()); 
    
    // pre-processing: convert input files to acceptable pgm file

    // load pgm file into memory
    netPbm::NetPbmImage* p = netPbm::ReadNetPbmImage("resource/p1.pbm");
    delete(p);

    // transformation
}
