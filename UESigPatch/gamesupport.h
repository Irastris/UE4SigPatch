#pragma once

#include <string>
#include <windows.h>

const char* GetPatternFromExecutableName() {
	char buffer[MAX_PATH];

	GetModuleFileNameA(NULL, buffer, MAX_PATH);

	std::string path(buffer);

	size_t pos = path.find_last_of("/\\");
	if (pos != std::string::npos) {
		path = path.substr(pos + 1);
	}

	std::cout << "Executable name: " << path << std::endl;

	if (path == "Bramble_TMK-Win64-Shipping.exe") return		"48 83 EC 28 65 48 8B 04 25 58 00 00 00 8B 0D 15 D3 E2 03 BA 08 01 00 00";
	if (path == "BlueClient-Win64-Shipping.exe") return			"48 83 EC 28 65 48 8B 04 25 58 00 00 00 8B 0D 29 4C F6 08 BA 04 11 00 00";
	if (path == "b1-Win64-Shipping.exe") return					"48 83 EC 28 65 48 8B 04 25 58 00 00 00 8B 0D 45 CB 64 11 BA 1C 04 00 00";
	if (path == "CartOfGlory-Win64-Shipping.exe") return		"48 83 EC 28 65 48 8B 04 25 58 00 00 00 8B 0D 05 1C D7 03 BA 08 01 00 00";
	if (path == "darkhours-Win64-Shipping.exe") return			"48 83 EC 28 8B 0D 5A 17 DA 07 65 48 8B 04 25 58 00 00 00 BA EC 0E 00 00";
	if (path == "Genesis-Win64-Shipping.exe") return			"48 83 EC 28 65 48 8B 04 25 58 00 00 00 8B 0D FD E2 41 04 BA 08 01 00 00";
	if (path == "MK12.exe") return								"48 83 EC 28 65 48 8B 04 25 58 00 00 00 8B 0D C5 E4 70 05 BA 40 01 00 00";
	if (path == "ProjectBakery-Win64-Shipping.exe") return		"48 83 EC 28 65 48 8B 04 25 58 00 00 00 8B 0D 69 6C 7E 06 BA 6C 0E 00 00";
	if (path == "QuidditchChampions-Win64-Shipping.exe") return	"48 83 EC 28 65 48 8B 04 25 58 00 00 00 8B 0D 2D 71 E7 04 BA 58 01 00 00";
	if (path == "Sifu-Win64-Shipping.exe") return				"48 83 EC 28 65 48 8B 04 25 58 00 00 00 8B 0D A5 BE 08 04 BA 68 02 00 00";
	if (path == "SparkingZERO-Win64-Shipping.exe") return		"48 83 EC 28 65 48 8B 04 25 58 00 00 00 8B 0D 4D 06 EE 05 BA 0C 08 00 00";

	return NULL;
}