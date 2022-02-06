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
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent || AbilitySystemComponent->CharacterAbilitiesGiven)
	{
		return;
	}

	for (TSubclassOf<UXIGameplayAbility>& StartupAbility : CharacterAbilities)
	{
		AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(StartupAbility, GetAbilityLevel(StartupAbility.GetDefaultObject()->AbilityID), static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
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

void AXICharacterBase::AddStartupEffects()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent || AbilitySystemComponent->StartupEffectsApplied)
	{
		UE_LOG(LogTemp, Warning, TEXT("Startup Effects Will not Apply"));
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempting to apply GE Spec to Self"));
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 0, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
			UE_LOG(LogTemp, Warning, TEXT("Applied GE Spec to Self"));
		}
		UE_LOG(LogTemp, Warning, TEXT("GE Handle Invalid"));
	}

	AbilitySystemComponent->StartupEffectsApplied = true;
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

UAnimMontage* AXICharacterBase::GetRandomMontage(TArray <UAnimMontage*> AnimMontage)
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
	switch (CombatStyle)
	{
		case ECombatStyle::Unarmed:
		return UnarmedStartCombat;

		case ECombatStyle::Sword:
		return SwordStartCombat;

		case ECombatStyle::Axe:
		return AxeStartCombat;

		case ECombatStyle::Dagger:
		return DaggerStartCombat;

		case ECombatStyle::Club:
		return ClubStartCombat;

		case ECombatStyle::Katana:
		return KatanaStartCombat;

		case ECombatStyle::Hand2Hand:
		return H2HStartCombat;

		case ECombatStyle::GreatKatana:
		return GreatKatanaStartCombat;

		case ECombatStyle::GreatSword:
		return GreatSwordStartCombat;

		case ECombatStyle::TwoHanded:
		return TwoHandedStartCombat;
	}
	return nullptr;
}

UAnimMontage* AXICharacterBase::GetCombatExitMontage()
{
	switch (CombatStyle)
	{
		case ECombatStyle::Unarmed:
		return UnarmedExitCombat;

		case ECombatStyle::Sword:
		return SwordExitCombat;

		case ECombatStyle::Axe:
		return AxeExitCombat;

		case ECombatStyle::Dagger:
		return DaggerExitCombat;

		case ECombatStyle::Club:
		return ClubExitCombat;

		case ECombatStyle::Katana:
		return KatanaExitCombat;

		case ECombatStyle::Hand2Hand:
		return H2HExitCombat;

		case ECombatStyle::GreatKatana:
		return GreatKatanaExitCombat;

		case ECombatStyle::GreatSword:
		return GreatSwordExitCombat;

		case ECombatStyle::TwoHanded:
		return TwoHandedExitCombat;
	}
	return nullptr;
}

#pragma endregion AnimationMontages

#pragma region XICharacterInterfaceFunctions

FText AXICharacterBase::GetCharacterName() const
{
	return CharacterName;
}

AActor* AXICharacterBase::GetMainTarget() const
{
	return MainTarget;
}

AActor* AXICharacterBase::GetSubTarget() const
{
	return SubTarget;
}

