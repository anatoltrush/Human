#include "AbstractHuman.h"

man::AbstractHuman::AbstractHuman()
{

}

man::AbstractHuman::~AbstractHuman()
{    
    delete skeleton;
    std::cout << "-XXX-Delete AbsHum-XXX-" << std::endl; // NOTE: delete
}
