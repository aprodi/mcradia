/*-------------------------------------------------------------------------
*
* File name:      radsbdep.cpp
*
* Project:        RADIA
*
* Description:    Magnetic field source:
*                 subdivided extruded polygon (prism)
*
* Author(s):      Oleg Chubar
*
* First release:  1997
* 
* Copyright (C):  1997 by European Synchrotron Radiation Facility, France
*                 All Rights Reserved
*
-------------------------------------------------------------------------*/

#include "radsbdep.h"
#include "radg3dgr.h"

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

radTg3dGraphPresent* radTSubdividedExtrPolygon::CreateGraphPresent()
{
	radTg3dGraphPresent* g3dGraphPresentPtr = 0;
	if(!AlgsBasedOnKsQsMayNotWork) g3dGraphPresentPtr = new radTSubdivExtrPolygGraphPresent((radTGroup*)this);
	else g3dGraphPresentPtr = new radTGroupGraphPresent((radTGroup*)this);
	g3dGraphPresentPtr->ShowInternalFacesAfterCut = false;
	return g3dGraphPresentPtr;
}

//-------------------------------------------------------------------------

void radTSubdividedExtrPolygon::Dump(std::ostream& o, int ShortSign)
{
	((radTg3d*)((radTGroup*)this))->radTg3d::Dump(o, ShortSign);

	o << "Subdivided ThckPgn";

	if(ShortSign==1) return;

	o << endl;
	radTExtrPolygon::DumpPureObjInfo(o, ShortSign);
	DumpMaterApplied(o);

	o << endl;
	radTGroup::DumpPureObjInfo(o, ShortSign);

	o << endl;
	((radTg3d*)((radTGroup*)this))->radTg3d::DumpTransApplied(o);

	o << endl;
	o << "   Memory occupied (incl. the content): " << SizeOfThis() << " bytes";
}

//-------------------------------------------------------------------------
