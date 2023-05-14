#ifndef STRUCT_H
#define STRUCT_H

#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <codecvt>
#include <locale>
#include <random>
#include "etcfunction.h"

using namespace std;

struct Politician
{
	std::string name;
	struct Party* party;		// 소속 정당
	int age;
	int procons;
	int libauth;
	float status[4]{ 0,0,0,0 };
	int NOV = 0;

	Politician() : name(""), party(NULL), age(0), procons(0), libauth(0), status{0,0,0,0} {}

	int setAge()
	{
		return rand() % 60 + 20;
	}

	bool is_dead() {
		if (age >= 90)
			return (float)rand() / (float)RAND_MAX < 0.05;
		else if (age >= 80)
			return (float)rand() / (float)RAND_MAX < 0.02;
		else if (age >= 70)
			return (float)rand() / (float)RAND_MAX < 0.005;
		else
			return (float)rand() / (float)RAND_MAX < 0.0001;
	}
};

struct POP {
	int population = 0;
	int procons;
	int libauth;
	std::vector<int> supporter;
	std::vector<float> approval_rate;
	std::vector<Politician*> Politicians;
};

//---------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------//

struct LocalParty {
	int procons;
	int libauth;
	int member{ 0 };
	int supporter{ 0 };
	std::vector<Politician*> politician;
	struct Party* party;
	struct Politician candidate;
};

struct Party {
	char name[40]{""};
	float size{0};
	int procons;
	int libauth;
	int NOV{ 0 };
	int NOS{ 0 };
	int member{ 0 };
	int supporter{ 0 };
	std::vector<Politician*> politician;

	void setPartyName() {
		std::ifstream usedname("used_party_name.txt");
		std::string used;
		std::vector<std::string> used_vec;
		while (getline(usedname, used)) {
			used_vec.push_back(used);
		}
		usedname.close();

		std::string selected;
		if (procons >= 0) {
			std::ifstream file("party_name_l.txt");
			if (file.is_open()) {
				std::string line;
				int count = 0;
				int chosen = rand() % 30;
				while (getline(file, line)) {
					if (count == chosen) {
						selected = line;
						if (std::find(used_vec.begin(), used_vec.end(), selected) != used_vec.end()) {
							continue;
						}
						strncpy_s(name, selected.c_str(), 40);
						break;
					}
					count++;
				}
				file.close();
			}
		}
		else {
			std::ifstream file("party_name_r.txt");
			if (file.is_open()) {
				std::string line;
				int count = 0;
				int chosen = rand() % 30;
				while (getline(file, line)) {
					if (count == chosen) {
						selected = line;
						if (std::find(used_vec.begin(), used_vec.end(), selected) != used_vec.end()) {
							continue;
						}
						strncpy_s(name, selected.c_str(), 40);
						break;
					}
					count++;
				}
				file.close();
			}
		}
		std::ofstream outfile;
		outfile.open("used_party_name.txt", std::ios_base::app);
		outfile << selected.c_str() << std::endl;
		outfile.close();
	}
};

void setSize(std::vector<Party>& parties) {
	float member_sum = 0;
	for (int i = 0; i < parties.size(); i++) {
		member_sum += parties[i].member;
	}
	for (int i = 0; i < parties.size(); i++) {
		parties[i].size = (parties[i].member / member_sum) * 100;
		cout << parties[i].name << "\t\t" << parties[i].size << endl;
	}
}

//---------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------//

struct District{
	char prov_name[60]{ "" };
	char name[60]{""};
	float procons{0};
	int population{0};
	int supporter{ 0 };
	POP popu[21][21];
	std::vector<Politician*> Politicians;
	std::vector<Party>& Parties;
	std::vector<LocalParty*> LocalOrg;
	std::vector<Politician*> candidates;
	struct Politician* Congressman;
	std::vector<float> approval_rate;
	District(std::vector<Party>& parties) : Parties(parties) {}

