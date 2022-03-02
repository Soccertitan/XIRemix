// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "XICharacterCombatMontages.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class XIREMIX_API UXICharacterCombatMontages : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Unarmed")
	UAnimMontage* UnarmedStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Unarmed")
	UAnimMontage* UnarmedExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Unarmed")
	TArray <UAnimMontage*> UnarmedBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Unarmed")
	UAnimMontage* UnarmedAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Unarmed")
	UAnimMontage* UnarmedAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Unarmed")
	UAnimMontage* UnarmedAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Unarmed")
	UAnimMontage* UnarmedAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Sword")
	UAnimMontage* SwordStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Sword")
	UAnimMontage* SwordExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Sword")
	TArray <UAnimMontage*> SwordBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Sword")
	UAnimMontage* SwordAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Sword")
	UAnimMontage* SwordAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Sword")
	UAnimMontage* SwordAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Sword")
	UAnimMontage* SwordAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Axe")
	UAnimMontage* AxeStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Axe")
	UAnimMontage* AxeExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Axe")
	TArray <UAnimMontage*> AxeBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Axe")
	UAnimMontage* AxeAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Axe")
	UAnimMontage* AxeAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Axe")
	UAnimMontage* AxeAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Axe")
	UAnimMontage* AxeAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Dagger")
	UAnimMontage* DaggerStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Dagger")
	UAnimMontage* DaggerExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Dagger")
	TArray <UAnimMontage*> DaggerBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Dagger")
	UAnimMontage* DaggerAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Dagger")
	UAnimMontage* DaggerAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Dagger")
	UAnimMontage* DaggerAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Dagger")
	UAnimMontage* DaggerAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Club")
	UAnimMontage* ClubStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Club")
	UAnimMontage* ClubExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Club")
	TArray <UAnimMontage*> ClubBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Club")
	UAnimMontage* ClubAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Club")
	UAnimMontage* ClubAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Club")
	UAnimMontage* ClubAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Club")
	UAnimMontage* ClubAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Katana")
	UAnimMontage* KatanaStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Katana")
	UAnimMontage* KatanaExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Katana")
	TArray <UAnimMontage*> KatanaBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Katana")
	UAnimMontage* KatanaAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Katana")
	UAnimMontage* KatanaAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Katana")
	UAnimMontage* KatanaAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Katana")
	UAnimMontage* KatanaAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|H2H")
	UAnimMontage* H2HStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|H2H")
	UAnimMontage* H2HExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|H2H")
	TArray <UAnimMontage*> H2HBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|H2H")
	UAnimMontage* H2HAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|H2H")
	UAnimMontage* H2HAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|H2H")
	UAnimMontage* H2HAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|H2H")
	UAnimMontage* H2HAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|GreatSword")
	UAnimMontage* GreatSwordStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|GreatSword")
	UAnimMontage* GreatSwordExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|GreatSword")
	TArray <UAnimMontage*> GreatSwordBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|GreatSword")
	UAnimMontage* GreatSwordAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|GreatSword")
	UAnimMontage* GreatSwordAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|GreatSword")
	UAnimMontage* GreatSwordAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|GreatSword")
	UAnimMontage* GreatSwordAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|GreatKatana")
	UAnimMontage* GreatKatanaStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|GreatKatana")
	UAnimMontage* GreatKatanaExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|GreatKatana")
	TArray <UAnimMontage*> GreatKatanaBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|GreatKatana")
	UAnimMontage* GreatKatanaAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|GreatKatana")
	UAnimMontage* GreatKatanaAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|GreatKatana")
	UAnimMontage* GreatKatanaAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|GreatKatana")
	UAnimMontage* GreatKatanaAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|TwoHanded")
	UAnimMontage* TwoHandedStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|TwoHanded")
	UAnimMontage* TwoHandedExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|TwoHanded")
	TArray <UAnimMontage*> TwoHandedBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|TwoHanded")
	UAnimMontage* TwoHandedAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|TwoHanded")
	UAnimMontage* TwoHandedAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|TwoHanded")
	UAnimMontage* TwoHandedAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|TwoHanded")
	UAnimMontage* TwoHandedAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Range")
	UAnimMontage* Bow;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Range")
	UAnimMontage* Gun;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Range")
	UAnimMontage* Throw;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Range")
	UAnimMontage* Harp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Range")
	UAnimMontage* Flute;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Range")
	UAnimMontage* Sing;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Skills")
	UAnimMontage* JobAbility;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Skills")
	UAnimMontage* JobAbilityCombat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Skills")
	UAnimMontage* BlackMagic;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Skills")
	UAnimMontage* WhiteMagic;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Skills")
	UAnimMontage* SummonerMagic;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Skills")
	UAnimMontage* NinjitsuMagic;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Skills")
	UAnimMontage* BlueMagic;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Skills")
	UAnimMontage* GeoMagic;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat|Skills")
	UAnimMontage* HandbellMagic;
};
