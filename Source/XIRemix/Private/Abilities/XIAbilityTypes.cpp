// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/XIAbilityTypes.h"


bool FGameplayAbilitySingleTargetData::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
    Ar << TargetActor;
    Ar << AttackMontage;
    Ar << UniqueID;
    bOutSuccess = true;
    return true;
}

bool FXIGameplayEffectContext::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
   uint32 RepBits = 0;
   if (Ar.IsSaving())
   {
      if (Instigator.IsValid())
      {
         RepBits |= 1 << 0;
      }
      if (EffectCauser.IsValid())
      {
         RepBits |= 1 << 1;
      }
      if (AbilityCDO.IsValid())
      {
         RepBits |= 1 << 2;
      }
      if (bReplicateSourceObject && SourceObject.IsValid())
      {
         RepBits |= 1 << 3;
      }
      if (Actors.Num() > 0)
      {
         RepBits |= 1 << 4;
      }
      if (HitResult.IsValid())
      {
         RepBits |= 1 << 5;
      }
      if (bHasWorldOrigin)
      {
         RepBits |= 1 << 6;
      }
      if (bIsCriticalHit)
      {
         RepBits |= 1 << 7;
      }
      if (bIsBlocked)
      {
         RepBits |= 1 << 8;
      }
      if (bIsParried)
      {
         RepBits |= 1 << 9;
      }
      if (bIsGuarded)
      {
         RepBits |= 1 << 10;
      }
      if (bIsEvaded)
      {
         RepBits |= 1 << 11;
      }
      if (bIsResisted)
      {
         RepBits |= 1 << 12;
      }
   }
 
   Ar.SerializeBits(&RepBits, 10);
 
   if (RepBits & (1 << 0))
   {
      Ar << Instigator;
   }
   if (RepBits & (1 << 1))
   {
      Ar << EffectCauser;
   }
   if (RepBits & (1 << 2))
   {
      Ar << AbilityCDO;
   }
   if (RepBits & (1 << 3))
   {
      Ar << SourceObject;
   }
   if (RepBits & (1 << 4))
   {
      SafeNetSerializeTArray_Default<31>(Ar, Actors);
   }
   if (RepBits & (1 << 5))
   {
      if (Ar.IsLoading())
      {
         if (!HitResult.IsValid())
         {
            HitResult = MakeShared<FHitResult>();
         }
      }
      HitResult->NetSerialize(Ar, Map, bOutSuccess);
   }
   if (RepBits & (1 << 6))
   {
      Ar << WorldOrigin;
      bHasWorldOrigin = true;
   }
   else
   {
      bHasWorldOrigin = false;
   }
 
   if (RepBits & (1 << 7))
   {
      Ar << bIsCriticalHit;
   }

   if (RepBits & (1 << 8))
   {
      Ar << bIsBlocked;
   }

   if (RepBits & (1 << 9))
   {
      Ar << bIsParried;
   }

   if (RepBits & (1 << 10))
   {
      Ar << bIsGuarded;
   }

   if (RepBits & (1 << 11))
   {
      Ar << bIsEvaded;
   }

   if (RepBits & (1 << 12))
   {
      Ar << bIsResisted;
   }
 
   if (Ar.IsLoading())
   {
      AddInstigator(Instigator.Get(), EffectCauser.Get()); // Just to initialize InstigatorAbilitySystemComponent
   }  
 
   bOutSuccess = true;
   return true;
}