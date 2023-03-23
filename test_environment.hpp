#include "Environment.h"
#include "cell.h"

#include "doctest.h"

// #ifdef _DEBUG

namespace environment
{
    TEST_SUITE("Environment")
    {
        TEST_CASE("Vision")
        {
            Environment env(10, 10);
            env.AddCell(new Cell({1, 1}));
            env.AddCell(new Cell({5, 5}));
            env.AddCell(new Cell({9, 9}));
            env.AddCell(new Cell({9, 1}));
            env.AddCell(new Cell({2, 9}));

            std::vector<bool> field1 = env.getVisionField({1, 0});
            std::vector<bool> checkVec1 = {0, 0, 0, 0, 0,
                                           0, 0, 0, 0, 0,
                                           0, 0, 1, 0,
                                           0, 0, 0, 0, 0,
                                           0, 0, 0, 0, 0};
            for (int i = 0; i < 24; i++)
            {
                CHECK(field1[i] == checkVec1[i]);
            }

            std::vector<bool> field2 = env.getVisionField({8, 8});
            std::vector<bool> checkVec2 = {0, 0, 0, 0, 0,
                                           0, 0, 0, 0, 0,
                                           0, 0, 0, 0,
                                           0, 0, 0, 1, 0,
                                           0, 0, 0, 0, 0};
            for (int i = 0; i < 24; i++)
            {
                CHECK(field2[i] == checkVec2[i]);
            }

            std::vector<bool> field3 = env.getVisionField({9, 0});
            std::vector<bool> checkVec3 = {0, 0, 0, 0, 0,
                                           0, 0, 0, 0, 0,
                                           0, 0, 1, 0,
                                           0, 0, 0, 0, 0,
                                           0, 0, 0, 0, 0};
            for (int i = 0; i < 24; i++)
            {
                CHECK(field3[i] == checkVec3[i]);
            }

            std::vector<bool> field4 = env.getVisionField({1, 9});
            std::vector<bool> checkVec4 = {0, 0, 0, 0, 0,
                                           0, 0, 0, 0, 0,
                                           0, 0, 0, 0,
                                           0, 0, 1, 0, 0,
                                           0, 0, 0, 0, 0};
            for (int i = 0; i < 24; i++)
            {
                CHECK(field4[i] == checkVec4[i]);
            }
        }
    }

    TEST_CASE("Test randomFreePosition")
    {
        // Create an environment with a single free cell at (0, 0)
        Environment env(2, 2);
        genotype::Point freeCell{0, 0};

        SUBCASE("Test getting a random free position near a free cell")
        {
            // Try 10 times to get a random free position near the free cell
            for (int i = 0; i < 10; ++i)
            {
                genotype::Point randPoint = env.randomFreePosition(freeCell);
                CHECK(randPoint != genotype::Point{-1, -1}); // Make sure a valid point is returned
                CHECK(abs(randPoint.i - freeCell.i) <= 1);   // Make sure the returned point is within a radius of one from the free cell
                CHECK(abs(randPoint.j - freeCell.j) <= 1);   // Make sure the returned point is within a radius of one from the free cell
                CHECK(randPoint != freeCell);                // Make sure the returned point is not the same as the free cell
            }
        }

        SUBCASE("Test getting a random free position near a occupied cell")
        {
            // Add an occupied cell at (0, 1)
            genotype::Point occupiedCell{0, 1};
            env.AddCell(new Cell(occupiedCell));

            // Try 10 times to get a random free position near the occupied cell
            for (int i = 0; i < 10; ++i)
            {
                genotype::Point randPoint = env.randomFreePosition(occupiedCell);
                CHECK(randPoint != genotype::Point{-1, -1});   // Make sure a valid point is returned
                CHECK(abs(randPoint.i - occupiedCell.i) <= 1); // Make sure the returned point is within a radius of one from the occupied cell
                CHECK(abs(randPoint.j - occupiedCell.j) <= 1); // Make sure the returned point is within a radius of one from the occupied cell
                CHECK(randPoint != occupiedCell);              // Make sure the returned point is not the same as the occupied cell
            }
        }

        SUBCASE("Test getting a random free position near a cell at the edge of the map")
        {
            // Try 10 times to get a random free position near the cell at the edge of the map
            genotype::Point cellAtEdge{0, env.getWidth() - 1};
            for (int i = 0; i < 10; ++i)
            {
                genotype::Point randPoint = env.randomFreePosition(cellAtEdge);
                CHECK(randPoint != genotype::Point{-1, -1}); // Make sure a valid point is returned
                CHECK(abs(randPoint.i - cellAtEdge.i) <= 1); // Make sure the returned point is within a radius of one from the cell at the edge of the map
                CHECK(abs(randPoint.j - cellAtEdge.j) <= 1); // Make sure the returned point is within a radius of one from the cell at the edge of the map
                CHECK(randPoint != cellAtEdge);              // Make sure the returned point is not the same as the cell at the edge of the map
            }
        }
    }

    TEST_CASE("Test updateMap")
    {
        /*
         * Tests that the frameMatrix is properly updated when there are no cells.
         */
        SUBCASE("NoCells")
        {
            Environment env(5, 5);
            env.updateMap();

            for (int i = 0; i < env.getHeight(); i++)
            {
                for (int j = 0; j < env.getWidth(); j++)
                {
                    CHECK(env.getFrame({i, j}) == nullptr);
                }
            }
        }

        /**
         * Tests that the frameMatrix is properly updated when there is one cell.
         */
        SUBCASE("OneCell")
        {
            Environment env(5, 5);

            Cell cell;
            cell.setPosition({0, 0});

            env.AddCell(&cell);
            env.updateMap();

            CHECK(env.getFrame({0, 0}) == &cell);
        }

        /**
         * Tests that the frameMatrix is properly updated when there are multiple cells.
         */
        SUBCASE("MultipleCells")
        {
            Environment env(5, 5);

            Cell cell1;
            cell1.setPosition({0, 0});

            Cell cell2;
            cell2.setPosition({4, 4});

            env.AddCell(&cell1);
            env.AddCell(&cell2);
            env.updateMap();

            CHECK(env.getFrame({0, 0}) == &cell1);
            CHECK(env.getFrame({4, 4}) == &cell2);

            // Change position
            cell1.setPosition({0, 1});
            env.updateMap();

            CHECK(env.getFrame({0, 1}) == &cell1);
            CHECK(env.getFrame({0, 0}) == nullptr);
        }
    }
}
// #endif // _DEBUG
