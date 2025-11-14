#include <iostream>
#include <vector>
#include <limits>
#include <chrono>
#include <sstream>
#include <fstream>

using namespace std;
using namespace std::chrono;

class Project{
    public:
        string name;
        string status;
        string description;
        year_month_day date;
        Project(string a, string b, string c, year_month_day d): name(a), status(b), description(c), date(d) {}
};

vector<Project> projectsList;
int* selectedProjectIndex = nullptr;
bool tryParseInt(const string& input, int& output) {
    stringstream ss(input);
    ss >> output;
    return !ss.fail() && ss.eof();
}

string add(){
    string data;
    bool correct=true;
    string name;
    int s;
    string status;
    string description;
    year_month_day date = year_month_day{floor<days>(system_clock::now())};
    cout<<"enter new project name:"<<endl;
    getline(cin,name);
    data+=name+";";
    bool tof=true;
    while (tof)
    {
        cout<<"what is new project status?"<<endl;
        cout<<"not started : 1"<<endl
        <<"in process : 2"<<endl
        <<"ended : 3"<<endl;
        cin>>s;
        switch (s)
        {
        case 1:
            tof=false;
            status="not started";
            break;
        case 2:
            tof=false;
            status="in process";
            break;
        case 3:
            tof=false;
            status="ended";
            break;
        default:
            cout<<"error: incorrect input, enter 1, 2 or 3";
        }
        data+=status+";";
    }
    cout<<"enter new project description:"<<endl;
    cin.ignore();
    getline(cin, description);
    data+=description+";";
    string res;
    while (true)
    {
        cout<<"do you want save this data? yes/no"<<endl;
        cin>>res;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if(res=="yes" || res=="YES"){
            cout<<"save..."<<endl;
            projectsList.push_back(Project(name, status, description, date));
            cout<<"data saved, new project was created"<<endl;
            std::ofstream file("data/objects.txt", std::ios::app);
            if (file.is_open()) {
                file << data<<"\n";
                file.close();
            } else {
                std::cout << "data filie not found!" << std::endl;
                correct=false;
            }
            break;
        }
        else if (res=="no"||res=="NO")
        {
            cout<<"data not saved, new project wasn't created"<<endl;
            correct=false;
            break;
        }
        else{
            cout<<"error: incorrect input, enter yes or no"<<endl;
        }
        
    }
    if(correct){
        return "successfull";
    }
    return "unsuccessfull";
    
}

void show(){
    cout<<"enter project name or id to see thier info"<<endl<<"enter 'all' to see all projects"<<endl;
    string r;
    int x; 
    while (true)
    {
        string r;
        getline(cin,r);
        if(r=="all"){
            cout<<"id    name    status    date added"<<endl;
            for(int i=0; i<size(projectsList); i++){
                cout<<i<<"    "+projectsList[i].name+"    "+projectsList[i].status+"    "<<int(projectsList[i].date.year())<<"-"<<unsigned(projectsList[i].date.month())<<"-"<<unsigned(projectsList[i].date.day())<<endl;
            }
            break;
        }else{
            if(tryParseInt(r, x)){
                if(x>=0 && x<size(projectsList)){
                    cout<<"Project info:"<<endl
                    <<"Name: "+projectsList[x].name<<endl
                    <<"Status: "+projectsList[x].status<<endl
                    <<"Description: "+projectsList[x].description<<endl
                    <<"Date added: "<<int(projectsList[x].date.year())<<"-"<<unsigned(projectsList[x].date.month())<<"-"<<unsigned(projectsList[x].date.day())<<endl;
                    break;
                }else{
                    cout<<"error: project with id "+r+" not exist, enter correct id or project name"<<endl;
                }
            }else{
                bool found=false;
                for(int i=0; i<size(projectsList); i++){
                    if(projectsList[i].name==r){
                        cout<<"Project info:"<<endl
                        <<"Name: "+projectsList[i].name<<endl
                        <<"Status: "+projectsList[i].status<<endl
                        <<"Description: "+projectsList[i].description<<endl
                        <<"Date added: "<<int(projectsList[i].date.year())<<"-"<<unsigned(projectsList[i].date.month())<<"-"<<unsigned(projectsList[i].date.day())<<endl;
                        found=true;
                        break;
                    }
                }
                if(found){
                    break;
                }else{
                    cout<<"error: project with name "+r+" not exist, enter correct name or project id"<<endl;
                }
            }
        }
    }
}

void select(){
    cout<<"enter project name or id to select it"<<endl;
    string r;
    int x; 
    while (true)
    {
        string r;
        getline(cin,r);
        if(tryParseInt(r, x)){
            if(x>=0 && x<size(projectsList)){
                selectedProjectIndex = new int(x);
                cout<<"Project info:"<<endl
                    <<"Name: "+projectsList[x].name<<endl
                    <<"Status: "+projectsList[x].status<<endl
                    <<"Description: "+projectsList[x].description<<endl
                    <<"Date added: "<<int(projectsList[x].date.year())<<"-"<<unsigned(projectsList[x].date.month())<<"-"<<unsigned(projectsList[x].date.day())<<endl;
                break;
            }else{
                cout<<"error: project with id "+r+" not exist, enter correct id or project name"<<endl;
            }
        }else{
            bool found=false;
            for(int i=0; i<size(projectsList); i++){
                if(projectsList[i].name==r){
                    selectedProjectIndex = new int(i);
                    cout<<"Name: "+projectsList[i].name<<endl
                    <<"Status: "+projectsList[i].status<<endl
                    <<"Description: "+projectsList[i].description<<endl
                    <<"Date added: "<<int(projectsList[i].date.year())<<"-"<<unsigned(projectsList[i].date.month())<<"-"<<unsigned(projectsList[i].date.day())<<endl;
                    found=true;
                    break;
                }
            }
            if(found){
                break;
            }else{
                cout<<"error: project with name "+r+" not exist, enter correct name or project id"<<endl;
            }
        }
    }
}   

string comands(string comand){
    if (comand=="help"){
        cout<<"comands manual:"<<endl
        <<"    add : add project"<<endl
        <<"    change : change data of selected project"<<endl
        <<"    delete : delete selected project"<<endl
        <<"    exit : exit form selected project"<<endl
        <<"    help : shows comands and descriptions"<<endl
        <<"    info : shows info of selected project"<<endl
        <<"    run : run selected project"<<endl
        <<"    select: select project by project name or project id"<<endl
        <<"    show : show all projects and thier info or show info about project by project name and project id"<<endl;
        return "";
    }
    else if (comand=="add")
    {
        return add();
    }
    else if (comand=="select")
    {
        select();
        return "successfull";
    }
    else if (comand=="show")
    {
        show();
        return "successfull";
    }
    else{
        return "error: "+comand+" not exist!";
    }
    
}

int main() {
    cout << "Welcome in Projects Menager!"<<endl<<"Type 'help' for comands manual"<<endl;
    string comand;
    string selected;
    while (true)
    {
        if(selectedProjectIndex!=nullptr){
            selected=projectsList[*selectedProjectIndex].name;
        }else{
            selected="";
        }
        cout<<"/"<<selected<<"> ";
        getline(cin, comand);
        if(comand!=""){
            cout<<comands(comand)<<endl;
        }
    }
    
    return 0;
}