// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	UE_LOG(LogTemp, Warning, TEXT("Gaga: C++ Construct"))
}

void ATank::BeginPlay()
{
	Super::BeginPlay(); // Needed for BP BeginPlay to run
	UE_LOG(LogTemp, Warning, TEXT("Gaga: C++ BeginPlay"))
}

void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed); //TankAimingComponent's AimAt()
}

void ATank::Fire()
{
	if (!ensure(Barrel)) { return; }
	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;
	if (IsReloaded)
	{
	
	//Spawn a projectile at socket location of the barrel
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile"))
		);

	Projectile->LaunchProjectile(LaunchSpeed);
	LastFireTime = FPlatformTime::Seconds();
	}
}