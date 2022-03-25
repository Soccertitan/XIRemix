// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/XICharacterBase.h"
#include "Abilities/AttributeSetGlobal.h"
#include "Abilities/XIAbilitySystemComponent.h"
#include "Abilities/XIGameplayAbility.h"
#include "Net/UnrealNetwork.h"
#include "Components/CapsuleComponent.h"
#include "Characters/XICharacterMovementComponent.h"
#include "Interfaces/AnimBPInterface.h"
#include "AI/XIAIControllerBase.h"

// Sets default values
AXICharacterBase::AXICharacterBase(const class FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UXICharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	bReplicates = true;
	bAlwaysRelevant = true;
	bUseControllerRotationYaw = false;
	
	PrimaryActorTick.bStartWithTickEnabled = false;
	GetCapsuleComponent()->PrimaryComponentTick.bStartWithTickEnabled = false;
	GetMesh()->PrimaryComponentTick.bStartWithTickEnabled = false;

	// Cache Tags
	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Gameplay.Dead"));

	AbilitySystemComponent = CreateDefaultSubobject<UXIAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAttributeSetGlobal>("AttributeSet");

	// Default AI Controller
	AIControllerClass = AXIAIControllerBase::StaticClass();
}

// Called when the game starts or when spawned
void AXICharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		HitPointsChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHitPointsAttribute()).AddUObject(this, &AXICharacterBase::HitPointsChanged);
		HitPointsMaxChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHitPointsMaxAttribute()).AddUObject(this, &AXICharacterBase::HitPointsMaxChanged);
		ManaPointsChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetManaPointsAttribute()).AddUObject(this, &AXICharacterBase::ManaPointsChanged);
		TacticalPointsChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetTacticalPointsAttribute()).AddUObject(this, &AXICharacterBase::TacticalPointsChanged);
	}
}

UAbilitySystemComponent * AXICharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

int32 AXICharacterBase::GetAbilityLevel(EXIAbilityInputID AbilityID) const
{
	return 1;
}

void AXICharacterBase::AddCharacterAbilities()
{
	// Grant abilities, but only on the server	
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent || AbilitySystemComponent->CharacterAbilitiesGiven || !AbilitySets.IsValidIndex(0))
	{
		return;
	}

	for(UXIAbilitySet* AbilitySet : AbilitySets)
	{
		AbilitySet->GiveAbilitySetTo(AbilitySystemComponent);
	}

	AbilitySystemComponent->CharacterAbilitiesGiven = true;
}

void AXICharacterBase::InitializeAttributes()
{
	if (!AbilitySystemComponent)
	{
		return;
	}

	if (!DefaultAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	// Can run on Server and Client
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
	}
}

#pragma region CharacterName

bool AXICharacterBase::Server_SetCharacterName_Validate(FText Name)
{
	return true;
}

void AXICharacterBase::Server_SetCharacterName_Implementation(FText Name)
{
	CharacterName = Name;
}

#pragma endregion CharacterName

#pragma region AttributeChangeCallbacks

void AXICharacterBase::HitPointsChanged(const FOnAttributeChangeData & Data)
{
	float HitPoints = Data.NewValue;
	if (!IsAlive() && !AbilitySystemComponent->HasMatchingGameplayTag(DeadTag))
	{
		Die();
	}
}

void AXICharacterBase::HitPointsMaxChanged(const FOnAttributeChangeData & Data)
{
	float HitPointsMax = Data.NewValue;
}

void AXICharacterBase::ManaPointsChanged(const FOnAttributeChangeData & Data)
{
	float ManaPoints = Data.NewValue;
}

void AXICharacterBase::TacticalPointsChanged(const FOnAttributeChangeData & Data)
{
	float TacticalPoints = Data.NewValue;
}

#pragma endregion AttributeChangeCallbacks

void AXICharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const 
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AXICharacterBase, CharacterName);
}

#pragma region AnimationMontages

