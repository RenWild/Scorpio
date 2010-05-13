#include "scorpio.h"

/*
 *Copyright (C) 2007 Pradyumna Kannan.
 *
 This code is directly copied from Pradu's sample code with no
 modifications whatsoever. Thanks Pradu.
*/
const unsigned int magicmoves_r_shift[64] = {
	52, 53, 53, 53, 53, 53, 53, 52,
	53, 54, 54, 54, 54, 54, 54, 53,
	53, 54, 54, 54, 54, 54, 54, 53,
	53, 54, 54, 54, 54, 54, 54, 53,
	53, 54, 54, 54, 54, 54, 54, 53,
	53, 54, 54, 54, 54, 54, 54, 53,
	53, 54, 54, 54, 54, 54, 54, 53,
	53, 54, 54, 53, 53, 53, 53, 53
};
const BITBOARD magicmoves_r_magics[64] = {
	UINT64(0x0080001020400080), UINT64(0x0040001000200040), UINT64(0x0080081000200080), UINT64(0x0080040800100080),
	UINT64(0x0080020400080080), UINT64(0x0080010200040080), UINT64(0x0080008001000200), UINT64(0x0080002040800100),
	UINT64(0x0000800020400080), UINT64(0x0000400020005000), UINT64(0x0000801000200080), UINT64(0x0000800800100080),
	UINT64(0x0000800400080080), UINT64(0x0000800200040080), UINT64(0x0000800100020080), UINT64(0x0000800040800100),
	UINT64(0x0000208000400080), UINT64(0x0000404000201000), UINT64(0x0000808010002000), UINT64(0x0000808008001000),
	UINT64(0x0000808004000800), UINT64(0x0000808002000400), UINT64(0x0000010100020004), UINT64(0x0000020000408104),
	UINT64(0x0000208080004000), UINT64(0x0000200040005000), UINT64(0x0000100080200080), UINT64(0x0000080080100080),
	UINT64(0x0000040080080080), UINT64(0x0000020080040080), UINT64(0x0000010080800200), UINT64(0x0000800080004100),
	UINT64(0x0000204000800080), UINT64(0x0000200040401000), UINT64(0x0000100080802000), UINT64(0x0000080080801000),
	UINT64(0x0000040080800800), UINT64(0x0000020080800400), UINT64(0x0000020001010004), UINT64(0x0000800040800100),
	UINT64(0x0000204000808000), UINT64(0x0000200040008080), UINT64(0x0000100020008080), UINT64(0x0000080010008080),
	UINT64(0x0000040008008080), UINT64(0x0000020004008080), UINT64(0x0000010002008080), UINT64(0x0000004081020004),
	UINT64(0x0000204000800080), UINT64(0x0000200040008080), UINT64(0x0000100020008080), UINT64(0x0000080010008080),
	UINT64(0x0000040008008080), UINT64(0x0000020004008080), UINT64(0x0000800100020080), UINT64(0x0000800041000080),
	UINT64(0x00FFFCDDFCED714A), UINT64(0x007FFCDDFCED714A), UINT64(0x003FFFCDFFD88096), UINT64(0x0000040810002101),
	UINT64(0x0001000204080011), UINT64(0x0001000204000801), UINT64(0x0001000082000401), UINT64(0x0001FFFAABFAD1A2)
};
const BITBOARD magicmoves_r_mask[64] = {	
	UINT64(0x000101010101017E), UINT64(0x000202020202027C), UINT64(0x000404040404047A), UINT64(0x0008080808080876),
	UINT64(0x001010101010106E), UINT64(0x002020202020205E), UINT64(0x004040404040403E), UINT64(0x008080808080807E),
	UINT64(0x0001010101017E00), UINT64(0x0002020202027C00), UINT64(0x0004040404047A00), UINT64(0x0008080808087600),
	UINT64(0x0010101010106E00), UINT64(0x0020202020205E00), UINT64(0x0040404040403E00), UINT64(0x0080808080807E00),
	UINT64(0x00010101017E0100), UINT64(0x00020202027C0200), UINT64(0x00040404047A0400), UINT64(0x0008080808760800),
	UINT64(0x00101010106E1000), UINT64(0x00202020205E2000), UINT64(0x00404040403E4000), UINT64(0x00808080807E8000),
	UINT64(0x000101017E010100), UINT64(0x000202027C020200), UINT64(0x000404047A040400), UINT64(0x0008080876080800),
	UINT64(0x001010106E101000), UINT64(0x002020205E202000), UINT64(0x004040403E404000), UINT64(0x008080807E808000),
	UINT64(0x0001017E01010100), UINT64(0x0002027C02020200), UINT64(0x0004047A04040400), UINT64(0x0008087608080800),
	UINT64(0x0010106E10101000), UINT64(0x0020205E20202000), UINT64(0x0040403E40404000), UINT64(0x0080807E80808000),
	UINT64(0x00017E0101010100), UINT64(0x00027C0202020200), UINT64(0x00047A0404040400), UINT64(0x0008760808080800),
	UINT64(0x00106E1010101000), UINT64(0x00205E2020202000), UINT64(0x00403E4040404000), UINT64(0x00807E8080808000),
	UINT64(0x007E010101010100), UINT64(0x007C020202020200), UINT64(0x007A040404040400), UINT64(0x0076080808080800),
	UINT64(0x006E101010101000), UINT64(0x005E202020202000), UINT64(0x003E404040404000), UINT64(0x007E808080808000),
	UINT64(0x7E01010101010100), UINT64(0x7C02020202020200), UINT64(0x7A04040404040400), UINT64(0x7608080808080800),
	UINT64(0x6E10101010101000), UINT64(0x5E20202020202000), UINT64(0x3E40404040404000), UINT64(0x7E80808080808000)
};
const unsigned int magicmoves_b_shift[64] = {
	58, 59, 59, 59, 59, 59, 59, 58,
	59, 59, 59, 59, 59, 59, 59, 59,
	59, 59, 57, 57, 57, 57, 59, 59,
	59, 59, 57, 55, 55, 57, 59, 59,
	59, 59, 57, 55, 55, 57, 59, 59,
	59, 59, 57, 57, 57, 57, 59, 59,
	59, 59, 59, 59, 59, 59, 59, 59,
	58, 59, 59, 59, 59, 59, 59, 58
};

