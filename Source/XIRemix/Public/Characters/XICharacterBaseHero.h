// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/XICharacterBase.h"
#include "Components/SphereComponent.h"
#include "XICharacterBaseHero.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API AXICharacterBaseHero : public AXICharacterBase
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	AXICharacterBaseHero(const class FObjectInitializer& ObjectInitializer);

	// Only called on the Server. Calls before Server's AcknowledgePossession.
	virtual void PossessedBy(AController* NewController) override;

	// /**
	// * Getters for attributes from AttributeSetHero
	// **/
	UFUNCTION(BlueprintCallable, Category = "XICharacter|Attributes|Jobs")
	float GetWarriorLevel() const;

protected:
	
	UPROPERTY()
	class UAttributeSetHero* AttributeSetHero;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USphereComponent* XITargetSphere;

#pragma region CombatMontages

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Unarmed")
	class UAnimMontage* UnarmedStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Unarmed")
	class UAnimMontage* UnarmedExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Unarmed")
	TArray <class UAnimMontage*> UnarmedBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Unarmed")
	class UAnimMontage* UnarmedAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Unarmed")
	class UAnimMontage* UnarmedAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Unarmed")
	class UAnimMontage* UnarmedAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Unarmed")
	class UAnimMontage* UnarmedAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Sword")
	class UAnimMontage* SwordStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Sword")
	class UAnimMontage* SwordExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Sword")
	TArray <class UAnimMontage*> SwordBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Sword")
	class UAnimMontage* SwordAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Sword")
	class UAnimMontage* SwordAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Sword")
	class UAnimMontage* SwordAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Sword")
	class UAnimMontage* SwordAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Axe")
	class UAnimMontage* AxeStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Axe")
	class UAnimMontage* AxeExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Axe")
	TArray <class UAnimMontage*> AxeBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Axe")
	class UAnimMontage* AxeAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Axe")
	class UAnimMontage* AxeAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Axe")
	class UAnimMontage* AxeAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Axe")
	class UAnimMontage* AxeAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Dagger")
	class UAnimMontage* DaggerStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Dagger")
	class UAnimMontage* DaggerExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Dagger")
	TArray <class UAnimMontage*> DaggerBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Dagger")
	class UAnimMontage* DaggerAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Dagger")
	class UAnimMontage* DaggerAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Dagger")
	class UAnimMontage* DaggerAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Dagger")
	class UAnimMontage* DaggerAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Club")
	class UAnimMontage* ClubStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Club")
	class UAnimMontage* ClubExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Club")
	TArray <class UAnimMontage*> ClubBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Club")
	class UAnimMontage* ClubAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Club")
	class UAnimMontage* ClubAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Club")
	class UAnimMontage* ClubAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Club")
	class UAnimMontage* ClubAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Katana")
	class UAnimMontage* KatanaStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Katana")
	class UAnimMontage* KatanaExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Katana")
	TArray <class UAnimMontage*> KatanaBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Katana")
	class UAnimMontage* KatanaAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Katana")
	class UAnimMontage* KatanaAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Katana")
	class UAnimMontage* KatanaAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Katana")
	class UAnimMontage* KatanaAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|H2H")
	class UAnimMontage* H2HStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|H2H")
	class UAnimMontage* H2HExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|H2H")
	TArray <class UAnimMontage*> H2HBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|H2H")
	class UAnimMontage* H2HAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|H2H")
	class UAnimMontage* H2HAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|H2H")
	class UAnimMontage* H2HAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|H2H")
	class UAnimMontage* H2HAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatSword")
	class UAnimMontage* GreatSwordStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatSword")
	class UAnimMontage* GreatSwordExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatSword")
	TArray <class UAnimMontage*> GreatSwordBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatSword")
	class UAnimMontage* GreatSwordAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatSword")
	class UAnimMontage* GreatSwordAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatSword")
	class UAnimMontage* GreatSwordAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatSword")
	class UAnimMontage* GreatSwordAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatKatana")
	class UAnimMontage* GreatKatanaStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatKatana")
	class UAnimMontage* GreatKatanaExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatKatana")
	TArray <class UAnimMontage*> GreatKatanaBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatKatana")
	class UAnimMontage* GreatKatanaAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatKatana")
	class UAnimMontage* GreatKatanaAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatKatana")
	class UAnimMontage* GreatKatanaAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatKatana")
	class UAnimMontage* GreatKatanaAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|TwoHanded")
	class UAnimMontage* TwoHandedStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|TwoHanded")
	class UAnimMontage* TwoHandedExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|TwoHanded")
	TArray <class UAnimMontage*> TwoHandedBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|TwoHanded")
	class UAnimMontage* TwoHandedAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|TwoHanded")
	class UAnimMontage* TwoHandedAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|TwoHanded")
	class UAnimMontage* TwoHandedAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|TwoHanded")
	class UAnimMontage* TwoHandedAtkRight;

#pragma endregion CombatMontages

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Client only
	virtual void OnRep_PlayerState() override;	
};
