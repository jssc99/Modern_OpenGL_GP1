#pragma once

#include "basicMath.hpp"

namespace Physics {

	using namespace Core::Maths;

	class Transform
	{
	private:
		// Local space information
		vec3 m_pos = { 0.0f, 0.0f, 0.0f };
		vec3 m_eulerRot = { 0.0f, 0.0f, 0.0f }; //In degs
		vec3 m_scale = { 1.0f, 1.0f, 1.0f };

		// Global space information concatenate in matrix
		mat4 m_modelMatrix = mat::identity4();

		// Dirty flag
		bool m_isDirty = true;

		mat4 getTRS()
		{
			mat4 transformX = mat::rotateX(deg2Rad(m_eulerRot.x));
			mat4 transformY = mat::rotateY(deg2Rad(m_eulerRot.y));
			mat4 transformZ = mat::rotateZ(deg2Rad(m_eulerRot.z));

			// Y * X * Z
			mat4 rotationMatrix = transformY * transformX * transformZ;

			// TRS matrix
			return mat::translate(m_pos) * rotationMatrix * mat::scale(m_scale);
		}

	public:
		void computeModelMatrix() {
			m_modelMatrix = getTRS();
			m_isDirty = false;
		}

		void computeModelMatrix(const mat4& parentGlobalModelMatrix) {
			m_modelMatrix = parentGlobalModelMatrix * getTRS();
			m_isDirty = false;
		}

		void setLocalPosition(const vec3& newPosition) {
			m_pos = newPosition;
			m_isDirty = true;
		}

		void setLocalRotation(const vec3& newRotation) {
			m_eulerRot = newRotation;
			m_isDirty = true;
		}

		void setLocalScale(const vec3& newScale) {
			m_scale = newScale;
			m_isDirty = true;
		}

		const vec3& getGlobalPosition() const {
			return { m_modelMatrix.v[3].x, m_modelMatrix.v[3].y, m_modelMatrix.v[3].z };
		}

		const vec3& getLocalPosition() const {
			return m_pos;
		}

		const vec3& getLocalRotation() const {
			return m_eulerRot;
		}

		const vec3& getLocalScale() const {
			return m_scale;
		}

		const mat4& getModelMatrix() const {
			return m_modelMatrix;
		}

		vec3 getRight() const {
			return { m_modelMatrix.v[0].x, m_modelMatrix.v[0].y, m_modelMatrix.v[0].z };
		}

		vec3 getUp() const {
			return { m_modelMatrix.v[1].x, m_modelMatrix.v[1].y, m_modelMatrix.v[1].z };
		}

		vec3 getBackward() const {
			return{ m_modelMatrix.v[2].x, m_modelMatrix.v[2].y, m_modelMatrix.v[2].z };
		}

		vec3 getForward() const {
			return -getBackward();
		}

		vec3 getGlobalScale() const {
			return { length(getRight()), length(getUp()), length(getBackward()) };
		}

		bool isDirty() const {
			return m_isDirty;
		}
	};
}