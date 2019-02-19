// Copyright Paul Klinker, 2019.

#include "SprungWheel.h"

//#include "Tank.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("WheelConstraint"));
	SetRootComponent(Spring);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(Spring);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
	AxleWheelConstraint->SetupAttachment(Axle);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);
	Wheel->SetNotifyRigidBodyCollision(true);
	// gets the parent actor
	if (GetAttachParentActor())
	{
		UPrimitiveComponent *BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
		if (!BodyRoot)
		{
			UE_LOG(LogTemp, Warning, TEXT("Can't find body root."));
			return;
		}
		
		Spring->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
		AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
	}

}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("Ticking."));
	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ticking is post physics."));
		TotalForceMagnitudeThisFrame = 0.;
	}

}

void ASprungWheel::AddDrivingForce(float TrackMaxDrivingForce, float ForceMagnitude)
{
	// TODO only apply when on ground
	TotalForceMagnitudeThisFrame += ForceMagnitude;
	if (TotalForceMagnitudeThisFrame > TrackMaxDrivingForce)
	{
		TotalForceMagnitudeThisFrame = TrackMaxDrivingForce;
	}
	UE_LOG(LogTemp, Warning, TEXT("TotalForceMagnitudeThisFrame - %f"), TotalForceMagnitudeThisFrame);
}


void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//Super::OnHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	ApplyForce();
}

void ASprungWheel::ApplyForce()
{
	UE_LOG(LogTemp, Warning, TEXT("Applying Force of %f."), TotalForceMagnitudeThisFrame);
	Wheel->AddForce(Axle->GetForwardVector()*TotalForceMagnitudeThisFrame);
}
