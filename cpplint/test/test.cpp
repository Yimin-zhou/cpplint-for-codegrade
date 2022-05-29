#include <iostream>
#include <fstream>
#include <vector>

// test part
// int Xssd = 2;
// const int XX = 2;
// int cssd = 2;
// const int cc = 2;
// pid_t xc;
// pid_t Xc;




void copyBoolVector(const std::vector<bool>& source, std::vector<bool>& target)
{
    for ( int i=0; i< source.size(); i++)
    {
        target.at(i) = source.at(i);
    }
}
int knapsack(int capacity, const std::vector<int>& weights, const std::vector<int>& values, int index, std::vector<bool>& included)
{
    if ( ( capacity == 0 ) || ( index == -1 ) ) return 0;
    if ( weights.at(index) > capacity ) return knapsack(capacity, weights, values, index-1, included);
    std::vector<bool> includedWith(included.size());
    copyBoolVector(included, includedWith);
    int valueWith = values.at(index) + knapsack(capacity-weights.at(index), weights, values, index-1, includedWith);
    int valueWithout = knapsack(capacity, weights, values, index-1, included);
    if ( valueWith > valueWithout )
    {
        includedWith.at(index) = true;
        copyBoolVector(includedWith, included);
        return valueWith;
    }
    else
    {
        return valueWithout;
    }
}
int totalWeight(const std::vector<int>& weights, const std::vector<bool>& included)
{
    int sum = 0;
    for ( int i=0; i < weights.size(); i++ )
    {
        if ( included.at(i) ) sum += weights.at(i);
    }
    return sum;
}
std::vector<std::string> argumentVector(int argc, char *argv[])
{
    std::vector<std::string> v(argc);
    for (int i=0; i<argc; i++)
    {
        v.at(i) = argv[i];
    }
    return v;
}
int main(int argc, char *argv[])
{
    std::vector<std::string> arguments;
    arguments = argumentVector(argc,argv);
    if ( arguments.size() < 2 )
    {
        std::cout << "No input filename given" << std::endl;
        return 1;
    }
    
    std::ifstream inputFile;
    inputFile.open(arguments.at(1));
    if ( !inputFile.is_open() )
    {
        std::cout << "Could not open file " << arguments.at(1) << std::endl;
        return 1;
    }
    int capacity;
    inputFile >> capacity;
    std::vector<int> weights;
    std::vector<int> values;
    do
    {
        int weight, value;
        inputFile >> weight >> value;
        if ( inputFile.good() )
        {
            weights.push_back(weight);
            values.push_back(value);
        }
    }
    while ( inputFile.good() );
    inputFile.close();
    std::vector<bool> included(weights.size());
    int totalValue = knapsack(capacity, weights, values, weights.size()-1, included);
    
    std::cout << "With a capacity of " << capacity << " kg, the total value is " 
              << totalValue << " Eur, leading to a total weight of "
              << totalWeight(weights, included) << " kg" << std::endl;
    std::cout << "The following items are included: ";
    for (int i=0; i<included.size(); i++)
    {
        if ( included.at(i) )
        {
            std::cout << '[' << weights.at(i) << ',' << values.at(i) << "] ";
        }
    }
    std::cout << std::endl;
    return 0;
}
