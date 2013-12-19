/*-------------------------------------------------------------------------
*
* File name:      radsbdvp.cpp
*
* Project:        RADIA
*
* Description:    Magnetic field source:
*                 subdivided polyhedron with constant magnetization
*
* Author(s):      Oleg Chubar
*
* First release:  1997
* 
* Copyright (C):  1997 by European Synchrotron Radiation Facility, France
*                 All Rights Reserved
*
-------------------------------------------------------------------------*/

#include "radsbdvp.h"
#include "radg3dgr.h"

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

radTg3dGraphPresent* radTSubdividedPolyhedron::CreateGraphPresent()
{
	radTg3dGraphPresent* g3dGraphPresentPtr = new radTSubdivPolyhedronGraphPresent((radTGroup*)this);
	return g3dGraphPresentPtr;
}

//-------------------------------------------------------------------------

void radTSubdividedPolyhedron::Dump(std::ostream& o, int ShortSign)
{
	((radTg3d*)((radTGroup*)this))->radTg3d::Dump(o, ShortSign);

	o << "Subdivided Polyhedron";

	if(ShortSign==1) return;

	o << endl;
	radTPolyhedron::DumpPureObjInfo(o, ShortSign);
	DumpMaterApplied(o);

	o << endl;
	radTGroup::DumpPureObjInfo(o, ShortSign);

	o << endl;
	((radTg3d*)((radTGroup*)this))->radTg3d::DumpTransApplied(o);

	o << endl;
	o << "   Memory occupied (incl. the content): " << SizeOfThis() << " bytes";
}

//-------------------------------------------------------------------------