UAnimMontage* AXICharacterBase::GetRandomMontage(TArray <UAnimMontage*> AnimMontage) const
{
	if (!AnimMontage.IsValidIndex(0))
	{
		return nullptr;
	}
	int number = FMath::RandRange(0, AnimMontage.Num() - 1);
	return AnimMontage[number];
}

UAnimMontage* AXICharacterBase::GetCombatStartMontage()
{
	if (!CombatMontages)
	{
		return nullptr;
	}

	switch (CombatStyle)
	{
		case ECombatStyle::Unarmed:
		return CombatMontages->UnarmedStartCombat;

		case ECombatStyle::Sword:
		return CombatMontages->SwordStartCombat;

		case ECombatStyle::Axe:
		return CombatMontages->AxeStartCombat;

		case ECombatStyle::Dagger:
		return CombatMontages->DaggerStartCombat;

		case ECombatStyle::Club:
		return CombatMontages->ClubStartCombat;

		case ECombatStyle::Katana:
		return CombatMontages->KatanaStartCombat;

		case ECombatStyle::Hand2Hand:
		return CombatMontages->H2HStartCombat;

		case ECombatStyle::GreatKatana:
		return CombatMontages->GreatKatanaStartCombat;

		case ECombatStyle::GreatSword:
		return CombatMontages->GreatSwordStartCombat;

		case ECombatStyle::TwoHanded:
		return CombatMontages->TwoHandedStartCombat;
	}
	return nullptr;
}

UAnimMontage* AXICharacterBase::GetCombatExitMontage()
{
	if (!CombatMontages)
	{
		return nullptr;
	}

	switch (CombatStyle)
	{
		case ECombatStyle::Unarmed:
		return CombatMontages->UnarmedExitCombat;

		case ECombatStyle::Sword:
		return CombatMontages->SwordExitCombat;

		case ECombatStyle::Axe:
		return CombatMontages->AxeExitCombat;

		case ECombatStyle::Dagger:
		return CombatMontages->DaggerExitCombat;

		case ECombatStyle::Club:
		return CombatMontages->ClubExitCombat;

		case ECombatStyle::Katana:
		return CombatMontages->KatanaExitCombat;

		case ECombatStyle::Hand2Hand:
		return CombatMontages->H2HExitCombat;

		case ECombatStyle::GreatKatana:
		return CombatMontages->GreatKatanaExitCombat;

		case ECombatStyle::GreatSword:
		return CombatMontages->GreatSwordExitCombat;

		case ECombatStyle::TwoHanded:
		return CombatMontages->TwoHandedExitCombat;
	}
	return nullptr;
}

#pragma endregion AnimationMontages

#pragma region XICharacterInterfaceFunctions

AXICharacterBase * AXICharacterBase::GetXICharacterBase()
{
	return this;
}

FText AXICharacterBase::GetCharacterName() const
{
	return CharacterName;
}

AActor* AXICharacterBase::GetMainTarget() const
{
	return MainTarget;
}

void AXICharacterBase::SetMainTarget(AActor* TargetActor)
{
	if(TargetActor)
	{
		MainTarget = TargetActor;
	}
	else
	{
		MainTarget = nullptr;
	}
}

AActor* AXICharacterBase::GetSubTarget() const
{
	return SubTarget;
}

EXITeamAttitude AXICharacterBase::GetAttitudeTowardsActor(AActor* OtherActor) const
{
	IXICharacterInterface* XICharInt = Cast<IXICharacterInterface>(OtherActor);
	if (XICharInt)
	{
		EXITeam OtherTeam = XICharInt->GetXITeam();
		if (OtherTeam == EXITeam::Neutral)
		{
			return EXITeamAttitude::Neutral;
		}
		
		if (OtherTeam == XITeam)
		{
			return EXITeamAttitude::Friendly;
		}
		
		if (OtherTeam != XITeam)
		{
			return EXITeamAttitude::Hostile;
		}
	}
	return EXITeamAttitude::Neutral;
}

EXITeam AXICharacterBase::GetXITeam() const
{
	return XITeam;
}

float AXICharacterBase::GetCapsuleRadius() const
{
	return GetCapsuleComponent()->GetScaledCapsuleRadius();
}

