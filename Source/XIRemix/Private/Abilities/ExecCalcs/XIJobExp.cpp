// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/ExecCalcs/XIJobExp.h"
#include "Abilities/Enemy/AttributeSetEnemy.h"
#include "Abilities/XIAbilitySystemComponent.h"
#include "Characters/XICharacterBaseHero.h"
#include "GameplayTagsManager.h"

struct XIJobExpStatics
{
    DECLARE_ATTRIBUTE_CAPTUREDEF(Level);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ExpBounty)

    XIJobExpStatics()
    {
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetEnemy, Level, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetEnemy, ExpBounty, Source, true);
    }
};

static const XIJobExpStatics& JobExpStatics()
{
    static XIJobExpStatics ExpStatics;
    return ExpStatics;
}

UXIJobExp::UXIJobExp()
{
	RelevantAttributesToCapture.Add(JobExpStatics().LevelDef);
	RelevantAttributesToCapture.Add(JobExpStatics().ExpBountyDef);
}

void UXIJobExp::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.TargetTags = TargetTags;

	UXIAbilitySystemComponent* TargetASC = Cast<UXIAbilitySystemComponent>(TargetAbilitySystemComponent);
	AXICharacterBaseHero* TargetHero = Cast<AXICharacterBaseHero>(TargetActor);
	if (!TargetASC || !TargetHero)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor or ASC is not of type XICharacterBaseHero/XIAbilitySystemComponent"));
		return;
	}
	UCurveTable* ExpForNextLevelCT = TargetASC->GetExpToNextLevelCurveTable();

	if(!ExpForNextLevelCT)
	{
		UE_LOG(LogTemp, Error, TEXT("The EXPToNextLevelCurveTable is empty on the ASC blueprint. %s"), *TargetHero->GetName());
		return;
	}

	FXIJobTagRelationshipItem JobTagRelationshipItem;
	FXICharacterHeroActiveJobsLevels HeroCharacterJobs;

	static const FString ContextString(TEXT("Getting EXP Required for Next Level"));
    float RequiredExp = 0.f;

    FCurveTableRowHandle RequiredExpHandle;
    RequiredExpHandle.CurveTable = ExpForNextLevelCT;
    RequiredExpHandle.RowName = FName::FName("ExpToNextLevel");

	float ExpBounty = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(JobExpStatics().ExpBountyDef, EvaluationParameters, ExpBounty);
	float EnemyLevel = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(JobExpStatics().LevelDef, EvaluationParameters, EnemyLevel);

	HeroCharacterJobs = TargetHero->GetCharacterActiveJobsAndLevels();

	/*
	// Formula for calculating EXP earned. Will need some more refinement for LevelDif < 0.
	// TODO: Add Multiplier for chain kills.
	*/
	float LevelDif = EnemyLevel - HeroCharacterJobs.MainJobLevel;
	if(LevelDif < 0)
	{
		ExpBounty = FMath::Floor(ExpBounty * FMath::Clamp(1.f + (LevelDif * 0.3f), 0.f, 1.f));
	}
	else
	{
		ExpBounty = FMath::Floor(ExpBounty * FMath::Clamp((1.f + (LevelDif * 0.2f)), 0.f, 4.f));
	}

	/*
	//Add Exp to Main Job
	*/
	TargetASC->GetXIJobTagRelationship(HeroCharacterJobs.MainJobTag, JobTagRelationshipItem);
			
	if(!JobTagRelationshipItem.JobExpAttribute.IsValid() || !JobTagRelationshipItem.JobLevelAttribute.IsValid() || !JobTagRelationshipItem.JobLevelMaxAttribute.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("The JobTagRelationshipItem for Job Experience/Level defined in the ASC is invalid: %s"), *HeroCharacterJobs.MainJobTag.ToString());
		return;
	}
	else
	{
		float CurrentExp = TargetASC->GetNumericAttribute(JobTagRelationshipItem.JobExpAttribute);
		float MaxLevel = TargetASC->GetNumericAttribute(JobTagRelationshipItem.JobLevelMaxAttribute);
		RequiredExpHandle.Eval(HeroCharacterJobs.MainJobLevel, &RequiredExp,ContextString);

		if(HeroCharacterJobs.MainJobLevel >= MaxLevel)
		{
			OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(JobTagRelationshipItem.JobExpAttribute, EGameplayModOp::Additive, FMath::Min(ExpBounty, RequiredExp - CurrentExp)));
		}
		else
		{
			OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(JobTagRelationshipItem.JobExpAttribute, EGameplayModOp::Additive, ExpBounty));
			if(CurrentExp + ExpBounty > RequiredExp)
			{
				OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(JobTagRelationshipItem.JobLevelAttribute, EGameplayModOp::Additive, 1.f));
				HeroCharacterJobs.MainJobLevel = TargetASC->GetNumericAttribute(JobTagRelationshipItem.JobLevelAttribute);
				TargetASC->LevelUp();
			}
		}
	}

	/*
	//Add Exp to Sub Job
	*/
	TargetASC->GetXIJobTagRelationship(HeroCharacterJobs.SubJobTag, JobTagRelationshipItem);

	if(!JobTagRelationshipItem.JobExpAttribute.IsValid() || !JobTagRelationshipItem.JobLevelAttribute.IsValid() || !JobTagRelationshipItem.JobLevelMaxAttribute.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("The JobTagRelationshipItem for Job Experience/Level defined in the ASC is invalid or there is no SubJob: %s"), *HeroCharacterJobs.SubJobTag.ToString());
		return;
	}
	else
	{
		float CurrentExp = TargetASC->GetNumericAttribute(JobTagRelationshipItem.JobExpAttribute);
		float MaxLevel = TargetASC->GetNumericAttribute(JobTagRelationshipItem.JobLevelMaxAttribute);
		RequiredExpHandle.Eval(HeroCharacterJobs.SubJobLevel, &RequiredExp,ContextString);

		float SubJobGainedExp = FMath::Floor(ExpBounty / 5.f);

		if(HeroCharacterJobs.SubJobLevel >= FMath::Floor(HeroCharacterJobs.MainJobLevel / 2.f) || HeroCharacterJobs.SubJobLevel >= MaxLevel)
		{
			OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(JobTagRelationshipItem.JobExpAttribute, EGameplayModOp::Additive, FMath::Min(SubJobGainedExp, RequiredExp - CurrentExp)));
		}
		else
		{
			OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(JobTagRelationshipItem.JobExpAttribute, EGameplayModOp::Additive, SubJobGainedExp));
			if(CurrentExp + SubJobGainedExp > RequiredExp)
			{
				OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(JobTagRelationshipItem.JobLevelAttribute, EGameplayModOp::Additive, 1.f));
				TargetASC->LevelUp();
			}
		}			
	}

}