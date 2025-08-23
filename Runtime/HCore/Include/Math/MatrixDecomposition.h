#pragma once

#include "HMath.h"
#include "GLM/gtx/euler_angles.hpp"
#include "GLM/gtx/matrix_decompose.hpp"

namespace Horizon
{
	class MatrixDecomposition {

	public:
		MatrixDecomposition() = default;

		explicit MatrixDecomposition(matrix matrix)
		{
			Decompose(matrix);
		}

		void Decompose(matrix matrix)
		{
			quaternion Rotation;
			float3 Skew;
			float4 Perspective;

			glm::decompose(matrix, Scale, Rotation, Translation, Skew, Perspective);

			Rotation = glm::conjugate(Rotation);
			Rotation = glm::eulerAngles(Rotation);
		}

		matrix Compose()
		{
			auto mat = glm::translate(matrix(1.0f), Translation);
			mat = glm::scale(mat, Scale);
			mat = mat * glm::eulerAngleXYZ(Rotation.x, Rotation.y, Rotation.z);

			return mat;
		}

		float3 Translation = float3(0.0f);
		float3 Rotation = float3(0.0f);
		float3 Scale = float3(1.0f);

	};
}

