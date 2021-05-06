#pragma once
#include "BehaviorTree/BTTaskNode.h"

#include "UBTTaskPatrol.generated.h"

UCLASS()
class UBTTaskPatrol : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