	void setPOP() {
		int pol_num = population * 0.0015;
		std::string filename = "politician_name.txt";
		std::ifstream infile(filename);
		std::vector<std::string> names;
		std::string line;
		while (getline(infile, line)) {
			names.push_back(line);
		}
		int name_idx = names.size();

		for (int i = 0; i < pol_num; i++) {
			struct Politician* pol;
			pol = new Politician;
			int procons = rand() % 21 - 10;
			int libauth = rand() % 21 - 10;
			popu[procons+10][libauth+10].Politicians.push_back(pol);
			pol->age = pol->setAge();
			pol->procons = procons;
			pol->libauth = libauth;
			pol->status[0] = rand() % 10 + 1;
			pol->status[1] = rand() % 10 + 1;
			pol->status[2] = (float)rand() / (float)RAND_MAX * 0.2;
			pol->status[3] = pol->status[0] * pol->status[1] * (1 - pol->status[2]);

			double cal_dis;
			double min_cal_dis = INFINITY;
			struct Party* party = NULL;
			struct LocalParty* localparty = NULL;
			for (int j = 0; j < LocalOrg.size(); j++) {
				double cal_dis = sqrt2(dis_cal(pol->procons, LocalOrg[j]->procons), dis_cal(pol->libauth, LocalOrg[j]->libauth));
				if (cal_dis < min_cal_dis && (pol->procons * LocalOrg[j]->procons > 0) && (pol->libauth * LocalOrg[j]->libauth > 0)) {
					min_cal_dis = cal_dis;
					party = LocalOrg[j]->party;
					localparty = LocalOrg[j];
				}
				else if (cal_dis == min_cal_dis && (pol->procons * LocalOrg[j]->procons > 0) && (pol->libauth * LocalOrg[j]->libauth > 0)) {
					if (rand() % 2 == 0) {
						min_cal_dis = cal_dis;
						party = LocalOrg[j]->party;
						localparty = LocalOrg[j];
					}
					else {
						continue;
					}
				}
			}

			if (party != NULL) {
				pol->party = party;
				party->politician.push_back(pol);
				localparty->politician.push_back(pol);
				if (infile.is_open()) {
					name_idx = rand() % name_idx;
					pol->name = names[name_idx];
					infile.close();
				}
				Politicians.push_back(pol);
			}
		}
		
		float sum = 0;
		for (int i = 0; i < Parties.size(); i++) {
			float prodis = abs(this->procons - Parties[i].procons);
			approval_rate.push_back(float(Parties[i].politician.size()) / float(this->Politicians.size()));
			if (prodis <= 5) {
				this->approval_rate[i] = sqrt2(dis_cal(Parties[i].procons, this->procons), dis_cal(Parties[i].libauth, 0)) * prodis;
				sum += this->approval_rate[i];
			}
			else {
				this->approval_rate[i] = sqrt2(dis_cal(Parties[i].procons, this->procons), dis_cal(Parties[i].libauth, 0)) / prodis;
				sum += this->approval_rate[i];
			}
		}

		int pro = 0;
		int lib = 0;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<double> range(-10.0, 10.0); // -10에서 10까지의 값으로 설정		

		// 정규분포 생성
		std::normal_distribution<double> prov_pro(this->procons, 4);
		std::normal_distribution<double> prov_lib(this->procons + rand() % 5 - 2, 4);

		for (int i = 0; i < population * 0.8; i++) {
			pro = rand() % 21;
			lib = rand() % 21;
			float polint = (float)rand() / (float)RAND_MAX;
			float max_dis = sqrt2(dis_cal(-20, 20), dis_cal(-20, 20));
			if (polint > 0.25) {
				for (int j = 0; j < Parties.size(); j++) {
					float prodis = sqrt2(dis_cal(pro, Parties[j].procons), dis_cal(lib, Parties[j].libauth));
				}
			}
			
			if (rand() % 5 > 0) {
				popu[pro][lib].population++;
			}
			else {
				while (pro * pro > 100 || lib * lib > 100) {
					pro = prov_pro(gen);
					lib = prov_lib(gen);
				}
				popu[pro + 10][lib + 10].population++;
			}
		}

		float sup_rate = (float)rand() / (float)RAND_MAX * 0.15 + 0.7;
		float mem_rate = (float)rand() / (float)RAND_MAX * 0.15;
		for (int i = 0; i < 21; i++) {
			for (int j = 0; j < 21; j++) {
				popu[i][j].procons = i - 10;
				popu[i][j].libauth = j - 10;
				popu[i][j].approval_rate.resize(Parties.size());
				popu[i][j].supporter.resize(Parties.size());
				sum = 0;
				float prodis = sqrt2(dis_cal(popu[i][j].procons, 0), dis_cal(popu[i][j].libauth, 0));
				
				for (int k = 0; k < popu[i][j].approval_rate.size(); k++) {
					if (prodis < 3) {
						popu[i][j].approval_rate[k] = max_dis - sqrt2(dis_cal(Parties[k].procons, i), dis_cal(Parties[k].libauth, j));
						sum += popu[i][j].approval_rate[k];
					}
					else {
						if (popu[i][j].procons * Parties[k].procons >= 0) {
							popu[i][j].approval_rate[k] = max_dis - sqrt2(dis_cal(Parties[k].procons, i), dis_cal(Parties[k].libauth, j));
							sum += popu[i][j].approval_rate[k];
						}
						else {
							popu[i][j].approval_rate[k] = 0;
							sum += popu[i][j].approval_rate[k];
						}
					}
				}
				
				for (int k = 0; k < popu[i][j].approval_rate.size(); k++) {
					popu[i][j].approval_rate[k] /= sum;
				}
				for (int k = 0; k < popu[i][j].supporter.size(); k++) {
					popu[i][j].supporter[k] = popu[i][j].population * popu[i][j].approval_rate[k] * sup_rate;
					LocalOrg[k]->supporter += popu[i][j].supporter[k];
					LocalOrg[k]->member += (popu[i][j].supporter[k] * mem_rate);
					Parties[k].supporter += popu[i][j].supporter[k];
					Parties[k].member = LocalOrg[k]->member;
				}
			}
			
		}
	}