const BITBOARD magicmoves_b_magics[64] = {
	UINT64(0x0002020202020200), UINT64(0x0002020202020000), UINT64(0x0004010202000000), UINT64(0x0004040080000000),
	UINT64(0x0001104000000000), UINT64(0x0000821040000000), UINT64(0x0000410410400000), UINT64(0x0000104104104000),
	UINT64(0x0000040404040400), UINT64(0x0000020202020200), UINT64(0x0000040102020000), UINT64(0x0000040400800000),
	UINT64(0x0000011040000000), UINT64(0x0000008210400000), UINT64(0x0000004104104000), UINT64(0x0000002082082000),
	UINT64(0x0004000808080800), UINT64(0x0002000404040400), UINT64(0x0001000202020200), UINT64(0x0000800802004000),
	UINT64(0x0000800400A00000), UINT64(0x0000200100884000), UINT64(0x0000400082082000), UINT64(0x0000200041041000),
	UINT64(0x0002080010101000), UINT64(0x0001040008080800), UINT64(0x0000208004010400), UINT64(0x0000404004010200),
	UINT64(0x0000840000802000), UINT64(0x0000404002011000), UINT64(0x0000808001041000), UINT64(0x0000404000820800),
	UINT64(0x0001041000202000), UINT64(0x0000820800101000), UINT64(0x0000104400080800), UINT64(0x0000020080080080),
	UINT64(0x0000404040040100), UINT64(0x0000808100020100), UINT64(0x0001010100020800), UINT64(0x0000808080010400),
	UINT64(0x0000820820004000), UINT64(0x0000410410002000), UINT64(0x0000082088001000), UINT64(0x0000002011000800),
	UINT64(0x0000080100400400), UINT64(0x0001010101000200), UINT64(0x0002020202000400), UINT64(0x0001010101000200),
	UINT64(0x0000410410400000), UINT64(0x0000208208200000), UINT64(0x0000002084100000), UINT64(0x0000000020880000),
	UINT64(0x0000001002020000), UINT64(0x0000040408020000), UINT64(0x0004040404040000), UINT64(0x0002020202020000),
	UINT64(0x0000104104104000), UINT64(0x0000002082082000), UINT64(0x0000000020841000), UINT64(0x0000000000208800),
	UINT64(0x0000000010020200), UINT64(0x0000000404080200), UINT64(0x0000040404040400), UINT64(0x0002020202020200)
};
const BITBOARD magicmoves_b_mask[64] = {
	UINT64(0x0040201008040200), UINT64(0x0000402010080400), UINT64(0x0000004020100A00), UINT64(0x0000000040221400),
	UINT64(0x0000000002442800), UINT64(0x0000000204085000), UINT64(0x0000020408102000), UINT64(0x0002040810204000),
	UINT64(0x0020100804020000), UINT64(0x0040201008040000), UINT64(0x00004020100A0000), UINT64(0x0000004022140000),
	UINT64(0x0000000244280000), UINT64(0x0000020408500000), UINT64(0x0002040810200000), UINT64(0x0004081020400000),
	UINT64(0x0010080402000200), UINT64(0x0020100804000400), UINT64(0x004020100A000A00), UINT64(0x0000402214001400),
	UINT64(0x0000024428002800), UINT64(0x0002040850005000), UINT64(0x0004081020002000), UINT64(0x0008102040004000),
	UINT64(0x0008040200020400), UINT64(0x0010080400040800), UINT64(0x0020100A000A1000), UINT64(0x0040221400142200),
	UINT64(0x0002442800284400), UINT64(0x0004085000500800), UINT64(0x0008102000201000), UINT64(0x0010204000402000),
	UINT64(0x0004020002040800), UINT64(0x0008040004081000), UINT64(0x00100A000A102000), UINT64(0x0022140014224000),
	UINT64(0x0044280028440200), UINT64(0x0008500050080400), UINT64(0x0010200020100800), UINT64(0x0020400040201000),
	UINT64(0x0002000204081000), UINT64(0x0004000408102000), UINT64(0x000A000A10204000), UINT64(0x0014001422400000),
	UINT64(0x0028002844020000), UINT64(0x0050005008040200), UINT64(0x0020002010080400), UINT64(0x0040004020100800),
	UINT64(0x0000020408102000), UINT64(0x0000040810204000), UINT64(0x00000A1020400000), UINT64(0x0000142240000000),
	UINT64(0x0000284402000000), UINT64(0x0000500804020000), UINT64(0x0000201008040200), UINT64(0x0000402010080400),
	UINT64(0x0002040810204000), UINT64(0x0004081020400000), UINT64(0x000A102040000000), UINT64(0x0014224000000000),
	UINT64(0x0028440200000000), UINT64(0x0050080402000000), UINT64(0x0020100804020000), UINT64(0x0040201008040200)
};

