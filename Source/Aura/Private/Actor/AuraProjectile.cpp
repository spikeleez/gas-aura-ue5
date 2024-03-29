// Copyright SpiKe Lee


#include "Actor/AuraProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Aura/Aura.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

AAuraProjectile::AAuraProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileRadius = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(ProjectileRadius);
	ProjectileRadius->SetCollisionObjectType(ECC_Projectile);
	ProjectileRadius->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileRadius->SetCollisionResponseToAllChannels(ECR_Ignore);
	ProjectileRadius->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	ProjectileRadius->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	ProjectileRadius->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
	ProjectileNiagara = CreateDefaultSubobject<UNiagaraComponent>("Projectile");
	ProjectileNiagara->SetupAttachment(GetRootComponent());
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 550.f;
	ProjectileMovement->MaxSpeed = ProjectileMovement->InitialSpeed;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

void AAuraProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileRadius->OnComponentBeginOverlap.AddDynamic(this, &AAuraProjectile::OnSphereOverlap);
	
	SetLifeSpan(ProjectileLifeSpan);
	ProjectileAudioComponent = UGameplayStatics::SpawnSoundAttached(ProjectileSound, GetRootComponent(), NAME_None,
		FVector(ForceInit), FRotator::ZeroRotator, EAttachLocation::SnapToTarget,true);
	
}

void AAuraProjectile::Destroyed()
{
	if (!bHit && !HasAuthority())
	{
		UGameplayStatics::PlaySoundAtLocation(this, ProjectileImpactSound, GetActorLocation(), FRotator::ZeroRotator);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ProjectileImpactSystem, GetActorLocation());
	}
	Super::Destroyed();
}

void AAuraProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UGameplayStatics::PlaySoundAtLocation(this, ProjectileImpactSound, GetActorLocation(), FRotator::ZeroRotator);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ProjectileImpactSystem, GetActorLocation());
	
	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
		}
		Destroy();
	}
	else
	{
		bHit = true;
	}
}

