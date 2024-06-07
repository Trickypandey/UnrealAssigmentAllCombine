#pragma once

#include "CoreMinimal.h"

class AMeshGenerator;

class ASSIGNMENT6_API AsyncScatterTask : public FNonAbandonableTask
{
public:

	AsyncScatterTask(AMeshGenerator* MeshGenerator);

	void DoWork();

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(AsyncScatterTask, STATGROUP_ThreadPoolAsyncTasks);
	}

private:

	AMeshGenerator* MeshGenerator;
};
