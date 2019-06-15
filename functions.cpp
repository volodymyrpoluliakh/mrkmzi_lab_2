#include "functions.h"
#include <string>
#include "big_int.h"
#include <time.h>
#include <algorithm>

uint32_t* idealGenerator(){
    uint32_t* masInt = new uint32_t [65536];
    uint8_t buf = 0;
    for(int i = 0 ; i < 65536; i++){
        for(int j = 0; j < 4; j++){
            masInt[i] = (masInt[i] << 8) ^ buf;
            buf++;
        }
    }
    return masInt;
}

uint32_t* generateBuiltInRand()
{
    cout << " start generating " << endl;
    uint32_t* masInt = new uint32_t [65536];
    uint32_t rd;

    srand(time(NULL));
    for (int i = 0; i < 65536; i++){
        for (int j = 0; j < 4; j++){
            rd = rand();
            masInt[i] = (masInt[i] << 8) | (rd & 0xFF);
        }
    }

    cout << "built-in gen finished " << endl;

    return masInt;
}

uint32_t* generateLehmerHigh()
{
    uint32_t  xN, a = 0x10001, c = 0x77;
    uint32_t* masInt = new uint32_t [65536];

    int rd;
    srand(time(NULL));
    while ( rd == 0 )
    {
        rd = rand();
    }
    xN = rd;

    for (int i = 0; i < 65536; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            xN = xN * a + c;
 //           buf = ((xN >> 24) & 0xFF);
            masInt[i] = (masInt[i] << 8) | ((xN >> 24) & 0xFF);
        }
    }
    return masInt;
}

uint32_t* generateLehmerLow(){
    uint32_t  xN, a = 0x10001, c = 0x77;
    uint32_t* masInt = new uint32_t [65536];

    int rd;
    srand(time(NULL));
    while ( rd == 0 )
    {
        rd = rand();
    }
    xN = rd;

    uint8_t buf = 0;
    for (int i = 0; i < 65536; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            xN = xN *a + c;
            masInt[i] = (masInt[i] << 8) | (xN & 0xFF);
        }
    }
    return masInt;
}

uint32_t* generateL20()
{
    uint32_t* masInt = new uint32_t [65536];

    int rd;
    srand(time(NULL));
    while ( rd == 0 )
    {
        rd = rand();
    }
    uint32_t state = rd;
    uint32_t buf = 0;

    for(int i = 0; i < 65536; i++)
    {
        for (int j = 0; j < 32; j++){
            buf = (( (state >> 19) ^ (state >> 8) ^ (state >> 4) ^ (state >> 2))&1);
            state <<= 1;
            state = state | buf;
        }
        masInt[i] = state;
    }
    return masInt;
}

uint32_t* generateL89()
{
    uint32_t* masInt = new uint32_t [65536];


    int rd;
    srand(time(NULL));
    while ( rd == 0 )
    {
        rd = rand();
    }
    uint32_t state[3];
    state[2] = rd;
    state[2] = (state[2] << 15) | rand();
    state[2] = (state[2] << 2) | (rand() >> 13);

    state[0] = rand();
    state[1] = rand();
    for (int i = 0; i < 3; i++){
        state[1] = (state[1] << 8) | rand();
        state[0] = (state[0] << 8) | rand();

    }

    uint32_t buf = 0;
    for (int i = 0; i < 21844; i++)
    {
        for (int j = 0; j < 96; j++)
        {
            buf = (((state[0] >> 24)  ^ (state[1] >> 6))&1);
            state[0] = (state[0] << 1) | (state[1] >> 31);
            state[1] = (state[1] << 1) | (state[2] >> 31);
            state[2] <<= 1;
            state[2] |= buf;
        }
        masInt[i*3] = state[0];
        masInt[i*3 + 1] = state[1];
        masInt[i*3 + 2] = state[2];
    }
    for (int i = 0 ; i < 64; i++)
    {
        buf = (((state[2] >> 25)  ^ (state[1] >> 21))&1);
        state[0] = (state[0] << 1) | (state[1] >> 31);
        state[1] = (state[1] << 1) | (state[2] >> 31);
        state[2] <<= 1;
        state[2] |= buf;
    }
    masInt[65535] = state[0];

    return masInt;
}

