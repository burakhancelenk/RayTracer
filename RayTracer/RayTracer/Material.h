#ifndef MATERIAL_H
#define MATERIAL_H

#include "Vector3.h"
#include <cmath>
#include <algorithm>

using namespace Utility;

namespace Core {

	// Parameters that determine the behaviour of the related object towards light sources
	struct MaterialParameters
	{
		private:
			// Instead of using float coefficient and Vector3 color seperated,
			// we use Vector3 coefficient which is (color * coefficient)  
			Vector3 kd = { 1, 0, 0 };
			Vector3 ks = { 1, 1, 1 };
			Vector3 ka = { 1, 0, 0 };
			float ns = 8;
			float kr = 0.05;

		public:
			/*
			* @param _kd, diffuse coefficient
			* @param _ks, specular coefficient
			* @param _ka, ambient coefficient
			* @param _kr, reflection coefficient
			* @param _ns, specular exponential coefficient
			*/
			MaterialParameters(const Vector3& _kd, const Vector3& _ks, const Vector3& _ka, const float& _kr, const float& ns);

			// Returns diffuse coefficient
			Vector3 get_kd() const { return kd; }

			// Returns specular coefficient
			Vector3 get_ks() const { return ks; }

			// Returns ambient coefficient
			Vector3 get_ka() const { return ka; }

			// Returns reflection coefficient
			float get_kr() const { return kr; }

			// Returns specular exponential coefficient
			float get_ns() const { return ns; }


			// All parameters are assumed to be normalized
			Vector3 reflected_proportion(const Vector3& incomingDirection, 
										const Vector3& outgoingDirection, 
										const Vector3& normal) const;

			// Debug
			friend std::ostream& operator<<(std::ostream& os, const MaterialParameters& params) {
				os << "MaterialParameters(" 
					<< "kd : " << params.kd << " , " 
					<< "ks : " << params.ks << " , " 
					<< "ns : " << params.ns << " , " 
					<< "kr : " << params.kr << ")";
				return os;
			}
	};

	// Doesn't mean anything for now, makes easier further implementations
	class Material 
	{
		private:
			MaterialParameters parameters;

		public:
			// Default constructor
			Material();

			// See MaterialParameters for explanation
			Material(const Vector3& kd, const Vector3& ks, const Vector3& ka, const float& kr, const float& ns);

			Material(const MaterialParameters& params);

			// Returns material parameters
			MaterialParameters get_params() const { return parameters; }

			// Debug
			friend std::ostream& operator<<(std::ostream& os, const Material& material) {
				os << "Material(" << "parameters : " << material.parameters << ")";
				return os;
			}
	};

}

#endif // !MATERIAL_H



