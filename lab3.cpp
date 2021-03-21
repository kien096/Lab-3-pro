#include <iostream>
#include "pugixml.hpp"
#include "pugixml.cpp"
#include "pugiconfig.hpp"
#include <fstream>
#include <vector>
#include <locale.h>
#include <iomanip>
#include <string>

using namespace std;
using namespace pugi;

///help to find max of vector
pair < int, int> max_find(vector <pair<string,float>> rout_distant){
	float max = rout_distant[0].second;
	int mark = 0;
	for (int i = 0; i < rout_distant.size(); i++){
		if ( rout_distant[i].second > max) {
			max = rout_distant[i].second;
			mark = i;
		}
	}
	pair <int, int> b (mark, max );
	return b;
}
pair < int, int> max_find_route(vector <pair<string, int>> rout_distant){
	float max = rout_distant[0].second;
	int mark = 0;
	for (int i = 0; i < rout_distant.size(); i++){
		if ( rout_distant[i].second > max) {
			max = rout_distant[i].second;
			mark = i;
		}
	}
	pair <int, int> b (mark, max );
	return b;
}
class Transport_station{
	private:
		pair <float, float> Split_coordinates(string str){
			string str1 = str.substr(0, str.find(","));
			string str2 = str.substr(str.find(",") + 1, str.size());
			pair <float,float> b ( stof(str1), stof(str2));
			return b;
		}

		vector<string> get_routes(string &s) {
		    vector<string> result;
		    stringstream ss (s);
		    string item;

			int a = s.find(",");
			int b = s.find(".");

			if (!(a + 1) && !(b + 1)){
				result.push_back(s);
				return result;
			} result;
			if (a + 1) {
			    while (getline (ss, item, ',')) {
			        result.push_back (item);
			    }
			    return result;
			}
			if (b + 1) {
			    while (getline (ss, item, '.')) {
			        result.push_back (item);
			    }
		    	return result;
			}
		}

	public:
		string location, number, type_vehicle,object_type,name_stopping, the_official_name;
		vector <string> routes;
		pair <float,float> coordinates;
		Transport_station(){
		};
		~Transport_station(){
		};
		Transport_station(Transport_station const &p){
			number = p.number;
			object_type = p.object_type;
			name_stopping = p.name_stopping;
			the_official_name = p.the_official_name;
			location = p.location;
			routes = p.routes;
			coordinates = p.coordinates;
		};

	void operator= (Transport_station const &u){
		number = u.number;
		object_type = u.object_type;
		name_stopping = u.name_stopping;
		the_official_name = u.the_official_name;
		location = u.location;
		routes = u.routes;
		coordinates = u.coordinates;
	}
	void get(string number, string type_vehicle_save, string object_type_save, string name_stopping_save, string the_official_name_save, string location_save, string routes_save, string coordinates_save){
		this->number = number;
		this->type_vehicle = type_vehicle_save;
		this->object_type = object_type_save;
		this->name_stopping = name_stopping_save;
		this->the_official_name = the_official_name_save;
		this->location = location_save;
		this->routes = get_routes(routes_save);
		this->coordinates = Split_coordinates(coordinates_save);
	}
};
class Vehicle{
	private:
		float distance(pair <float, float> a, pair <float, float> b){
			return sqrt(pow((a.first - b.first),2) + pow((a.second - b.second),2));
		}
		void set_routes_list(){
			// tim so tuyen duong khac nhau
			int count;
			routes_list.push_back(List[0].routes[0]);
			for(int i = 0; i < List.size(); i++){
				for(int j = 0; j < List[i].routes.size(); j++){
					count = 0;
					for(int k = 0; k < routes_list.size(); k++){
						if (routes_list[k] != List[i].routes[j]) {
							count ++;
						}
					}
					if (count ==  routes_list.size()) {
						routes_list.push_back(List[i].routes[j]);
					}
				}
			}
			return;
		}

