#pragma once

#include "transform.hpp"
#include "model.hpp"

#include <list>

namespace Physics
{
	using namespace Resources;

	class Entity
	{
	public:
		//Scene graph
		std::list<std::unique_ptr<Entity> > children;
		Entity* parent = nullptr;

		Transform transform;
		Model* model = nullptr;

		Entity(Model& model) : model(&model) {}

		template<typename... TArgs>
		void addChild(TArgs&... args) {
			children.emplace_back(std::make_unique<Entity>(args...));
			children.back()->parent = this;
		}

		void updateSelfAndChild()
		{
			if (transform.isDirty()) {
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