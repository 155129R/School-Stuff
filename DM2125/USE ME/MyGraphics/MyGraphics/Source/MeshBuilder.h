#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string &meshName, Color color);
	static Mesh* GenerateCube(const std::string &meshName, Color color);
    static Mesh* GenerateCircle(const std::string &meshName, Color color, unsigned numSlices);
    static Mesh* GenerateRing(const std::string &meshName, Color color, unsigned numSlices , float innerRadius);
    static Mesh* GenerateSphere(const std::string &meshName, Color color, unsigned numSlices, unsigned numStacks);
    static Mesh* GenerateHemisphere(const std::string &meshName, Color color, unsigned numSlices, unsigned numStacks);
    static Mesh* GenerateCylinder(const std::string &meshName, Color color, unsigned numSlices, bool hollow);
    static Mesh* GenerateTorus(const std::string &meshName, unsigned numStack, unsigned numSlice, float outerRadius, float innerRadius, Color color);
	static Mesh* GenerateSemiCircle(const std::string &meshName, Color color, unsigned numSlices);

	static Mesh* GenerateOBJ(const std::string &meshName, const std::string &file_path);

    static Mesh* GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol);
};

#endif