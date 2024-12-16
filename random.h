#pragma once
#include <random>
#include <ctime>

// This random class was provided in the minesweeper project in programming II
// I added a function that generates a vector of N random IDs
using namespace std;
class Random
{
    static std::mt19937 random;
public:

    static int x;
    static int Int(int min, int max);
    static vector<string> randIDs(int amount);
};

std::mt19937 Random::random(time(0));


int Random::Int(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(random);
}
vector<string> Random::randIDs(int amount)
{
    vector<string> IDs;
    for (int i = 0; i < amount; i++)
    {
        string randID = to_string(Random::Int(0, 99999999));
        // I could make sure there are no repeats, but the probability of having a repeat after inserting the largest test
        // case amount of nodes (1000) is less than 0.0009.

        // ensures that each number is a valid ID
        string leading_zeros;
        while (leading_zeros.size() + randID.size() < 8){
            leading_zeros.append("0");
        }
        randID = leading_zeros.append(randID);
        IDs.push_back(randID);
    }
    return IDs;
}