uint32_t* generateLibrarist()
{
    uint32_t* masInt = new uint32_t [65535];
    string str_link = "C:\\Users\\User\\Desktop\\asymcrypt\\AsymCryptoLab2\\adams_douglas_the_hitchhiker_s_guide_to_the_galaxy.txt";

    ifstream f;
    f.open(str_link);
    string buf{}, text{};

    while (!f.eof() && (text.length() <= 262144))
    {
        getline(f, buf);
        if(buf != "\0"){
            transform(buf.begin(), buf.end(), buf.begin(), ::tolower);
            text += buf;
        }
        buf = "";
    }
    cout << text.length() << " " << text;
    for (int i = 0 ; i < 65536; i++)
    {
        for (int j = 0 ; j < 4; j++){
            masInt[i] = ((masInt[i] << 8) |  (uint32_t)text[i + j*4]);
        }
    }

    return masInt;
}

uint32_t* generateGiffi()
{
    uint32_t* l1 = new uint32_t[65536];
    uint32_t* l2 = new uint32_t[65536];
    uint32_t* l3 = new uint32_t[65536];

    uint32_t buf, state = 0;
    srand(time(NULL));

    while(state == 0){
        state = rand();
    }
    state = (state << 15) | rand();
    state = (state << 2) | (rand() >> 13);

    for (int i = 0 ; i < 65536; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            buf = (((state >> 10) ^ (state >> 8)) & 1);
            state <<= 1;
            state = state | buf;
        }
        l1[i] = state;
    }

    state = rand();
    while(state == 0){
        state = rand();
    }
    state = (state << 15) | rand();
    state = (state << 2) | (rand() >> 13);

    for (int i  = 0; i < 65536; i++)
    {
        for ( int j = 0; j < 32; j++)
        {
            buf = (((state >> 8) ^ (state >> 7) ^ (state >> 5) ^ (state >> 4)) & 1);
            state <<= 1;
            state = state | buf;
        }
        l2[i] = state;
    }

    state = rand();
    while(state == 0){
        state = rand();
    }
    state = (state << 15) | rand();
    state = (state << 2) | (rand() >> 13);

    for (int i = 0; i < 65536; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            buf = (((state >> 9) ^ (state >> 6))& 1);
            state <<= 1;
            state = state | buf;
        }
        l3[i] = state;
    }
    uint32_t* gf = new uint32_t[65536];
    for (int i = 0; i < 65536; i++){
        gf[i] = (l1[i] & l3[i]) ^ ((~l3[i]) & l2[i]);
    }

    return gf;
}

uint32_t* generateWolfram()
{
    uint32_t* masInt = new uint32_t [65536];

    uint32_t state, buf;
    state = rand();
    state = (state << 16) | rand();
    while (state == 0)
    {
        state = rand();
        state = (state << 16) | rand();
    }

    for (int i = 0 ; i < 65536; i++)
    {
        for (int j = 0 ; j < 32; j++)
        {
            state = ((state << 1) | (state >> 31)) ^ (state | ((state >> 1) | (state << 31))); //cicle rotate
            buf <<= 1;
            buf = buf | (state & 1);
        }
        masInt[i] = buf;
    }

    return masInt;
}

uint32_t* generateBM(uint64_t length)
{
    big_int* p = new big_int("CEA42B987C44FA642D80AD9F51F10457690DEF10C83D0BC1BCEE12FC3B6093E3");
    big_int* a = new big_int("5B88C41246790891C095E2878880342E88C79974303BD0400B090FE38A688356");
    big_int* q = new big_int("675215CC3E227D3216C056CFA8F8822BB486F788641E85E0DE77097E1DB049F1");

    srand(time(NULL));
    uint64_t rd;
    for(int i = 0; i < 8; i++){
        rd = (rd << 8) | (rand() & 0xFF);
    }
    big_int* T0 = new big_int(rd);
    uint32_t buf = 0;
    uint32_t* arrInt = new uint32_t [65536];
    big_int* mu = p->getMu();

   for (int i = 0; i < length/32; i++)
   {
       for (int j = 0; j < 32; j++)
       {
            big_int* T1 = new big_int(a);
            T1 -> powMod(T0, p, mu);
            buf = (buf << 1) | T1->few(q);
            delete T0;
            T0 = T1;
       }
       arrInt[i] = buf;
       if (i % 655 == 0) cout << ".";
   }

   return arrInt;
}

