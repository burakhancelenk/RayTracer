#include "Material.h"

using namespace Core;

Material::Material()
	: parameters(Vector3(1,0,0)
	, Vector3(1,1,1)
	, Vector3(1,0,0), 0, 1) 
{}
Material::Material(
	const Vector3& kd,
	const Vector3& ks,
	const Vector3& ka, 
	const float& kr,
	const float& ns)

	: parameters(kd, ks, ka, kr, ns) 
{}

Material::Material(const MaterialParameters& params)
	: parameters(params)
{}

MaterialParameters::MaterialParameters(
	const Vector3& _kd,
	const Vector3& _ks,
	const Vector3& _ka,
	const float& _kr,
	const float& _ns)

	: kd(_kd)
	, ks(_ks)
	, ka(_ka)
	, kr(_kr)
	, ns(_ns)
{}

Vector3 MaterialParameters::reflected_proportion(
	const Vector3& incomingDirection,
	const Vector3& outgoingDirection,
	const Vector3& normal) const
{
	float NoL = std::max(0.0f, Vector3::dot(normal,incomingDirection));
	Vector3 S = normal.reflect(outgoingDirection);
	float SoL = std::max(0.0f, Vector3::dot(S,incomingDirection));
	return kd * NoL + ks * std::powf(SoL, ns);
}