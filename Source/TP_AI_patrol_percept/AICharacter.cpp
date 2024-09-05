#include "AICharacter.h"
#include "Components/SplineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "AIController.h"
#include "NavigationSystem.h"


AAICharacter::AAICharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    CurrentPatrolSplinePoint = 0;
    bReversePatrolDirection = false;
}

void AAICharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AAICharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AAICharacter::MoveAlongPatrolPath()
{
    if (!PatrolSplineActor) return;

    USplineComponent* SplineComponent = PatrolSplineActor->FindComponentByClass<USplineComponent>();
    if (!SplineComponent) return;

    FVector CurrentLocation = GetActorLocation();
    FVector TargetLocation = SplineComponent->GetLocationAtSplinePoint(CurrentPatrolSplinePoint, ESplineCoordinateSpace::World);
    CurrentLocation.Z = 0.0f;
    TargetLocation.Z = 0.0f;

    float DistanceToTarget = FVector::Dist(CurrentLocation, TargetLocation);

    if (DistanceToTarget <= PatrolPointReachedAcceptanceDistance)
    {
        OnReachedSplinePoint();
    }

    AAIController* AIController = Cast<AAIController>(GetController());
    if (AIController)
    {
        GetCharacterMovement()->MaxWalkSpeed = PatrolMovementSpeed;
        AIController->MoveToLocation(TargetLocation, -1.0f, true, true, false, true, 0, true);
    }
}

void AAICharacter::ChaseTargetAtLocation(FVector Location)
{
    FVector CurrentLocation = GetActorLocation();
    FVector TargetLocation = Location;
    CurrentLocation.Z = 0.0f;
    TargetLocation.Z = 0.0f;

    float DistanceToTarget = FVector::Dist(CurrentLocation, TargetLocation);

    if (DistanceToTarget <= ChaseTargetReachedAcceptanceDistance)
    {
        return;
    }

    AAIController* AIController = Cast<AAIController>(GetController());
    if (AIController)
    {
        GetCharacterMovement()->MaxWalkSpeed = ChasingMovementSpeed;
        AIController->MoveToLocation(Location, -1.0f, true, true, false, true, 0, true);
    }
}

void AAICharacter::OnReachedSplinePoint()
{
    if (!PatrolSplineActor) return;

    USplineComponent* SplineComponent = PatrolSplineActor->FindComponentByClass<USplineComponent>();;
    if (!SplineComponent) return;

    int32 NumSplinePoints = SplineComponent->GetNumberOfSplinePoints();

    if (!bReversePatrolDirection)
    {
        CurrentPatrolSplinePoint++;
        if (CurrentPatrolSplinePoint >= NumSplinePoints)
        {
            CurrentPatrolSplinePoint = NumSplinePoints - 1;
            bReversePatrolDirection = true;
        }
    }
    else
    {
        CurrentPatrolSplinePoint--;
        if (CurrentPatrolSplinePoint < 0)
        {
            CurrentPatrolSplinePoint = 0;
            bReversePatrolDirection = false;
        }
    }
}
