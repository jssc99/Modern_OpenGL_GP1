#pragma once

#include "basicMath.hpp"

namespace Physics {
	using namespace Core::Maths;

	class Transform
	{
	private:
		vec3 pos = { 0.0f, 0.0f, 0.0f };
		vec3 eulerRot = { 0.0f, 0.0f, 0.0f }; // In degrees
		vec3 scale = { 1.0f, 1.0f, 1.0f };

		mat4 modelMatrix = mat::identity4();

		mat4 getTRS()
		{
			mat4 transformX = mat::rotateX(deg2Rad(eulerRot.x));
			mat4 transformY = mat::rotateY(deg2Rad(eulerRot.y));
			mat4 transformZ = mat::rotateZ(deg2Rad(eulerRot.z));

			mat4 rotationMatrix = transformZ * transformY * transformX;

			return mat::translate(pos) * rotationMatrix * mat::scale(scale);
		}

	public:
		bool isDirty = true;

		void computeModelMatrix() {
			modelMatrix = getTRS();
			isDirty = false;
		}

		void computeModelMatrix(const mat4& parentGlobalModelMatrix) {
			modelMatrix = parentGlobalModelMatrix * getTRS();
			isDirty = false;
		}

		void setLocalPosition(const vec3& newPosition) {
			pos = newPosition;
			isDirty = true;
		}

		void setLocalRotation(const vec3& newRotation) {
			eulerRot = newRotation;
			isDirty = true;
		}

		void setLocalScale(const vec3& newScale) {
			scale = newScale;
			isDirty = true;
		}

		const vec3& getGlobalPosition() const {
			return { modelMatrix.v[3].x, modelMatrix.v[3].y, modelMatrix.v[3].z };
		}

		const vec3& getLocalPosition() const {
			return pos;
		}

		const vec3& getLocalRotation() const {
			return eulerRot;
		}

		const vec3& getLocalScale() const {
			return scale;
		}

		const mat4& getModelMatrix() const {
			return modelMatrix;
		}

		vec3 getRight() const {
			return { modelMatrix.v[0].x, modelMatrix.v[0].y, modelMatrix.v[0].z };
		}

		vec3 getUp() const {
			return { modelMatrix.v[1].x, modelMatrix.v[1].y, modelMatrix.v[1].z };
		}

		vec3 getBackward() const {
			return{ modelMatrix.v[2].x, modelMatrix.v[2].y, modelMatrix.v[2].z };
		}

		vec3 getForward() const {
			return -getBackward();
		}

		vec3 getGlobalScale() const {
			return { length(getRight()), length(getUp()), length(getBackward()) };
		}
	};
}