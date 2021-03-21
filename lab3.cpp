#include <iostream>
#include "pugixml.hpp"
#include "pugixml.cpp"
#include "pugiconfig.hpp"
#include <fstream>
#include <map>
#include <cstring>
#include <vector>
#include <locale.h>
#include <utility>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;
using namespace pugi;

//help find max of vector //помогите найти макс вектора
pair < int, float> max_find(vector <pair<string,float>> rou_dis){
	float max = rou_dis[0].second;
	int mark = 0;
	for (int i = 0; i < rou_dis.size(); i++){
		if ( rou_dis[i].second > max) {
			max = rou_dis[i].second;
			mark = i;
		}
	}
	pair <int, int> b (mark, max );
	return b;
}
class Transport_station{
	private:
		pair <float, float> Split_coordinates(string str){     ///Разделить координаты <напимер: <coordinates>59.833108,30.182092</coordinates>>
			string str1 = str.substr(0, str.find(","));        ///59.833108 , 30.182092
			string str2 = str.substr(str.find(",") + 1, str.size());
			pair <float,float> b ( stof(str1), stof(str2));
			return b;
		}

		vector<string> get_routes(string &s) { /// read route and split
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
		string location, number, type_of_vehicle,object_type,name_stopping, the_official_name;
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
	void get(string numberx, string type_of_vehiclex, string object_typex, string name_stoppingx, string the_official_namex, string locationx, string routesx, string coordinatesx){
		this->number = numberx;
		this->type_of_vehicle = type_of_vehiclex;
		this->object_type = object_typex;
		this->name_stopping = name_stoppingx;
		this->the_official_name = the_official_namex;
		this->location = locationx;
		this->routes = get_routes(routesx);
		this->coordinates = Split_coordinates(coordinatesx);
	}
};
class Vehicle{
	private:
		float distance(pair <float, float> a, pair <float, float> b){    /// Рассчитать расстояние между двумя координатами
			return sqrt(pow((a.first - b.first),2) + pow((a.second - b.second),2));
		}
        map <string, int> routes;/// используется для упражнения 1
        string routes_transport;



		void set_routes_list(){    ///используется для упражнения 2
			/// Найдем разные номера маршрутов
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
				rou_dis.push_back(temp);
			}
			return;
		}

		void set_rou_quantity(){
			//Найдем количество остановок
			int count;
			pair <string, int> temp (List[0].routes[0], 1);
			rou_quantity.push_back(temp);
			for(int i = 1; i < List.size(); i++){
				for(int j = 0; j < List[i].routes.size(); j++){
					count = 0;
					for(int k = 0; k < rou_quantity.size(); k++){
						if(rou_quantity[k].first == List[i].routes[j]) {
							rou_quantity[k].second++;
						}
						else count ++;
					}
					if (count ==  rou_quantity.size()) {
						temp.first = List[i].routes[j];
						temp.second = 1;
						rou_quantity.push_back(temp);
					}
				}
			}
			return;
		}

	public:
		vector <Transport_station> List;
		vector <string> routes_list;
		vector <pair<string,float>> rou_dis;
		vector <pair<string,int>> rou_quantity;
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

		Vehicle (string trans) : routes_transport(trans) {}

        void print_max_most_stoppings() {      ///маршрут с наибольшим количеством остановок
                int max = -1;
                string name;
                map <string, int>::iterator iter;
                for (iter = routes.begin(); iter != routes.end(); ++iter) {
	    	        if (iter->second > max) {
                        max = iter->second;
                        name = iter->first;
                    }
	            }
        cout << "name_routes = " << "'" <<  name << "'" << "\tmax_routes = "<< max << endl;
        }


		void maps_routes() {                    ///читать routes в data.xml
            xml_document doc;
            if (!doc.load_file("data.xml"))
            exit(1);
        //pugi::xml_node panels = doc.child("dataset");
            xml_node panels = doc.first_child();
            for (xml_node panel1 = panels.first_child(); panel1; panel1 = panel1.next_sibling()) {
                string transport;
            for (xml_node panel2 = panel1.first_child(); panel2; panel2 = panel2.next_sibling()) {
                string name = panel2.name();
                string value = panel2.child_value();
                if (name == "type_of_vehicle") {
                    transport = value;
                }
                if ((transport == routes_transport) && (name == "routes")) {
                    int size = value.length();
                    string value_temp;
                    for (int i = 0; i < size; ++i) {
                        char ch;
                        ch = value[i];
                        if ((ch == '.') || (ch == ',')) {
                            routes[value_temp]++;
                            value_temp = "";
                        }
                        else {
                            value_temp += ch;
                        }
                    }
                    if ((value_temp != "") && (value_temp != " ")){
                        routes[value_temp]++;
                    }
                }
            }
        }
    }

		void print_max_route(){            ///Наиболее длинный маршрут (основывая на координатах) по отдельным видам транспорта
			set_routes_list();
			set_list_coord_of_routes();
			set_pair_routes_dis();
			pair <int, float> b = max_find(rou_dis);
			cout <<"Longest Routes: " << rou_dis[b.first].first << " lenght = " << rou_dis[b.first].second<<endl;
			return;
		}
		~Vehicle(){
		};
};

class Tramvai_t : public Vehicle{
	public:
	Tramvai_t() : Vehicle(){
	};

	Tramvai_t(Tramvai_t const &m) : Vehicle(m){
	};

	Tramvai_t(vector <Transport_station> &p) : Vehicle(p){
	};