	/*void selectCand() {
		int party_num = 0;
		for (int i = 0; i < LocalOrg.size(); i++) {
			if (LocalOrg[i]->politician.size() > 0)
				party_num++;
		}
		this->candidates.resize(party_num);
		party_num = 0;
		
		int max_prefer = 0;
		for (int i = 0; i < LocalOrg.size(); i++) {
			max_prefer = 0;
			if (LocalOrg[i]->politician.size() > 0) {
				this->candidates[party_num] = new Person;
				for (int j = 0; j < LocalOrg[i]->politician.size(); j++) {
					if (max_prefer < LocalOrg[i]->politician[j]->status[3]) {
						this->candidates[party_num] = LocalOrg[i]->politician[j];
						this->candidates[party_num]->NOV = 0;
						max_prefer = LocalOrg[i]->politician[j]->status[3];
					}
				}
				party_num++;
			}
			else
				continue;
		}
	}*/

	//void CongressVote() {
	//	int* NOV;
	//	NOV = (int*)malloc(candidates.size() * sizeof(int));
	//	for (int i = 0; i < candidates.size(); i++) {
	//		NOV[i] = 0;
	//	}

	//	double min_dist;
	//	double dist = 0;
	//	float vote_possibility = ((float)rand() / (float)RAND_MAX * 0.5);
	//	for (int i = 0; i < pop.size(); i++) {
	//		struct Person* select = NULL;
	//		if (pop[i]->age >= 19 && pop[i]->polint > vote_possibility) {
	//			if (pop[i]->sup_party != NULL) {
	//				for (int j = 0; j < candidates.size(); j++) {
	//					if (candidates[j]->party == pop[i]->sup_party) {
	//						candidates[j]->NOV++;
	//					}
	//				}
	//				pop[i]->sup_party->NOV++;	// 지지 정당에게 비례 투표
	//			}
	//			else {
	//				if (pop[i]->polint > 0.9) {		// 정치 관심도가 높은 경우 가장 이념적으로 유사한 정당에게 투표
	//					min_dist = INFINITY;
	//					for (int j = 0; j < candidates.size(); j++) {
	//						if (candidates[j]->party->size > candidates[j]->status[3] / 100) {		// 후보의 종합 선호도보다 높은 난수가 나올 시, 유권자는 정당을 기준으로 투표 여부를 결정
	//							float dis1 = dis_cal(pop[i]->IDE[0], LocalOrg[j]->IDE[pop[i]->index[0]]);
	//							float dis2 = dis_cal(pop[i]->IDE[1], LocalOrg[j]->IDE[pop[i]->index[1]]);
	//							dist = sqrt2(dis1, dis2);
	//						}
	//						else {
	//							float dis1 = dis_cal(pop[i]->IDE[0], LocalOrg[j]->IDE[pop[i]->index[0]]);
	//							float dis2 = dis_cal(pop[i]->IDE[1], LocalOrg[j]->IDE[pop[i]->index[1]]);
	//							dist = sqrt2(dis1, dis2);
	//						}
	//						if (dist < min_dist) {
	//							min_dist = dist;
	//							select = candidates[j];
	//						}
	//					}
	//					if (select != NULL) {
	//						select->NOV++;
	//						select->party->NOV++;
	//					}
	//				}
	//				else {
	//					min_dist = INFINITY;
	//					for (int j = 0; j < candidates.size(); j++) {
	//						if (candidates[j]->party->size > candidates[j]->status[3] / 100) {		// 후보의 종합 선호도보다 높은 난수가 나올 시, 유권자는 정당을 기준으로 투표 여부를 결정
	//							dist = sqrt2(dis_cal(pop[i]->IDE[0], LocalOrg[j]->IDE[pop[i]->index[0]]), dis_cal(pop[i]->IDE[1], LocalOrg[j]->IDE[pop[i]->index[1]]));
	//						}
	//						else {
	//							dist = sqrt2(dis_cal(pop[i]->IDE[0], LocalOrg[j]->IDE[pop[i]->index[0]]), dis_cal(pop[i]->IDE[1], LocalOrg[j]->IDE[pop[i]->index[1]]));		// 후보의 종합 선호도보다 낮은 난수가 나올 시, 유권자는 정당과 후보자의 평균 척도를 기준으로 결정
	//						}

