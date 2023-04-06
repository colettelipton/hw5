#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool schedhelp(size_t day, size_t shift, map<Worker_T, int> numshifts, AvailabilityMatrix& avail, const size_t dailyNeed, DailySchedule& sched);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    /*
    wanna start worker 0 day 0. if the worker is available, plug the worker in and move on.
    then go to worker 1 day 0. if the worker is available, and max shifts aren't reached, plug them in.
    whatever d is, you need to have exactly d workers per day. as soon as you hit d workers,
    in a day, move on to the next day. hit a point where if you assign a worker at some point,
    they might not be available later when you actually need them. At this point, if there's no 
    one available anymore, recursively call and set back to 0
    you would do sched[i][j] = INVALID_ID, then recursively call. sched[i][j] i is the day
    and j is the column which is the shift. also keep track of how do you know if
    worker 0 is already out of shifts? keep track in a separate data structure.
    right after you assign a certain worker to a time slot, decrement that worker's number
    of available shifts: a map of workers to avaiable days

    at very start initialize schedule into an n x n array, is easier to work with
    */

    int k = avail.at(0).size(); // num workers

    // maps each worker to how many shifts they have
    map<Worker_T, int> numshifts;
    for(int i = 0; i < k; i++){
        numshifts.insert(make_pair(i, maxShifts));
    }

    // initializes sched
    for(unsigned i = 0; i < avail.size(); i++){
        vector<Worker_T> vec;
        for(unsigned j = 0; j < dailyNeed; j++){
            vec.push_back(INVALID_ID);
        }
        sched.push_back(vec);
    }
    AvailabilityMatrix available = avail;

    return schedhelp(0, 0, numshifts, available, dailyNeed, sched);

}

bool schedhelp(size_t day, size_t shift, map<Worker_T, int> numshifts, AvailabilityMatrix& avail, const size_t dailyNeed, DailySchedule& sched){
    if(day >= avail.size()){
        return true;
    }

    bool x = false;

    // loops through all the workers
    for(int i = 0; i < (int)avail.at(0).size(); i++){
        if(avail[day][i] == 1 && numshifts[i] > 0 && sched[day][shift] == INVALID_ID){
            sched[day][shift] = i;
            (numshifts[i])--;
            avail[day][i] = 0;

            // resets shift if a new day
            if(shift + 1 == dailyNeed){
                x = schedhelp(day + 1, 0, numshifts, avail, dailyNeed, sched);
            }
            else{
                x = schedhelp(day, shift + 1, numshifts, avail, dailyNeed, sched);
            }
            
            if(x){
                return true;
            }
            else{
                // goes back if can't find a worker
                (numshifts[i])++;
                avail[day][i] = 1;
                sched[day][shift] = INVALID_ID;
                continue;
            }
        }
    }
    return false;
}

