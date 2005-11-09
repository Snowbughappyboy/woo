/*************************************************************************
*  Copyright (C) 2004 by Olivier Galizzi                                 *
*  olivier.galizzi@imag.fr                                               *
*  Copyright (C) 2004 by Janek Kozicki                                   *
*  cosurgi@berlios.de                                                    *
*                                                                        *
*  This program is free software; it is licensed under the terms of the  *
*  GNU General Public License v2 or later. See file LICENSE for details. *
*************************************************************************/

#ifndef BODY_HPP
#define BODY_HPP

#include <iostream>

#include "GeometricalModel.hpp"
#include "InteractingGeometry.hpp"
#include "BoundingVolume.hpp"
#include "PhysicalParameters.hpp"
#include "InteractionContainer.hpp"
#include "Interaction.hpp"
#include "PhysicalActionContainer.hpp"

#include <yade/yade-lib-wm3-math/Se3.hpp>
#include <yade/yade-lib-serialization/Serializable.hpp>
#include <yade/yade-lib-multimethods/Indexable.hpp>


/*! \brief Abstract interface for bodies stored in BodyContainer, Body represents the atomic element of simulation.
*/

class Body : public Serializable
{
	private	:
		unsigned int id;
		/*! group to which body belongs (maybe vector<int> , to allow multiple groups?)
		 * we can use them to make group one yellow, and group two red, or to record data
		 * from some selected bodies */
		int groupMask;
	public	:
		unsigned int getId() const {return id;};

		// FIXME - but we SHOULDN'T use them in InteractionSolver, because it allows
		//         to have flat simulation. We should make tree simulation and see...
		int getGroupMask() {return groupMask; };

		// only BodyContainer can set the id of a body
		friend class BodyContainer;

		// FIXME - should be private ...
		/// here are stored physical things that describe the Body: mass, stiffness
		shared_ptr<PhysicalParameters>	physicalParameters;
		/// the 'perfect' representation of body's geometry: Polyhedron, Box
		shared_ptr<GeometricalModel>	geometricalModel;
		/// description of how this body interacts with others, like: SphereHierarchy, InteractingBox
		shared_ptr<InteractingGeometry> interactionGeometry;
		/// BoundingVolume is used for quick detection of potential interactions, that can be: AABB, K-Dop
		shared_ptr<BoundingVolume>	boundingVolume;
	
		/*! isDynamic is true if the state of the body is not modified by a kinematicEngine.
		 * It is useful	for example for collision detection : if two colliding bodies are only
		 * kinematic then it is useless to modelise their contact */
		// FIXME : should be determined automatically or not ?? if the body has a subscription to a
		// kinematic engine then it is not dynamic but maybe a body with no subscription can be not dynamic ??
		bool isDynamic;
	
		// Constructor/Destructor
		Body ();
		Body (unsigned int newId, int newGroup);

		// Serialization
	protected:
		void registerAttributes();
	REGISTER_CLASS_NAME(Body);
	REGISTER_BASE_CLASS_NAME(Serializable);
};

REGISTER_SERIALIZABLE(Body,false);

#endif // BODY_HPP