	~Tramvai_t(){
	};
};

class Trolleybus_t : public Vehicle{
	public:
	Trolleybus_t() : Vehicle(){
	};
	Trolleybus_t(vector <Transport_station> &p) : Vehicle(p){
	};
	Trolleybus_t(Trolleybus_t const &p) : Vehicle(p){
	};
	~Trolleybus_t(){
	};
};

class Bus_t : public Vehicle{
	public:
	Bus_t() : Vehicle(){
	};
	Bus_t(vector <Transport_station> &p) : Vehicle(p){
	};
	Bus_t(Bus_t const &p) : Vehicle(p){
	};
	~Bus_t(){
	};
};

class Street_t{
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
		vector <pair<string, int>> street_numberstopping;
		Street_t(){}
		Street_t(vector <string> p){
			this->List = p;
		}
		void operator= (Street_t &u){
			this->List = u.List;
		}
		void Print_street_with_most_route(){
			shorten_streets_name();
			pair <string,int> temp (street[0], 1);
			street_numberstopping.push_back(temp);
			for(int i = 1; i < street.size(); i++){
				if(street[i] == street_numberstopping[street_numberstopping.size() - 1].first)
				 street_numberstopping[street_numberstopping.size() - 1].second++;
				else {
					temp.first = street[i];
					temp.second = 1;
					street_numberstopping.push_back(temp);
				}
			}
			pair <string,int> max = street_numberstopping[0];
			for(int i = 0; i < street_numberstopping.size(); i++){
				if (max.second < street_numberstopping[i].second) max = street_numberstopping[i];
			}
			cout<<"Street with most routes: "<< max.first<<endl;
			return;
		}
		~Street_t(){}

};

int number_type_of_vehicle(vector <xml_node> &DATA, vector <string> &type_of_vehicle){
		type_of_vehicle.push_back(DATA[0].child_value("type_of_vehicle"));
		for (int i = 1; i < DATA.size(); i++){
		if (DATA[i].child_value("type_of_vehicle") != type_of_vehicle[type_of_vehicle.size() - 1]){
			type_of_vehicle.push_back(DATA[i].child_value("type_of_vehicle"));
		}
	}
		return type_of_vehicle.size();
}

int main()
{
	setlocale(LC_ALL, "Россия");
    vector <xml_node> DATA;
    ifstream stream("data.xml");
    xml_document doc;
	doc.load(stream);

    for (xml_node i = doc.child("dataset").first_child(); i; i = i.next_sibling()){
    	xml_node temp = i;
    	DATA.push_back(temp);
	}

	// Find the number of different types of vehicles
	vector <string> type_of_vehicle;
	number_type_of_vehicle(DATA, type_of_vehicle);
	string bus_1 = "Автобус";
    string trolleybus_1 = "Троллейбус";
    string tramvai_1 = "Трамвай";


	vector <Transport_station> Tramvai;
	vector <Transport_station> Trolleybus;
	vector <Transport_station> Bus;
	vector <string> street_list;

	string stopping = DATA[0].child_value("object_type"); // stopping = Остановка;
	for (int i = 0; i < DATA.size(); i++){
		if ( DATA[i].child_value("object_type") == stopping){
			Transport_station temp;
			temp.get(DATA[i].child_value("number"), DATA[i].child_value("type_of_vehicle"),DATA[i].child_value("object_type"),
					DATA[i].child_value("name_stopping"),DATA[i].child_value("the_official_name"),DATA[i].child_value("location"),
					DATA[i].child_value("routes"),DATA[i].child_value("coordinates"));
/*  for (int i = 0; i < street_list.size();i++){
		if (street_list[i].child_value("type_vehicle") == "Трамвай") tramvai.push_back(street_list[i]);
               // cout << datalab3[i].child_value("type_of_vehicle") << endl;
		if (street_list[i].child_value("type_vehicle") == "Троллейбус") troll.push_back(street_list[i]);
               // cout << datalab3[i].child_value("type_of_vehicle") << endl;
		if (street_list[i].child_value("type_vehicle") == "Автобус") bus.push_back(street_list[i]);
               // cout << datalab3[i].child_value("type_of_vehicle") << endl;
	}*/

			street_list.push_back(DATA[i].child_value("the_official_name"));
			if(temp.type_of_vehicle == type_of_vehicle[0]) Tramvai.push_back(temp);
			else if(temp.type_of_vehicle == type_of_vehicle[1]) Trolleybus.push_back(temp);
			else Bus.push_back(temp);
		}
	}




	cout<< "-------------------- TRAMVAI --------------------"<<endl;
	Vehicle a1(tramvai_1);
	Tramvai_t tram(Tramvai);
	a1.maps_routes();
	tram.print_max_route();
	a1.print_max_most_stoppings();

	cout<< endl << "-------------------- TROLLEYBUS --------------------"<<endl;
	Vehicle a2(trolleybus_1);
	Trolleybus_t troll(Trolleybus);
	a2.maps_routes();
	troll.print_max_route();
	a2.print_max_most_stoppings();

	cout<< endl << "-------------------- BUS --------------------" <<endl;
	Vehicle a3(bus_1);
	Bus_t buss(Bus);
	a3.maps_routes();
	buss.print_max_route();
	a3.print_max_most_stoppings();

	// 3
	cout <<endl;
	Street_t a4(street_list);
	a4.Print_street_with_most_route();

	return 0;
}

