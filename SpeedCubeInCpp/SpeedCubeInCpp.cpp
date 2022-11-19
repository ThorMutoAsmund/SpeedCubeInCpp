// SpeedCubeInCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "NCube.h"
#include <chrono>

using namespace std::chrono;
using namespace std;

int main()
{
    NCube id;
    id.MakeId();



    //F R D2 U2 R D2 R2 F2 L' U2 R' D2 B' R2 F R2 F' D' U2
    uint8_t moves[] = { _F, _R, _D2, _U2, _R, _D2, _R2, _F2, _iL, _U2, _iR, _D2, _iB, _R2, _F, _R2, _iF, _iD, _U2 };

    auto start = high_resolution_clock::now();
    for (int i = 0; i < 10000000; ++i)
    {
        NCube c = id;
        for (int t = 0; t < 19; ++t)
        {
            c.Turn(moves[t]);
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << duration.count()/1000 << "ms" << endl;
}

