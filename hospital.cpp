#include "hospital.hh"
#include "utils.hh"
#include <iostream>
#include <algorithm>
#include <set>
#include <map>

Hospital::Hospital()
{
}

Hospital::~Hospital()
{
    // Deallocating staff
    for( std::map<std::string, Person*>::iterator
         iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        delete iter->second;
    }

    // Remember to deallocate patients also
}

void Hospital::recruit(Params params)
{
    std::string specialist_id = params.at(0);
    if( staff_.find(specialist_id) != staff_.end() )
    {
        std::cout << ALREADY_EXISTS << specialist_id << std::endl;
        return;
    }
    Person* new_specialist = new Person(specialist_id);
    staff_.insert({specialist_id, new_specialist});
    std::cout << STAFF_RECRUITED << std::endl;
}
//function which adds patient to the hospital, using vector to save the patients name. Checks if patient is already
//in the data struct.
void Hospital::enter(Params params)
{
    std::string patient_id = params.at(0);
    if( current_patients_.find(patient_id) != current_patients_.end() )
    {
        std::cout << ALREADY_EXISTS << patient_id << std::endl;
        return;
    }

    Person* new_patient = new Person(patient_id);
    current_patients_.insert({patient_id, new_patient});
    CarePeriod* new_care_period = new CarePeriod(utils::today, new_patient);
    if( Care_periods_.find(patient_id) != Care_periods_.end() )
    {
        Care_periods_.at(patient_id).push_back(new_care_period);
        std::cout << PATIENT_ENTERED << std::endl;
        return;
    }
    else
    {
        std::vector<CarePeriod*> patients_careperiods;
        patients_careperiods.push_back(new_care_period);
        Care_periods_.insert({patient_id, patients_careperiods});
        Care_periods_all.push_back({patient_id, patients_careperiods});
        std::cout << PATIENT_ENTERED << std::endl;
    }



}
// checks if patient is in the hospital and prints error if it is. uses name as a key and erases
//it from map
void Hospital::leave(Params params)
{
    std::string patient_id = params.at(0);
    if( current_patients_.find(patient_id) != current_patients_.end() )
    {

        Care_periods_.at(patient_id).at(Care_periods_.at(patient_id).size() - 1)->end_period(utils::today);

        current_patients_.at(patient_id) = nullptr;
        current_patients_.erase(patient_id);

        std::cout << PATIENT_LEFT << std::endl;

    }
    else{
        std::cout << CANT_FIND << patient_id << std::endl;
    }

}
//function which checks if patient is in the map and adds it to given vector.
//return false if vector is empty and true if not
bool Hospital::is_patient_here(std::string patient_id)
{

    std::vector<std::string> tutkija;
    for(unsigned int i = 0; i < Care_periods_.size(); i++){
        if(Care_periods_.find(patient_id) != Care_periods_.end()){
            tutkija.push_back(patient_id);
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
void Hospital::assign_staff(Params params)
{
    
    std::string staff_id = params.at(0);
    std::string patient_id = params.at(1);

    if(staff_.find(staff_id) != staff_.end() and is_patient_here(patient_id) == false){
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }
    if(staff_.find(staff_id) != staff_.end() and is_patient_here(patient_id) == true){
        std::vector<std::string> patients_staff_for_careperiod = Care_periods_.at(patient_id).at(Care_periods_.at(patient_id).size()-1)->get_staff();
        for(unsigned int i = 0; i < patients_staff_for_careperiod.size();i++){
            if(patients_staff_for_careperiod.at(i) == staff_id){
                std::cout << STAFF_ASSIGNED << patient_id << std::endl;
                return;
            }
        }

        Care_periods_.at(patient_id).at(Care_periods_.at(patient_id).size() - 1)->assing_staff_for_careperiod(staff_id);
        std::cout << STAFF_ASSIGNED << patient_id << std::endl;
    }
    else{
        std::cout << CANT_FIND << staff_id << std::endl;
    }


}

void Hospital::add_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string strength = params.at(1);
    std::string dosage = params.at(2);
    std::string patient = params.at(3);
    if( not utils::is_numeric(strength, true) or
        not utils::is_numeric(dosage, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    std::map<std::string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->add_medicine(medicine, stoi(strength), stoi(dosage));
    all_medicines_.push_back(medicine);
    std::cout << MEDICINE_ADDED << patient << std::endl;
}

void Hospital::remove_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string patient = params.at(1);
    std::map<std::string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->remove_medicine(medicine);
    std::cout << MEDICINE_REMOVED << patient << std::endl;
}

void Hospital::print_patient_info(Params params)
{
    std::string id = params.at(0);

    if( Care_periods_.find(id) != Care_periods_.end() )
    {
        for(unsigned int i = 0 ; i < Care_periods_.at(id).size(); ++i)
        {
            std::cout << CARE_PERIODS; Care_periods_.at(id).at(i)->get_start().print();
            std::cout << " - ";
            if(Care_periods_.at(id).at(i)->get_end().is_default())
            {
                std::cout << std::endl;
                std::cout << "   - Staff: ";
            }
            else
            {
                Care_periods_.at(id).at(i)->get_end().print(); std::cout << std::endl;
                std::cout << "   - Staff: ";
            }

            if(Care_periods_.at(id).at(i)->get_staff().size() == 0)
            {
                std::cout << "None" << std::endl;
            }
            else
            {
                for(unsigned int j = 0 ; j < Care_periods_.at(id).at(i)->get_staff().size(); ++j)
                {
                    std::cout << Care_periods_.at(id).at(i)->get_staff().at(j) << " ";
                }
            }



        }

        std::cout << "* Medicines: ";
        if(Care_periods_.at(id).at(0)->patient_out()->get_medicines().size() == 0)
        {
            std::cout << "None" << std::endl;
        }

        else
        {

            for(unsigned int i = 0 ; i < Care_periods_.at(id).at(0)->patient_out()->get_medicines().size() ; ++i)
            {


                std::cout << "  - " << Care_periods_.at(id).at(0)->patient_out()->get_medicines().at(i)
                << " " << Care_periods_.at(id).at(0)->patient_out()->get_prescription_strenght().at(i) << " mg x "
                << Care_periods_.at(id).at(0)->patient_out()->get_prescription_dosage().at(i) << std::endl;

            }
        }

    }
    else
    {
        std::cout << CANT_FIND << id << std::endl;
    }

}


void Hospital::print_care_periods_per_staff(Params params)
{
    std::string staff_id = params.at(0);
    std::vector<std::string> check;
    if( staff_.find(staff_id) != staff_.end() )
    {
        for ( auto pair : Care_periods_all)
        {
            for(auto pair1 : pair.second)
            {
                std::vector<std::string> staff_for_patient = pair1->get_staff();

                for(unsigned int j = 0; j < staff_for_patient.size(); ++j)
                {
                    if(staff_for_patient.at(j) == staff_id)
                    {
                        check.push_back(pair.first);
                        pair1->get_start().print();
                        std::cout << " - ";
                        if(pair1->get_end().is_default())
                        {
                            std::cout << std::endl;
                        }
                        else
                        {
                            pair1->get_end().print(); std::cout << std::endl;
                        }
                        std::cout << "* Patient: " << pair.first << std::endl;
                    }
                }
            }
        }
        if(check.size() == 0)
        {
            std::cout << "None" << std::endl;
        }
    }
    else
    {
        std::cout << CANT_FIND << staff_id << std::endl;
    }
}

bool compareFunction (std::string a, std::string b) {
    return a<b;
} 

//prints all the medicines by going through the map with two for loops. If container is
//empty prints none.

void Hospital::print_all_medicines(Params)
{
    
    if(all_medicines_.size() == 0)
    {
        std::cout << "None" << std::endl;
        return;
    }
    for(unsigned int i = 0; i < all_medicines_.size(); ++i)
    {

            std::cout << all_medicines_.at(i) << " prescribed for" << std::endl;

            for(auto pair : Care_periods_)
            {
               for(auto pair2 : pair.second)
               {
                   std::vector<std::string> patients_medicine = pair2->patient_out()->get_medicines();
                   for(unsigned int j = 0; j < patients_medicine.size(); ++j)
                   {
                       if(patients_medicine.at(j) == all_medicines_.at(i))
                        {
                            std::cout << "* " << pair.first << std::endl;
                            break;
                        }
                   }
               }
            }
        }

}




void Hospital::print_all_staff(Params)
{
    if( staff_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }
    for( std::map<std::string, Person*>::const_iterator iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        std::cout << iter->first << std::endl;
    }
}

void Hospital::print_all_patients(Params)
{

    if( current_patients_.size() == 0){
        std::cout << "None" << std::endl;
        return;
    }
    for(unsigned int i = 0; i < current_patients_.size(); ++i)
    {

            std::cout << all_medicines_.at(i) << std::endl;

            for(auto pair : Care_periods_)
            {
               for(auto pair2 : pair.second)
               {
                   std::vector<std::string> patients_medicine = pair2->patient_out()->get_medicines();
                   for(unsigned int j = 0; j < patients_medicine.size(); ++j)
                   {
                       if(patients_medicine.at(j) == all_medicines_.at(i))
                        {
                            std::cout << "* " << pair.first << std::endl;
                            break;
                        }
                   }
               }
            }
        }



}

void Hospital::print_current_patients(Params)

{
    if( current_patients_.size() == 0){
        std::cout << "None" << std::endl;
        return;
    }    

    std::string patient;
    if( Care_periods_.find(patient) != Care_periods_.end() )
    {
        std::cout << patient << std::endl;
        for(unsigned int i = 0 ; i < Care_periods_.at(patient).size(); ++i)
        {
            std::cout << CARE_PERIODS; Care_periods_.at(patient).at(i)->get_start().print();
            std::cout << " - ";
            if(Care_periods_.at(patient).at(i)->get_end().is_default())
            {
                std::cout << std::endl;
                std::cout << "   - Staff: ";
            }
            else
            {
                Care_periods_.at(patient).at(i)->get_end().print(); std::cout << std::endl;
                std::cout << "   - Staff: ";
            }

            if(Care_periods_.at(patient).at(i)->get_staff().size() == 0)
            {
                std::cout << "None" << std::endl;
            }
            else
            {
                for(unsigned int j = 0 ; j < Care_periods_.at(patient).at(i)->get_staff().size(); ++j)
                {
                    std::cout << Care_periods_.at(patient).at(i)->get_staff().at(j) << " ";
                }
            }
            std::cout << std::endl;


        }

        std::cout << "* Medicines: ";
        if(Care_periods_.at(patient).at(0)->patient_out()->get_medicines().size() == 0)
        {
            std::cout << "None" << std::endl;
        }

        else
        {


            for(unsigned int i = 0 ; i < Care_periods_.at(patient).at(0)->patient_out()->get_medicines().size() ; ++i)
            {


                std::cout << "  - " << Care_periods_.at(patient).at(0)->patient_out()->get_medicines().at(i)
                << " " << Care_periods_.at(patient).at(0)->patient_out()->get_prescription_strenght().at(i) << " mg x "
                << Care_periods_.at(patient).at(0)->patient_out()->get_prescription_dosage().at(i) << std::endl;

            }



        }

    }


}


void Hospital::set_date(Params params)
{
    std::string day = params.at(0);
    std::string month = params.at(1);
    std::string year = params.at(2);
    if( not utils::is_numeric(day, false) or
        not utils::is_numeric(month, false) or
        not utils::is_numeric(year, false) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.set(stoi(day), stoi(month), stoi(year));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void Hospital::advance_date(Params params)
{
    std::string amount = params.at(0);
    if( not utils::is_numeric(amount, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.advance(stoi(amount));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}
