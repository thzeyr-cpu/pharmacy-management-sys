// در این پروژه ما نیاز به چهار کتابخونه زیر داریم که تعریفشون می‌کنیم.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
//مقدار حداکثر دارو یک مقدار ثابته پس میشه به عنوان const خارج از کلاس تعریفش کرد
const int Max_stock = 100;
// میتونیم نام پروژه رو به نوان یک متغیر سراسری تعریف کنیم و از globaleاستفاده میکنیم
string project = " Pharmacy Management System ";
// با استفاده از enum نوع دارو های مورد استفاده در پروژه تعریف میکنیم
enum Drugtype {tablet,syrup,capsule,injection};
//برای پیاده‌سازی وراثت و چندریختی، یک کلاس نیاز داریم که اطلاعات مشترک افراد در آن قرار گرفته باشد ،پس یک کلاس به اسم person ساختم 
class Person{
    protected :
        string firstname;
        string lastname;
    public :
        Person(string f,string l){
        firstname = f; 
        lastname = l;
  }
    void setname(string f,string l){
        firstname = f;
        lastname = l;
  }
    string getname(){
        return firstname +" "+ lastname;
  }
    virtual void show(){
    cout << "Name: " << firstname<<" "<<lastname << endl;
  }
};
class Drug{
    private :
        string name;
        Drugtype type;//   نوع دارو با استفاده از enum محدود کردیم
        int price;
        int stock;
    
