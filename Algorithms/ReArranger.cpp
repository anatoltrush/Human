#include "ReArranger.h"

man::ReArranger::ReArranger()
{

}

man::Status man::ReArranger::reArrange(const man::AbstractHuman &native, man::AbstractHuman &cyber)
{
    Status resDists = reArrangeDistances(native, cyber);
    if(resDists == StatusOk){
        Status resAngles = reArrangeAngle(native, cyber);
        return resAngles;
    }
    else return resDists;
}

man::Status man::ReArranger::reArrangeDistances(const man::AbstractHuman &native, man::AbstractHuman &cyber)
{
    AbstractBone* startBoneCyber = cyber.skeleton->getStartBone();
    AbstractBone* startBoneNative = native.skeleton->getStartBone();

    return StatusOk;
}

man::Status man::ReArranger::reArrangeAngle(const man::AbstractHuman &native, man::AbstractHuman &cyber)
{
    return StatusOk;
}
