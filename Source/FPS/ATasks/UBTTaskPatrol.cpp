 
#include "UBTTaskPatrol.h"


#include "NavigationSystem.h"
#include "NPCAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UBTTaskPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANPCAIController* Controller = Cast<ANPCAIController>(OwnerComp.GetOwner());

	float PatrolRadius = Controller->GetPatrolRadius();

	if(PatrolRadius > 0.f)
	{
		FNavLocation ResultLocation;

		if(UNavigationSystemV1::GetNavigationSystem(&OwnerComp)->GetRandomReachablePointInRadius(Controller->GetNavAgentLocation(),PatrolRadius,ResultLocation))
		{
			Controller->GetBlackboardComponent()->SetValueAsVector(Controller->GetPatrolTargetKey(), ResultLocation.Location);

			return EBTNodeResult::Succeeded;
		}
		
	}
	return EBTNodeResult::Failed;
}