BITBOARD magicmovesbdb[5248];
const BITBOARD* magicmoves_b_indices[64] = {
	magicmovesbdb+4992, magicmovesbdb+2624,  magicmovesbdb+256,  magicmovesbdb+896,
	magicmovesbdb+1280, magicmovesbdb+1664, magicmovesbdb+4800, magicmovesbdb+5120,
	magicmovesbdb+2560, magicmovesbdb+2656,  magicmovesbdb+288,  magicmovesbdb+928,
	magicmovesbdb+1312, magicmovesbdb+1696, magicmovesbdb+4832, magicmovesbdb+4928,
	magicmovesbdb+0,     magicmovesbdb+128,  magicmovesbdb+320,  magicmovesbdb+960,
	magicmovesbdb+1344, magicmovesbdb+1728, magicmovesbdb+2304, magicmovesbdb+2432,
	magicmovesbdb+32,    magicmovesbdb+160,  magicmovesbdb+448, magicmovesbdb+2752,
	magicmovesbdb+3776, magicmovesbdb+1856, magicmovesbdb+2336, magicmovesbdb+2464,
	magicmovesbdb+64,    magicmovesbdb+192,  magicmovesbdb+576, magicmovesbdb+3264,
	magicmovesbdb+4288, magicmovesbdb+1984, magicmovesbdb+2368, magicmovesbdb+2496,
	magicmovesbdb+96,    magicmovesbdb+224,  magicmovesbdb+704, magicmovesbdb+1088,
	magicmovesbdb+1472, magicmovesbdb+2112, magicmovesbdb+2400, magicmovesbdb+2528,
	magicmovesbdb+2592, magicmovesbdb+2688,  magicmovesbdb+832, magicmovesbdb+1216,
	magicmovesbdb+1600, magicmovesbdb+2240, magicmovesbdb+4864, magicmovesbdb+4960,
	magicmovesbdb+5056, magicmovesbdb+2720,  magicmovesbdb+864, magicmovesbdb+1248,
	magicmovesbdb+1632, magicmovesbdb+2272, magicmovesbdb+4896, magicmovesbdb+5184
};

