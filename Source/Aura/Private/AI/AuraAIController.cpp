// Copyright SpiKe Lee


#include "AI/AuraAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AAuraAIController::AAuraAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComponent");
	check(Blackboard);
	BehaviorTree = CreateDefaultSubobject<UBehaviorTree>("BehaviorTree");
	check(BehaviorTree);
}
