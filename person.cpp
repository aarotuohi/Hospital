#include "person.hh"
#include <iostream>
#include <map>

Person::Person()
{
}

Person::Person(const std::string &id):
    id_(id)
{
    date_of_birth_ = Date();
}

Person::Person(const std::string& id, const std::string& date_of_birth):
    id_(id), date_of_birth_(date_of_birth)
{
}

Person::~Person()
{
    // Remove the print below before submitting the program in Plussa
    std::cout << "Person " << id_ << " destructed." << std::endl;
}

std::string Person::get_id() const
{
    return id_;
}

std::vector<std::string> Person::get_medicines() const
{
    std::vector<std::string> result;
    for( std::map<std::string, Prescription>::const_iterator
         iter = medicines_.begin();
         iter != medicines_.end();
         ++iter )
    {
        result.push_back(iter->first);
    }
    return result;
}
std::vector<unsigned int> Person::get_prescription_strenght()
{
    std::vector<unsigned int> result1;
    for( std::map<std::string, Prescription>::const_iterator
         iter = medicines_.begin();
         iter != medicines_.end();
         ++iter )
    {
        result1.push_back(iter->second.strength_);
    }
    return result1;

}
std::vector<unsigned int> Person::get_prescription_dosage()
{
    std::vector<unsigned int> result2;
    for( std::map<std::string, Prescription>::const_iterator
         iter = medicines_.begin();
         iter != medicines_.end();
         ++iter )
    {
        result2.push_back(iter->second.dosage_);
    }
    return result2;

}

void Person::prescription_name(std::string name)
{
    if(medicines_.find(name) != medicines_.end()){
        all_medicines_.push_back(name);
    }
}
void Person::prescription_strength(unsigned int strength){

    all_medicines_strength.push_back(strength);



}
void Person::prescription_dosage(unsigned int dosage){

    all_medicines_dosage.push_back(dosage);


}

void Person::add_medicine(const std::string& name,
                          unsigned int strength,
                          unsigned int dosage)
{
    Prescription pre;
    pre.strength_ = strength;
    pre.dosage_ = dosage;
    if( medicines_.find(name) != medicines_.end() )
    {
        medicines_.at(name) = pre;
    }
    else
    {
        medicines_.insert({name, pre});
    }
}

void Person::remove_medicine(const std::string& name)
{
    medicines_.erase(name);
}

void Person::print_id() const
{
    std::cout << id_;
    //date_of_birth_.print();
    //std::cout << std::endl;
}

void Person::print_medicines(const std::string& pre_text) const
{
    if( medicines_.empty() )
    {
        std::cout << " None" << std::endl;
        return;
    }
    std::cout << std::endl;
    for( std::map<std::string, Prescription>::const_iterator
         iter = medicines_.begin();
         iter != medicines_.end();
         ++iter )
    {
        std::cout << pre_text
                  << iter->first << " "
                  << iter->second.strength_ << " mg x "
                  << iter->second.dosage_ << std::endl;
    }
}
bool Person::does_any_patient_have_this_medicine(std::string staff_id)
{
    std::vector<std::string> tutkija;
    for(unsigned int i = 0; i < all_medicines_.size(); ++i)
    {
        if(staff_id == all_medicines_.at(i))
        {
            tutkija.push_back(staff_id);
        }
    }
    if(tutkija.size() == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}
bool Person::operator<(const Person &rhs) const
{
    return id_ < rhs.id_;
}