BITBOARD magicmovesrdb[102400];
const BITBOARD* magicmoves_r_indices[64] = {
	magicmovesrdb+86016, magicmovesrdb+73728, magicmovesrdb+36864, magicmovesrdb+43008,
	magicmovesrdb+47104, magicmovesrdb+51200, magicmovesrdb+77824, magicmovesrdb+94208,
	magicmovesrdb+69632, magicmovesrdb+32768, magicmovesrdb+38912, magicmovesrdb+10240,
	magicmovesrdb+14336, magicmovesrdb+53248, magicmovesrdb+57344, magicmovesrdb+81920,
	magicmovesrdb+24576, magicmovesrdb+33792,  magicmovesrdb+6144, magicmovesrdb+11264,
	magicmovesrdb+15360, magicmovesrdb+18432, magicmovesrdb+58368, magicmovesrdb+61440,
	magicmovesrdb+26624,  magicmovesrdb+4096,  magicmovesrdb+7168,     magicmovesrdb+0,
	 magicmovesrdb+2048, magicmovesrdb+19456, magicmovesrdb+22528, magicmovesrdb+63488,
	magicmovesrdb+28672,  magicmovesrdb+5120,  magicmovesrdb+8192,  magicmovesrdb+1024,
	 magicmovesrdb+3072, magicmovesrdb+20480, magicmovesrdb+23552, magicmovesrdb+65536,
	magicmovesrdb+30720, magicmovesrdb+34816,  magicmovesrdb+9216, magicmovesrdb+12288,
	magicmovesrdb+16384, magicmovesrdb+21504, magicmovesrdb+59392, magicmovesrdb+67584,
	magicmovesrdb+71680, magicmovesrdb+35840, magicmovesrdb+39936, magicmovesrdb+13312,
	magicmovesrdb+17408, magicmovesrdb+54272, magicmovesrdb+60416, magicmovesrdb+83968,
	magicmovesrdb+90112, magicmovesrdb+75776, magicmovesrdb+40960, magicmovesrdb+45056,
	magicmovesrdb+49152, magicmovesrdb+55296, magicmovesrdb+79872, magicmovesrdb+98304
};
BITBOARD initmagicmoves_occ(const int* squares, const int numSquares, const BITBOARD linocc) {
	int i;
	BITBOARD ret=0;
	for(i=0;i<numSquares;i++)
		if(linocc&(((BITBOARD)(1))<<i)) ret|=(((BITBOARD)(1))<<squares[i]);
	return ret;
}

