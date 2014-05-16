#include "ElfParser.h"

using namespace std;



ElfParser::ElfParser(const std::string& fileName)
:
    fileName(fileName),
    elfIn(fileName),
    elfHeader(elfIn),
    elfSectionHeader(elfIn, elfHeader)
{

}
