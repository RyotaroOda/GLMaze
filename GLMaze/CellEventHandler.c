#include "Header.h"
#include "CellEventHandler.h"
#include "TrapAnimation.h"
#include "GoalAnimation.h"

//マスの着地判定
void cellEvent(cellType type){
    switch(type){
        case trap:
            trapAnimation(0);
            score -= 10;
            break;
            
        case goal:
            BoxAnimationTrigger(0);
            break;
            
        default:
            break;
    }
}