BITBOARD initmagicmoves_Rmoves(const int square, const BITBOARD occ) {
	BITBOARD ret=0;
	BITBOARD bit;
	BITBOARD rowbits=(((BITBOARD)0xFF)<<(8*(square/8)));
	
	bit=(((BITBOARD)(1))<<square);
	do {
		bit<<=8;
		ret|=bit;
	}while(bit && !(bit&occ));
	bit=(((BITBOARD)(1))<<square);
	do {
		bit>>=8;
		ret|=bit;
	}while(bit && !(bit&occ));
	bit=(((BITBOARD)(1))<<square);
	do {
		bit<<=1;
		if(bit&rowbits) ret|=bit;
		else break;
	}while(!(bit&occ));
	bit=(((BITBOARD)(1))<<square);
	do {
		bit>>=1;
		if(bit&rowbits) ret|=bit;
		else break;
	}while(!(bit&occ));
	return ret;
}
BITBOARD initmagicmoves_Bmoves(const int square, const BITBOARD occ) {
	BITBOARD ret=0;
	BITBOARD bit;
	BITBOARD bit2;
	BITBOARD rowbits=(((BITBOARD)0xFF)<<(8*(square/8)));
	
	bit=(((BITBOARD)(1))<<square);
	bit2=bit;
	do {
		bit<<=8-1;
		bit2>>=1;
		if(bit2&rowbits) ret|=bit;
		else break;
	}while(bit && !(bit&occ));
	bit=(((BITBOARD)(1))<<square);
	bit2=bit;
	do {
		bit<<=8+1;
		bit2<<=1;
		if(bit2&rowbits) ret|=bit;
		else break;
	}while(bit && !(bit&occ));
	bit=(((BITBOARD)(1))<<square);
	bit2=bit;
	do {
		bit>>=8-1;
		bit2<<=1;
		if(bit2&rowbits) ret|=bit;
		else break;
	}while(bit && !(bit&occ));
	bit=(((BITBOARD)(1))<<square);
	bit2=bit;
	do {
		bit>>=8+1;
		bit2>>=1;
		if(bit2&rowbits) ret|=bit;
		else break;
	}while(bit && !(bit&occ));
	return ret;
}

#define BmagicNOMASK2(square, occupancy) *(magicmoves_b_indices2[square]+(((occupancy)*magicmoves_b_magics[square])>>magicmoves_b_shift[square]))
#define RmagicNOMASK2(square, occupancy) *(magicmoves_r_indices2[square]+(((occupancy)*magicmoves_r_magics[square])>>magicmoves_r_shift[square]))