UAnimMontage* AXICharacterBase::GetAutoAttackMontage()
{
	IAnimBPInterface* IntAnimBP = Cast<IAnimBPInterface>(GetMesh()->GetAnimInstance());
	if(IntAnimBP)
	{
		float Speed = IntAnimBP->GetSpeed();
		float Direction = IntAnimBP->GetDirection();
		
		// Stationary Attack
		if(FMath::IsNearlyZero(Speed))
		{
			switch (CombatStyle)
			{
				case ECombatStyle::Unarmed:
				return GetRandomMontage(UnarmedBasicAttacks);

				case ECombatStyle::Sword:
				return GetRandomMontage(SwordBasicAttacks);

				case ECombatStyle::Axe:
				return GetRandomMontage(AxeBasicAttacks);

				case ECombatStyle::Dagger:
				return GetRandomMontage(DaggerBasicAttacks);

				case ECombatStyle::Club:
				return GetRandomMontage(ClubBasicAttacks);

				case ECombatStyle::Katana:
				return GetRandomMontage(KatanaBasicAttacks);

				case ECombatStyle::Hand2Hand:
				return GetRandomMontage(H2HBasicAttacks);

				case ECombatStyle::GreatKatana:
				return GetRandomMontage(GreatKatanaBasicAttacks);

				case ECombatStyle::GreatSword:
				return GetRandomMontage(GreatSwordBasicAttacks);

				case ECombatStyle::TwoHanded:
				return GetRandomMontage(TwoHandedBasicAttacks);
			}
		}
		// Moving Right Attack Montage
		else if((Direction > 40) & (Direction < 140))
		{
			switch (CombatStyle)
			{
				case ECombatStyle::Unarmed:
				return UnarmedAtkRight;

				case ECombatStyle::Sword:
				return SwordAtkRight;

				case ECombatStyle::Axe:
				return AxeAtkRight;

				case ECombatStyle::Dagger:
				return DaggerAtkRight;

				case ECombatStyle::Club:
				return ClubAtkRight;

				case ECombatStyle::Katana:
				return KatanaAtkRight;

				case ECombatStyle::Hand2Hand:
				return H2HAtkRight;

				case ECombatStyle::GreatKatana:
				return GreatKatanaAtkRight;

				case ECombatStyle::GreatSword:
				return GreatSwordAtkRight;

				case ECombatStyle::TwoHanded:
				return TwoHandedAtkRight;
			}
		}
		// Moving Left Attack Montage
		else if((Direction > -140) & (Direction < -40))
		{
			switch (CombatStyle)
			{
				case ECombatStyle::Unarmed:
				return UnarmedAtkLeft;

				case ECombatStyle::Sword:
				return SwordAtkLeft;

				case ECombatStyle::Axe:
				return AxeAtkLeft;

				case ECombatStyle::Dagger:
				return DaggerAtkLeft;

				case ECombatStyle::Club:
				return ClubAtkLeft;

				case ECombatStyle::Katana:
				return KatanaAtkLeft;

				case ECombatStyle::Hand2Hand:
				return H2HAtkLeft;

				case ECombatStyle::GreatKatana:
				return GreatKatanaAtkLeft;

				case ECombatStyle::GreatSword:
				return GreatSwordAtkLeft;

				case ECombatStyle::TwoHanded:
				return TwoHandedAtkLeft;
			}
		}
		// Moving Backwards Attack Montage
		else if((Direction >= 140) | (Direction <= -140))
		{
			switch (CombatStyle)
			{
				case ECombatStyle::Unarmed:
				return UnarmedAtkNeutral;

				case ECombatStyle::Sword:
				return SwordAtkNeutral;

				case ECombatStyle::Axe:
				return AxeAtkNeutral;

				case ECombatStyle::Dagger:
				return DaggerAtkNeutral;

				case ECombatStyle::Club:
				return ClubAtkNeutral;

				case ECombatStyle::Katana:
				return KatanaAtkNeutral;

				case ECombatStyle::Hand2Hand:
				return H2HAtkNeutral;

				case ECombatStyle::GreatKatana:
				return GreatKatanaAtkNeutral;

				case ECombatStyle::GreatSword:
				return GreatSwordAtkNeutral;

				case ECombatStyle::TwoHanded:
				return TwoHandedAtkNeutral;
			}
		}
		// Moving Forwards Attack Montage
		else
		{
			switch (CombatStyle)
			{
				case ECombatStyle::Unarmed:
				return UnarmedAtkFw;

				case ECombatStyle::Sword:
				return SwordAtkFw;

				case ECombatStyle::Axe:
				return AxeAtkFw;

				case ECombatStyle::Dagger:
				return DaggerAtkFw;

				case ECombatStyle::Club:
				return ClubAtkFw;

				case ECombatStyle::Katana:
				return KatanaAtkFw;

				case ECombatStyle::Hand2Hand:
				return H2HAtkFw;

				case ECombatStyle::GreatKatana:
				return GreatKatanaAtkFw;

				case ECombatStyle::GreatSword:
				return GreatSwordAtkFw;

				case ECombatStyle::TwoHanded:
				return TwoHandedAtkFw;
			}
		}
	}
	return nullptr;
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

#pragma endregion AttributeGetters

#pragma endregion XICharacterInterfaceFunctions

void AXICharacterBase::Die()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->GravityScale = 0;
	GetCharacterMovement()->Velocity = FVector(0);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AddLooseGameplayTag(DeadTag);
	}
}