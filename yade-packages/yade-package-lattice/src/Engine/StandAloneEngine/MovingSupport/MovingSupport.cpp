/*************************************************************************
*  Copyright (C) 2004 by Janek Kozicki                                   *
*  cosurgi@berlios.de                                                    *
*                                                                        *
*  This program is free software; it is licensed under the terms of the  *
*  GNU General Public License v2 or later. See file LICENSE for details. *
*************************************************************************/

#include "MovingSupport.hpp"
#include <yade/yade-core/MetaBody.hpp>
#include "LatticeBeamParameters.hpp"
#include "LatticeNodeParameters.hpp"
// to calculate strain of whole speciemen - first two bodies in subscribedBodies are Nodes. FIXME - make it clean!
#include <boost/lexical_cast.hpp>

MovingSupport::MovingSupport () : DataRecorder()
{
	subscribedBodies.clear();
	first = true;
	// FIXME ...
        nodeGroupMask           = 1;
        beamGroupMask           = 2;
}


void MovingSupport::postProcessAttributes(bool deserializing)
{
	if(deserializing)
	{
//		first = true;
//		subscribedBodies.clear();
	}
}


void MovingSupport::registerAttributes()
{
	DataRecorder::registerAttributes();
	REGISTER_ATTRIBUTE(sections);

	REGISTER_ATTRIBUTE(first);
	REGISTER_ATTRIBUTE(subscribedBodies);
}


bool MovingSupport::isActivated()
{
	return true;
}


void MovingSupport::action(Body * body)
	// FIXME: about "bool first":
	// FIXME: maybe it could be added to initialiers, and called with a bool argument saying that the initialisation is performed. 
{
//	std::cerr << "MovingSupport quits\n";
//	return;
	
	MetaBody * ncb = static_cast<MetaBody*>(body);

	if(first)
	{
	// scan the sections and delete beams that cross each of them
	// FIXME - this is still problematic, because this should be done only
	// on the first run, regardless of saving/loading this file...
		first = false;
		subscribedBodies.resize( sections.size() );

		std::list<std::pair<Vector3r,std::pair<int,Real> > >::iterator i  =sections.begin();
		std::list<std::pair<Vector3r,std::pair<int,Real> > >::iterator end=sections.end();

		for( int section=0 ; i != end ; ++i, ++section )
		{
			Vector3r midpoint = i->first;
			Real     half     = i->second.second;
			int	 dir	  = i->second.first;
// std::vector
//	<
//		std::pair
//		<
//			std::list
//			<
//				std::pair
//				<
//					std::pair
//					<unsigned int,unsigned int>
//					,Real distance
//				>
//			>
//			, int direction
//		>
//	>	subscribedBodies; // [region]<(list of node pairs, distance), direction>
			if(!subscribedBodies[section].first.empty())
				std::cerr << "First, but not empty\n";

			subscribedBodies[section].second=dir; 

			BodyContainer::iterator bi    = ncb->bodies->begin();
			BodyContainer::iterator biEnd = ncb->bodies->end();
			for(  ; bi!=biEnd ; ++bi )
			{
				if( (*bi)->getGroupMask() & beamGroupMask )
				{
					Vector3r pos1 = (*(ncb->bodies))[static_cast<LatticeBeamParameters*>( (*bi)->physicalParameters.get() )->id1]->physicalParameters->se3.position; // beam first node
					Vector3r pos2 = (*(ncb->bodies))[static_cast<LatticeBeamParameters*>( (*bi)->physicalParameters.get() )->id2]->physicalParameters->se3.position; // beam second node
					
					if( pos1[dir] < pos2[dir] )
						std::swap(pos1,pos2); // make sure that pos1[dir] is bigger 
		
					if(        pos1[dir] > midpoint[dir]
						&& pos2[dir] < midpoint[dir] // beam crosses the plane!

						&& pos1[(dir+1)%3] > midpoint[(dir+1)%3]-half
						&& pos1[(dir+1)%3] < midpoint[(dir+1)%3]+half
						&& pos2[(dir+1)%3] > midpoint[(dir+1)%3]-half
						&& pos2[(dir+1)%3] < midpoint[(dir+1)%3]+half // both points are within halflength in direction (dir+1)%3

						&& pos1[(dir+2)%3] > midpoint[(dir+2)%3]-half
						&& pos1[(dir+2)%3] < midpoint[(dir+2)%3]+half
						&& pos2[(dir+2)%3] > midpoint[(dir+2)%3]-half
						&& pos2[(dir+2)%3] < midpoint[(dir+2)%3]+half // both points are within halflength in direction (dir+2)%3
						)
					{
						subscribedBodies[section].first.push_back(
							 std::make_pair( // push nodes
								 std::make_pair(
								 static_cast<LatticeBeamParameters*>( (*bi)->physicalParameters.get() )->id1
								,static_cast<LatticeBeamParameters*>( (*bi)->physicalParameters.get() )->id2)
								,
								  (*(ncb->bodies))[static_cast<LatticeBeamParameters*>( (*bi)->physicalParameters.get() )->id1]->physicalParameters->se3.position[dir]
								- (*(ncb->bodies))[static_cast<LatticeBeamParameters*>( (*bi)->physicalParameters.get() )->id2]->physicalParameters->se3.position[dir]
								) ); 
						futureDeletes.push_back( (*bi)->getId() );
					}
				}
			}
		}
		// still first: delete
		std::list<unsigned int>::iterator vend = futureDeletes.end();
		for( std::list<unsigned int>::iterator vsta = futureDeletes.begin() ; vsta != vend ; ++vsta)
			ncb->bodies->erase(*vsta); 
	}


	for( int section=0 ; section<sections.size() ; ++section )
	{
	//	std::list<unsigned int>::iterator i   = subscribedBodies[section].first.begin();
	//	std::list<unsigned int>::iterator end = subscribedBodies[section].first.end();
		std::list<std::pair<std::pair<unsigned int,unsigned int>,Real> >::iterator i   = subscribedBodies[section].first.begin();
		std::list<std::pair<std::pair<unsigned int,unsigned int>,Real> >::iterator end = subscribedBodies[section].first.end();
		int dir                               = subscribedBodies[section].second;
		
		Real stress=0; // in direction 'dir'

		for( ; i != end ; ++i )
		{
			unsigned int id1 = i->first.first;
			unsigned int id2 = i->first.second;
			Real        dist = i->second;
			if( (*(ncb->bodies)).exists(id1) && (*(ncb->bodies)).exists(id2) )
			{
				Real current_dist	= (*(ncb->bodies))[id1]->physicalParameters->se3.position[dir]
							- (*(ncb->bodies))[id2]->physicalParameters->se3.position[dir];
				Real delta = (dist - current_dist)/2.0;

				(*(ncb->bodies))[id1]->physicalParameters->se3.position[dir] += delta;
				(*(ncb->bodies))[id2]->physicalParameters->se3.position[dir] -= delta;

				(*(ncb->bodies))[id1]->geometricalModel->diffuseColor = Vector3f(0.0,0.0,((float)section)/2.0); // FIXME [1]
				(*(ncb->bodies))[id2]->geometricalModel->diffuseColor = Vector3f(0.0,0.0,((float)section)/2.0); // FIXME [1]
			}
		}
	}
		
	// [1]
	// mark colors what is monitored - FIXME - provide a way to do that for ALL DataRecorders in that parent class.
	// GLDrawSomething can just put a getClassName()
	 
}