void initmagicmoves(void) {
	int i,j;

	int initmagicmoves_bitpos64_database[64] = {
		63,  0, 58,  1, 59, 47, 53,  2,
		60, 39, 48, 27, 54, 33, 42,  3,
		61, 51, 37, 40, 49, 18, 28, 20,
		55, 30, 34, 11, 43, 14, 22,  4,
		62, 57, 46, 52, 38, 26, 32, 41,
		50, 36, 17, 19, 29, 10, 13, 21,
		56, 45, 25, 31, 35, 16,  9, 12,
		44, 24, 15,  8, 23,  7,  6,  5
	};

	BITBOARD* magicmoves_b_indices2[64] = {
		magicmovesbdb+4992, magicmovesbdb+2624,  magicmovesbdb+256,  magicmovesbdb+896,
		magicmovesbdb+1280, magicmovesbdb+1664, magicmovesbdb+4800, magicmovesbdb+5120,
		magicmovesbdb+2560, magicmovesbdb+2656,  magicmovesbdb+288,  magicmovesbdb+928,
		magicmovesbdb+1312, magicmovesbdb+1696, magicmovesbdb+4832, magicmovesbdb+4928,
		magicmovesbdb+0,     magicmovesbdb+128,  magicmovesbdb+320,  magicmovesbdb+960,
		magicmovesbdb+1344, magicmovesbdb+1728, magicmovesbdb+2304, magicmovesbdb+2432,
		magicmovesbdb+32,    magicmovesbdb+160,  magicmovesbdb+448, magicmovesbdb+2752,
		magicmovesbdb+3776, magicmovesbdb+1856, magicmovesbdb+2336, magicmovesbdb+2464,
		magicmovesbdb+64,    magicmovesbdb+192,  magicmovesbdb+576, magicmovesbdb+3264,
		magicmovesbdb+4288, magicmovesbdb+1984, magicmovesbdb+2368, magicmovesbdb+2496,
		magicmovesbdb+96,    magicmovesbdb+224,  magicmovesbdb+704, magicmovesbdb+1088,
		magicmovesbdb+1472, magicmovesbdb+2112, magicmovesbdb+2400, magicmovesbdb+2528,
		magicmovesbdb+2592, magicmovesbdb+2688,  magicmovesbdb+832, magicmovesbdb+1216,
		magicmovesbdb+1600, magicmovesbdb+2240, magicmovesbdb+4864, magicmovesbdb+4960,
		magicmovesbdb+5056, magicmovesbdb+2720,  magicmovesbdb+864, magicmovesbdb+1248,
		magicmovesbdb+1632, magicmovesbdb+2272, magicmovesbdb+4896, magicmovesbdb+5184
	};
	BITBOARD* magicmoves_r_indices2[64] = {
		magicmovesrdb+86016, magicmovesrdb+73728, magicmovesrdb+36864, magicmovesrdb+43008,
		magicmovesrdb+47104, magicmovesrdb+51200, magicmovesrdb+77824, magicmovesrdb+94208,
		magicmovesrdb+69632, magicmovesrdb+32768, magicmovesrdb+38912, magicmovesrdb+10240,
		magicmovesrdb+14336, magicmovesrdb+53248, magicmovesrdb+57344, magicmovesrdb+81920,
		magicmovesrdb+24576, magicmovesrdb+33792,  magicmovesrdb+6144, magicmovesrdb+11264,
		magicmovesrdb+15360, magicmovesrdb+18432, magicmovesrdb+58368, magicmovesrdb+61440,
		magicmovesrdb+26624,  magicmovesrdb+4096,  magicmovesrdb+7168,     magicmovesrdb+0,
		magicmovesrdb+2048,  magicmovesrdb+19456, magicmovesrdb+22528, magicmovesrdb+63488,
		magicmovesrdb+28672,  magicmovesrdb+5120,  magicmovesrdb+8192,  magicmovesrdb+1024,
		magicmovesrdb+3072,  magicmovesrdb+20480, magicmovesrdb+23552, magicmovesrdb+65536,
		magicmovesrdb+30720, magicmovesrdb+34816,  magicmovesrdb+9216, magicmovesrdb+12288,
		magicmovesrdb+16384, magicmovesrdb+21504, magicmovesrdb+59392, magicmovesrdb+67584,
		magicmovesrdb+71680, magicmovesrdb+35840, magicmovesrdb+39936, magicmovesrdb+13312,
		magicmovesrdb+17408, magicmovesrdb+54272, magicmovesrdb+60416, magicmovesrdb+83968,
		magicmovesrdb+90112, magicmovesrdb+75776, magicmovesrdb+40960, magicmovesrdb+45056,
		magicmovesrdb+49152, magicmovesrdb+55296, magicmovesrdb+79872, magicmovesrdb+98304
	};
#ifdef _MSC_VER
#pragma warning (disable: 4146)
#endif
	for(i=0;i<64;i++) {
		int squares[64];
		int numsquares=0;
		BITBOARD temp=magicmoves_b_mask[i];
		while(temp) {
			BITBOARD bit=temp&-temp;
			squares[numsquares++]=initmagicmoves_bitpos64_database[(bit*UINT64(0x07EDD5E59A4E28C2))>>58];
			temp^=bit;
		}
		for(temp=0;temp<(((BITBOARD)(1))<<numsquares);temp++) {
			BITBOARD tempocc=initmagicmoves_occ(squares,numsquares,temp);
			BmagicNOMASK2(i,tempocc)=initmagicmoves_Bmoves(i,tempocc);
		
		}
	}
	for(i=0;i<64;i++) {
		int squares[64];
		int numsquares=0;
		BITBOARD temp=magicmoves_r_mask[i];
		while(temp) {
			BITBOARD bit=temp&-temp;
			squares[numsquares++]=initmagicmoves_bitpos64_database[(bit*UINT64(0x07EDD5E59A4E28C2))>>58];
			temp^=bit;
		}
		for(temp=0;temp<(((BITBOARD)(1))<<numsquares);temp++) {
			BITBOARD tempocc=initmagicmoves_occ(squares,numsquares,temp);
			RmagicNOMASK2(i,tempocc)=initmagicmoves_Rmoves(i,tempocc);
		}
	}
#ifdef _MSC_VER
#pragma warning (default: 4146)
#endif
	/*
	initialize other bitboards
	*/
	int step,from,to;
	for(i = 0;i < 8;i++) {
		for(j = 0;j < 8;j++) {
			__unit_bb[SQ(i,j)] = (((BITBOARD)1) << SQ64(i,j));
		}
	}
	for(i = 0;i < 64;i++) {
		for(j = 0;j < 64;j++) {
			in_between[i][j] = 0;
			from = SQ6488(i);
			to = SQ6488(j);
			step = sqatt[to - from].step;
			if(step) {
				from += step;
				while(from != to) {
					in_between[i][j] |= __unit_bb[from];
					from += step;
				};
			}
		}
	}
}

