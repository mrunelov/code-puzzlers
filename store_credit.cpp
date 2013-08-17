#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>

/**
 * @author Martin Runelöv
 * Solution to the code jam problem "Store Credit"
 * http://code.google.com/codejam/contest/351101/dashboard#s=p0
 */

void processFile();
void findItems(int testCase, int credit, int numItems, std::vector<int> itemPrices);

int main(int argc, char *argv[]) {
    processFile();
}

void processFile() {
    using std::cout;
    
    int numTestCases;
    std::ifstream infile("A-large-practice.in");
    std::string line;
    
    // Read first int, number of test cases
    std::getline(infile,line);
    std::istringstream iss(line);
    iss >> numTestCases;
    iss.clear();
    //cout << "Number of test cases: " << numTestCases << "\n";  
    
    for (int i = 0; i < numTestCases; ++i) {
        using std::vector;
        using std::istream_iterator;
        
        int credit, numItems;
        vector<int> itemPrices;
        
        //Parse credit
        std::getline(infile,line);
        iss.str(line);
        iss >> credit;
        iss.clear();

        //Parse number of items        
        std::getline(infile,line);
        iss.str(line);
        iss >> numItems;
        iss.clear();

        //Parse list of item prices
        std::getline(infile,line);
        iss.str(line);
        copy(istream_iterator<int>(iss), istream_iterator<int>(),
             back_inserter(itemPrices));
        iss.clear();
        
        findItems(i+1,credit,numItems,itemPrices);
  } 
} 

/**
 * Find two items whose price adds up to the store credit
 */
void findItems(int testCase, int credit, int numItems, std::vector<int> itemPrices) {
    using std::cout;
    using std::endl;
    //cout << "Credit: " << credit << "\n"; 
    //cout << "Number of items: " << numItems << "\n"; 
    for (int i = 0; i < numItems; ++i) {
        if (itemPrices[i] > credit)
            continue;
        for (int j = i+1; j < numItems; ++j) {
            if (itemPrices[i] + itemPrices[j] == credit) {
                cout << "Case #" << testCase << ": " << i+1 << " " << j+1 << endl;
                break;
            }
        }
    }
}    

    