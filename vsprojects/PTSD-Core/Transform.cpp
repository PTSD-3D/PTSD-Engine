#include "Transform.h"
#include "TransformImplementation.h"

namespace PTSD
{
	Transform::Transform() {
		mImplementation = std::make_unique<TransformImplementation>();
	}
}