		void set_list_coord_of_routes(){
			// tim cap rou - coordinates
			for (int i = 0; i < routes_list.size(); i++){
				pair<string, vector<pair<float,float>>> temp;
				temp.first = routes_list[i];
				for (int j = 0; j < List.size(); j++){
					for(int k = 0; k < List[j].routes.size(); k++){
						if (temp.first == List[j].routes[k])
							temp.second.push_back(List[j].coordinates);
					}
				}
				coords_each_route.push_back(temp);
			}
			return;
		}
		void set_pair_routes_dis(){
			for(int i = 0; i < coords_each_route.size(); i++){
				pair <string,float> temp (coords_each_route[i].first, 0);
				float dis = 0;
				for(int j = 0; j < coords_each_route[i].second.size() - 1; j++){
					dis += distance(coords_each_route[i].second[j], coords_each_route[i].second[j+1]);
				}
				temp.second = dis;
				rout_distant.push_back(temp);
			}
			return;
		}
		void set_rou_quantity(){
			//ham de tao ra vector cac cap tuyen duong - so luong diem dung
			int count;
			pair <string, int> temp (List[0].routes[0], 1);
			rout_quantity.push_back(temp);
			for(int i = 1; i < List.size(); i++){
				for(int j = 0; j < List[i].routes.size(); j++){
					count = 0;
					for(int k = 0; k < rout_quantity.size(); k++){
						if(rout_quantity[k].first == List[i].routes[j]) {
							rout_quantity[k].second++;
						}
						else count ++;
					}
					if (count ==  rout_quantity.size()) {
						temp.first = List[i].routes[j];
						temp.second = 1;
						rout_quantity.push_back(temp);
					}
				}
			}
			return;
		}

	public:
		vector <Transport_station> List;
		vector <string> routes_list;
		vector <pair<string,float>> rout_distant; // khoang cach
		vector <pair<string,int>> rout_quantity; // so luong diem dung
		vector < pair<string, vector< pair<float,float>> > > coords_each_route;
		Vehicle(){
		};
		Vehicle( Vehicle const &m){
			this->List = m.List;
		};
		Vehicle(vector <Transport_station> &p){
			this->List = p;
		};
		void operator= (Vehicle u){
			this->List = u.List;
		}


		void route_have_most_stoppings(){
			// tim tuyen duong co so luong diem dung lon nhat
			set_rou_quantity();
			pair <int, int> b = max_find_route(rout_quantity);
			cout << "Route '"<< rout_quantity[b.first].first <<"' has the most number of Stopping, with: " << rout_quantity[b.first].second << " Stopping(s)."<<endl;
			return;
		}

		void print_longest_route(){
			// dung de in tuyen duong dai nhat
			set_routes_list();
			set_list_coord_of_routes();
			set_pair_routes_dis();
			pair <int, float> b = max_find(rout_distant);
			cout <<"Longest Routes: '" << rout_distant[b.first].first << "' with lenght = " << rout_distant[b.first].second<<"."<<endl;
			return;
		}
		~Vehicle(){
		};
};
class Tramvay : public Vehicle{
	public:
	Tramvay() : Vehicle(){
	};

	Tramvay(Tramvay const &m) : Vehicle(m){
	};

	Tramvay(vector <Transport_station> &p) : Vehicle(p){
	};

	~Tramvay(){
	};
};
class Trolleybuss : public Vehicle{
	public:
	Trolleybuss() : Vehicle(){
	};
	Trolleybuss(vector <Transport_station> &p) : Vehicle(p){
	};
	Trolleybuss(Trolleybuss const &p) : Vehicle(p){
	};
	~Trolleybuss(){
	};
};

class Buss : public Vehicle{
	public:
	Buss() : Vehicle(){
	};
	Buss(vector <Transport_station> &p) : Vehicle(p){
	};
	Buss(Buss const &p) : Vehicle(p){
	};
	~Buss(){
	};
};
class Streett{
	private:
		void shorten_streets_name(){
			street.push_back(List[0]);
			for (int i = 1; i < List.size(); i++){
					string b = List[i];
					int c = b.find(",");
					if(c + 1) b.resize(c);
					c = b.find(" (");
					if(c + 1) b.resize(c);
					c = b.find(" /");
					if(c + 1) b.resize(c);
					c = b.find(" [");
					if(c + 1) b.resize(c);
					c = b.find(" №");
					if(c + 1) b.resize(c);
					c = b.find("/ ");
					if(c + 1) b.resize(c);
					street.push_back(b);
			}
			return;
		}