bool AXICharacterBase::IsAlive() const
{
	return GetHitPoints() > 0.0f;
}

#pragma region AnimationMontageGetters

UAnimMontage* AXICharacterBase::GetAutoAttackMontage() const
{
	IAnimBPInterface* IntAnimBP = Cast<IAnimBPInterface>(GetMesh()->GetAnimInstance());
	if(IntAnimBP && CombatMontages)
	{
		float Speed = IntAnimBP->GetSpeed();
		float Direction = IntAnimBP->GetDirection();
		
		// Stationary Attack
		if(FMath::IsNearlyZero(Speed))
		{
			switch (CombatStyle)
			{
				case ECombatStyle::Unarmed:
				return GetRandomMontage(CombatMontages->UnarmedBasicAttacks);

				case ECombatStyle::Sword:
				return GetRandomMontage(CombatMontages->SwordBasicAttacks);

				case ECombatStyle::Axe:
				return GetRandomMontage(CombatMontages->AxeBasicAttacks);

				case ECombatStyle::Dagger:
				return GetRandomMontage(CombatMontages->DaggerBasicAttacks);

				case ECombatStyle::Club:
				return GetRandomMontage(CombatMontages->ClubBasicAttacks);

				case ECombatStyle::Katana:
				return GetRandomMontage(CombatMontages->KatanaBasicAttacks);

				case ECombatStyle::Hand2Hand:
				return GetRandomMontage(CombatMontages->H2HBasicAttacks);

				case ECombatStyle::GreatKatana:
				return GetRandomMontage(CombatMontages->GreatKatanaBasicAttacks);

				case ECombatStyle::GreatSword:
				return GetRandomMontage(CombatMontages->GreatSwordBasicAttacks);

				case ECombatStyle::TwoHanded:
				return GetRandomMontage(CombatMontages->TwoHandedBasicAttacks);
			}
		}
		// Moving Right Attack Montage
		else if((Direction > 40) & (Direction < 140))
		{
			switch (CombatStyle)
			{
				case ECombatStyle::Unarmed:
				return CombatMontages->UnarmedAtkRight;

				case ECombatStyle::Sword:
				return CombatMontages->SwordAtkRight;

				case ECombatStyle::Axe:
				return CombatMontages->AxeAtkRight;

				case ECombatStyle::Dagger:
				return CombatMontages->DaggerAtkRight;

				case ECombatStyle::Club:
				return CombatMontages->ClubAtkRight;

				case ECombatStyle::Katana:
				return CombatMontages->KatanaAtkRight;

				case ECombatStyle::Hand2Hand:
				return CombatMontages->H2HAtkRight;

				case ECombatStyle::GreatKatana:
				return CombatMontages->GreatKatanaAtkRight;

				case ECombatStyle::GreatSword:
				return CombatMontages->GreatSwordAtkRight;

				case ECombatStyle::TwoHanded:
				return CombatMontages->TwoHandedAtkRight;
			}
		}
		// Moving Left Attack Montage
		else if((Direction > -140) & (Direction < -40))
		{
			switch (CombatStyle)
			{
				case ECombatStyle::Unarmed:
				return CombatMontages->UnarmedAtkLeft;

				case ECombatStyle::Sword:
				return CombatMontages->SwordAtkLeft;

				case ECombatStyle::Axe:
				return CombatMontages->AxeAtkLeft;

				case ECombatStyle::Dagger:
				return CombatMontages->DaggerAtkLeft;

				case ECombatStyle::Club:
				return CombatMontages->ClubAtkLeft;

				case ECombatStyle::Katana:
				return CombatMontages->KatanaAtkLeft;

				case ECombatStyle::Hand2Hand:
				return CombatMontages->H2HAtkLeft;

				case ECombatStyle::GreatKatana:
				return CombatMontages->GreatKatanaAtkLeft;

				case ECombatStyle::GreatSword:
				return CombatMontages->GreatSwordAtkLeft;

				case ECombatStyle::TwoHanded:
				return CombatMontages->TwoHandedAtkLeft;
			}
		}
		// Moving Backwards Attack Montage
		else if((Direction >= 140) | (Direction <= -140))
		{
			switch (CombatStyle)
			{
				case ECombatStyle::Unarmed:
				return CombatMontages->UnarmedAtkNeutral;

				case ECombatStyle::Sword:
				return CombatMontages->SwordAtkNeutral;

				case ECombatStyle::Axe:
				return CombatMontages->AxeAtkNeutral;

				case ECombatStyle::Dagger:
				return CombatMontages->DaggerAtkNeutral;

				case ECombatStyle::Club:
				return CombatMontages->ClubAtkNeutral;

				case ECombatStyle::Katana:
				return CombatMontages->KatanaAtkNeutral;

				case ECombatStyle::Hand2Hand:
				return CombatMontages->H2HAtkNeutral;

				case ECombatStyle::GreatKatana:
				return CombatMontages->GreatKatanaAtkNeutral;

				case ECombatStyle::GreatSword:
				return CombatMontages->GreatSwordAtkNeutral;

				case ECombatStyle::TwoHanded:
				return CombatMontages->TwoHandedAtkNeutral;
			}
		}
		// Moving Forwards Attack Montage
		else
		{
			switch (CombatStyle)
			{
				case ECombatStyle::Unarmed:
				return CombatMontages->UnarmedAtkFw;

				case ECombatStyle::Sword:
				return CombatMontages->SwordAtkFw;

				case ECombatStyle::Axe:
				return CombatMontages->AxeAtkFw;

				case ECombatStyle::Dagger:
				return CombatMontages->DaggerAtkFw;

				case ECombatStyle::Club:
				return CombatMontages->ClubAtkFw;

				case ECombatStyle::Katana:
				return CombatMontages->KatanaAtkFw;

				case ECombatStyle::Hand2Hand:
				return CombatMontages->H2HAtkFw;

				case ECombatStyle::GreatKatana:
				return CombatMontages->GreatKatanaAtkFw;

				case ECombatStyle::GreatSword:
				return CombatMontages->GreatSwordAtkFw;

				case ECombatStyle::TwoHanded:
				return CombatMontages->TwoHandedAtkFw;
			}
		}
	}
	return nullptr;
}