    public : 
       Drug(string name,Drugtype type,int price,int stock){
           this -> name = name;
           this -> type = type;
           this -> price = price;
       if(stock <= Max_stock)//با یک شرط مقدار حداکثر دارو مجاز مشخص میکنیم
           this -> stock = stock;
       else
           this -> stock = Max_stock;
    }
    ~Drug(){}//من از وکتور استفاده کردم که خودش مدیریت حافظه داره و به صورت دستی حافظه رو مدیریت نمیکنم.این مخرب صرفا برای نشون دادن نوع نوشتن و کارکردش قرار دادم.
       Drugtype convertType(int t){
           if(t == 0)
             return tablet;
           else if(t == 1)
             return syrup;
          else if(t == 2)
             return capsule;
          else
             return injection;
    }
    void show(){
       cout << "Drug name: "<< name << endl;//دگر enum صدا بزنیم شماره جایگاه هر دارو میگه برای اینکه نوع دارو بگه از شرط if استفاده کردم
           if(type==tablet)
               cout << "Drug type:tablet" << endl;
           else if(type==syrup)  
               cout << "Drug type:syrup" << endl;
           else if(type==capsule)    
               cout << "Drug type:capsule" << endl;
           else if(type==injection)    
               cout << "Drug type:injection" << endl;
       cout << "price: "<< price << endl;
       cout << "stock :"<< stock << endl;
    }
    void savetofile(){
        ofstream file("Drug.txt",ios::app);//دلیل استفاده از ios::app اینکه با هربار اجرا این کلاس اطلاعات قبلی حفظ بشه و اطلاعات جدید به انتهای فایل اضافه بشه.app مخفف append هست
            if (!file){
            cout << "Error opening file!" << endl;
            return;
            }
            file << name << endl;
            file << type << endl;
            file << price << endl;
            file << stock << endl;
            file.close();//فایل میبنده    
    }
    void readfromfile(){
        ifstream file("Drug.txt");
            if (!file){
            cout << "Error opening file!" << endl;
            return;
            }
        int t;
            file >> name ;
            file >> t ;
            type = convertType(t);
            file >> price ;
            file >> stock ;
            file.close();
    }        
};
class Patient :public Person{//از کلاس person برای وراثت اینجا میتونیم استفاده کنیم چون بیمار یک شخص محسوب میشه    
    private :
         string nationalCode;//برای رعایت کپسوله سازی کد ملی بیمار رو خصوصی اعلام کردم
    public :
    Patient(string f,string l,string code):Person(f,l){//در اینجا من نام رو از کلاس پدر صدا زدم و خواستم نام از اونجا ارث بری کنه
         nationalCode = code;
    }//اینکه یک نکته درباره کد ملی وجود داره و اون استفاده از int و string هست .من از string استفاده کردم چون کد ملی با ۰ شروع میشه و در int صفر ابتدا نادیده گرفته میشه
    void setnationalCode(string code){
         nationalCode = code;
    }
         string getnationalCode(){//برای get از void استفاده نمیشه چون ما اینجا میخوایم یه چیزی بر گردونیم
    return nationalCode;
    }
    void show()override{
        cout << "name: " << firstname <<" " << lastname << endl;
        cout << "national code: "<< nationalCode << endl;
    }
    void savetofile(){
        ofstream file("Patient.txt", ios::app);
            if (!file){
            cout << "Error opening file!" << endl;
            return;
            }
            file << firstname << endl;
            file << lastname << endl;
            file << nationalCode << endl;
            file.close();
    }
    void readfromfile(){
        ifstream file("Patient.txt");
            if (!file){
            cout << "Error opening file!" << endl;
            return;
            }
            getline(file, firstname);
            getline(file, lastname);
            getline(file, nationalCode);
            file.close();
   }
};
class Prescription{//کلاس نسخه هم مانند کلاس بیمار نوشتم
    private:
        string PatientfirstName;
        string PatientlastName;
        string DoctorName;
        string DrugName;
        string DrugDosage;
    public:
       Prescription (string PatientfirstName,string PatientlastName,string DoctorName,string DrugName,string DrugDosage){
           this -> PatientfirstName = PatientfirstName;
           this -> PatientlastName = PatientlastName;
           this -> DoctorName = DoctorName;
           this -> DrugName = DrugName;
           this -> DrugDosage = DrugDosage;     
    }
    void show(){
        cout << "Patient firstname: "<< PatientfirstName << endl;
        cout << "Patient lastname: "<< PatientlastName << endl;
        cout << "Doctor name: "<< DoctorName << endl;
        cout << "Drug name: " << DrugName << endl;
        cout << "Drug dosage: "<< DrugDosage << endl;
    }   
    void savetofile(){
        ofstream outfile("Prescription.txt",ios::app);
            if (!outfile){
            cout << "Error opening file!" << endl;
            return;
            }
            outfile<< PatientfirstName << endl;
            outfile<< PatientlastName << endl;
            outfile<< DoctorName << endl;
            outfile<< DrugName << endl;
            outfile<< DrugDosage << endl;     
            outfile.close();
    }        
    //چون این کلاس هم خوندنی و هم نوشتنی نمیشد نام file به هر دو کلاس بدم پس اسم های متفاوتی گزاشتم
    void readfromfile(){     
        ifstream infile("Prescription.txt");
            if (!infile){
            cout << "Error opening file!" << endl;
            return;
            }
            getline(infile,PatientfirstName);
            getline(infile,PatientlastName);
            getline(infile,DoctorName);
            getline(infile,DrugName);
            getline(infile,DrugDosage);
            infile.close();
    }        
};
int main(){ 
   vector <Drug>drugs ;
   vector<Patient> patients;
   vector<Prescription> prescriptions;

   int choice;// این خط ما یک متغیر عددی داریم که کاربر با انتخاب عدد به اون بخش مدیریت نظر میر
 //منو رو با do while میسازیم دلیلش اینکه میخوام حداقل یکبار منو نمایش داده بشه
   do{
         cout << "°•○°•○°•○°•○°•○°•○°•○°•○°•○" << endl;
         cout <<" Pharmacy Management System "<< endl; 
         cout << "°•○°•○°•○°•○°•○°•○°•○°•○°•○" << endl;
         cout << "please enter your choice:" << endl;
         
         cout << "1. Add New Drug" << endl;
         cout << "2. Add New Patient" << endl;
         cout << "3. Add New prescription" << endl;
         cout << "4. Show Registered Information" << endl;
         cout << "5. Save Registered" << endl;
         cout << "6. Exit" << endl;
         cout << "°•°•°•°•°•°•°•°•°•°•°•°•°•°•°" << endl;
         cin>> choice;   
         
switch(choice){//با استفاده از swich گزینه ها رو بررسی میکنیم
     case 1:{//متغیر های مورد نیاز تعریف میکنیم
         string drugName;
         string typeName;
         Drugtype type;
         int price;
         int stock;
         cout << "Enter drug name: ";
             cin >> drugName;
         cout << "Enter drug type: ";
             cin >> typeName;
             if(typeName == "tablet")//نام دارو وارد شده رو با استفاده از شرط در enum پیدا میکنه
                 type = tablet;
             else if(typeName == "syrup")
                 type = syrup;
             else if(typeName == "capsule")
                 type = capsule;
             else if(typeName == "injection")
                 type = injection;
             else{
         cout << "Invalid drug type" << endl;//اگر نام دارو وارد شده نام enum همخوانی نداشت ارور میده
     }  
         cout << "Enter price: ";
             cin >> price;
         cout << "Enter stock: ";
             cin >> stock;
         cout <<"~°~°~°~°~°~°~°~°~°~°~°~°~"<< endl;    
         drugs.push_back(Drug(drugName,type,price,stock));//یک شیء جدید از کلاس Drug ساخته شده و با استفاده از push_back به انتهای vector داروها اضافه میشه
         drugs[drugs.size()-1].show();//آخرین شیء دارویی که داخل وکتور ذخیره شده را انتخاب میکنه و اون نمیاش میده.
     break;
     }
     
     case 2:{
         string firstname;
         string lastname;
         string nationalCode;
         cout << "Enter patient first name: ";
             cin >> firstname;
         cout << "Enter patient last name:";
             cin >> lastname;     
         cout << "Enter national code: ";
            cin >> nationalCode;
         cout <<"~°~°~°~°~°~°~°~°~°~°~°~°~"<< endl;
         patients.push_back(Patient(firstname,lastname,nationalCode));
         patients[patients.size()-1].show();
    break;
    }
    
    case 3:{
        string patientfirstName;
        string patientlastName;
        string doctorName;
        string drugName;
        string drugDosage;
        cout << "Enter patient first name: ";
            cin >> patientfirstName;
        cout << "Enter patient last name: ";
            cin >> patientlastName;    
        cout << "Enter doctor name: ";
            cin >> doctorName;
        cout << "Enter drug name: ";
            cin >> drugName;
        cout << "Enter drug dosage: ";
            cin >> drugDosage;
        cout <<"~°~°~°~°~°~°~°~°~°~°~°~°~"<< endl; 
        prescriptions.push_back(Prescription(patientfirstNamepatientlastName,doctorName, drugName, drugDosage));
        prescriptions[prescriptions.size()-1].show();
    break;
    }
    
    case 4:
           cout << "--------------------------" << endl;    
        cout << " 💉.Drugs " << endl;
           if(drugs.size() == 0)
           cout << "No drugs registered!" << endl;
           else
           for(int i = 0; i < drugs.size(); i++)
           drugs[i].show();
           cout << "--------------------------" << endl;    
        cout << "📑.Patients" << endl;
           if(patients.size() == 0)
           cout << "No patients registered!" << endl;
           else
           for(int i = 0; i < patients.size(); i++)
           patients[i].show();
           cout << "---------------------------" << endl;       
        cout << "🩻.Prescriptions " << endl;
           if(prescriptions.size() == 0)
           cout << "No prescriptions registered!" << endl;
           else
           for(int i = 0; i < prescriptions.size(); i++)
           prescriptions[i].show();
    break;
    
    case 5:
        for(int i = 0; i < drugs.size(); i++){
        drugs[i].savetofile();
    }
        for(int i = 0; i < patients.size(); i++){
        patients[i].savetofile();
    }
        for(int i = 0; i < prescriptions.size(); i++){
        prescriptions[i].savetofile();
    }
        cout << "All information saved successfully!" << endl;
        break;
        
    case 6:
        cout << "Program exited successfully!" << endl;
        break;
           
    default:
        cout << "error!invalid menu option." << endl;
        break;
 }   
    }while(choice !=6);//در این ما بررسی میکنیم تا زمانی انتخاب برابر شش نباشه منو اجرا بشه و وقتی با شش برابر بود خروج اتفاق بیوفته
       return 0;
}
