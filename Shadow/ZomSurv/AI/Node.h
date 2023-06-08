#include "sdpch.h"
#pragma once

struct Node
{
	Node() { }
	Node(short id, const glm::vec2& position) : id(id), position(position) { }

	glm::vec2 position;
	short id;
};

//std::unordered_map<short, std::vector<short> > nodesPerRoomId;
//nodesPerRoomId[1] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//nodesPerRoomId[2] = { 10, 11, 12, 13 };
//nodesPerRoomId[3] = { 14, 15, 16, 17, 18, 19, 20, 21 };
//nodesPerRoomId[4] = { 22, 23, 24, 25, 26, 27, 28, 29 };
//nodesPerRoomId[5] = { 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 53, 54 };
//nodesPerRoomId[6] = { 45, 46, 47, 48, 49, 50 };
//nodesPerRoomId[7] = { 51, 52, 55 };
//nodesPerRoomId[8] = { 56, 57, 58, 59, 61 };
//
//std::unordered_map<short, std::vector<short> > nodeConnections;
//nodeConnections[1] = { 6, 5, 2, 7, 3 };
//nodeConnections[2] = { 4, 1, 5 };
//nodeConnections[3] = { 4, 5, 1, 6 };
//nodeConnections[4] = { 2, 3, 5 };
//nodeConnections[5] = { 1, 2, 3, 4, 9 };
//nodeConnections[6] = { 1, 3 };
//nodeConnections[7] = { 1, 8, 61 };
//nodeConnections[8] = { 7, 9 };
//nodeConnections[9] = { 5, 8, 10, 11 };
//nodeConnections[10] = { 9, 11, 12 };
//nodeConnections[11] = { 9, 10, 12, 13 };
//nodeConnections[12] = { 10, 11, 14, 13 };
//nodeConnections[13] = { 11, 12 };
//nodeConnections[14] = { 12, 15 };
//nodeConnections[15] = { 14, 16 };
//nodeConnections[16] = { 15, 17 };
//nodeConnections[17] = { 16, 18 };
//nodeConnections[18] = { 17, 19 };
//nodeConnections[19] = { 18, 20, 21 };
//nodeConnections[20] = { 19 };
//nodeConnections[21] = { 19, 22 };
//nodeConnections[22] = { 21, 23, 24 };
//nodeConnections[23] = { 22, 24, 25, 27 };
//nodeConnections[24] = { 22, 23, 26 };
//nodeConnections[25] = { 23, 27 };
//nodeConnections[26] = { 24, 28 };
//nodeConnections[27] = { 23, 25, 28 };
//nodeConnections[28] = { 26, 27, 29 };
//nodeConnections[29] = { 28, 30 };
//nodeConnections[30] = { 29, 31, 33, 34 };
//nodeConnections[31] = { 30, 32, 41, 34 };
//nodeConnections[32] = { 31, 33, 41 };
//nodeConnections[33] = { 30, 32, 34, 39 };
//nodeConnections[34] = { 30, 33, 31, 37, 54 };
//nodeConnections[35] = { 37, 36 };
//nodeConnections[36] = { 35, 37 };
//nodeConnections[37] = { 25, 26, 24, 38, 54 };
//nodeConnections[38] = { 37, 54, 39, 42, 43 };
//nodeConnections[39] = { 33, 38, 40 };
//nodeConnections[40] = { 39, 41, 44 };
//nodeConnections[41] = { 31, 32, 40, 44 };
//nodeConnections[42] = { 38, 43 };
//nodeConnections[43] = { 38, 42, 44 };
//nodeConnections[44] = { 40, 41, 43, 45 };
//nodeConnections[45] = { 44, 46 };
//nodeConnections[46] = { 45, 47 };
//nodeConnections[47] = { 46, 48 };
//nodeConnections[48] = { 47, 50, 49 };
//nodeConnections[49] = { 50, 48 };
//nodeConnections[50] = { 51, 53, 55 };
//nodeConnections[51] = { 41, 49, 48 };
//nodeConnections[52] = { 51, 53, 55 };
//nodeConnections[53] = { 52, 54 };
//nodeConnections[54] = { 37, 38, 34 };
//nodeConnections[55] = { 56, 52, 51 };
//nodeConnections[56] = { 55, 57, 60, 58 };
//nodeConnections[57] = { 56, 58, 60 };
//nodeConnections[58] = { 57, 61, 59 };
//nodeConnections[59] = { 58, 60, 61 };
//nodeConnections[60] = { 57, 59 };
//nodeConnections[61] = { 7, 58, 59 };

