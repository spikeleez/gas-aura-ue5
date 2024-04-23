// Copyright SpiKe Lee


#include "Character/AuraCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Data/AuraCharacterData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/Widget/AuraUserWidget.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
	HealthBar->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBar->SetDrawAtDesiredSize(true);
	HealthBar->SetGenerateOverlapEvents(false);
}

void AAuraCharacterBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetupCharacter(CharacterData);
	SetupWeapon(CharacterData);
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	// Bind Callback Health Delegates (Progress Bar).
	BindCallbackHealthBarDelegates();

	GetCharacterMovement()->MaxWalkSpeed = GetCharacterData()->CharacterInfo.CharacterBaseWalkSpeed;

	AbilitySystemComponent->RegisterGameplayTagEvent(FAuraGameplayTags::Get().Status_Effect_HitReact,
		EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AAuraCharacterBase::OnHitReactAbilityActivated);
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
	/*
	 * This function initializes the Ability Actor Info.
	 * By default, if the Ability System Component resides and is built in the character class, then this function does
	 * not need to be overwritten. However, if it is built and exists within the Player State, then you will necessarily
	 * need to overwrite this function so that it meets the requirements of the InitAbilityActorInfo in a Player State.
	 */

	// Optional check.
	//check(AbilitySystemComponent);

	// Init Ability Actor Info.
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	// Initialize Default Attributes (Only Enemies and NPCs). You can override this function for players.
	if (HasAuthority())
	{
		InitializeDefaultAbilities();
		InitializeDefaultAttributes();
	}
}

void AAuraCharacterBase::BindCallbackHealthBarDelegates()
{
	if (UAuraUserWidget* Widget = Cast<UAuraUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		Widget->SetWidgetController(this);
	}
	
	if (const UAuraAttributeSet* AuraAS = Cast<UAuraAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		});

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		});

		// Broadcast the initial values of Health.
		OnHealthChanged.Broadcast(AuraAS->GetHealth());
		OnMaxHealthChanged.Broadcast(AuraAS->GetMaxHealth());
	}
}

void AAuraCharacterBase::MulticastHandleDeath_Implementation()
{
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	Dissolve();

	bIsDead = true;
}

FVector AAuraCharacterBase::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
	for (const FTaggedMontage& AttackInfo : GetCharacterData()->AnimationInfo.AttackMontages)
	{
		if (MontageTag.MatchesTagExact(AttackInfo.AttackMontageTag))
		{
			if (MontageTag.MatchesTag(GameplayTags.Montage_Attack_Melee_Weapon) ||
			MontageTag.MatchesTag(GameplayTags.Montage_Attack_Ranged_Weapon))
			{
				return Weapon->GetSocketLocation(AttackInfo.AttackSocketName);
			}

			if (MontageTag.MatchesTag(GameplayTags.Montage_Attack_Melee_Unarmed) ||
				MontageTag.MatchesTag(GameplayTags.Montage_Attack_Ranged_Unarmed))
			{
				return GetMesh()->GetSocketLocation(AttackInfo.AttackSocketName);
			}
		}
	}
	return FVector();
}

bool AAuraCharacterBase::IsDead_Implementation() const
{
	return bIsDead;
}

AActor* AAuraCharacterBase::GetAvatar_Implementation()
{
	return this;
}

void AAuraCharacterBase::Dissolve()
{
	if (CharacterData)
	{
		UMaterialInstance* BodyDissolveMat = CharacterData->CharacterInfo.CharacterDissolveMaterial;
		UMaterialInstance* WeaponDissolveMat = CharacterData->WeaponInfo.WeaponDissolveMaterial;
		
		if (IsValid(BodyDissolveMat))
		{
			UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(BodyDissolveMat, this);
			GetMesh()->SetMaterial(0, DynamicMatInst);
			StartDissolveTimeline(DynamicMatInst);
		}
		if (IsValid(WeaponDissolveMat))
		{
			UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(WeaponDissolveMat, this);
			Weapon->SetMaterial(0, DynamicMatInst);
			StartWeaponDissolveTimeline(DynamicMatInst);
		}
	}
}

void AAuraCharacterBase::SetupCharacter(UAuraCharacterData* Data) const
{
	if (Data)
	{
		GetMesh()->SetSkeletalMeshAsset(Data->CharacterInfo.CharacterMesh);
		GetMesh()->SetAnimInstanceClass(Data->AnimationInfo.CharacterAnimClass);

		GetCharacterMovement()->RotationRate = FRotator(0.f, Data->CharacterInfo.CharacterRotationRate, 0.f);
	}
}

void AAuraCharacterBase::SetupWeapon(UAuraCharacterData* Data) const
{
	if (Data)
	{
		Weapon->SetSkeletalMeshAsset(Data->WeaponInfo.WeaponMesh);
		Weapon->SetAnimInstanceClass(Data->AnimationInfo.WeaponAnimClass);
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, Data->WeaponInfo.WeaponHandSocket);
	}
}

UAuraCharacterData* AAuraCharacterBase::GetCharacterData()
{
	if (CharacterData) return CharacterData;
	return nullptr;
}

EAuraCharacterClass AAuraCharacterBase::GetCharacterClass()
{
	return UAuraAbilitySystemLibrary::AuraGetCharacterClass(this, GetCharacterData());
}

void AAuraCharacterBase::OnHitReactAbilityActivated(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : GetCharacterData()->CharacterInfo.CharacterBaseWalkSpeed;
}

void AAuraCharacterBase::Die()
{
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	MulticastHandleDeath();
}

TArray<FTaggedMontage> AAuraCharacterBase::GetAttackMontagesInfo_Implementation()
{
	return GetCharacterData()->AnimationInfo.AttackMontages;
}

void AAuraCharacterBase::InitializeDefaultAttributes() const
{
	if (!HasAuthority()) return;
	UAuraAbilitySystemLibrary::GiveGrantedAttributes(this, CharacterData, AbilitySystemComponent);
}

void AAuraCharacterBase::InitializeDefaultAbilities() const
{
	if (!HasAuthority()) return;
	UAuraAbilitySystemLibrary::GiveGrantedAbilities(this, CharacterData, AbilitySystemComponent);
	UAuraAbilitySystemLibrary::GiveGrantedCommonAbilities(this, CharacterData, AbilitySystemComponent);
}