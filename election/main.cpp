#include "Struct.h"

int main(int argc, char* argv[]) {
	cout << fixed;
	cout.precision(2);

	srand(time(NULL));
	clock_t start, end;
	double cpu_time_used;
	start = clock();

	//-----------------------------------------------------------------------------------------//
	std::vector<Party> Parties;
	setParty(Parties, rand() % 3 + 3);

	string line;
	int line_count = 0;
	ifstream infile("Congress_District.csv");
	while (getline(infile, line)) {
		line_count++;
	}

	std::vector<District*> Districts(line_count, nullptr); // District 포인터를 저장하는 vector
	for (int i = 0; i < line_count; i++) {
		Districts[i] = new District(Parties); // District 포인터 생성 및 초기화
	}

	std::string Districtfile("Congress_District.csv");
	setDistrictInfo(Districtfile, Parties, Districts);

	line_count = 0;
	ifstream provfile("Province_name.txt");
	while (getline(provfile, line)) {
		line_count++;
	}

	std::vector<Province> Provinces(line_count, Province(Parties));
	std::string Provincefile("Province_name.txt");
	setProvinceInfo(Provincefile, Parties, Provinces);

	/*Provinces.clear();
	Districts.clear();*/

	struct Country Korea(Parties);

	// Districts vector의 포인터를 이용해 Province의 D vector에 District 포인터 저장
	for (int i = 0; i < Districts.size(); i++) {
		for (int j = 0; j < Provinces.size(); j++) {
			if (strcmp(Provinces[j].name, Districts[i]->prov_name) == 0) {
				if (Provinces[j].procons > 0) {
					Districts[i]->procons = max(min(rand() % 4 - 1 + Provinces[j].procons, 9), -9);
				}
				else if (Provinces[j].procons < 0) {
					Districts[i]->procons = max(min(rand() % 4 - 2 + Provinces[j].procons, 9), -9);
				}
				else {
					Districts[i]->procons = max(min(rand() % 5 - 2 + Provinces[j].procons, 9), -9);
				}
				Districts[i]->setPOP();
				Provinces[j].D.push_back(Districts[i]);
				cout << Districts[i]->name << " 생성 완료\t" << "[" << Districts[i]->procons << "]" << endl;
				for (int k = 0; k < Parties.size(); k++) {
					Districts[i]->supporter += Districts[i]->LocalOrg[k]->supporter++;
				}
				cout << "정당명\t" << "지지율" << endl;
				int tmp_pop = Districts[i]->population;
				for (int k = 0; k < Districts[k]->LocalOrg.size(); k++) {
					cout << Districts[i]->LocalOrg[k]->party->name << "\t\t" << float(Districts[i]->LocalOrg[k]->supporter) / float(Districts[i]->population) * 100 << "%" << endl;
					tmp_pop -= Districts[i]->LocalOrg[k]->supporter;
				}cout << "무당층\t" << float(tmp_pop) / float(Districts[i]->population) * 100 << "%" << endl;
				cout << endl;
				//Korea.population += Districts[i]->pop.size();
			}
		}
	}
	setSize(Parties);

	end = clock();
	cpu_time_used = ((double)(end - start) / CLOCKS_PER_SEC);
	printf("생성 소요 시간 : %f\n", cpu_time_used);
	//printf("%d\n", Korea.population);

	//-----------------------------------------------------------------------------------------//


	//int year = 2019;
	//int month = 8;
	//int election_month[3] = { 31, 8, 34 };	// 대선, 총선, 지선
	//while (1) {
	//	cout << year << "년 " << month << "월" << endl;

	//	if (election_month[1] == 5) {
	//		for (int i = 0; i < Provinces.size(); i++) {
	//			for (int j = 0; j < Provinces[i].D.size(); j++) {
	//				Provinces[i].D[j]->selectCand();
	//			}
	//		}
	//	}

	//	if (election_month[1] == 0) {
	//		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	//		ofstream outFile;
	//		outFile.open("Congress_election_Result.csv", ios::app);
	//		outFile << char(0xEF) << char(0xBB) << char(0xBF);

	//		for (int i = 0; i < Provinces.size(); i++) {
	//			outFile << Provinces[i].name << "," << endl;
	//			for (int j = 0; j < Provinces[i].D.size(); j++) {
	//				Provinces[i].D[j]->CongressVote();
	//			}
	//		}
	//		for (int i = 0; i < Parties.size(); i++) {
	//			cout << Parties[i].name << " : " << Parties[i].NOS << "석" << endl;
	//		}
	//	}

	//	month++;
	//	for (int i = 0; i < 3; i++) {
	//		election_month[i]--;
	//	}

	//	if (month > 12) {
	//		year++;
	//		month = 1;
	//	}
	//	if (month == 5)
	//		break;
	//}

	//for (int i = 0; i < Parties.size(); i++) {
	//	cout << Parties[i].name << Parties[i].NOV << "표" << endl;
	//}

	//---------------------------------------------------------------------------------//
	Provinces.clear();
	Districts.clear();
	std::ofstream file("used_party_name.txt", std::ios::out | std::ios::trunc);
	file.close();

	return 0;
}