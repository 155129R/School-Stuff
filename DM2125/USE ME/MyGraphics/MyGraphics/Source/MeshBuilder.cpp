#include "MeshBuilder.h"
#include <GL\glew.h>
#include <vector>
#include "MyMath.h"
#include "LoadOBJ.h"

/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;

    v.pos.Set(-lengthX, 0, 0);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(lengthX, 0, 0);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(0, -lengthY, 0);	v.color.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(0, lengthY, 0);	v.color.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(0, 0, -lengthZ);	v.color.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0, 0, lengthZ);	v.color.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    for (int i = 0; i < 6; i++){

        index_buffer_data.push_back(i);

    }
    Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();
    mesh->mode = Mesh::DRAW_LINES;

    return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, Color color)
{
    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;

    v.pos.Set(0.5f, 0.f, 0.5f);   v.color = color;	v.texCoord.Set(0, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, 0.f, -0.5f);  v.color = color;	v.texCoord.Set(1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.f, -0.5f); v.color = color;	v.texCoord.Set(1, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, 0.f, 0.5f);	  v.color = color;	v.texCoord.Set(0, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.f, -0.5f); v.color = color;	v.texCoord.Set(1, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.f, 0.5f);  v.color = color;	v.texCoord.Set(0, 1);	vertex_buffer_data.push_back(v);



    for (unsigned i = 0; i < 6; ++i)
    {

        index_buffer_data.push_back(i);

    }

    Mesh *mesh = new Mesh(meshName);


    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();

    mesh->mode = Mesh::DRAW_TRIANGLES;


    return mesh;



}


/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string &meshName, Color color)
{
    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;

    v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, -0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, 0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);

    v.pos.Set(0.5f, -0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, -0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, 0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, -0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);

    v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, -0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, -0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);

    v.pos.Set(-0.5f, 0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, -0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, -0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, 0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, -0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, 0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);

    v.pos.Set(0.5f, -0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, 0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, -0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, 0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, 0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);

    v.pos.Set(0.5f, 0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, 0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, -0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);

    for (unsigned i = 0; i < 36; ++i)
    {
        index_buffer_data.push_back(i);
    }

    Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLES;

    return mesh;
}

float circleX(float theta){

    return cos(Math::DegreeToRadian(theta));

}

float circleZ(float theta){

    return sin(Math::DegreeToRadian(theta));

}

Mesh* MeshBuilder::GenerateCircle(const std::string &meshName, Color color, unsigned numSlices){

    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;

    float anglePerSlice = 360.0f / numSlices;

    for (unsigned short slice = 0; slice <= numSlices; ++slice){

        float theta = slice * anglePerSlice;
        v.pos.Set(circleX(theta), 0, circleZ(theta));
        v.color = color;
        vertex_buffer_data.push_back(v);

    }

    v.pos.Set(0, 0, 0);
    v.color = color;
    vertex_buffer_data.push_back(v);

    for (unsigned int slice = 0; slice <= numSlices; ++slice){

        index_buffer_data.push_back(slice);
        index_buffer_data.push_back(numSlices);

    }

    Mesh *mesh = new Mesh(meshName);


    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

    return mesh;

}

Mesh* MeshBuilder::GenerateSemiCircle(const std::string &meshName, Color color, unsigned numSlices){

    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;

    float anglePerSlice = 180.0f / numSlices;

    for (unsigned short slice = 0; slice <= numSlices; ++slice){

        float theta = slice * anglePerSlice;
        v.pos.Set(circleX(theta), 0, circleZ(theta));
        v.color = color;
        vertex_buffer_data.push_back(v);

    }

    v.pos.Set(0, 0, 0);
    v.color = color;
    vertex_buffer_data.push_back(v);

    for (unsigned int slice = 0; slice <= numSlices; ++slice){

        index_buffer_data.push_back(slice);
        index_buffer_data.push_back(numSlices);

    }

    Mesh *mesh = new Mesh(meshName);


    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

    return mesh;

}

Mesh* MeshBuilder::GenerateRing(const std::string &meshName, Color color, unsigned numSlices, float innerRadius){


    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;

    float anglePerSlice = 360.0f / numSlices;

    for (unsigned short slice = 0; slice < numSlices + 1; ++slice){

        float theta = slice * anglePerSlice;

        v.pos.Set(circleX(theta), 0, circleZ(theta));//Outer Circle
        v.color = color;
        vertex_buffer_data.push_back(v);

        v.pos.Set(innerRadius * circleX(theta), 0, innerRadius * circleZ(theta));//Outer Circle
        v.color = color;
        vertex_buffer_data.push_back(v);

    }
    for (unsigned short slice = 0; slice < numSlices + 1; ++slice){

        float theta = slice * anglePerSlice;

        v.pos.Set(-circleX(theta), 0, circleZ(theta));//Outer Circle
        v.color = color;
        vertex_buffer_data.push_back(v);

        v.pos.Set(innerRadius * -circleX(theta), 0, innerRadius * circleZ(theta));//inner Circle
        v.color = color;
        vertex_buffer_data.push_back(v);

    }

    for (int i = 0; i < vertex_buffer_data.size(); i++){

        index_buffer_data.push_back(i);

    }

    Mesh *mesh = new Mesh(meshName);


    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

    return mesh;

}


