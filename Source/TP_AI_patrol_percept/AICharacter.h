#pragma once

#include "CoreMinimal.h"
#include "TP_AI_patrol_perceptCharacter.h"
#include "AICharacter.generated.h"




UCLASS()
class TP_AI_PATROL_PERCEPT_API AAICharacter : public ATP_AI_patrol_perceptCharacter
{
    GENERATED_BODY()

public:
    AAICharacter();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
    AActor* PatrolSplineActor;

    UPROPERTY(EditAnywhere, Category = "Patrol")
    float PatrolMovementSpeed = 100.0f;

    UPROPERTY(EditAnywhere, Category = "Patrol")
    float PatrolPointReachedAcceptanceDistance = 50.0f;

    UPROPERTY(EditAnywhere, Category = "PlayerChasing")
    float ChasingMovementSpeed = 500.0f;

    UPROPERTY(EditAnywhere, Category = "PlayerChasing")
    float ChaseTargetReachedAcceptanceDistance = 100.0f;

    UFUNCTION(BlueprintCallable)
    void MoveAlongPatrolPath();

    UFUNCTION(BlueprintCallable)
    void ChaseTargetAtLocation(FVector Location);

private:
    int32 CurrentPatrolSplinePoint;
    bool bReversePatrolDirection;

    void OnReachedSplinePoint();
};
