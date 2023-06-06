#pragma once

#include "transform.hpp"
#include "model.hpp"

#include <list>
#include <cstdarg>

namespace Physics
{
	using namespace Resources;

	class Entity
	{
	public:
		std::list<Entity*> children;
		Entity* parent = nullptr;

		Transform transform;
		Model* model = nullptr;

		Entity(Model& model) : model(&model) {};
		Entity() {};

		void addChild(Entity& t)
		{
			children.emplace_back(&t);
			children.back()->parent = this;
		}

		void updateSelfAndChild()
		{
			if (transform.isDirty) {
				forceUpdateSelfAndChild();
				return;
			}

			for (auto&& child : children)
				child->updateSelfAndChild();
		}

		void forceUpdateSelfAndChild()
		{
			if (parent)
				transform.computeModelMatrix(parent->transform.getModelMatrix());
			else
				transform.computeModelMatrix();

			for (auto&& child : children)
				child->forceUpdateSelfAndChild();
		}

		void drawSelfAndChild()
		{
			model->draw();

			for (auto&& child : children)
				child->drawSelfAndChild();
		}
	};
}