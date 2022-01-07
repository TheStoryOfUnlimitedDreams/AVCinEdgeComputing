#include "stdio.h"

void ShowRights()
{
	const char* ShowRights[10];
	ShowRights[0] = "Local Voltage Control and Power Flow Optimization";
	ShowRights[1] = "Version 3.0";
	ShowRights[2] = "Copyright (C) all rights reserved by";
	ShowRights[3] = "TIANJIN UNIVERSITY, CHINA";

	printf("\n//=========================================================================//\n");
	printf("//%11s %s %11s//\n", " ", ShowRights[0], " ");
	printf("//%30s %s %30s//\n", " ", ShowRights[1], " ");
	printf("//%73s//\n", " ");
	printf("//%18s %s %17s//\n", " ", ShowRights[2], " ");
	printf("//%73s//\n", " ");
	printf("//%23s %s %23s//\n", " ", ShowRights[3], " ");
	printf("//%73s//\n", " ");
	printf("//=========================================================================//\n");
	printf("\n\n\n\n\n\n");
}