#include "careperiod.hh"
#include <iostream>
#include "utils.hh"


CarePeriod::CarePeriod(const std::string& start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::CarePeriod(const Date &start, Person* patient):
    patient_(patient), start_(start)
{
}

void CarePeriod::end_period(Date &Today)
{

    end_ = Today;
}

Date CarePeriod::get_start()
{
    Date start = start_;
    return start;
}

Date CarePeriod::get_end()
{
    Date end = end_;
    return end;
}

Person* CarePeriod::patient_out()
{
    Person* patient = patient_;
    return patient;
}
std::vector<std::string> CarePeriod::get_staff()
{
    std::vector<std::string> patients_staff_for_careperiod = patients_staff_for_careperiod_;
    return patients_staff_for_careperiod;
}

bool CarePeriod::staff_member_found(std::string staff_id)
{
    std::vector<std::string> tutkija;
    for(unsigned int i = 0; i < patients_staff_for_careperiod_.size(); ++i)
    {
        if(staff_id == patients_staff_for_careperiod_.at(i))
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

std::vector<std::string> CarePeriod::get_patient()
{
    std::vector<std::string> assign_staff_for_careperiod_ = assign_staff_for_careperiod;
    return assign_staff_for_careperiod_;
}


bool CarePeriod::is_patient_here(std::string patient_id)
{
    std::vector<std::string> löytäjä;
    for(unsigned int i = 0; i < assign_staff_for_careperiod.size(); i++){
        if(patient_id == assign_staff_for_careperiod.at(i))
        {
            löytäjä.push_back(patient_id);
        }
    }
    if(löytäjä.size() == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}


void CarePeriod::assing_staff_for_careperiod(std::string staff_id)
{
    patients_staff_for_careperiod_.push_back(staff_id);
}

CarePeriod::~CarePeriod()
{
}
