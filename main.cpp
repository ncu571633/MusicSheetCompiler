#include "GlobalSetting.hpp"
#include "preprocessor.hpp"

#include "lib/netPbm/netPbm/NetPbmImage.hpp"

int main(int arg, char* argv[])
{
    // global setting info
    GlobalSetting setting = GlobalSetting::getInstance();
    setting.inputFile = "./resource/attach.pdf";

    // pre-processing: convert input files to acceptable pbm file
    preprocessor::convertIMG(setting);

    // load pgm file into memory
    netPbm::NetPbmImage* p = netPbm::ReadNetPbmImage(setting.file);
    p->Write("temp.pbm");
    delete(p);

    // transformation
}
