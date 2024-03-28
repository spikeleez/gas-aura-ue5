// Copyright SpiKe Lee

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraProjectile.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
class UAuraProjectileData;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class AURA_API AAuraProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraProjectile();
	
	UPROPERTY(VisibleAnywhere, Category="Projectile")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="*Projectile Setup")
	float ProjectileLifeSpan = 15.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="*Projectile Setup|Systems")
	TObjectPtr<UNiagaraSystem> ProjectileImpactSystem = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="*Projectile Setup|Systems")
	TObjectPtr<UNiagaraSystem> ProjectileDestroySystem = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="*Projectile Setup|Sounds")
	TObjectPtr<USoundBase> ProjectileSound = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="*Projectile Setup|Sounds")
	TObjectPtr<USoundBase> ProjectileImpactSound = nullptr;
	
private:
	bool bHit = false;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> ProjectileRadius;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> ProjectileNiagara;
	
	UPROPERTY()
	TObjectPtr<UAudioComponent> ProjectileAudioComponent;
};
