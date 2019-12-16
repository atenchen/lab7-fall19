#include "Hash.h"
#include "Hash.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <cassert>

using namespace std;

vector< pair<string, double> > parse(string filename){
    fstream file(filename, fstream::in);
    vector< pair<string, double> > planets;
    if(file.is_open()){
        while(!file.eof() && !file.fail()){
            string name;
            double probs;
            file >> name;
            file >> probs;
            file.ignore(1000, '\n');
            if(!name.empty()) planets.push_back(pair<string, double>(name, probs));
        }
        file.close();
    }
    return planets;
}

int main(){
#ifndef TEST0
    {
        cerr << "\n\tTEST #0: Create an empty hash of the correct size" << endl;
        unsigned int test_size = 10;
        Hash test(test_size);
        assert(test.size() == test_size);

        Node * table = test.getTable();
        for(Node * n = table; n < table + test_size; n++)
            assert(n->key.empty());
        cerr << "\n\t========================PASS========================\n" << endl;
    }
#endif
#ifndef TEST1
    {
        cerr << "\n\tTEST #1: Test hashing functions" << endl;
        unsigned int num_tests = 4;
        string keys[] = {"Don't","wait","To Start","THIS-LAB"};
        unsigned int hashes[] = {4,7,3,4};
        unsigned int test_size = 10;
        Hash test(test_size);
        for(unsigned int i = 0; i < num_tests; i++){
            cerr << test.hasher(keys[i]) << "\tExpected:" << hashes[i] << endl;
            assert(test.hasher(keys[i]) == hashes[i]);
        }

        unsigned int hashes2[] = {4,4,3,3};
        unsigned int test_size2 = 10;
        Hash test2(test_size2);

        assert(test2.nearestPrime(5) == 3);
        assert(test2.nearestPrime(20) == 19);
        assert(test2.nearestPrime(100) == 97);

        for(unsigned int i = 0; i < num_tests; i++){
            cerr << test.hasher2(keys[i]) << "\tExpected:" << hashes2[i] << endl;
            assert(test.hasher2(keys[i]) == hashes2[i]);
        }
        cerr << "\n\t========================PASS========================\n" << endl;
    }
#endif
#ifndef TEST2
    {
        cerr << "\n\tTEST #2: Insert non-colliding keys into the Hash" << endl;
        vector< pair<string, double> > data = parse("testa.dat");
        unsigned int test_size = 10;
        Hash test(test_size);
        for(unsigned int i = 0; i < data.size(); i++){
            assert(test.insert(data.at(i).first, data.at(i).second));
        }
        //check that the hash does not accept values when full
        assert(!test.insert("full", 0.0));
        Node * table = test.getTable();
        for(unsigned int i = 0; i < test.size(); i++){
            cerr << table[i].key << "\tExpected:" << data[i].first << endl;
            assert(table[i].key == data[i].first);
        }
        cerr << "\n\t========================PASS========================\n" << endl;
    }
#endif
#ifndef TEST3
    {
        cerr << "\n\tTEST #3: Insert colliding keys into the Hash" << endl;
        vector< pair<string, double> > data = parse("testb.dat");
        unsigned int test_size = 10;
        Hash test(test_size);
        for(unsigned int i = 0; i < data.size(); i++){
            assert(test.insert(data.at(i).first, data.at(i).second));
        }
        Node * table = test.getTable();
        string keys[] = {"ca", "aaa", "bbbbbbbb", "zxyabcdef", "abc", "abd", "acd", "bc", "bd", "cd"};
        for(unsigned int i = 0; i < test.size(); i++){
            cerr << table[i].key << "\tExpected:" << keys[i] << endl;
            assert(table[i].key == keys[i]);
        }
        cerr << "\n\t========================PASS========================\n" << endl;
    }
#endif
#ifndef TEST4
    {
        cerr << "\n\tTEST #4: Verify valid keys are retrievable" << endl;
        vector< pair<string, double> > data = parse("testc.dat");
        unsigned int test_size = 12;
        Hash test(test_size);
        for(unsigned int i = 0; i < data.size(); i++){
            assert(test.insert(data.at(i).first, data.at(i).second));
        }
        for(unsigned int i = 0; i < data.size(); i++){
            assert(test.find(data.at(i).first) == data.at(i).second);
        }
        assert(test.find("Not in Hash Table") == -1.0);
        cerr << "\n\t========================PASS========================\n" << endl;
    }
#endif
#ifndef TEST5
    {
        cerr << "\n\tTEST #5: Remove entries from the hash" << endl;
        vector< pair<string, double> > data = parse("testc.dat");
        unsigned int test_size = 12;
        Hash test(test_size);
        for(unsigned int i = 0; i < data.size(); i++){
            assert(test.insert(data.at(i).first, data.at(i).second));
        }
        //can't remove data that is not in the table
        assert(!test.remove("Still not in the Hash Table"));

        for(unsigned int i = 0; i < data.size(); i++){
            assert(test.find(data.at(i).first) != -1.0);
            assert(test.remove(data.at(i).first));
            assert(test.find(data.at(i).first) == -1.0);
        }
        assert(test.empty());
        cerr << "\n\t========================PASS========================\n" << endl;
    }
#endif
    cerr << "\n\tAll Tests Passed.\nDon't forget to run with Valgrind and commit to Github!\n" << endl;
}
