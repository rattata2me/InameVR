
#include "InameComponent.h"

InameComponent::InameComponent(int id)
{
	component_id = id;
}

InameComponent::~InameComponent()
{
}

int InameComponent::getId() const
{
	return component_id;
}

void InameComponent::setId(int newid)
{
	component_id = newid;
}

