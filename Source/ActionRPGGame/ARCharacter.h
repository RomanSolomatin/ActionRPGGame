// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/ChildActorComponent.h"
#include "GameplayTags.h"
#include "AFEffectsComponent.h"
#include "AFAbilityComponent.h"
#include "AFAbilityInterface.h"
#include "OrionInterface.h"
#include "OrionAnimComponent.h"
#include "IFInventoryComponent.h"
#include "ARCharacter.generated.h"

UENUM(BlueprintType)
enum class EEightCardinalDirection : uint8
{
	N = 0,
	SW = 1,
	E = 2,
	NW = 3,
	S = 4,
	NE = 5,
	W = 6,
	SE = 7
};

UENUM(BlueprintType)
enum class EFourCardinalDirection : uint8
{
	N = 0,
	E = 1,
	S = 2,
	W = 3
};

UENUM(BlueprintType)
enum class EPivotDirectionChange : uint8
{
	NtoE = 0,
	NtoW = 1,
	NToS = 2,
};

USTRUCT(BlueprintType)
struct FCardinalDirection
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
		EFourCardinalDirection CaridnalDirections;

	EEightCardinalDirection HelperDirections;
};

USTRUCT(BlueprintType)
struct FARCameraTransform
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
		FVector ForwardVector;
	UPROPERTY(BlueprintReadOnly)
		FVector Location;
};
struct WeaponSocket
{
	static const FName HolsteredRightWeapon;
	static const FName HolsteredLeftWeapon;

	static const FName EquipedMainWeapon;
};
UCLASS(config=Game)
class AARCharacter : public ACharacter, public IAFAbilityInterface, public IOrionInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UAFAbilityComponent* Abilities;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UAFEffectsComponent* EffectsComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UARWeaponPawnManagerComponent* Weapons;
	
	UPROPERTY(EditAnywhere, Category = "Default Abilities")
		TArray<FGameplayTag> AbilitiesToGive;

	//Character parts:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Parts", meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* Head;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Parts", meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* Shoulders;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Parts", meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* Arms;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Parts", meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* Hands;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Parts", meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* Torso;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Parts", meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* Legs;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Parts", meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* Feets;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Parts", meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* Backpack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Parts", meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* LegsCloth;


	//Weapons
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
		UChildActorComponent* WeaponHolsteredRight;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
		UChildActorComponent* WeaponHolsteredLeft;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
		UChildActorComponent* HolsteredBackDown;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
		UChildActorComponent* WeaponHolsteredSideLeft;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
		UChildActorComponent* WeaponEquipedMain;

public:
	UPROPERTY()
		class UARItemWeapon* WeaponRightItem;
	UPROPERTY()
		class UARItemWeapon* WeaponLeftItem;
	UPROPERTY()
		class UARItemWeapon* WeaponBackItem;
	UPROPERTY()
		class UARItemWeapon* WeaponSideItem;
public:
	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Player Character Camera")
		FARCameraTransform CameraTransform;

	UPROPERTY(BlueprintReadOnly, Category = "Character Animation")
		bool bStopDistancePredicted;
	UPROPERTY(BlueprintReadOnly, Category = "Character Animation")
		bool bStartedLocomotion;

	UPROPERTY(BlueprintReadOnly, Category = "Character Animation")
		EEightCardinalDirection EigthDirections;
	
	UPROPERTY(BlueprintReadOnly, Category = "Character Animation")
		EFourCardinalDirection OldFourDirections;

	UPROPERTY(BlueprintReadOnly, Category = "Character Animation")
		EFourCardinalDirection FourDirections;

	UPROPERTY(BlueprintReadOnly, Category = "Character Animation")
		float MovingAngle;
	UPROPERTY(BlueprintReadOnly, Category = "Character Animation")
		float OrientN;
	UPROPERTY(BlueprintReadOnly, Category = "Character Animation")
		float OrientS;
	UPROPERTY(BlueprintReadOnly, Category = "Character Animation")
		float OrientE;
	UPROPERTY(BlueprintReadOnly, Category = "Character Animation")
		float OrientW;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Animation")
		float OrientInterpolationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Animation")
		float OrientationDOT;

	float ForwardDirection;
	float LateralDirection;
	UPROPERTY(BlueprintReadOnly, Category = "Character Animation")
		float CurrentOrient;
	float OldOrient;
public:
	AARCharacter(const FObjectInitializer& ObjectInitializer);
	float GetAnimOrient() final;
	EFCardinalDirection GetCardianlDirection() final;
	float GetAnimOrientN() final;
	float GetAnimOrientE() final;
	float GetAnimOrientS() final;
	float GetAnimOrientW() final;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
	virtual void PossessedBy(AController* NewController) override;
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/* IAFAbilityInterface- BEGIN */

	UFUNCTION(BlueprintCallable, Category = "AbilityFramework|Attributes")
		virtual class UAFAbilityComponent* GetAbilityComp() override;
	UFUNCTION(BlueprintCallable, Category = "AbilityFramework|Attributes")
		virtual class UAFEffectsComponent* GetEffectsComponent() override;
	virtual class UAFEffectsComponent* NativeGetEffectsComponent() const override;

	UFUNCTION(BlueprintCallable, Category = "AbilityFramework|Attributes")
		virtual float GetAttributeValue(FGAAttribute AttributeIn) const override;

	virtual void ModifyAttribute(FGAEffectMod& ModIn, const FGAEffectHandle& HandleIn,
		struct FGAEffectProperty& InProperty) override;
	virtual FAFAttributeBase* GetAttribute(FGAAttribute AttributeIn) override;
	virtual void RemoveBonus(FGAAttribute AttributeIn, const FGAEffectHandle& HandleIn, EGAAttributeMod InMod) override;

	virtual float NativeGetAttributeValue(const FGAAttribute AttributeIn) const override;
	/* IAFAbilityInterface- END */

	void OnCameraTransformUpdate(USceneComponent* UpdatedComponent, EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport);

	inline UARWeaponPawnManagerComponent* GetWeapons()
	{
		return Weapons;
	}

	inline UChildActorComponent* GetHolsteredRightWeapon()
	{
		return WeaponHolsteredRight;
	}
	inline UChildActorComponent* GetHolsteredLeftWeapon()
	{
		return WeaponHolsteredLeft;
	}
	inline UChildActorComponent* GetHolsteredBackDownWeapon()
	{
		return HolsteredBackDown;
	}
	inline UChildActorComponent* GetHolsteredSideLeftWeapon()
	{
		return WeaponHolsteredSideLeft;
	}

	inline UChildActorComponent* GetEquipedMainWeapon() const
	{
		return WeaponEquipedMain;
	}

	template<typename T>
	T* GetMainWeapon() const
	{
		return Cast<T>(GetEquipedMainWeapon()->GetChildActor());
	}

	UFUNCTION(BlueprintPure, Category = "Character | Weapons")
	class AARWeaponBase* GetMainWeapon() const;

	UFUNCTION(BlueprintPure, Category = "Character | Weapons")
		USkeletalMeshComponent* GetMainWeaponMesh() const;

	UFUNCTION(BlueprintPure, Category = "Character | Weapons")
		FVector GetMainWeaponSocket(const FName& Socket) const;
};

