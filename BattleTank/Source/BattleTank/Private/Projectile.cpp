// Copyright Paul Klinker, 2019.

#include "../Public/Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	if (!ensure(CollisionMesh)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("AProjectile Collsion Mesh can't be created."));
		return;
	}

	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(true);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	FAttachmentTransformRules AttachXformRules = FAttachmentTransformRules::KeepRelativeTransform;
	LaunchBlast->AttachToComponent(RootComponent, AttachXformRules);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachToComponent(RootComponent, AttachXformRules);
	ImpactBlast->bAutoActivate = false;

	if (!ensure(LaunchBlast))
	{
		UE_LOG(LogTemp, Warning, TEXT("AProjectile Launch Blast can't be created."));
		return;
	}

	CannonProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Cannon Projectile Movement"));
	CannonProjectileMovement->bAutoActivate = false;
	if (!ensure(CannonProjectileMovement))
	{
		UE_LOG(LogTemp, Warning, TEXT("AProjectile CannonProjectileMovement can't be created."));
		return;
	}

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent, AttachXformRules);
	ExplosionForce->bAutoActivate = false;
}

void AProjectile::LaunchProjectile(float LaunchSpeed)
{
	auto Time = GetWorld()->GetTimeSeconds(); 
	///UE_LOG(LogTemp, Warning, TEXT("%f Firing cannon at speed %f."), Time, LaunchSpeed);
	CannonProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector*LaunchSpeed);
	CannonProjectileMovement->Activate();
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

void AProjectile::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->Activate();
	ExplosionForce->FireImpulse(); // applies the force.
}