	public:
		vector <string> List, street;
		vector <pair<string, int>> street_number_stopping;
		Streett(){}
		Streett(vector <string> p){
			this->List = p;
		}
		void operator= (Streett &u){
			this->List = u.List;
		}
		void street_have_most_number_of_route(){
			shorten_streets_name();
			pair <string,int> temp (street[0], 1);
			street_number_stopping.push_back(temp);
			for(int i = 1; i < street.size(); i++){
				//int count = 0;
				if(street[i] == street_number_stopping[street_number_stopping.size() - 1].first)
				 street_number_stopping[street_number_stopping.size() - 1].second++;
				else {
					temp.first = street[i];
					temp.second = 1;
					street_number_stopping.push_back(temp);
				}
			}
			pair <string,int> max = street_number_stopping[0];
			for(int i = 0; i < street_number_stopping.size(); i++){
				if (max.second < street_number_stopping[i].second) max = street_number_stopping[i];
			}
			cout<<"Street with most number of route: '"<< max.first <<"'." <<endl;
			return;
		}
		~Streett(){}

};
int vehicle(vector <xml_node> &data, vector <string> &type_vehicle){
		type_vehicle.push_back(data[0].child_value("type_vehicle"));
		for (int i = 1; i < data.size(); i++){
		if (data[i].child_value("type_vehicle") != type_vehicle[type_vehicle.size() - 1])
			type_vehicle.push_back(data[i].child_value("type_vehicle"));
	}
		return type_vehicle.size();
}

int main()
{
	std::locale::global(std::locale(""));
    vector <xml_node> data;
    ifstream stream("data.xml");
    xml_document doc;
	doc.load(stream);

    for (xml_node i = doc.child("dataset").first_child(); i; i = i.next_sibling()){
    	xml_node temp = i;
    	data.push_back(temp);
	}

	// Find the number of different types of vehicles
	vector <string> type_vehicle;
	vehicle(data, type_vehicle);

	vector <Transport_station> tramvai;
	vector <Transport_station> troll;
	vector <Transport_station> bus;
	vector <string> street_list;

	string stopping = data[0].child_value("object_type"); // stopping = Остановка;
	for (int i = 0; i < data.size(); i++){
		if ( data[i].child_value("object_type") == stopping){
			Transport_station temp;
			temp.get(data[i].child_value("number"), data[i].child_value("type_of_vehicle"),data[i].child_value("object_type"),
					data[i].child_value("name_stopping"),data[i].child_value("the_official_name"),data[i].child_value("location"),
					data[i].child_value("routes"),data[i].child_value("coordinates"));

			street_list.push_back(data[i].child_value("the_official_name"));
			if(temp.type_vehicle == type_vehicle[0]) tramvai.push_back(temp);
			else if(temp.type_vehicle == type_vehicle[1]) troll.push_back(temp);
			else bus.push_back(temp);
      /*      for (int i = 0; i < street_list.size();i++){
		if (street_list[i].child_value("type_vehicle") == "Трамвай") tramvai.push_back(street_list[i]);
               // cout << datalab3[i].child_value("type_of_vehicle") << endl;
		if (street_list[i].child_value("type_vehicle") == "Троллейбус") troll.push_back(street_list[i]);
               // cout << datalab3[i].child_value("type_of_vehicle") << endl;
		if (street_list[i].child_value("type_vehicle") == "Автобус") bus.push_back(street_list[i]);
               // cout << datalab3[i].child_value("type_of_vehicle") << endl;
	}*/
		}
	}

	// hien thi routes Tramvai
	//cout<<endl;
	Tramvay tramv(tramvai);
	tramv.print_longest_route();
	tramv.route_have_most_stoppings();

	//cout<< endl;
	Trolleybuss trolley(troll);
	trolley.print_longest_route();
	trolley.route_have_most_stoppings();

	//cout<< endl;
	Buss avbus(bus);
	avbus.print_longest_route();
	avbus.route_have_most_stoppings();

	//cout <<endl;
	Streett street(street_list);
	street.street_have_most_number_of_route();

	return 0;

}
