#include "lib/netPbm/netPbm/NetPbmImage.hpp"

int main(int arg, char* argv[])
{
    // pre-processing: convert input files to acceptable pgm file

    // load pgm file into memory
    netPbm::NetPbmImage* p = netPbm::ReadNetPbmImage("resource/p1.pbm");
    delete(p);
    // transformation
}