float sphereX(float phi, float theta){

    return (cos(Math::DegreeToRadian(theta)) * cos(Math::DegreeToRadian(phi)));

}

float sphereY(float phi, float theta){

    return sin(Math::DegreeToRadian(phi));

}

float sphereZ(float phi, float theta){

    return (sin(Math::DegreeToRadian(theta)) * cos(Math::DegreeToRadian(phi)));

}

Mesh* MeshBuilder::GenerateSphere(const std::string &meshName, Color color, unsigned numSlices, unsigned numStacks){

    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;

    float anglePerStack = 180.0f / numStacks;
    float anglePerSlice = 360.0f / numSlices;

    for (unsigned stack = 0; stack <= numStacks; stack++){

        float phi = -90 + stack * anglePerStack;

        for (unsigned short slice = 0; slice <= numSlices; ++slice){

            float theta = slice * anglePerSlice;
            v.pos.Set(sphereX(phi, theta), sphereY(phi, theta), sphereZ(phi, theta));
            v.color = color;
            v.normal.Set(sphereX(phi, theta), sphereY(phi, theta), sphereZ(phi, theta));
            vertex_buffer_data.push_back(v);

        }

    }

    for (unsigned stack = 0; stack < numStacks; ++stack){
        for (unsigned int slice = 0; slice <= numSlices; ++slice){

            index_buffer_data.push_back(stack * (numSlices + 1) + slice);
            index_buffer_data.push_back((stack + 1) * (numSlices + 1) + slice);

        }
    }

    Mesh *mesh = new Mesh(meshName);


    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();

    mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

    return mesh;



}

Mesh* MeshBuilder::GenerateTorus(const std::string &meshName, unsigned numStack, unsigned numSlice, float outerRadius, float innerRadius, Color color)
{
    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;

    float degreePerStack = 360.f / numStack;
    float degreePerSlice = 360.f / numSlice;
    float x1, z1; //y1 is always zero
    float x2, y2, z2;

    for (unsigned stack = 0; stack < numStack + 1; stack++)
    {

        for (unsigned slice = 0; slice < numSlice + 1; slice++){
            z1 = (outerRadius * cos(Math::DegreeToRadian(stack * degreePerStack)));
            x1 = outerRadius * sin(Math::DegreeToRadian(stack * degreePerStack));
            z2 = (outerRadius + innerRadius * cos(Math::DegreeToRadian(slice * degreePerSlice))) * cos(Math::DegreeToRadian(stack * degreePerStack));
            y2 = innerRadius * sin(Math::DegreeToRadian(slice * degreePerSlice));
            x2 = (outerRadius + innerRadius * cos(Math::DegreeToRadian(slice * degreePerSlice))) * sin(Math::DegreeToRadian(stack * degreePerStack));

            v.pos.Set(x2, y2, z2);
            v.color = color;
            v.normal.Set((x2 - x1), y2, (z2 - z1));
            vertex_buffer_data.push_back(v);

        }
    }

    for (unsigned stack = 0; stack < numStack; stack++)
    {
        for (unsigned slice = 0; slice < numSlice + 1; slice++)
        {
            index_buffer_data.push_back((numSlice + 1) * stack + slice + 0);
            index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 0);
        }
    }

    Mesh *mesh = new Mesh(meshName);


    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();

    mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

    return mesh;
}

Mesh* MeshBuilder::GenerateCylinder(const std::string &meshName, Color color, unsigned numSlices, bool hollow)
{
    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;

    float anglePerSlice = 360.f / numSlices;

    for (unsigned slice = 0; slice < numSlices + 1; ++slice)
    {
        float theta = slice *anglePerSlice;
        v.pos.Set(circleX(theta), 0, circleZ(theta));
        v.color = color;
        v.normal.Set(circleX(theta), 0, circleZ(theta));
        vertex_buffer_data.push_back(v);

        v.pos.Set(circleX(theta), 1, circleZ(theta));
        v.color = color;
        v.normal.Set(circleX(theta), 0, circleZ(theta));
        vertex_buffer_data.push_back(v);
    }

    v.pos.Set(0, 0, 0);
    v.color = color;
    v.normal.Set(0, -1, 0);
    vertex_buffer_data.push_back(v);

    v.pos.Set(0, 1, 0);
    v.color = color;
    v.normal.Set(0, 1, 0);
    vertex_buffer_data.push_back(v);

    for (unsigned slice = 0; slice < numSlices + 1; ++slice)
    {
        index_buffer_data.push_back(2 * slice);
        index_buffer_data.push_back(2 * slice + 1);
    }

    if (hollow == false){
        for (unsigned slice = 0; slice < numSlices + 1; ++slice)
        {
            index_buffer_data.push_back(2 * (numSlices + 1));
            index_buffer_data.push_back(2 * slice);

        }

        for (unsigned slice = 0; slice < numSlices + 1; ++slice)
        {
            index_buffer_data.push_back(2 * slice + 1);
            index_buffer_data.push_back(2 * (numSlices + 1) + 1);
        }
    }
    Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

    return mesh;
}

