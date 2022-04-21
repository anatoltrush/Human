#include "MediaPipeReArranger.h"

man::Status man::MediaPipeReArranger::reArrange(man::AbstractHuman &human)
{
    makeGroups(human);

    offsetGroups();

    return StatusOk;
}

void man::MediaPipeReArranger::adjustPoints()
{

}

void man::MediaPipeReArranger::offsetGroups()
{
    for(auto group = groups.begin(); group != groups.end(); group++){
        QVector3D offsetDistance = group.value().front()->basePoint - anchorPoints[group.key()];
        // --- TODO: continue... ---
    }
}

void man::MediaPipeReArranger::scaleGroups()
{

}

void man::MediaPipeReArranger::rotateGroups()
{

}

void man::MediaPipeReArranger::makeGroups(AbstractHuman &human)
{
    groups.clear();
    // ---
    for(auto anchor = anchorPoints.begin(); anchor != anchorPoints.end(); anchor++){
        for(auto bn = human.skeleton->bones.begin(); bn != human.skeleton->bones.end(); bn++){
            if(!bn.value()) continue;
            if(anchor.key() == bn.value()->basePoint.str){
                std::vector<AbstractBone*> allSegments = {bn.value()};
                // ---
                std::vector<AbstractBone*> vecParents = {bn.value()};
                while (true) {
                    std::vector<AbstractBone*> vecChildren;
                    for(size_t j = 0; j < vecParents.size(); j++){
                        for(size_t k = 0; k < vecParents[j]->childrenPointers.size(); k++){
                            if(vecParents[j]->childrenPointers[k] != nullptr && vecParents[j]->childrenPointers[k]->basePoint.str == notAvlbl){
                                vecChildren.push_back(vecParents[j]->childrenPointers[k]);
                            }
                        }
                    }
                    // -----
                    if(vecChildren.empty()) break;
                    allSegments.insert(allSegments.end(), vecChildren.begin(), vecChildren.end());
                    vecParents = vecChildren;
                }
                // --- --- ---
                if(allSegments.size() > 0)
                    groups.insert(anchor.key(), allSegments);
            }
        }
    }
}
