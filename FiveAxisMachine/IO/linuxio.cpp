#include "linuxio.h"
#include <iostream>
#include <QThread>
#if basesystem == 0
#include <sys/io.h>
#include <unistd.h>
#endif
#include <bitset>
#include <stdio.h>
#include <iomanip>
typedef boost::numeric::ublas::vector<double> bstvector;

#define address 0xd060   // Address for CNT Board
#define portDA 0xd040    // Address for DA Board

linuxio::linuxio()
{

}

bool linuxio::Init(){
#if basesystem == 0
    int adminIO;
    adminIO = iopl(3);//admin edit IO return0 success
    std::cout<<"adminIO  "<<adminIO<<std::endl;
//CNT INIT
    /*Initialize -------------------------------------------------------- */
    outw(0x0008, address+0x08);/* 動作モード設定 */
    outl(0x00000022, address+0x0c); /* 差動入力、CW=UP、2相入力、同期、4逓倍 */
    outw(0x0009, address+0x08);/* 動作モード設定 */
    outl(0x00000022, address+0x0c); /* 差動入力、CW=UP、2相入力、同期、4逓倍 */
    outw(0x000A, address+0x08);/* 動作モード設定 */
    outl(0x00000022, address+0x0c); /* 差動入力、CW=UP、2相入力、同期、4逓倍 */
    outw(0x000B, address+0x08);/* 動作モード設定 */
    outl(0x00000022, address+0x0c); /* 差動入力、CW=UP、2相入力、同期、4逓倍 */
    outw(0x000C, address+0x08);/* 動作モード設定 */
    outl(0x00000022, address+0x0c); /* 差動入力、CW=UP、2相入力、同期、4逓倍 */
    outw(0x000D, address+0x08);/* 動作モード設定 */
    outl(0x00000022, address+0x0c); /* 差動入力、CW=UP、2相入力、同期、4逓倍 */
    outw(0x000E, address+0x08);/* 動作モード設定 */
    outl(0x00000022, address+0x0c); /* 差動入力、CW=UP、2相入力、同期、4逓倍 */
    outw(0x000F, address+0x08);/* 動作モード設定 */
    outl(0x00000022, address+0x0c); /* 差動入力、CW=UP、2相入力、同期、4逓倍 */




    outw(0x0010, address+0x08);/* プリセットレジスタ設定 */
    outl(0x77359400, address+0x0c); // データ"00000000"設定2000000000
    outw(0x0011, address+0x08);/* プリセットレジスタ設定 */
    outl(0x77359400, address+0x0c); // データ"00000000"設定2000000000
    outw(0x0012, address+0x08);/* プリセットレジスタ設定 */
    outl(0x77359400, address+0x0c); // データ"00000000"設定2000000000
    outw(0x0013, address+0x08);/* プリセットレジスタ設定 */
    outl(0x77359400, address+0x0c); // データ"00000000"設定2000000000
    outw(0x0014, address+0x08);/* プリセットレジスタ設定 */
    outl(0x77359400, address+0x0c); // データ"00000000"設定2000000000
    outw(0x0015, address+0x08);/* プリセットレジスタ設定 */
    outl(0x77359400, address+0x0c); // データ"00000000"設定2000000000
    outw(0x0016, address+0x08);/* プリセットレジスタ設定 */
    outl(0x77359400, address+0x0c); // データ"00000000"設定2000000000
    outw(0x0017, address+0x08);/* プリセットレジスタ設定 */
    outl(0x77359400, address+0x0c); // データ"00000000"設定2000000000


    outw(0x0030, address+0x08);
    outl(0x00000001, address+0x0c); /* 無効 */
    outw(0x0031, address+0x08);
    outl(0x00000001, address+0x0c); /* 無効 */
    outw(0x0032, address+0x08);
    outl(0x00000001, address+0x0c); /* 無効 */
    outw(0x0033, address+0x08);
    outl(0x00000001, address+0x0c); /* 無効 */
    outw(0x0034, address+0x08);
    outl(0x00000001, address+0x0c); /* 無効 */
    outw(0x0035, address+0x08);
    outl(0x00000001, address+0x0c); /* 無効 */
    outw(0x0036, address+0x08);
    outl(0x00000001, address+0x0c); /* 無効 */
    outw(0x0037, address+0x08);
    outl(0x00000001, address+0x0c); /* 無効 */


    outw( 0x003c,address+0x08);/* プリセットデータロード */
    outl(0x000000ff, address+0x0c); /* 全チャネルロード */
    /* ----------- Counter Start ---------------------------------------------- */
    outw(0x00ff, address+0x04); /* Ch0のみスタート */  ///2 sinsuu de miro
//CNT INIT

//DA INIT
    outb(00,portDA + 0x08 );   //init device

    outb(01,portDA + 0x08);     //sampling
    outw(0x01,portDA + 0x0c);     //Synchronously output

    outb(002,portDA + 0x0008);     //range
    outb(0x80,portDA + 0x00c);     //range: target channel(ALL)
    outb(002,portDA + 0x00d);     //range All channel bipola 10V

//DA EXIT
#endif
    return 0;
}

