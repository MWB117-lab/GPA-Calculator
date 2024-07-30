#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


class student{
private:
    std::vector<float> semesters;
    float gpa;
public:
    student();
    void addSemester(float gpa, ofstream& ofile);
    float calcGPA(std::vector<float> points, float size);
    float totalGPA(float size);
};

int main(){

    student miguel;
    bool deleteFile = 0;
    cout << "Is this a new student (do you want to delete old file) (1 or 0)";
    cin >> deleteFile;
    cout << endl;
    int oldSemesters = 0;
    ofstream ofile;
    
    ifstream ifile;
    std::vector<float> oldSemesterGPAs;
    if(deleteFile){
        remove("semesters");
        cout << "File successfully deleted" << endl << endl;
    }else{
        if(!deleteFile){
            cout << "Using the following semester GPAs: " << endl;
            ifile.open("semesters");
            float gpa;
            while(ifile>>gpa){
                oldSemesters++;
                oldSemesterGPAs.push_back(gpa);
                cout << gpa << endl;
            }
            ifile.close();
        }
    }

    ofile.open("semesters");

    int total;
    if(deleteFile){
        cout << "How many semesters? "<< endl;
    }else{
        cout << "You have " << oldSemesters << " old semesters" << endl;
        cout << "How many new semesters? "<< endl;
        for(int i = 0; i < oldSemesters; i++){
            miguel.addSemester(oldSemesterGPAs[i],ofile);
        }
    }
    
    cin >> total;
    cout << endl;
    std::vector<float> list;

    for(int i = 0; i < total; i++){
        int classes;
        if(deleteFile){
            cout << "How many classes in semester " << i+1 << " ";
            cin >> classes;
        }else{
            cout << "How many classes in semester " << i+oldSemesters+1 << " ";
            cin >> classes;
        }


        for (int i = 0; i < classes; i++){
            float points;
            cout << "Enter points for class " << i+1 << endl;
            cin >> points;
            
            list.push_back(points);
        }
        cout << "This semester's GPA: " << miguel.calcGPA(list,classes) << endl;
        miguel.addSemester(miguel.calcGPA(list,classes),ofile);
        list.clear();
    }
    
    cout << endl << "Your gpa is " << miguel.totalGPA(total+oldSemesters);
    
    ofile.close();
    return 0;
}
student::student(){
    gpa = 0;
}
float student::calcGPA(std::vector<float> points, float size){
    float gpa = 0;
    //cout << "size: " << size << endl;
    for(int i = 0; i < size; i++){
        gpa += points[i];
        //cout << points[i]/size<< endl;
    }
    gpa /= size;
    return gpa;
}
void student::addSemester(float gpa, ofstream& ofile){
    this->semesters.push_back(gpa);

    ofile << gpa <<endl;

}
float student::totalGPA(float size){
    float gpa = 0;
    for (int i = 0; i < size; i++){
        //cout << semesters[i]/size << endl;
        gpa += semesters[i];
    }
    gpa /= size;
    return gpa;
}

/*
no duped msjc
4
4
4.33333
4.5
4.875
4.88889
*/

/*
duped msjc
4
4
4.5
4.5
4.88889
4.9
*/