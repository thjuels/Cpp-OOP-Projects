#include "RandomForest.h"

// TODO 2: 
// Take as input the test point x.
// Compute the predictions for every tree in the forest
// Find and return the majority label
int RandomForest::ForestPredict( int *x) { 
    // You can change this
    int results[NumberOfTrees];
    int freq[3] = {};
    for (int i = 0; i < NumberOfTrees; i++){
        results[i] = Trees[i].TreePredict(x);
        if (results[i] == 0){
            ++freq[0];
        } else if (results[i] == 1){
            ++freq[1];
        } else {
            ++freq[2];
        }
    }
    if (freq[0] > freq[1] && freq[0] > freq[2]){
        //return results[0];
        return 0;
    } else if (freq[1] > freq[0] && freq[1] > freq[2]){
        // return results[1];
        return 1;
    } else if (freq[2] > freq[0] && freq[2] > freq[1]){
        // return results[2]; 
        return 2;
    } else if (freq[1] > freq[0] && freq[1] > freq[2]){
        // return results[1]; 
        return 1;
    } else if (freq[0] == freq[1] && freq[0] > freq[2]){
        // return results[0]; 
        return 0;
    } else if (freq[1] == freq[2] && freq[1] > freq[0]){
        // return results[1]; 
        return 1;
    } else if (freq[0] == freq[2] && freq[0] > freq[0]){
        // return results[0]; 
        return 0;
    }
    return 0;
}