uint32_t* generateBM_bytes(){
    big_int* p = new big_int("CEA42B987C44FA642D80AD9F51F10457690DEF10C83D0BC1BCEE12FC3B6093E3");
    big_int* a = new big_int("5B88C41246790891C095E2878880342E88C79974303BD0400B090FE38A688356");
    big_int* q = new big_int("675215CC3E227D3216C056CFA8F8822BB486F788641E85E0DE77097E1DB049F1");

    srand(time(NULL));
    uint64_t rd;
    for(int i = 0; i < 8; i++){
        rd = (rd << 8) | (rand() & 0xFF);
    }
    big_int* T0 = new big_int(rd);
    uint32_t buf = 0;
    uint32_t* arrInt = new uint32_t [65536];
    big_int* mu = p->getMu();

    big_int* pMinusOne = new big_int(p);
    pMinusOne->sub(1);
    pMinusOne->shl(8);
    big_int** arrBytes = new big_int* [256];
    arrBytes[0] = new big_int ((uint64_t)0);
    for(int i = 1; i < 256; i++){
        arrBytes[i] = new big_int (pMinusOne);
        arrBytes[i]->mul(new big_int ((uint64_t)i));
    }

    for (int i = 0; i < 65536; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            big_int* T1 = new big_int(a);
            T1 -> powMod(T0, p, mu);
            delete T0;
            T0 = T1;
            int k = 0;
            while (T0->few(arrBytes[k]) && !T0->few(arrBytes[k + 1])){
                k++;
            }
            buf = (buf << 8) | k;
        }
        arrInt[i] = buf;
        if (i % 655 == 0) cout << ".";
    }
    return arrInt;
}

uint32_t* generateBBS()
{
    big_int* n = new big_int("D5BBB96D30086EC484EBA3D7F9CAEB07");
    big_int* q = new big_int("425D2B9BFDB25B9CF6C416CC6E37B59C1F");
    n->mul(q);
    big_int* zero = new big_int((uint64_t) 0);
    srand(time(NULL));
    uint64_t buf;

    while (buf == 0 || buf == 1){
        for (int i = 0; i < 8; i++){
            buf = (buf << 8) | (rand() & 0xFF);
        }
    }

    uint32_t* arrInt = new uint32_t[65536];
    big_int* r0 = new big_int(buf);
    big_int* mu = n->getMu();
    for (int i = 0 ; i < 65536; i++)
    {
        arrInt[i] = 0;
        for(int j = 0; j < 32; j++){
            big_int* r1 = new big_int(r0);
            r1->mulMod(r0, n, mu);
            arrInt[i] = (arrInt[i] << 1) | (r1->getByte() & 1);
            delete r0;
            r0 = r1;
        }
    }

    return arrInt;
}

uint32_t* generateBBS_bytes()
{
    big_int* n = new big_int("D5BBB96D30086EC484EBA3D7F9CAEB07");
    big_int* q = new big_int("425D2B9BFDB25B9CF6C416CC6E37B59C1F");
    n->mul(q);
    big_int* zero = new big_int((uint64_t) 0);
    srand(time(NULL));
    uint64_t buf;

    while (buf == 0 || buf == 1){
        for (int i = 0; i < 8; i++){
            buf = (buf << 8) | (rand() & 0xFF);
        }
    }

    uint32_t* arrInt = new uint32_t[65536];
    big_int* r0 = new big_int(buf);
    big_int* mu = n->getMu();
    for (int i = 0 ; i < 65536; i++)
    {
        arrInt[i] = 0;
        for(int j = 0; j < 4; j++){
            big_int* r1 = new big_int(r0);
            r1->mulMod(r0, n, mu);
            arrInt[i] = (arrInt[i] << 8) | (r1->getByte());
            delete r0;
            r0 = r1;
        }
    }

    return arrInt;
}

