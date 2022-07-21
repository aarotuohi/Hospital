/* Class CarePeriod
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for describing a patient's care period in hospital.
 *
 * Note: Students need to implement almost all of this class by themselves.
 * */
#ifndef CAREPERIOD_HH
#define CAREPERIOD_HH

#include "person.hh"
#include "date.hh"
#include <string>

class CarePeriod
{
public:
    // Constructor, start date given as a string (ddmmyyyy).
    CarePeriod(const std::string& start, Person* patient);

    // Constructor, start date given as a Date object.
    CarePeriod(const Date& start, Person* patient);

    // Destructor.
    ~CarePeriod();

    void end_period(Date &Today);

    Date get_start();

    Date get_end();

    Person* patient_out();

    std::vector<std::string> get_staff();

    bool staff_member_found(std::string staff_id);

    std::vector<std::string> get_patient();

    bool is_patient_here(std::string patient_id);



    void assing_staff_for_careperiod(std::string staff_id);

    // More public methods

private:
    Person* patient_;

    Date start_;
    Date end_;

    std::vector<std::string> patients_staff_for_careperiod_;

    std::vector<std::string> assign_staff_for_careperiod;

    // More attributes and methods
};

#endif // CAREPERIOD_HH
