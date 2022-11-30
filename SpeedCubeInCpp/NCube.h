#pragma once

#include <iostream>
using namespace std;

#define U64 unsigned long long

#define _0 -1
#define _U 0 
#define _iU 1 
#define _F 2 
#define _iF 3 
#define _R 4 
#define _iR 5 
#define _L 6 
#define _iL 7 
#define _B 8 
#define _iB 9 
#define _D 10 
#define _iD 11 

#define _U2 30
#define _iU2 31
#define _F2 32
#define _iF2 33
#define _R2 34
#define _iR2 35
#define _L2 36
#define _iL2 37
#define _B2 38
#define _iB2 39
#define _D2 40
#define _iD2 41


#define pUBL 0
#define pURB 1
#define pUFR 2
#define pULF 3
#define pDLB 4
#define pDBR 5
#define pDRF 6
#define pDFL 7

#define pUB 0
#define pUR 1
#define pUF 2
#define pUL 3
#define pBL 4
#define pBR 5
#define pFR 6
#define pFL 7
#define pDB 8
#define pDR 9
#define pDF 10
#define pDL 11

#define ps6UBL (1ULL << 3)
#define ps6URB (1ULL << 9)
#define ps6UFR (1ULL << 15)
#define ps6ULF (1ULL << 21)
#define ps6DLB (1ULL << 27)
#define ps6DBR (1ULL << 33)
#define ps6DRF (1ULL << 39)
#define ps6DFL (1ULL << 45)

#define cornerMask ((1ULL << 6) - 1)
#define edgeMask ((1ULL << 5) - 1)

#define p6UBL (pUBL * 6)
#define p6URB (pURB * 6)
#define p6UFR (pUFR * 6)
#define p6ULF (pULF * 6)
#define p6DLB (pDLB * 6)
#define p6DBR (pDBR * 6)
#define p6DRF (pDRF * 6)
#define p6DFL (pDFL * 6)

#define p5UB (pUB * 5)
#define p5UR (pUR * 5)
#define p5UF (pUF * 5)
#define p5UL (pUL * 5)
#define p5BL (pBL * 5)
#define p5BR (pBR * 5)
#define p5FR (pFR * 5)
#define p5FL (pFL * 5)
#define p5DB (pDB * 5)
#define p5DR (pDR * 5)
#define p5DF (pDF * 5)
#define p5DL (pDL * 5)

struct NCube
{
private:
    void SwapCorners(int p1, int p2)
    {
        //U64 d = (this->C >> p1 ^ this->C >> p2) & cornerMask;
        //this->C ^= (d << p1) | (d << p2);

        U64 d = p1 > p2 ?
            (this->C ^ this->C << (p1 - p2)) & (cornerMask << p1) :
            (this->C ^ this->C << (p2 - p1)) & (cornerMask << p2);
        this->C ^= p1 > p2 ? 
            (d | (d >> (p1 - p2))) :
            (d | (d >> (p2 - p1)));
    }

    void SwapEdges(int p1, int p2)
    {
        //U64 d1 = (this->E >> p1 ^ this->E >> p2) & edgeMask;
        //this->E ^= (d1 << p1) | (d1 << p2);

        U64 d = p1 > p2 ? 
            (this->E ^ this->E << (p1 - p2)) & (edgeMask << p1) :
            (this->E ^ this->E << (p2 - p1)) & (edgeMask << p2);
        this->E ^= p1 > p2 ? 
            (d | (d >> (p1 - p2))) :
            (d | (d >> (p2 - p1)));
    }

    void OrientEdges(int p1, int p2, int p3, int p4)
    {
        this->E ^= (1ULL << p1 | 1ULL << p2 | 1ULL << p3 | 1ULL << p4) << 4;
    }


    void OrientCorners(U64 ccw1, U64 ccw2, U64 cw1, U64 cw2)
    {
        U64 ccw = ccw1 | ccw2;
        U64 cw = cw1 | cw2;

        U64 cwx2 = cw << 1;
        U64 three = this->C + ccw + (this->C >> 1 & ccw) + (cwx2 | cw);
        U64 mask = ~((cw | ccw) << 2);
        this->C = (three - ((three & cwx2) >> 1)) & mask;
    }

public:
    U64 C;
    U64 E;

    NCube() : C(0ULL), E(0ULL)
    {
    }

    NCube(U64 c, U64 e) : C(c), E(e)
    {
    }

    void MakeId()
    {
        this->C = 0ULL;
        U64 i = 7ULL;
        do
        {
            this->C += i;
            this->C <<= 6;
            i--;
        } while (i > 0ULL);

        this->E = 0ULL;
        i = 11ULL;
        do
        {
            this->E += i;
            this->E <<= 5;
            i--;
        } while (i > 0ULL);
    }

