#include <iostream>
#include <GUSEGE/Utility.h>

struct VoxelData
{
    std::string name;
    Vector3 color;

    VoxelData(std::string name = "air", Vector3 color = Vector3())
    : name(name), color(color) {}
};


class VoxelRegistry{
public:
    inline static std::vector<VoxelData> voxels;

    static void AddToRegistry(VoxelData voxelData)
    {
        voxels.push_back(voxelData);
    }

    static VoxelData GetBlockFromRegistry(std::string voxelName)
    {
        for (auto voxelData : voxels)
        {
            if(voxelData.name == voxelName)
                return voxelData;
        }

        return VoxelData();
    }
};