UXICharacterCombatMontages* AXICharacterBase::GetXICharacterCombatMontages() const
{
	return CombatMontages;
}

#pragma endregion AnimationMontageGetters

#pragma region AttributeGetters

float AXICharacterBase::GetHitPoints() const
{
	if (AttributeSet)
	{
		return AttributeSet->GetHitPoints();
	}
	return 0.0f;
}

float AXICharacterBase::GetHitPointsMax() const
{
	if (AttributeSet)
	{
		return AttributeSet->GetHitPointsMax();
	}

	return 0.0f;
}

float AXICharacterBase::GetManaPoints() const
{
	if (AttributeSet)
	{
		return AttributeSet->GetManaPoints();
	}

	return 0.0f;
}

float AXICharacterBase::GetManaPointsMax() const
{
	if (AttributeSet)
	{
		return AttributeSet->GetManaPointsMax();
	}

	return 0.0f;
}

float AXICharacterBase::GetTacticalPoints() const
{
	if (AttributeSet)
	{
		return AttributeSet->GetTacticalPoints();
	}

	return 0.0f;
}

float AXICharacterBase::GetTacticalPointsMax() const
{
	if (AttributeSet)
	{
		return AttributeSet->GetTacticalPointsMax();
	}

	return 0.0f;
}

float AXICharacterBase::GetMoveSpeed() const
{
	if (AttributeSet)
	{
		return AttributeSet->GetMoveSpeed();
	}

	return 0.0f;
}

float AXICharacterBase::GetCharacterLevel() const
{
	return 0.f;
}

#pragma endregion AttributeGetters

#pragma endregion XICharacterInterfaceFunctions

void AXICharacterBase::Die()
{
	OnCharacterDied.Broadcast(this);
	
	// GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->GravityScale = 0;
	GetCharacterMovement()->Velocity = FVector(0);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AddLooseGameplayTag(DeadTag);
	}
}