    void Turn(int t)
    {
        switch (t)
        {
        case _U:
            SwapCorners(p6UBL, p6URB);
            SwapCorners(p6UBL, p6UFR);
            SwapCorners(p6UBL, p6ULF);
            SwapEdges(p5UB, p5UR);
            SwapEdges(p5UB, p5UF);
            SwapEdges(p5UB, p5UL);
            break;
        case _iU:
            SwapCorners(p6UBL, p6ULF);
            SwapCorners(p6UBL, p6UFR);
            SwapCorners(p6UBL, p6URB);
            SwapEdges(p5UB, p5UL);
            SwapEdges(p5UB, p5UF);
            SwapEdges(p5UB, p5UR);
            break;
        case _D:
            SwapCorners(p6DLB, p6DFL);
            SwapCorners(p6DLB, p6DRF);
            SwapCorners(p6DLB, p6DBR);
            SwapEdges(p5DB, p5DL);
            SwapEdges(p5DB, p5DF);
            SwapEdges(p5DB, p5DR);
            break;
        case _iD:
            SwapCorners(p6DLB, p6DBR);
            SwapCorners(p6DLB, p6DRF);
            SwapCorners(p6DLB, p6DFL);
            SwapEdges(p5DB, p5DR);
            SwapEdges(p5DB, p5DF);
            SwapEdges(p5DB, p5DL);
            break;
        case _F:
            SwapCorners(p6ULF, p6UFR);
            SwapCorners(p6ULF, p6DRF);
            SwapCorners(p6ULF, p6DFL);
            SwapEdges(p5UF, p5FR);
            SwapEdges(p5UF, p5DF);
            SwapEdges(p5UF, p5FL);
            OrientEdges(p5UF, p5FR, p5DF, p5FL);
            OrientCorners(ps6ULF, ps6DRF, ps6UFR, ps6DFL);
            break;
        case _iF:
            SwapCorners(p6ULF, p6DFL);
            SwapCorners(p6ULF, p6DRF);
            SwapCorners(p6ULF, p6UFR);
            SwapEdges(p5UF, p5FL);
            SwapEdges(p5UF, p5DF);
            SwapEdges(p5UF, p5FR);
            OrientEdges(p5UF, p5FR, p5DF, p5FL);
            OrientCorners(ps6ULF, ps6DRF, ps6UFR, ps6DFL);
            break;
        case _B:
            SwapCorners(p6UBL, p6DLB);
            SwapCorners(p6UBL, p6DBR);
            SwapCorners(p6UBL, p6URB);
            SwapEdges(p5UB, p5BL);
            SwapEdges(p5UB, p5DB);
            SwapEdges(p5UB, p5BR);
            OrientEdges(p5UB, p5BL, p5DB, p5BR);
            OrientCorners(ps6DLB, ps6URB, ps6UBL, ps6DBR);
            break;
        case _iB:
            SwapCorners(p6UBL, p6URB);
            SwapCorners(p6UBL, p6DBR);
            SwapCorners(p6UBL, p6DLB);
            SwapEdges(p5UB, p5BR);
            SwapEdges(p5UB, p5DB);
            SwapEdges(p5UB, p5BL);
            OrientEdges(p5UB, p5BL, p5DB, p5BR);
            OrientCorners(ps6DLB, ps6URB, ps6UBL, ps6DBR);
            break;
        case _R:
            SwapCorners(p6UFR, p6URB);
            SwapCorners(p6UFR, p6DBR);
            SwapCorners(p6UFR, p6DRF);
            SwapEdges(p5UR, p5BR);
            SwapEdges(p5UR, p5DR);
            SwapEdges(p5UR, p5FR);
            OrientCorners(ps6UFR, ps6DBR, ps6URB, ps6DRF);
            break;
        case _iR:
            SwapCorners(p6UFR, p6DRF);
            SwapCorners(p6UFR, p6DBR);
            SwapCorners(p6UFR, p6URB);
            SwapEdges(p5UR, p5FR);
            SwapEdges(p5UR, p5DR);
            SwapEdges(p5UR, p5BR);
            OrientCorners(ps6UFR, ps6DBR, ps6URB, ps6DRF);
            break;
        case _L:
            SwapCorners(p6UBL, p6ULF);
            SwapCorners(p6UBL, p6DFL);
            SwapCorners(p6UBL, p6DLB);
            SwapEdges(p5UL, p5FL);
            SwapEdges(p5UL, p5DL);
            SwapEdges(p5UL, p5BL);
            OrientCorners(ps6UBL, ps6DFL, ps6ULF, ps6DLB);
            break;
        case _iL:
            SwapCorners(p6UBL, p6DLB);
            SwapCorners(p6UBL, p6DFL);
            SwapCorners(p6UBL, p6ULF);
            SwapEdges(p5UL, p5BL);
            SwapEdges(p5UL, p5DL);
            SwapEdges(p5UL, p5FL);
            OrientCorners(ps6UBL, ps6DFL, ps6ULF, ps6DLB);
            break;

        case _U2:
        case _iU2:
            SwapCorners(p6UBL, p6UFR);
            SwapCorners(p6URB, p6ULF);
            SwapEdges(p5UB, p5UF);
            SwapEdges(p5UR, p5UL);
            break;
        case _D2:
        case _iD2:
            SwapCorners(p6DLB, p6DRF);
            SwapCorners(p6DFL, p6DBR);
            SwapEdges(p5DB, p5DF);
            SwapEdges(p5DL, p5DR);
            break;
        case _F2:
        case _iF2:
            SwapCorners(p6ULF, p6DRF);
            SwapCorners(p6UFR, p6DFL);
            SwapEdges(p5UF, p5DF);
            SwapEdges(p5FR, p5FL);
            break;
        case _B2:
        case _iB2:
            SwapCorners(p6UBL, p6DBR);
            SwapCorners(p6DLB, p6URB);
            SwapEdges(p5UB, p5DB);
            SwapEdges(p5BL, p5BR);
            break;
        case _R2:
        case _iR2:
            SwapCorners(p6UFR, p6DBR);
            SwapCorners(p6URB, p6DRF);
            SwapEdges(p5UR, p5DR);
            SwapEdges(p5BR, p5FR);
            break;
        case _L2:
        case _iL2:
            SwapCorners(p6UBL, p6DFL);
            SwapCorners(p6ULF, p6DLB);
            SwapEdges(p5UL, p5DL);
            SwapEdges(p5FL, p5BL);
            break;

        }
    }
};


