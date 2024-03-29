// Copyright SpiKe Lee


#include "Character/AuraCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Aura/Aura.h"
#include "Components/CapsuleComponent.h"
#include "Data/AuraCharacterData.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAuraCharacterBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetupCharacter(CharacterData);
	SetupWeapon(CharacterData);
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
	InitializeDefaultAbilities();
	InitializeDefaultAttributes();
}

FVector AAuraCharacterBase::GetCombatSocketLocation()
{
	check(Weapon);
	check(CharacterData);
	return Weapon->GetSocketLocation(CharacterData->GetCharacterWeaponInfos().WeaponSocket);
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
}

void AAuraCharacterBase::SetupCharacter(UAuraCharacterData* Data) const
{
	if (Data)
	{
		GetMesh()->SetSkeletalMeshAsset(Data->GetCharacterMeshData());
		GetMesh()->SetAnimInstanceClass(Data->GetCharacterAnimClassData());
	}
}

void AAuraCharacterBase::SetupWeapon(UAuraCharacterData* Data) const
{
	if (Data)
	{
		Weapon->SetSkeletalMeshAsset(Data->GetWeaponMeshData());
	}
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}