Mesh* MeshBuilder::GenerateHemisphere(const std::string &meshName, Color color, unsigned numSlices, unsigned numStacks){

    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;

    float anglePerStack = 90.0f / numStacks;
    float anglePerSlice = 360.0f / numSlices;

    for (unsigned stack = 0; stack <= numStacks; stack++){

        float phi = -90 + stack * anglePerStack;

        for (unsigned short slice = 0; slice <= numSlices; ++slice){

            float theta = slice * anglePerSlice;
            v.pos.Set(sphereX(phi, theta), sphereY(phi, theta), sphereZ(phi, theta));
            v.color = color;
            v.normal.Set(sphereX(phi, theta), sphereY(phi, theta), sphereZ(phi, theta));
            vertex_buffer_data.push_back(v);

        }

    }

    for (unsigned stack = 0; stack < numStacks; ++stack){
        for (unsigned int slice = 0; slice <= numSlices; ++slice){

            index_buffer_data.push_back(stack * (numSlices + 1) + slice);
            index_buffer_data.push_back((stack + 1) * (numSlices + 1) + slice);

        }
    }

    for (unsigned short slice = 0; slice <= numSlices; ++slice){

        float theta = slice * anglePerSlice;
        v.pos.Set(circleX(theta), 0, circleZ(theta));
        v.color = color;
        vertex_buffer_data.push_back(v);

    }

    v.pos.Set(0, 0, 0);
    v.color = color;
    vertex_buffer_data.push_back(v);

    for (unsigned int slice = 0; slice <= numSlices; ++slice){

        index_buffer_data.push_back(slice);
        index_buffer_data.push_back(numSlices);

    }

    Mesh *mesh = new Mesh(meshName);


    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();

    mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

    return mesh;



}


Mesh* MeshBuilder::GenerateOBJ(const std::string &meshName, const std::string &file_path){
    //Read vertices, texcoords & normals from OBJ
    std::vector<Position> vertices;
    std::vector<TexCoord> uvs;
    std::vector<Vector3> normals;
    bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);
    if (!success)
        return NULL;
    //Index the vertices, texcoords & normals properly
    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);
    //Create the mesh and call glBindBuffer, glBufferData
    //Use triangle list and remember to set index size

    Mesh *mesh = new Mesh(meshName);


    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();

    mesh->mode = Mesh::DRAW_TRIANGLES;

    return mesh;
}

Mesh* MeshBuilder::GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol)
{
    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;

    int offset = 0;

    float width = 1.f / numCol;
    float height = 1.f / numRow;
    for (unsigned i = 0; i < numRow; ++i)
    {
        for (unsigned j = 0; j < numCol; ++j)
        {
            //Task: Add 4 vertices into vertex_buffer_data
            v.pos.Set(-0.5f, -0.5f, 0.f);   /*v.color = (1,1,1);*/	v.texCoord.Set((j)*width, 1.f - (i + 1) * height);	 v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v);
            v.pos.Set(0.5f, -0.5f, 0.f);  /*v.color = (1,1,1);*/	v.texCoord.Set((j + 1) * width, 1.f - (i + 1) * height);	v.normal.Set(0, 0, 1);  vertex_buffer_data.push_back(v);
            
            v.pos.Set(0.5f, 0.5f, 0.f);	  /*v.color = (1,1,1);*/	v.texCoord.Set((j + 1) * width, 1.f - (i)* height);	v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v);
            v.pos.Set(-0.5f, 0.5f, 0.f); /*v.color = (1,1,1);*/    v.texCoord.Set((j)* width, 1.f - i * height);	v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v);
            




            //Task: Add 6 indices into index_buffer_data


            index_buffer_data.push_back(offset + 0);
            index_buffer_data.push_back(offset + 1);
            index_buffer_data.push_back(offset + 2);
            index_buffer_data.push_back(offset + 0);
            index_buffer_data.push_back(offset + 2);
            index_buffer_data.push_back(offset + 3);
            //  index_buffer_data.push_back(offset + 6);
            offset += 4;

        }
    }





    Mesh *mesh = new Mesh(meshName);


    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();

    mesh->mode = Mesh::DRAW_TRIANGLES;


    return mesh;
}