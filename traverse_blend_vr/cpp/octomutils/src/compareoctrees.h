#ifndef COMPAREOCTREES_H
#define COMPAREOCTREES_H

#include <bitset>
#include <vector>
#include <iostream>
#include <math.h>
#include <algorithm>    // std::reverse

#include "binaryoctree.h"
using namespace std;

class Origin
{
public:
    Origin(float x,float y,float z){
        this->x = x;
        this->y = y;
        this->z = z;
    }
    void setOrigin(float x,float y,float z){
        this->x = x;
        this->y = y;
        this->z = z;
    }
    vector<float> getOrigin(){
        vector<float> origins;
        origins.push_back(this->x);
        origins.push_back(this->y);
        origins.push_back(this->z);
        return origins;
    }
    void printOrigin(){
        cout << "\t****************************************" << endl
             << "\tx: \ty \tz " << endl
             << "\t"<< this->x  << "\t"<< this->y << "\t"<< this->z << endl
             << "\t****************************************" << endl;
    }

    // equality between two origins is given when the coordinates coincide
    friend bool operator== (Origin & lo, Origin & ro){

        if(lo.x == ro.x && lo.y == ro.y && lo.z == ro.z ){
            return true;
        }
        return false;
    }

    float x;
    float y;
    float z;



};

class Subtree
{
public:
    Subtree(int subTreePointer,int depth,Origin origin,float size,int length = 0){
        this->subTreePointer = subTreePointer;
        this->depth = depth;
        //this->origin = origin;
        this->origin = new Origin(origin);
        this->size = size;
        this->subTreeEndPointer = length;
    }
    ~Subtree(void) {  }

    int getSubTreePointer(){
        return this->subTreePointer;
    }
    int getSubTreeEndPointer(){
        return this->subTreeEndPointer;
    }
    Origin* getOrigin(){
        return this->origin;
    }

    void setLength(int length){
        this->subTreeEndPointer = length;
    }

    void printSubTree(){
        cout << "\t****************************************" << endl
             << "\tTreePointer:  " << this->subTreePointer << "\t " << this->subTreeEndPointer << endl
             << "\tDepth: " << this->depth << endl
             << "\tOrigin: x " << this->origin->x << " y " << this->origin->y << " z " << this->origin->z << endl
             << "\tSize: " << this->size << endl
             << "\t****************************************" << endl;

    }

    int subTreePointer;
    int depth;
    Origin* origin;
    float size;
    int subTreeEndPointer;
};

class CompareOcTrees
{
public:
    CompareOcTrees();
    ~CompareOcTrees();

    int getChildCount_rec( std::vector<std::bitset<8> > *tree ,int depth=0, int maxDepth=16);
    void compare(BinaryOctree *orig_tree, BinaryOctree *up_tree);
    void compare(BinaryOctree *orig_tree, vector<Subtree>* orig_subTrees, BinaryOctree *up_tree, vector<Subtree> *up_subTrees);
    vector<Subtree> getSubtrees_iter(std::vector<std::bitset<8> > *tree, float resolution);
    bool compareSubTrees(std::vector<std::bitset<8> > *data_tree1, int lb1, int ub1, std::vector<std::bitset<8> > *data_tree2, int lb2, int ub2);
    bool isOccupied(bitset<8> node1to4, bitset<8> node5to8);
private:
    int getSubTrees_ntonp4_rec(bitset<8> child_n_to_n_p4,std::vector<std::bitset<8> > *tree,int depth=0);
    vector<Origin> calcOrigin(std::bitset<8>  child1to4,std::bitset<8>  child5to8, float resolution, int current_depth, Origin origin);

    float calcSize(float resolution,int depth,int maxDepth= 16);
    int getBranchCount(bitset<8> node1to4,bitset<8> node5to8);
    bool isLeafNode(bitset<8> node1to4,bitset<8> node5to8);



};

#endif // COMPAREOCTREES_H
