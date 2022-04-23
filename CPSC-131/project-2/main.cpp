#include <cstdlib>  // size_t
#include <iostream>
#include <string>

#include "Repair.hpp"
#include "RepairList.hpp"

using std::cout;
using std::endl;
using std::string;

// Helper Class
struct AssertEquals {
    static size_t tests;
    static size_t passed;

    template <typename T, typename U>
    void operator() (string test_name, const T& expected, const U& actual) {
        ++tests;

        if (actual == expected) {
            cout << "\033[32m" << "[PASSED] " << "\033[0m" << test_name << endl;
            ++passed;
        }
        else {
            cout << "\033[31m" << "[FAILED] " << "\033[0m" << test_name
                << " - Expected: " << expected
                << ", Actual: " << actual
                << endl;
        }
    }
};
size_t AssertEquals::tests = 0;
size_t AssertEquals::passed = 0;

int main() {
    AssertEquals assertEquals;
    RepairList   monday;
    
    monday.loadAdvanceList("monday.csv");
    //passed
    assertEquals("RepairList.name()", "Amy Carpenter", monday.currRepair().name());
    //passed
    assertEquals("RepairList.services()", "brake pads", monday.currRepair().services());
    //passed
    assertEquals("RepairList.cost()", 328.71, monday.currRepair().cost());


    monday.next();
    //passed
    assertEquals("next. RepairList.vehicle()", "Buick", monday.currRepair().vehicle());
    //passed
    assertEquals("RepairList.cost()", 667.18, monday.currRepair().cost());


    monday.next();
    //passed
    assertEquals("RepairList.date()", "9/28 11:00 am", monday.currRepair().date());
    //passed
    assertEquals("RepairList.services()", "flush radiator", monday.currRepair().services());
    //passed
    assertEquals("RepairList.cost()", 101.70, monday.currRepair().cost());


    monday.insertLoyal(Repair("Ana Caravelle", "Toyota Prius", "9/30 8:00 am", "high beams", 57.11));
    //passed
    assertEquals("insertLoyal.RepairList.cost()", 101.70, monday.currRepair().cost());

    monday.next();
    assertEquals("next.RepairList.cost()", 57.11, monday.currRepair().cost());

    monday.insertLoyal(Repair("Lazy Tumbleweed", "Chevy Spark", "9/30 10:00 am", "fuel pump", 192.00));
    assertEquals("insertLoyal.RepairList.cost()", 57.11, monday.currRepair().cost());

    monday.addToList(Repair("DJ Shadow", "Ford Focus", "9/30 11:00 am", "replace battery", 99.11));
    assertEquals("addToList.RepairList.cost()", 57.11, monday.currRepair().cost());

    monday.next();
    assertEquals("next.RepairList.name())", "Lazy Tumbleweed", monday.currRepair().name());

    monday.next();
    assertEquals("next.RepairList.vehicle()", "VW Bettle", monday.currRepair().vehicle());

    monday.next();
    assertEquals("next.RepairList.name()", "DJ Shadow", monday.currRepair().name());


    monday.addToList(Repair("Oscar La Fontaine", "Kia", "9/30 5:05 pm", "high beam", 19.99));

    monday.next();

    assertEquals("next.RepairList.vehicle()", "Kia", monday.currRepair().vehicle());

    monday.prev();
    assertEquals("prev.RepairList.services()", "replace battery", monday.currRepair().services());


    assertEquals("size.RepairList.services()", 8, monday.size());
    // Calculate Total Tests passed
    cout << endl << "Total tests passed : " << assertEquals.passed << " out of " << assertEquals.tests << endl;

    return 0;
}