bool linuxio::Exit(){
#if basesystem == 0
iopl(3);//admin edit IO return0 success
//DA  EXIT
    outb(00,portDA + 0x08);
//DA  EXIT

//CNC EXIT
    outw(0x0008, address+0x08);
//CNC EXIT
std::cout<<"exit"<<std::endl;
#endif
return 0;
}

bool linuxio::OutputDA(bstvector &DAdata){
 #if basesystem == 0
    unsigned short int voltage ;


    //0ch
    voltage = (DAdata[0]+10)*4096/20;
    outb(0000,portDA + 0x04);
    outw(voltage,portDA + 0x0000);//voltage set 16bit
    //1ch
    voltage = (DAdata[1]+10)*4096/20;
    outb(0001,portDA + 0x04);
    outw(voltage,portDA + 0x0000);//voltage set
    //2ch
    voltage = (DAdata[2]+10)*4096/20;
    outb(0002,portDA + 0x04);
    outw(voltage,portDA + 0x0000);//voltage set


    outb(0x0003,portDA + 0x008 );//multi out
    return 0;
#endif
    return 0;
}

bool linuxio::ReadCount(bstvector &CNTdata){
#if basesystem == 0
    unsigned int cntdata,stsdata;//8bit

    bstvector CNTdata2;

    outw(0x00ff, address+0x02); /* 全チャネルラッチ */

    outw(0x0000, address+0x00); /* チャネル0のカウント値読み出しを指定 */
    cntdata = inl(address+0x00); /* カウント値を読み出し(DWordアクセス以外不可)*/
    //if (cntdata > 2294967295.0)CNTdata[0]=cntdata- 4294967295.0;
    //else CNTdata[0] = cntdata;
    CNTdata[0]=(double)cntdata-2000000000;


    outw(0x0001, address+0x00); /* チャネル1のカウント値読み出しを指定 */
    cntdata = inl(address+0x00); /* カウント値を読み出し(DWordアクセス以外不可)*/
    //if (cntdata > 2294967295.0){CNTdata[1]=cntdata- 4294967295.0;std::cout<<"first";}
    //else {CNTdata[1] = cntdata;std::cout<<"second";}
    CNTdata[1]=(double)cntdata-2000000000;
    //std::cout.setf(std::ios_basesystem::scientific, std::ios_basesystem::floatfield);
    //std::cout<<std::setprecision(20)<<cntdata<<"      "<<CNTdata[1]<<"      ";


    outw(0x0002, address+0x00); /* チャネル1のカウント値読み出しを指定 */
    cntdata = inl(address+0x00); /* カウント値を読み出し(DWordアクセス以外不可)*/
    //if (cntdata > 2294967295.0)CNTdata[2]=cntdata- 4294967295.0;
    //else CNTdata[2] = cntdata;
    CNTdata[2]=(double)cntdata-2000000000;

    //printf("CountData StatusData"); /* カウント値、ステータス表示*/
    //printf("%08ld %02x \n", cntdata2, stsdata );
    //std::cout<<std::setprecision(9)<<CNTdata[0]<<"       "<<CNTdata[1]<<"       "<<CNTdata[2]<<std::endl;
#endif
    return 0;
}
