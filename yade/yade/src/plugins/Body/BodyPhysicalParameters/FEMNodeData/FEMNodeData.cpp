#include "FEMNodeData.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

FEMNodeData::FEMNodeData() : ParticleParameters()
{
	createIndex();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

FEMNodeData::~FEMNodeData()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void FEMNodeData::registerAttributes()
{
	ParticleParameters::registerAttributes();
	REGISTER_ATTRIBUTE(initialPosition);
}

