
#include "Holder.h"
#include "Connector.h"

#include <fstream>

static const unsigned int MIN_STEAM_ID = 0;
static const unsigned int MAX_STEAM_ID = 417100;
static const unsigned int STEAM_ID_INCREASE_INTERVAL = 10;
static const char* FILE_NAME = "Steam_Member_Result.txt";

#define LOG_IN_CONSOLE

static const SteamGameInfo* Parse(unsigned int id, const char* buffer, Holder& holder)
{
	SteamGameInfo game;
	game.ID = id;
	game.InGame = 0;
	game.InGroupChat = 0;
	game.Members = 0;
	game.Online = 0;
	memset(game.Name, 0, sizeof(game.Name));

	const char* title_start = strstr(buffer, "Steam Community :: ");
	const char* title_end = strstr(buffer, "Member List");
	if (title_start && title_end)
	{
		title_start += strlen("Steam Community :: ");
		title_end--;

		strncpy(game.Name, title_start, (size_t)(title_end - title_start));
	}
	else
	{
		return nullptr;
	}

	const char* pageLinks = strstr(buffer, "pageLinks");
	if (pageLinks == 0)
	{
	//	printf("Could not parse /1\n");
		return nullptr;
	}

	const char* members = strstr(pageLinks, "Members");
	if (members == 0)
	{
	//	printf("Could not parse /2\n");
		return nullptr;
	}

	while (*members == ' ')
		members--;

	const char* end = members;

	members--;

	while (*members == ' ')
		members--;

	while (isdigit(*members))
		members--;

	const char* start = members;

	char memberBuffer[256] = { 0 };
	strncpy_s(memberBuffer, start, (size_t)(end - start));

	game.Members = atoi(start);

	return holder.AddEntry(game);
}

int main()
{
	Connector connector;
	Holder holder;

	std::ofstream file;
	char buffer[1024] = { 0 };
	file.open(FILE_NAME, std::ios_base::app);
	if (!file.is_open())
	{
		printf("Could not open file at: %s\n", FILE_NAME);
	}

#if defined(LOG_IN_CONSOLE)
	printf("Started..\n");
#endif

	for (unsigned int i = MAX_STEAM_ID; i >= MIN_STEAM_ID; i -= STEAM_ID_INCREASE_INTERVAL)
	{
		if (!connector.RequestMembers(i))
			continue;

		const SteamGameInfo* info = Parse(i, connector.GetBuffer(), holder);
		if (!info)
			continue;

		file.open(FILE_NAME, std::ios_base::app);
		if (!file.is_open())
		{
			printf("Could not open file at: %s\n", FILE_NAME);
		}
		else
		{
			memset(buffer, 0, sizeof(buffer));
			sprintf(buffer, "%u \t\t, %s , %u\n", info->Members, info->Name, info->ID);
			file.write(buffer, strlen(buffer));
			file.close();
		}

#if defined(LOG_IN_CONSOLE)
		printf(buffer);
#endif
	}

#if defined(LOG_IN_CONSOLE)
	printf("Done!\n");
#endif 

	file.close();

	return 0;
}