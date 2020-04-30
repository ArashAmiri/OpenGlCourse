#pragma once

struct FVector
{
	float X, Y, Z = 0;

	FVector(const float &XYZ)
	{
		X = Y = Z = XYZ;
	}

	FVector(float XToSet, float YToSet, float ZToSet)
	{
		X = XToSet;
		Y = YToSet;
		Z = ZToSet;
	}

	void operator=(const FVector &Other)
	{
		X = Other.X;
		Y = Other.Y;
		Z = Other.Z;
	}

	FVector operator+(const FVector &Other)
	{
		X += Other.X;
		Y += Other.Y;
		Z += Other.Z;
		return FVector(X, Y, Z);
	}

	void operator+=(const FVector &Other)
	{
		X += Other.X;
		Y += Other.Y;
		Z += Other.Z;
	}

	void operator*(const float &Other)
	{
		X *= Other;
		Y *= Other;
		Z *= Other;
	}

	void operator-(const FVector &Other)
	{
		X -= Other.X;
		Y -= Other.Y;
		Z -= Other.Z;
	}

	void operator-=(const FVector &Other)
	{
		X -= Other.X;
		Y -= Other.Y;
		Z -= Other.Z;
	}
};

struct FTransform
{
public:

	FTransform();

	FVector Location = FVector(1.0f);
	FVector Scale = FVector(1.0f);

	inline FTransform AddToLocation(FVector Other) { 
		Location += Other; 
		FTransform RetTransform = FTransform(); 
		RetTransform.Location = Location; 
		return RetTransform;
	}

	inline FVector* GetLocation() { return &Location; }
	inline FVector GetScale() { return Scale; }
};