	//						if (dist < min_dist) {
	//							min_dist = dist;
	//							select = candidates[j];
	//						}
	//						else if (dist < min_dist) {
	//							min_dist = dist;
	//							select = candidates[j];
	//						}
	//					}
	//					if (select != NULL) {
	//						select->NOV++;
	//						select->party->NOV++;
	//					}
	//					else
	//						continue;
	//				}
	//			}
	//		}
	//	}

	//	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	//	ofstream outFile;
	//	outFile.open("Congress_election_Result.csv", ios::app);
	//	outFile << char(0xEF) << char(0xBB) << char(0xBF);

	//	int max = 0;
	//	struct Person* winner = NULL;
	//	//cout << this->name << "\t[" << this->procons << "]" << endl;
	//	outFile << this->name << "," << endl;
	//	for (int i = 0; i < candidates.size(); i++) {
	//		//cout << candidates[i]->party->name << "\t" << candidates[i]->name << "\t" << NOV[i] << "표" << endl;
	//		outFile << candidates[i]->party->name << "," << candidates[i]->name << "," << candidates[i]->NOV << "," << endl;
	//		if (candidates[i]->NOV > max) {
	//			max = candidates[i]->NOV;
	//			winner = candidates[i];
	//		}	
	//	}
	//	this->Congressman = winner;
	//	this->Congressman->party->NOS++;
	//	//cout << this->name << "\t" << this->Congressman->party->name << "\t" << this->Congressman->name << endl;
	//	outFile << this->name << "," << this->Congressman->party->name << "," << Congressman->name << "," << endl << "," << endl;
	//	outFile.close();
	//	//cout << endl;
	//}

	void summonLP() {
		this->LocalOrg.resize(Parties.size());
		for (int i = 0; i < Parties.size(); i++) {
			this->LocalOrg[i] = new LocalParty;
			this->LocalOrg[i]->party = &Parties[i];
			this->LocalOrg[i]->procons = Parties[i].procons;
			this->LocalOrg[i]->libauth = Parties[i].libauth;
		}
	}