BITBOARD __unit_bb[0x80];
BITBOARD in_between[64][64];

const BITBOARD knight_magics[64] = {
		UINT64(0x0000000000020400),UINT64(0x0000000000050800),UINT64(0x00000000000a1100),UINT64(0x0000000000142200),
		UINT64(0x0000000000284400),UINT64(0x0000000000508800),UINT64(0x0000000000a01000),UINT64(0x0000000000402000),
		UINT64(0x0000000002040004),UINT64(0x0000000005080008),UINT64(0x000000000a110011),UINT64(0x0000000014220022),
		UINT64(0x0000000028440044),UINT64(0x0000000050880088),UINT64(0x00000000a0100010),UINT64(0x0000000040200020),
		UINT64(0x0000000204000402),UINT64(0x0000000508000805),UINT64(0x0000000a1100110a),UINT64(0x0000001422002214),
		UINT64(0x0000002844004428),UINT64(0x0000005088008850),UINT64(0x000000a0100010a0),UINT64(0x0000004020002040),
		UINT64(0x0000020400040200),UINT64(0x0000050800080500),UINT64(0x00000a1100110a00),UINT64(0x0000142200221400),
		UINT64(0x0000284400442800),UINT64(0x0000508800885000),UINT64(0x0000a0100010a000),UINT64(0x0000402000204000),
		UINT64(0x0002040004020000),UINT64(0x0005080008050000),UINT64(0x000a1100110a0000),UINT64(0x0014220022140000),
		UINT64(0x0028440044280000),UINT64(0x0050880088500000),UINT64(0x00a0100010a00000),UINT64(0x0040200020400000),
		UINT64(0x0204000402000000),UINT64(0x0508000805000000),UINT64(0x0a1100110a000000),UINT64(0x1422002214000000),
		UINT64(0x2844004428000000),UINT64(0x5088008850000000),UINT64(0xa0100010a0000000),UINT64(0x4020002040000000),
		UINT64(0x0400040200000000),UINT64(0x0800080500000000),UINT64(0x1100110a00000000),UINT64(0x2200221400000000),
		UINT64(0x4400442800000000),UINT64(0x8800885000000000),UINT64(0x100010a000000000),UINT64(0x2000204000000000),
		UINT64(0x0004020000000000),UINT64(0x0008050000000000),UINT64(0x00110a0000000000),UINT64(0x0022140000000000),
		UINT64(0x0044280000000000),UINT64(0x0088500000000000),UINT64(0x0010a00000000000),UINT64(0x0020400000000000)
};
const BITBOARD king_magics[64] = {
		UINT64(0x0000000000000302),UINT64(0x0000000000000705),UINT64(0x0000000000000e0a),UINT64(0x0000000000001c14),
		UINT64(0x0000000000003828),UINT64(0x0000000000007050),UINT64(0x000000000000e0a0),UINT64(0x000000000000c040),
		UINT64(0x0000000000030203),UINT64(0x0000000000070507),UINT64(0x00000000000e0a0e),UINT64(0x00000000001c141c),
		UINT64(0x0000000000382838),UINT64(0x0000000000705070),UINT64(0x0000000000e0a0e0),UINT64(0x0000000000c040c0),
		UINT64(0x0000000003020300),UINT64(0x0000000007050700),UINT64(0x000000000e0a0e00),UINT64(0x000000001c141c00),
		UINT64(0x0000000038283800),UINT64(0x0000000070507000),UINT64(0x00000000e0a0e000),UINT64(0x00000000c040c000),
		UINT64(0x0000000302030000),UINT64(0x0000000705070000),UINT64(0x0000000e0a0e0000),UINT64(0x0000001c141c0000),
		UINT64(0x0000003828380000),UINT64(0x0000007050700000),UINT64(0x000000e0a0e00000),UINT64(0x000000c040c00000),
		UINT64(0x0000030203000000),UINT64(0x0000070507000000),UINT64(0x00000e0a0e000000),UINT64(0x00001c141c000000),
		UINT64(0x0000382838000000),UINT64(0x0000705070000000),UINT64(0x0000e0a0e0000000),UINT64(0x0000c040c0000000),
		UINT64(0x0003020300000000),UINT64(0x0007050700000000),UINT64(0x000e0a0e00000000),UINT64(0x001c141c00000000),
		UINT64(0x0038283800000000),UINT64(0x0070507000000000),UINT64(0x00e0a0e000000000),UINT64(0x00c040c000000000),
		UINT64(0x0302030000000000),UINT64(0x0705070000000000),UINT64(0x0e0a0e0000000000),UINT64(0x1c141c0000000000),
		UINT64(0x3828380000000000),UINT64(0x7050700000000000),UINT64(0xe0a0e00000000000),UINT64(0xc040c00000000000),
		UINT64(0x0203000000000000),UINT64(0x0507000000000000),UINT64(0x0a0e000000000000),UINT64(0x141c000000000000),
		UINT64(0x2838000000000000),UINT64(0x5070000000000000),UINT64(0xa0e0000000000000),UINT64(0x40c0000000000000)
};
const BITBOARD rank_mask[8] = {
		UINT64(0x00000000000000ff),
		UINT64(0x000000000000ff00),
		UINT64(0x0000000000ff0000),
		UINT64(0x00000000ff000000),
		UINT64(0x000000ff00000000),
		UINT64(0x0000ff0000000000),
		UINT64(0x00ff000000000000),
		UINT64(0xff00000000000000)
};
const BITBOARD file_mask[8] = {
		UINT64(0x0101010101010101),
		UINT64(0x0202020202020202),
		UINT64(0x0404040404040404),
		UINT64(0x0808080808080808),
		UINT64(0x1010101010101010),
		UINT64(0x2020202020202020),
		UINT64(0x4040404040404040),
		UINT64(0x8080808080808080)
};
