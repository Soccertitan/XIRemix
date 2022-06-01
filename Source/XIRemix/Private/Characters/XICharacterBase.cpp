// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/XICharacterBase.h"
#include "Abilities/AttributeSetGlobal.h"
#include "Abilities/XIAbilitySystemComponent.h"
#include "Abilities/XIGameplayAbility.h"
#include "Net/UnrealNetwork.h"
#include "Components/CapsuleComponent.h"
#include "Characters/XICharacterMovementComponent.h"
#include "Interfaces/XIAnimBPInterface.h"
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

void AXICharacterBase::SetCharacterName(FText Name)
{
	if(HasAuthority())
	{
		CharacterName = Name;
	}
	else
	{
		Server_SetCharacterName(Name);
	}
}

bool AXICharacterBase::Server_SetCharacterName_Validate(const FText& Name)
{
	return true;
}

void AXICharacterBase::Server_SetCharacterName_Implementation(const FText& Name)
{
	SetCharacterName(Name);
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
	DOREPLIFETIME_CONDITION_NOTIFY(AXICharacterBase, CombatStyle, COND_None, REPNOTIFY_Always);
}

UAnimMontage* AXICharacterBase::GetCombatStartMontage()
{
	if (!AnimMontages)
	{
		return nullptr;
	}

	return AnimMontages->DefaultStartCombat;
}

UAnimMontage* AXICharacterBase::GetCombatExitMontage()
{
	if (!AnimMontages)
	{
		return nullptr;
	}

	return AnimMontages->DefaultExitCombat;
}

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
	IXIAnimBPInterface* IntAnimBP = Cast<IXIAnimBPInterface>(GetMesh()->GetAnimInstance());
	if(IntAnimBP && AnimMontages)
	{
		float Speed = IntAnimBP->GetSpeed();
		float Direction = IntAnimBP->GetDirection();
		
		return AnimMontages->GetAutoAttackMontage(CombatStyle, Speed, Direction);
	}
	return nullptr;
}

UXICharacterAnimMontages* AXICharacterBase::GetXICharacterAnimMontages() const
{
	return AnimMontages;
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

UXIStatsGrowthRank* AXICharacterBase::GetXIStatsGrowthRank() const
{
	return StatsGrowthRank;
}

UXIStatsGrowthData* AXICharacterBase::GetXIStatsGrowthData() const
{
	return StatsGrowthData;
}

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

void AXICharacterBase::OnRep_CombatStyle()
{
	IXIAnimBPInterface* IntAnimBP = Cast<IXIAnimBPInterface>(GetMesh()->GetAnimInstance());
	if(IntAnimBP)
	{
		IntAnimBP->SetCombatStyle_Implementation(CombatStyle);
	}
}