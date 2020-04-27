#pragma once

struct FVector
{
	float X, Y, Z = 0;

	FVector(float XYZ)
	{
		X = Y = Z = XYZ;
	}

	FVector(float XToSet, float YToSet, float ZToSet)
	{
		X = XToSet;
		Y = YToSet;
		Z = ZToSet;
	}

	void operator+(FVector Other)
	{
		X += Other.X;
		Y += Other.Y;
		Z += Other.Z;
	}

	void operator+=(FVector Other)
	{
		X += Other.X;
		Y += Other.Y;
		Z += Other.Z;
	}


	void operator-(FVector Other)
	{
		X -= Other.X;
		Y -= Other.Y;
		Z -= Other.Z;
	}

	void operator-=(FVector Other)
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

	inline FVector GetLocation() { return Location; }
	inline FVector GetScale() { return Scale; }
};

