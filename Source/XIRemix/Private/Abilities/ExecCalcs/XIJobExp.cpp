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
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.TargetTags = TargetTags;

	UXIAbilitySystemComponent* TargetASC = Cast<UXIAbilitySystemComponent>(TargetAbilitySystemComponent);
	AXICharacterBaseHero* TargetHero = Cast<AXICharacterBaseHero>(TargetActor);
	if (TargetASC && TargetHero)
	{	
		float MainJobLevel = 0.f;
		float SubJobLevel = 0.f;
		FGameplayTag MainJobTag;
		FGameplayTag SubJobTag;
		FXIJobTagRelationshipItem JobTagRelationshipItem;

		float ExpBounty = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(JobExpStatics().ExpBountyDef, EvaluationParameters, ExpBounty);
		float EnemyLevel = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(JobExpStatics().LevelDef, EvaluationParameters, EnemyLevel);

		TargetHero->GetCharacterActiveJobsAndLevels(MainJobTag, MainJobLevel, SubJobTag, SubJobLevel);

		/*
		// Formula for calculating EXP earned. Will need some more refinement for LevelDif < 0.
		// TODO: Add Multiplier for chain kills.
		*/
		float LevelDif = EnemyLevel - MainJobLevel;
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
		TargetASC->GetXIJobTagRelationship(MainJobTag, JobTagRelationshipItem);
				
		if(!JobTagRelationshipItem.JobExpAttribute.IsValid() || !JobTagRelationshipItem.JobExpRequiredAttribute.IsValid() || !JobTagRelationshipItem.JobLevelAttribute.IsValid() || !JobTagRelationshipItem.JobLevelMaxAttribute.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("The JobTagRelationshipItem for Job Experience/Level defined in the ASC is invalid: %s"), *MainJobTag.ToString());
			return;
		}
		else
		{
			float CurrentExp = TargetASC->GetNumericAttribute(JobTagRelationshipItem.JobExpAttribute);
			float RequiredExp = TargetASC->GetNumericAttribute(JobTagRelationshipItem.JobExpRequiredAttribute);
			float MaxLevel = TargetASC->GetNumericAttribute(JobTagRelationshipItem.JobLevelMaxAttribute);

			if(MainJobLevel >= MaxLevel)
			{
				OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(JobTagRelationshipItem.JobExpAttribute, EGameplayModOp::Additive, FMath::Min(ExpBounty, RequiredExp - CurrentExp)));
			}
			else
			{
				OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(JobTagRelationshipItem.JobExpAttribute, EGameplayModOp::Additive, ExpBounty));
				if(CurrentExp + ExpBounty > RequiredExp)
				{
					//TODO: Notify the character that a level up has occured
					OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(JobTagRelationshipItem.JobLevelAttribute, EGameplayModOp::Additive, 1.f));
					MainJobLevel = TargetASC->GetNumericAttribute(JobTagRelationshipItem.JobLevelAttribute);
				}
			}
		}

		/*
		//Add Exp to Sub Job
		*/
		TargetASC->GetXIJobTagRelationship(SubJobTag, JobTagRelationshipItem);

		if(!JobTagRelationshipItem.JobExpAttribute.IsValid() || !JobTagRelationshipItem.JobExpRequiredAttribute.IsValid() || !JobTagRelationshipItem.JobLevelAttribute.IsValid() || !JobTagRelationshipItem.JobLevelMaxAttribute.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("The JobTagRelationshipItem for Job Experience/Level defined in the ASC is invalid or there is no SubJob: %s"), *SubJobTag.ToString());
			return;
		}
		else
		{
			float CurrentExp = TargetASC->GetNumericAttribute(JobTagRelationshipItem.JobExpAttribute);
			float RequiredExp = TargetASC->GetNumericAttribute(JobTagRelationshipItem.JobExpRequiredAttribute);
			float MaxLevel = TargetASC->GetNumericAttribute(JobTagRelationshipItem.JobLevelMaxAttribute);

			float SubJobGainedExp = FMath::Floor(ExpBounty / 5.f);

			if(SubJobLevel >= FMath::Floor(MainJobLevel / 2.f) || SubJobLevel >= MaxLevel)
			{
				OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(JobTagRelationshipItem.JobExpAttribute, EGameplayModOp::Additive, FMath::Min(SubJobGainedExp, RequiredExp - CurrentExp)));
			}
			else
			{
				OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(JobTagRelationshipItem.JobExpAttribute, EGameplayModOp::Additive, SubJobGainedExp));
				if(CurrentExp + SubJobGainedExp > RequiredExp)
				{
					//TODO: Notify the character that a level up has occured
					OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(JobTagRelationshipItem.JobLevelAttribute, EGameplayModOp::Additive, 1.f));
				}
			}			
		}
	}
}