#include "MiniginPCH.h"
#include "Loader.h"
#include "fstream"
#include "parser.hpp"
#include "PickupManager.h"

void dae::Loader::LoadLevel(const std::string & fileName)
{
	std::ifstream file;
	file.open("../Data/" + fileName);
	if (file.is_open())
	{
		//read in information from csv
		aria::csv::CsvParser result(file);
		for (auto& row : result)
		{
			if (row[0] == "candy")
			{
				//add candy pickup
				PickupManager::GetInstance().AddPickup(Pos{ std::stof(row[1]), std::stof(row[2]) },
					Scale{ std::stof(row[3]), std::stof(row[4]) }, dae::PickupType::Candy);
			}
			else if (row[0] == "pill")
			{
				//add pill pickup
				PickupManager::GetInstance().AddPickup(Pos{ std::stof(row[1]), std::stof(row[2]) },
					Scale{ std::stof(row[3]), std::stof(row[4]) }, dae::PickupType::Pill);
			}
			else if (row[0] == "crossing")
			{
				//add crossing object
				std::shared_ptr<CrossingObject> tempCrossing = std::make_shared<CrossingObject>(
					Pos{ std::stof(row[1]), std::stof(row[2]) }, Scale{ std::stof(row[3]), std::stof(row[4]) }
				, static_cast<Direction>(std::stoi(row[5])), static_cast<Direction>(std::stoi(row[6])));

				PickupManager::GetInstance().AddCrossing(tempCrossing);
			}
			else if (row[0] == "zone")
			{
				//add zone
				std::shared_ptr<dae::Zone> zone = std::make_shared<dae::Zone>(
					Rect{ Pos{ std::stof(row[1]), std::stof(row[2]) },
					Scale{ std::stof(row[3]), std::stof(row[4]) } });

				zone->MakePool(std::stoi(row[5]));

				PickupManager::GetInstance().AddZone(zone);
			}
		}
	}
}