bool testSimProb(uint32_t * masInt, double alpha)
{
    double z;

    switch((int)(alpha*100))
    {
    case 1:
        z = 307.618808424;
        break;
    case 5:
        z = 292.149330411;
        break;
    case 10: z = 281.648151906;
        break;
    default:
        cout << "тщ";
        return false;
    }

    uint32_t* arrNumBytes = new uint32_t [256];
    for (int i = 0 ; i < 256; i++){
        arrNumBytes[i] = 0;
    }

    for (int i = 0 ; i < 65536; i++){
        for (int j = 0 ; j < 4; j++){
            arrNumBytes[(masInt[i] >> (8*j)) & 0xFF]++;
        }
    }
    //    cout << " arrnumbytes: ";
    //     for (int i = 0 ; i < 256; i++) cout << arrNumBytes[i] << " ";
    //     cout << endl << endl << endl;;

    double hiquad = 0;

    for (int i = 0; i < 256; i++){
        hiquad += (arrNumBytes[i] - 1024)*(arrNumBytes[i] - 1024)/1024;
    }
    cout << "hiquad: " << hiquad << " z: " << z << endl;
    return (hiquad <= z);
}

bool testIndepend(uint32_t* masInt, double alpha){
    uint32_t* arrVAl = new uint32_t [65536];
    uint32_t* arrV = new uint32_t[256];
    uint32_t* arrAl = new uint32_t[256];

    for (int i = 0 ; i < 256; i++){
        arrV[i] = 0;
        arrAl[i] = 0;
    }

    for (int i = 0 ; i < 65536; i++){
        arrVAl[i] = 0;
    }

    for (int i = 0; i < 65536; i++){
        for (int j = 0; j < 2; j++){
            arrV[(masInt[i] >> (16*j + 8)) & 0xFF]++;
            arrAl[(masInt[i] >> (16*j)) & 0xFF]++;
            arrVAl[(masInt[i] >> (16*j)) & 0xFFFF]++;
        }
    }

    //    for (int i = 0 ; i < 256; i++){
    //        for (int j = 0; j < 256; j++){
    //            cout << arrVAl[i + j*256] << " ";
    //        }
    //        cout << endl;

    //    }
    //    for (int i = 0; i < 256; i++){
    //        cout <<" arrV[" << i << "] = " << arrV[i] << " arrAl[" << i << "] = " << arrAl[i] << endl;
    //    }


    float hiquad = 0;
    for (int i = 0; i < 256; i++){
        for (int j = 0; j < 256; j++){
            if(arrVAl[i*256 + j] != 0){
                hiquad += (((((float)arrVAl[i*256 + j])*(float)arrVAl[i*256 + j]) / ((float)arrV[i] * (float)arrAl[j])));
                //                cout << hiquad << " ";
            }
        }
    }

    double z;
    switch((uint32_t)(alpha*100))
    {
    case 1:
        z = 65683.93;
        break;
    case 5:
        z = 65618.17;
        break;
    case 10:
        z = 65487.15;
        break;
    default:
        cout << "тщ";
        return false;
    }
    hiquad -=1;
    //    cout << endl << "hiquad: " << hiquad << endl;
    cout << "hiquad: " << hiquad*131072 << " z: " << z << endl;

    return (hiquad*131072 <= z);
}

bool testUniform(uint32_t *masInt, double alpha){

    double z;
    switch((uint32_t)(alpha*100))
    {
    case 1:
        z = 4027.91713;
        break;
    case 5:
        z = 3951.8232;
        break;
    case 10:
        z = 3928.20785;
        break;
    default:
        cout << "тщ";
        return false;
    }

    uint32_t** arrV = new uint32_t*[16];
    for (int i = 0; i < 16; i++){
        arrV[i] = new uint32_t[256];
        for(int j = 0; j < 256; j++){
            arrV[i][j] = 0;
        }
    }


    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 4096; j++){
            for (int k = 0; k < 4; k++){
                arrV[i][(masInt[j + i*4096] >> (8*k)) & 0xFF]++;
            }
        }
    }

    uint32_t* arrVAll = new uint32_t[256];
    for (int i = 0; i < 256; i++){
        arrVAll[i] = 0;
        for(int j = 0; j < 16; j++){
            arrVAll[i] += arrV[j][i];
        }
        arrVAll[i] *= 16384;
    }

    float hiquad = 0;
    for(int i = 0; i < 256; i++){
        for(int j = 0; j < 16; j++){
            if (arrV[j][i] != 0 ){
                hiquad += ((float)arrV[j][i]*(float)arrV[j][i])/((float)arrVAll[i]);
            }
        }
    }

    hiquad -= 1;
    cout << "hiquad: " << hiquad*262144 << " z: " << z << endl;
    return (hiquad*262144 <= z);
}