	/*void Vote() {
		float vote_possibility = ((float)rand() / (float)RAND_MAX * 0.1);
		for (int i = 0; i < pop.size(); i++) {
			if (pop[i]->age >= 19 && (float)rand() / (float)RAND_MAX > 1 - pop[i]->polint - vote_possibility) {
				if (pop[i]->sup_party != NULL) {
					pop[i]->sup_party->NOV++;
				}
				else {
					int dis_idx = 0;
					double distance = double(INFINITY);
					for (int j = 0; j < Parties.size(); j++) {
						if (sqrt2(dis_cal(pop[i]->IDE[0], LocalOrg[j]->IDE[pop[i]->index[0]]), dis_cal(pop[i]->IDE[1], LocalOrg[j]->IDE[pop[i]->index[1]])) < distance) {
							distance = sqrt2(dis_cal(pop[i]->IDE[0], LocalOrg[j]->IDE[pop[i]->index[0]]), dis_cal(pop[i]->IDE[1], LocalOrg[j]->IDE[pop[i]->index[1]]));
							dis_idx = j;
						}
					}
					Parties[dis_idx].NOV++;
				}
			}
		}
	}*/
};

void setDistrictInfo(std::string& filename, std::vector<Party>& Parties, std::vector<District*>& Districts) {
	std::ifstream infile(filename);
	if (!infile) {
		cerr << "Error : could not open file " << filename << endl;
		return;
	}
	if (infile) {
		std::string line;
		int vec_idx = 0;
		while (std::getline(infile, line)) {
			std::stringstream ss(line);
			std::string prov_name, dis_name;
			int pop = 0;
			std::getline(ss, prov_name, ',');
			std::getline(ss, dis_name, ',');
			ss >> pop;
			strncpy_s(Districts[vec_idx]->prov_name, prov_name.c_str(), 60);
			strncpy_s(Districts[vec_idx]->name, dis_name.c_str(), 60);
			Districts[vec_idx]->population = pop;
			Districts[vec_idx]->summonLP();
			vec_idx++;
		}
	}
}

struct Province{
	Province* self;
	char name[60]{""};
	int procons{0};
	int population{0};
	int district_num{0};
	std::vector<District*> D;
	std::vector<Party>& Parties;
	Province(std::vector<Party>& parties) : Parties(parties) {
		self = this;
	}
};

void setProvinceInfo(std::string& filename, std::vector<Party>& Parties, std::vector<Province>& Provinces) {
	std::ifstream infile(filename);
	if (!infile) {
		cerr << "Error : could not open file " << filename << endl;
		return;
	}
	if (infile) {
		std::string line;
		int prov_idx = 0;
		while (std::getline(infile, line)) {
			std::string name;
			std::string procons_str;
			int Dsize = 0;
			std::stringstream ss(line);
			std::getline(ss, name, ',');
			std::getline(ss, procons_str, ',');
			ss >> Dsize;
			strncpy_s(Provinces[prov_idx].name, name.c_str(), 60);
			int procons;
			procons = std::stoi(procons_str);
			Provinces[prov_idx].procons = procons;
			Provinces[prov_idx].district_num = Dsize;
			prov_idx++;
		}
	}
}

struct Country{
	char name[20]{"Korea"};
	int province_num{0};
	int party_num{0};
	int population{0};
	std::vector<Party>& Parties;
	std::vector<Province> Prov;
	Country(std::vector<Party>& parties) : Parties(parties) {}
};

//---------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------//

void setParty(std::vector<Party>& Parties, int party_num) {
	for (int i = 0; i < party_num; i++) {
		Party p;
		p.procons = rand() % 21 - 10;
		p.libauth = rand() % 21 - 10;
		if (i > 0) {
			if (p.procons * Parties[i - 1].procons > 0) {
				p.procons *= -1;
			}
		}
		p.setPartyName();
		cout << p.name << "\t" << p.procons << "\t" << p.libauth << endl;
		Parties.push_back(p);
	}
}

#endif