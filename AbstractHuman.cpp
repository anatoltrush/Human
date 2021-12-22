#include "AbstractHuman.h"

man::AbstractHuman::AbstractHuman()
{

}

man::AbstractHuman::~AbstractHuman()
{    
    delete skeleton;
    std::cout << "-Delete AbsHuman-" <<  skeleton->name.toStdString() << std::endl; // NOTE: delete
}
