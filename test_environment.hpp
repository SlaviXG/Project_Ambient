#include "Environment.h"
#include "cell.h"

#include "doctest.h"


//#ifdef _DEBUG
TEST_CASE("Vision")
{
    Environment env(10, 10);
    env.AddCell(new Cell({1,1})); env.AddCell(new Cell({5,5})); env.AddCell(new Cell({9,9}));
    env.AddCell(new Cell({9,1})); env.AddCell(new Cell({2,9}));

    std::vector<bool> field1 = env.getVisionField({1,0});
    std::vector<bool> checkVec1 = {0,0,0,0,0,
                              0,0,0,0,0,
                              0,0,  1,0,
                              0,0,0,0,0,
                              0,0,0,0,0};
    for(int i = 0; i < 24; i++){
        CHECK(field1[i]== checkVec1[i]);
    }

    std::vector<bool> field2 = env.getVisionField({8,8});
    std::vector<bool> checkVec2 = {0,0,0,0,0,
               0,0,0,0,0,
               0,0,  0,0,
               0,0,0,1,0,
               0,0,0,0,0};  
    for(int i = 0; i < 24; i++){
        CHECK(field2[i] ==checkVec2[i]);
    }

    std::vector<bool> field3 = env.getVisionField({9,0});
    std::vector<bool> checkVec3 = {0,0,0,0,0,
               0,0,0,0,0,
               0,0,  1,0,
               0,0,0,0,0,
               0,0,0,0,0};  
    for(int i = 0; i < 24; i++){
        CHECK(field3[i]==checkVec3[i]);
    }

    std::vector<bool> field4 = env.getVisionField({1,9});
    std::vector<bool> checkVec4 = {0,0,0,0,0,
               0,0,0,0,0,
               0,0,  0,0,
               0,0,1,0,0,
               0,0,0,0,0};  
    for(int i = 0; i < 24; i++){
        CHECK(field4[i]==checkVec4[i]);
    }
    
}
//#endif // _DEBUG
