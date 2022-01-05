#include "Human.h"

man::Human::Human()
{
    skeleton = new HumanSkeleton();
}

QMap<QString, QVariant> man::Human::getPropertyList() const
{

}
